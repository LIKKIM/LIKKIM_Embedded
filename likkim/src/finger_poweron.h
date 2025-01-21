/*********************
 *      INCLUDES
 *********************/
#ifndef __FINGER_POWERON_H__
#define __FINGER_POWERON_H__


#include "lvgl/lvgl.h"
#include "gui_comm.h"


typedef struct
{
	lv_obj_t* bg_cont;
	app_index_t app_index;
} finger_poweron_t;

extern void finger_poweron_start(app_index_t app_index);
extern void finger_poweron_stop(void);

#endif /* __FINGER_POWERON_H__ */


