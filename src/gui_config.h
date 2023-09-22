/**
 * @file gui_config.h
 * @brief Support and action functions for the round timer configuration screen.
 * @author Thomas Reidemeister <treideme@gmail.com>
 * @copyright 2023 Thomas Reidemeister
 * @license Apache-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _gui_config_h_
#define _gui_config_h_

#include <lvgl.h>
#include <rtthread.h>
#include "ui.h"

/**
 * Register event handlers for config screen.
 * @param screen The screen to populate.
 */
void lv_user_config_screen_init(lv_obj_t *screen);

/**
 * Preselect the chosen configuration.
 * @param num The color to preselect.
 * @return 0 if successful, -1 otherwise.
 */
int lv_user_config_set(size_t num);

#endif // _gui_config_h_