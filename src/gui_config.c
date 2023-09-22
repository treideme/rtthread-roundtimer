/**
 * @file gui_config.c
 * @brief Support and action functions for the round timer configuration screen.
 * @author Thomas Reidemeister <treideme@gmail.com>
 * @copyright 2023 Thomas Reidemeister
 * @license Apache-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdlib.h>
#include <stdint.h>
#include "macro.h"
#include "gui_config.h"

static lv_obj_t *_button_presets[3] = {0};

static int _handle_preset(lv_event_t * event) {
  int preset = -1;
  for(size_t i = 0; i < ARRAY_SIZE(_button_presets); i++) {
    if(event->target == _button_presets[i]) {
      preset = (int)i;
    }
  }
  if(preset >= 0) {
    lv_user_config_set(preset);
    return 0;
  }
  return -1;
}

static void _click_cb(lv_event_t * event) {
  if(_handle_preset(event) == 0) {
    return;
  }
}

void lv_user_config_screen_init(lv_obj_t *screen) {
  // map presets for better handling
  _button_presets[0] = ui_btnConfig1;
  _button_presets[1] = ui_btnConfig2;
  _button_presets[3] = ui_btnConfig3;
  lv_user_config_set(0);
  for(size_t i = 0; i < ARRAY_SIZE(_button_presets); i++) {
    lv_obj_add_event_cb(_button_presets[i], _click_cb, LV_EVENT_ALL, NULL);
  }
}

int lv_user_config_set(size_t num) {
  for(size_t i = 0; i < ARRAY_SIZE(_button_presets); i++) {
    lv_obj_clear_state(_button_presets[i], LV_STATE_CHECKED);
    if(i == num) {
      lv_obj_add_state(_button_presets[i], LV_STATE_CHECKED);
    }
  }
  // FIXME: Add validity check for time entry
  if(num < ARRAY_SIZE(_button_presets)) {
    lv_obj_clear_state(ui_btnStart, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_btnSave, LV_STATE_DISABLED);
    return 0;
  } else {
    lv_obj_add_state(ui_btnStart, LV_STATE_DISABLED);
    lv_obj_add_state(ui_btnSave, LV_STATE_DISABLED);
    return -1;
  }
}