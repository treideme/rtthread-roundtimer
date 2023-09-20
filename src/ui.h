// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.2.0
// Project name: round_timer

#ifndef _ROUND_TIMER_UI_H
#define _ROUND_TIMER_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
  #if __has_include("lvgl.h")
    #include "lvgl.h"
  #elif __has_include("lvgl/lvgl.h")
    #include "lvgl/lvgl.h"
  #else
    #include "lvgl.h"
  #endif
#else
  #include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_Configuration
void ui_Configuration_screen_init(void);
extern lv_obj_t *ui_Configuration;
extern lv_obj_t *ui_labelHeadingConfiguration;
extern lv_obj_t *ui_labelGetReady;
extern lv_obj_t *ui_labelWorkout;
extern lv_obj_t *ui_labelRest;
extern lv_obj_t *ui_textGetReady;
extern lv_obj_t *ui_textWorkout;
extern lv_obj_t *ui_textRest;
extern lv_obj_t *ui_btnForegroundReady;
extern lv_obj_t *ui_btnForegroundWorkout;
extern lv_obj_t *ui_btnForegroundRest;
extern lv_obj_t *ui_btnBackgroundReady;
extern lv_obj_t *ui_btnBackgroundWorkout;
extern lv_obj_t *ui_btnBackgroundRest;
extern lv_obj_t *ui_labelConfigurationSelector;
extern lv_obj_t *ui_btnConfig1;
extern lv_obj_t *ui_labelConfig1;
extern lv_obj_t *ui_btnConfig2;
extern lv_obj_t *ui_labelConfig2;
extern lv_obj_t *ui_btnConfig3;
extern lv_obj_t *ui_labelConfig3;
extern lv_obj_t *ui_btnStart;
extern lv_obj_t *ui_labelStart;
extern lv_obj_t *ui_btnSave;
extern lv_obj_t *ui_labelSave;
extern lv_obj_t *ui_btnUp;
extern lv_obj_t *ui_labelUp;
extern lv_obj_t *ui_btnDown;
extern lv_obj_t *ui_labelDown;
// SCREEN: ui_Color_Chooser
void ui_Color_Chooser_screen_init(void);
extern lv_obj_t *ui_Color_Chooser;
extern lv_obj_t *ui_labelHeadingColor;
extern lv_obj_t *ui_btnAcceptColor;
extern lv_obj_t *ui_labelAcceptColor;
extern lv_obj_t *ui____initial_actions0;




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
