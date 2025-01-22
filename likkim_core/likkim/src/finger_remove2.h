/*********************
 *      INCLUDES
 *********************/
#ifndef __FINGER_REMOVE2_H__
#define __FINGER_REMOVE2_H__


#include "lvgl/lvgl.h"

typedef struct
{
	lv_obj_t* bg_cont;
} finger_remove2_t;

extern void finger_remove2_start(void);
extern void finger_remove2_stop(void);

#endif /* __FINGER_REMOVE2_H__ */


