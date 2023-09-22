/**
 * @file gui_color.c
 * @brief Support and action functions for the color chooser.
 * @author Thomas Reidemeister <treideme@gmail.com>
 * @copyright 2023 Thomas Reidemeister
 * @license Apache-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdlib.h>
#include <stdint.h>
#include "macro.h"
#include "gui_entry.h"
#include "gui_color.h"

/**
 * @brief Color chooser button colors.
 * RiscOS_16colors_palette.svg
 */
const uint32_t text_colors[] = {
  0xffffff,
  0xdcdcdc,
  0xbcbcbc,
  0x989898,
  0x787878,
  0x545454,
  0x343434,
  0x000000,

  0x004498,
  0xf0f000,
  0x00cc00,
  0xdc0000,
  0xf0f0bc,
  0x548800,
  0xffbc00,
  0x00bcff,
};

static lv_obj_t *_button_colors[ARRAY_SIZE(text_colors)] = {0};

static void _button_cb(lv_event_t * event) {
  rt_kprintf("Event Received 0x%03X\n", event->code);
  size_t btn = ARRAY_SIZE(text_colors);
  for(size_t i = 0; i < ARRAY_SIZE(text_colors); i++) {
    if(event->target == _button_colors[i]) {
      btn = i;
    }
  }
  lv_user_color_set(btn);
}

void lv_user_color_screen_init(lv_obj_t *screen) {
  for(size_t i = 0; i < ARRAY_SIZE(text_colors); i++) {
    _button_colors[i] = lv_btn_create(screen);
    lv_obj_set_width(_button_colors[i], 50);
    lv_obj_set_height(_button_colors[i], 50);
    lv_obj_set_style_bg_color(_button_colors[i], lv_color_hex(text_colors[i]), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_color(_button_colors[i], lv_color_hex(text_colors[i]), LV_PART_MAIN | LV_STATE_CHECKED );
    lv_obj_set_style_border_side(_button_colors[i], LV_BORDER_SIDE_FULL, LV_PART_MAIN| LV_STATE_CHECKED);
    lv_obj_set_style_outline_color(_button_colors[i], lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED );
    lv_obj_set_style_outline_width(_button_colors[i], 3, LV_PART_MAIN| LV_STATE_CHECKED);
    lv_obj_set_style_outline_pad(_button_colors[i], 3, LV_PART_MAIN| LV_STATE_CHECKED);

    if(i < 8) {
      lv_obj_set_x(_button_colors[i], 60 * (i + 1) - 55);
      lv_obj_set_y(_button_colors[i], 50);
    } else {
      lv_obj_set_x(_button_colors[i], 60 * (i - 7) - 55);
      lv_obj_set_y(_button_colors[i], 130);
    }
    lv_obj_add_flag(_button_colors[i], LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS );
    lv_obj_clear_flag(_button_colors[i], LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE );
    lv_obj_add_event_cb(_button_colors[i], _button_cb, LV_EVENT_CLICKED, NULL);
  }
}

int lv_user_color_set(size_t num) {
  for(size_t i = 0; i < ARRAY_SIZE(text_colors); i++) {
    lv_obj_clear_state(_button_colors[i], LV_STATE_CHECKED | LV_STATE_FOCUSED);
    if(i == num) {
      lv_obj_add_state(_button_colors[i], LV_STATE_CHECKED | LV_STATE_FOCUSED);
    }
  }
  if(num < ARRAY_SIZE(text_colors)) {
    lv_obj_clear_state( ui_btnAcceptColor, LV_STATE_DISABLED );
    return 0;
  } else {
    lv_obj_add_state( ui_btnAcceptColor, LV_STATE_DISABLED );
    return -1;
  }
}

ssize_t lv_user_color_get() {
  for(ssize_t i = 0; i < ARRAY_SIZE(text_colors); i++) {
    if(lv_obj_get_state(_button_colors[i]) & LV_STATE_CHECKED) {
      return i;
    }
  }
  return -1;
}