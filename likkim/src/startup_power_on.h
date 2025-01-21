/*********************
 *      INCLUDES
 *********************/
#ifndef __STARTUP_POWER_ON_H__
#define __STARTUP_POWER_ON_H__


#include "lvgl/lvgl.h"

typedef struct
{
	lv_obj_t* bg_cont;
	lv_obj_t* img_power_on;
	lv_timer_t *timer;
} startup_power_on_t;


void startup_power_on_start(void);
void startup_power_on_stop(void);

#endif /* __STARTUP_POWER_ON_H__ */


