/*********************
 *      INCLUDES
 *********************/
#ifndef __FINGER_ADDED_H__
#define __FINGER_ADDED_H__


#include "lvgl/lvgl.h"

typedef struct
{
	lv_obj_t* bg_cont;
} finger_added_t;

extern void finger_added_start(void);
extern void finger_added_stop(void);

#endif /* __FINGER_ADDED_H__ */


