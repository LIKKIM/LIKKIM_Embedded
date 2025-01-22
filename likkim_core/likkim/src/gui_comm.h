/*********************
 *      INCLUDES
 *********************/
#ifndef __GUI_COMM_H__
#define __GUI_COMM_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lvgl/lvgl.h"
//#include "lvgl/src/extra/libs/qrcode/lv_qrcode.h"

#include "gui_language_comm.h"

//#define lv_mem_alloc(size)                  app_malloc(size)
//#define lv_mem_free(size)                  app_free(size)
//#define strcmp(str1, str2)                  strcmp(str1, str2)
//#define strcpy(str1, str2)                  strcpy(str1, str2)
//#define strcat(str1, str2)                  strcat(str1, str2)
//#define strlen(str1)                  strlen(str1)


LV_IMG_DECLARE(img_small_bg1);
LV_IMG_DECLARE(img_small_bg2);
LV_IMG_DECLARE(img_small_bg3);
LV_IMG_DECLARE(img_small_bg4);
LV_IMG_DECLARE(img_small_bg5);
LV_IMG_DECLARE(img_small_bg6);
LV_IMG_DECLARE(img_small_bg7);
LV_IMG_DECLARE(img_bg1);
LV_IMG_DECLARE(img_bg2);
LV_IMG_DECLARE(img_bg3);
LV_IMG_DECLARE(img_bg4);
LV_IMG_DECLARE(img_bg5);
LV_IMG_DECLARE(img_bg6);
LV_IMG_DECLARE(img_bg7);

LV_IMG_DECLARE(img_power_10);
LV_IMG_DECLARE(img_power_25);
LV_IMG_DECLARE(img_power_50);
LV_IMG_DECLARE(img_power_75);
LV_IMG_DECLARE(img_power_100);
LV_IMG_DECLARE(img_power_charge);
LV_IMG_DECLARE(img_ble_connect);
LV_IMG_DECLARE(img_ble_unconnect);

LV_IMG_DECLARE(img_error);
LV_IMG_DECLARE(img_fingerprint);
LV_IMG_DECLARE(img_add)
LV_IMG_DECLARE(img_fingerprint_add_tip);
LV_IMG_DECLARE(img_fingerprint_1);
LV_IMG_DECLARE(img_fingerprint_2);
LV_IMG_DECLARE(img_fingerprint_3);
LV_IMG_DECLARE(img_fingerprint_4);
LV_IMG_DECLARE(img_fingerprint_5);
LV_IMG_DECLARE(img_fingerprint_6);

LV_IMG_DECLARE(img_slider_knob_1);
LV_IMG_DECLARE(img_slider_knob_2);
LV_IMG_DECLARE(img_slider_knob_3);
LV_IMG_DECLARE(img_slider_knob_4);

LV_IMG_DECLARE(img_menu_general);
LV_IMG_DECLARE(img_menu_guide);
LV_IMG_DECLARE(img_menu_settings);


LV_IMG_DECLARE(img_back)
LV_IMG_DECLARE(img_alert);

LV_IMG_DECLARE(img_keypad2_delete)
LV_IMG_DECLARE(img_keypad_delete);
LV_IMG_DECLARE(img_keypad_ok);
LV_IMG_DECLARE(img_chosen);
LV_IMG_DECLARE(img_unchosen);
LV_IMG_DECLARE(img_startup_arrow);
LV_IMG_DECLARE(img_loading);
LV_IMG_DECLARE(img_success);
LV_IMG_DECLARE(img_power_on);
LV_IMG_DECLARE(img_screen_shoosen);

LV_IMG_DECLARE(img_likkim);



typedef void (*gui_comm_callback)(void);


enum
{
	APP_POWER_ON,
	APP_STARTUP,
	APP_STARTUP_CREATE_WALLET,
	APP_STARTUP_IMPORT_WALLET,
	APP_MAIN,
	APP_SETTINGS,
	APP_SETTINGS_PIN,
	APP_SETTINGS_ERASE,
	APP_GENERAL,
	APP_CONNECT,
	APP_GUIDE,
};
typedef uint8_t app_index_t;


typedef struct
{
	lv_obj_t* img_charge;
	lv_obj_t* img_power;
	lv_obj_t* img_connect;
	lv_obj_t* label_power;
	lv_timer_t *timer;
} gui_comm_state_obj_t;

typedef struct
{
    const char **str;
    lv_coord_t x;
    lv_coord_t y;
} gui_comm_imgbtn_desc_t;

typedef struct
{
    const char *str;
    lv_coord_t x;
    lv_coord_t y;
} gui_comm_imgbtn_desc2_t;

typedef struct
{
    const char** str;
    lv_coord_t x;
    lv_coord_t y;
    const void* src;
} gui_comm_img_desc_t;

typedef struct
{
    lv_coord_t x;
    gui_comm_callback cb;
} gui_comm_slider_t;

typedef struct
{
	lv_obj_t* state_bg;
	
} gui_comm_t;



lv_obj_t* gui_comm_draw_bg(void);
lv_obj_t* gui_comm_draw_keypad_letter(lv_obj_t* parent, lv_event_cb_t num_cb, lv_event_cb_t ok_cb, lv_event_cb_t cancle_cb);
lv_obj_t *gui_comm_draw_keypad_num(lv_obj_t* parent, lv_event_cb_t num_cb, lv_event_cb_t ok_cb, lv_event_cb_t cancle_cb);
lv_obj_t *gui_comm_draw_title(lv_obj_t *parent, const char **str_tab, lv_event_cb_t event_cb);
lv_obj_t *gui_comm_draw_slider(lv_obj_t* parent, lv_coord_t y, gui_comm_callback cb);

void gui_comm_set_state_top(void);
lv_obj_t *gui_comm_draw_state(lv_obj_t *parent);

lv_obj_t *gui_comm_draw_obj(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, int32_t radius, uint32_t color_default, uint32_t color_pressed);
void gui_comm_init(void);
#endif /* __GUI_COMM_H__ */


