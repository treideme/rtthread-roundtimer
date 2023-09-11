/**
 * @file gui_entry.c
 * @brief Main entry point for GUI management.
 * @author Thomas Reidemeister <treideme@gmail.com>
 * @copyright 2023 Thomas Reidemeister
 * @license Apache-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "gui_entry.h"

//static void _btn_cb(lv_event_t * event) {
//    rt_kprintf("Event Received 0x%03X\n", event->code);
//}

void lv_user_gui_init(void) {
    ui_init();
//    /* Set background color red */
//    lv_obj_set_style_bg_color(lv_scr_act(), COLOR_RED, 0);
//    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
//
//    /*Create a white btn, set its text and align it to the center*/
//    lv_obj_t * btn = lv_btn_create(lv_scr_act());
//    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
//    lv_obj_add_event_cb(btn, _btn_cb, LV_EVENT_ALL, NULL); /*Assign an event callback*/
//    lv_obj_t * label = lv_label_create(btn);
//    lv_label_set_text(label, "Button");
//    lv_obj_center(label);
}
