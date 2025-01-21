/*********************
 *      INCLUDES
 *********************/
#ifndef __STARTUP_INVALID_RECORERY_H__
#define __STARTUP_INVALID_RECORERY_H__


#include "lvgl/lvgl.h"

typedef struct
{
	lv_obj_t* bg_cont;
} startup_invalid_recovery_t;

extern void startup_invalid_recovery_start(void);
extern void startup_invalid_recovery_stop(void);

#endif /* __STARTUP_INVALID_RECORERY_H__ */


