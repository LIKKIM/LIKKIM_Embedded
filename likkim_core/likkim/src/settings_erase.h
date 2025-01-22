﻿/*********************
 *      INCLUDES
 *********************/
#ifndef __SETTINGS_ERASE_H__
#define __SETTINGS_ERASE_H__


#include "lvgl/lvgl.h"

typedef struct
{
	lv_obj_t* bg_cont;
	lv_obj_t* slider;
	lv_timer_t *timer;

	lv_obj_t* img_check1;
	lv_obj_t* img_check2;

	bool check1;
	bool check2;
} settings_erase_t;

extern void settings_erase_start(void);
extern void settings_erase_stop(void);

#endif /* __SETTINGS_ERASE_H__ */


