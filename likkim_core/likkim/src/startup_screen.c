/*********************
 *      INCLUDES
 *********************/


#include "startup_screen.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


static startup_screen_t* p_startup_screen = NULL;

extern void startup_language_start(app_index_t app_index);
extern void startup_enter_pin_start(app_index_t app_index);



static void startup_screen_scroll_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);
    if (LV_EVENT_PRESSING == event)
    {
        lv_indev_t* indev = lv_indev_get_act();
        lv_point_t p;

        lv_indev_get_vect(indev, &p);
        p_startup_screen->move_y += p.y;

        if (p_startup_screen->move_y < -300)
        {
            lv_obj_set_pos(p_startup_screen->scroll_img, 230, 389);
            lv_obj_align_to(p_startup_screen->scroll_label, p_startup_screen->scroll_img, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
        }
        else
        {
            lv_obj_set_pos(p_startup_screen->scroll_img, 230, 689 + p_startup_screen->move_y);
            lv_obj_align_to(p_startup_screen->scroll_label, p_startup_screen->scroll_img, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
        }
    }    
    else if (LV_EVENT_RELEASED == event)
    {
        if (p_startup_screen->move_y <= -300)
        {
            startup_screen_stop();
		    if(gui_data_get_first_poweron())
	            startup_language_start(APP_STARTUP);
	        else
	        	startup_enter_pin_start(APP_STARTUP);
        }
        else
        {
            p_startup_screen->move_y = 0;
            lv_obj_set_pos(p_startup_screen->scroll_img, 230, 689);
            lv_obj_align_to(p_startup_screen->scroll_label, p_startup_screen->scroll_img, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
        }
    }
}
static void startup_screen_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* bg_img = lv_img_create(parent);
    lv_img_set_src(bg_img, gui_data_get_bg_src());
    lv_obj_center(bg_img);

    bg_img = lv_img_create(parent);
    lv_img_set_src(bg_img, &img_likkim);
    lv_obj_set_pos(bg_img, 111, 100);

    lv_obj_t* scroll_img = lv_img_create(parent);
    lv_img_set_src(scroll_img, &img_startup_arrow);
    lv_obj_set_pos(scroll_img, 230, 689);
    p_startup_screen->scroll_img = scroll_img;
	
    lv_obj_t* scroll_obj = lv_obj_create(parent);
    lv_obj_set_size(scroll_obj, 480, 400);
    lv_obj_set_y(scroll_obj, 400);
    lv_obj_set_style_opa(scroll_obj, LV_OPA_TRANSP, 0);
    lv_obj_add_event_cb(scroll_obj, startup_screen_scroll_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(scroll_obj, LV_OBJ_FLAG_SCROLL_CHAIN);
    
    lv_obj_t* scroll_label = lv_label_create(parent);
    lv_obj_set_style_text_color(scroll_label, lv_color_hex(0xffffff), 0);
	set_language_string(scroll_label, 24, language_table_swipe_to_show_app);
    lv_obj_align_to(scroll_label, parent, LV_ALIGN_TOP_MID, 0, 731);
    lv_obj_add_flag(scroll_label, LV_OBJ_FLAG_SCROLL_CHAIN);
    p_startup_screen->scroll_label = scroll_label;
}
void startup_screen_start(app_index_t app_index)
{
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("startup_screen",0);
    p_startup_screen = (startup_screen_t*)lv_mem_alloc(sizeof(startup_screen_t));
    lv_memset(p_startup_screen, 0, sizeof(startup_screen_t));
    p_startup_screen->bg_cont = gui_comm_draw_bg();
    startup_screen_bg_cont(p_startup_screen->bg_cont);
    gui_comm_set_state_top();
    p_startup_screen->app_index = app_index;
}

void startup_screen_stop(void)
{
    lv_obj_del(p_startup_screen->bg_cont);
    lv_mem_free(p_startup_screen);
    p_startup_screen = NULL;
}
