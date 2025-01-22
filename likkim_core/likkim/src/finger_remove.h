/*********************
 *      INCLUDES
 *********************/
#ifndef __FINGER_REMOVE_H__
#define __FINGER_REMOVE_H__


#include "lvgl/lvgl.h"

typedef struct
{
	lv_obj_t* bg_cont;
} finger_remove_t;

extern void finger_remove_start(void);
extern void finger_remove_stop(void);

#endif /* __FINGER_REMOVE_H__ */


