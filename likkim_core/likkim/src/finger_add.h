/*********************
 *      INCLUDES
 *********************/
#ifndef __FINGER_ADD_H__
#define __FINGER_ADD_H__


#include "lvgl/lvgl.h"

typedef struct
{
	lv_obj_t* bg_cont;
} finger_add_t;

extern void finger_add_start(void);
extern void finger_add_stop(void);

#endif /* __FINGER_ADD_H__ */


