/*********************
 *      INCLUDES
 *********************/
#ifndef __FINGER_START_H__
#define __FINGER_START_H__


#include "lvgl/lvgl.h"

typedef struct
{
	lv_obj_t* bg_cont;
	lv_timer_t *timer;
} finger_start_t;

extern void finger_start_start(void);
extern void finger_start_stop(void);

#endif /* __FINGER_START_H__ */


