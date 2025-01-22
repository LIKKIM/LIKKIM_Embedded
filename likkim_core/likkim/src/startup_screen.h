/*********************
 *      INCLUDES
 *********************/
#ifndef __STARTUP_SCREEN_H__
#define __STARTUP_SCREEN_H__


#include "lvgl/lvgl.h"
#include "gui_comm.h"


typedef struct
{	
	app_index_t app_index;

	lv_coord_t move_y;
	lv_obj_t* bg_cont;
	lv_obj_t* scroll_img;
	lv_obj_t* scroll_label;
} startup_screen_t;

extern void startup_screen_start(app_index_t app_index);
extern void startup_screen_stop(void);


#endif /* __STARTUP_SCREEN_H__ */


