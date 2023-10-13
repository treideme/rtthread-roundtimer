/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-10     Sherman       first version
 * 2023-10-01     Sherman       add mp3 decoder
 */

#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mp3/mp3dec.h"
#include "mp3/mp3common.h"

#define LED_PIN    BSP_IO_PORT_02_PIN_09 /* Onboard LED pins */

static int16_t audiodata[576*2*2];
static int8_t rbuf[152]; // 144 samples + 6 bytes header + 2 bytes for 8 byte alignment

int skip_id3v2(int fd, off_t file_size) {
  off_t position = lseek(fd, 0, SEEK_CUR);
  if ((file_size - position) < 10) {
    return -1;
  }
  uint8_t data[10];
  file_size = read(fd, data, 10);
  if(file_size != 10) {
    lseek(fd, position, SEEK_SET);
    return -2;
  }
  if (!(
      data[0] == 'I' &&
      data[1] == 'D' &&
      data[2] == '3' &&
      data[3] != 0xff &&
      data[4] != 0xff &&
      (data[5] & 0x1f) == 0 &&
      (data[6] & 0x80) == 0 &&
      (data[7] & 0x80) == 0 &&
      (data[8] & 0x80) == 0 &&
      (data[9] & 0x80) == 0)) {
    return -3;
  }
  uint32_t size = (data[6] << 21) | (data[7] << 14) | (data[8] << 7) | (data[9]);
  lseek(fd, size, SEEK_CUR);
  return 0;
}

int mp3file_find_sync_word(int fd, uint8_t *buf) {
  int state = 0;
  while (read(fd, &buf[state], 1) == 1) {
    switch (state) {
      case 0:
        if (buf[state] == SYNCWORDH) {
          state = 1;
        }
        break;
      case 1:
        if ((buf[state] & SYNCWORDL) == SYNCWORDL) {
          return 0;
        } else if (buf[state] == SYNCWORDH) {
          buf[0] = SYNCWORDH;
          state = 1;
        } else {
          state = 0;
        }
        break;
    }
  }
  return -1;
}

int queue_buffer(MP3FrameInfo *fi, int16_t *buf) {
  // Mix down to mono
  size_t num_samples = fi->outputSamps/fi->nChans;
  if(fi->nChans > 1) {
    for(int i = 0; i < num_samples; i++) {
      int val = (buf[i*2] + buf[i*2+1]) / 2;
      buf[i] = (int16_t)val;
    }
  }
  // Copy to output buffer
  rt_kprintf("queue_buffer: %u %i\n", num_samples, fi->samprate);

  return 0;
}

int play(const char*filename) {
  ssize_t ret;

  HMP3Decoder decoder = MP3InitDecoder();

  struct stat sbuf;
  ret = stat(filename, &sbuf);
  if(ret) {
    return (int)ret;
  }

  int fd = open(filename, O_RDONLY);
  if(fd < 0) {
    return fd;
  }

  ret = skip_id3v2(fd, sbuf.st_size);
  if(ret) {
    rt_kprintf("No ID3v2 tag found, code: %i\n", ret);
  }
  uint8_t *buf = &rbuf;
  int frame = 0;
  while(mp3file_find_sync_word(fd, buf) == 0) {
    rt_kprintf("Frame: %i\n", frame++);
    off_t pos = lseek(fd, 0, SEEK_CUR);
    // Remaining chunk
    ssize_t rsize = 148;
    if(sbuf.st_size - pos < rsize) {
      rsize = sbuf.st_size - pos;
    }
    ret = read(fd, &buf[2], rsize);
    if(ret != rsize) {
      rt_kprintf("Underread %i %i\n", rsize, ret);
      close(fd);
      return -1;
    }
    rt_kprintf("DRIN1");

    // decode suspected frame
    int bytes_read = rsize + 2;
    unsigned char **inbuf = (unsigned char **)&buf;
    ret = MP3Decode(decoder, inbuf, &bytes_read, audiodata, 0);
    if(ret < 0) {
      rt_kprintf("MP3Decode: %i %i\n", ret, bytes_read);
      close(fd);
      return -1;
    }
    rt_kprintf("DRIN2");
    lseek(fd, -bytes_read, SEEK_CUR);

    MP3FrameInfo fi;
    MP3GetLastFrameInfo(decoder, &fi);
    if(fi.layer != 3) {
      rt_kprintf("Frame info layer: %i\n", fi.layer);
      close(fd);
      return -1;
    }
    queue_buffer(&fi, audiodata);
  }

  close(fd);
  MP3FreeDecoder(decoder);
  return 0;
}


void hal_entry(void) {
  /* Check filesystem */
  rt_thread_mdelay(1000);
  if (rt_device_find("sd0") == RT_NULL) {
    rt_kprintf("Please insert an SD card\n");
  }

  /* Open mp3 file for reading if it exists */
  int ret;
  ret = play("song.mp3");
  if (ret == 0) {
    rt_kprintf("Playing song.mp3\n");
  } else {
    rt_kprintf("Error playing song.mp3: %i\n", ret);
  }

  while (1) {
    rt_pin_write(LED_PIN, PIN_HIGH);
    rt_thread_mdelay(500);
    rt_pin_write(LED_PIN, PIN_LOW);
    rt_thread_mdelay(500);
  }
}
