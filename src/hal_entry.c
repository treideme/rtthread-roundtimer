/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-10     Sherman       first version
 */

#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "mp3/mp3dec.h"
#include "mp3/mp3common.h"

#define LED_PIN    BSP_IO_PORT_02_PIN_09 /* Onboard LED pins */

static off_t skip_id3v2(int fd) {
  uint8_t data[10];
  ssize_t rsize = read(fd, data, sizeof(data));
  if(rsize < 10) {
    return -1;
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
    return -2;
  }
  uint32_t size = (data[6] << 21) | (data[7] << 14) | (data[8] << 7) | (data[9]);
  size += 10; // size excludes the "header" (but not the "extended header")
  return lseek(fd, size, SEEK_CUR);
}

static bool mp3FileReadToSync(int fd, uint8_t *buf) {
  char b;
  int state = 0;
  while (read(fd, &b, 1) == 1) {
    if(buf) {
      *buf++ = b;
    }
    switch (state) {
      case 0:
        if ((b & SYNCWORDH) == SYNCWORDH) {
          state = 1;
        } else {
          state = 0;
        }
        break;
      case 1:
        if ((b & SYNCWORDL) == SYNCWORDL) {
          return true;
        } else {
          state = 0;
        }
        break;
    }
  }

  return false;
}


void hal_entry(void) {
  rt_kprintf("\nHello RT-Thread!\n");

  HMP3Decoder dec = MP3InitDecoder();
  if(dec != NULL) {
    rt_kprintf("MP3 decoder initialized\n");
  }
  else {
    rt_kprintf("MP3 decoder initialization failed\n");
  }

  /* Check filesystem */
  rt_thread_mdelay(1000);
  if (rt_device_find("sd0") == RT_NULL) {
    rt_kprintf("Please insert an SD card\n");
  }

  /* Open mp3 file for reading if it exists */
  int ret;
  struct stat buf;
  ret = stat("song.mp3", &buf);
  if (ret == 0) {
    rt_kprintf("text.txt file size = %d\n", buf.st_size);
    int fd = open("song.mp3", O_RDONLY);
    if (fd >= 0) {
      off_t offset = skip_id3v2(fd);
      if(offset >= 0) {
        rt_kprintf("ID3v2 header skipped: %i bytes\n", offset);
      }
      else {
        rt_kprintf("ID3v2 header not found\n");
      }
      uint8_t * compressed_frame = NULL;
      while(mp3FileReadToSync(fd, compressed_frame)) {
        uint8_t frame_buffer[512];
        frame_buffer[0] = SYNCWORDH;
        frame_buffer[1] = SYNCWORDL;

        if(compressed_frame != NULL) {
          MP3FrameInfo fi;
          int err = MP3GetNextFrameInfo(dec, &fi, frame_buffer);
          if(err != ERR_MP3_NONE)
            rt_kprintf("MP3GetNextFrameInfo: ERR %i\n", err);
          else
            rt_kprintf("MP3GetNextFrameInfo: rate = %i bps = %i ch = %i r = %i Hz\n", fi.bitrate, fi.bitsPerSample, fi.nChans, fi.samprate);
        }
        compressed_frame = &frame_buffer[2];

//        err = MP3Decode(decoder, &inbuf, &bytes_left,
//                        audiodata, 0);
//        if(err != ERR_MP3_NONE) fatal("MP3Decode");
//        look_for_overflow(audiodata, fi.outputSamps, ++frame);
//        CONSUME(&s, BYTES_LEFT(&s) - bytes_left);
      }

      close(fd);
    }
  }
  MP3FreeDecoder(dec);

  while (1) {
    rt_pin_write(LED_PIN, PIN_HIGH);
    rt_thread_mdelay(500);
    rt_pin_write(LED_PIN, PIN_LOW);
    rt_thread_mdelay(500);
  }
}
