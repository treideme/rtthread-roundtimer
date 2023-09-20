/**
 * @file gui_color.h
 * @brief Main entry point for GUI management.
 * @author Thomas Reidemeister <treideme@gmail.com>
 * @copyright 2023 Thomas Reidemeister
 * @license Apache-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _gui_color_h_
#define _gui_color_h_

#include <lvgl.h>
#include <rtthread.h>
#include "ui.h"

extern const uint32_t text_colors[];

/**
 * Programmatically populate the color chooser buttons.
 * @param screen The screen to populate.
 */
void lv_user_color_screen_init(lv_obj_t *screen);

/**
 * Preselect the color of the text
 * @param num The color to preselect.
 * @return 0 if successful, -1 otherwise.
 */
int lv_user_color_set(size_t num);

#endif // _gui_color_h_
