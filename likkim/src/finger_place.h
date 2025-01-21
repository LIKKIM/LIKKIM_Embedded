/*********************
 *      INCLUDES
 *********************/
#ifndef __FINGER_PLACE_H__
#define __FINGER_PLACE_H__


#include "lvgl/lvgl.h"

typedef struct
{
	lv_obj_t* bg_cont;
	lv_obj_t* finger_icons;
	lv_timer_t *timer;
} finger_place_t;

extern void finger_place_start(void);
extern void finger_place_stop(void);

#endif /* __FINGER_PLACE_H__ */


