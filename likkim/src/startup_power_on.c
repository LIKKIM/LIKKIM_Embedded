/*********************
 *      INCLUDES
 *********************/

#include "startup_power_on.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

static startup_power_on_t* p_startup_power_on = NULL;


extern void startup_language_start(app_index_t app_index);
extern void startup_screen_start(app_index_t app_index);

static void timer_cb(lv_timer_t * tmr)
{
	startup_power_on_stop();

	if(gui_data_get_first_poweron())
		startup_language_start(APP_STARTUP);
	else
		startup_screen_start(APP_STARTUP);
}

void startup_power_on_start(void)
{
    gui_algo_data_set_pagelocation("startup_power_on",0);
    p_startup_power_on = (startup_power_on_t*)lv_mem_alloc(sizeof(startup_power_on_t));
    LV_ASSERT(p_startup_power_on);
    lv_memset(p_startup_power_on, 0, sizeof(startup_power_on_t));


    lv_obj_t *bg_obj = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(bg_obj);
	lv_obj_set_scrollbar_mode(bg_obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(bg_obj, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bg_obj, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_size(bg_obj, 480, 800);
    lv_obj_center(bg_obj);
	lv_obj_update_layout(bg_obj);
    p_startup_power_on->bg_cont = bg_obj;

    lv_obj_t* img_poweron = lv_img_create(bg_obj);
	lv_img_set_src(img_poweron, &img_power_on);
    lv_obj_center(img_poweron);
    p_startup_power_on->img_power_on = img_poweron;
    
	p_startup_power_on->timer = lv_timer_create(timer_cb, 2000, NULL);
}

void startup_power_on_stop(void)
{
	lv_timer_del(p_startup_power_on->timer);
    lv_obj_del(p_startup_power_on->bg_cont);
    lv_mem_free(p_startup_power_on);
    p_startup_power_on = NULL;
}


