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

#define LED_PIN    BSP_IO_PORT_02_PIN_09 /* Onboard LED pins */

void hal_entry(void) {
  rt_kprintf("\nHello RT-Thread!\n");

  /* Check filesystem */
  rt_thread_mdelay(1000);
  if (rt_device_find("sd0") == RT_NULL) {
    rt_kprintf("Please insert an SD card\n");
  }

  /* Open file for reading if it exists */
  int ret;
  struct stat buf;
  ret = stat("text.txt", &buf);
  if (ret == 0) {
    rt_kprintf("text.txt file size = %d\n", buf.st_size);
    int fd = open("text.txt", O_RDONLY);
    if (fd >= 0) {
      char buf[16];
      read(fd, buf, 13);
      buf[13] = '\0';
      rt_kprintf("text.txt contents: %s\n", buf);
      close(fd);
    }
  }
  else {
    int fd = open("text.txt", O_CREAT | O_WRONLY);
    if (fd >= 0) {
      rt_kprintf("text.txt file created\n");
      write(fd, "Hello World!\n", 13);
      close(fd);
    }
  }


  while (1) {
    rt_pin_write(LED_PIN, PIN_HIGH);
    rt_thread_mdelay(500);
    rt_pin_write(LED_PIN, PIN_LOW);
    rt_thread_mdelay(500);
  }
}
