/*********************
 *      INCLUDES
 *********************/

#include "settings_complete.h"
#include "gui_comm.h"

extern void settings_security_start(void);
extern void settings_main_start(void);


static settings_complete_t* p_settings_complete = NULL;

static void restart_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        settings_complete_stop();
        /*添加重启接口*/
        gui_rest_data();
        // settings_main_start();
        
    }
}

static void settings_complete_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* img_succ = lv_img_create(parent);
	lv_img_set_src(img_succ, &img_success);
    lv_obj_set_pos(img_succ, 40, 69);

    lv_obj_t* title_label = lv_label_create(parent);
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xffffff), 0); 
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(title_label, 350);
    lv_obj_set_pos(title_label, 90, 60); 
	set_language_string(title_label, 40, language_table_reset_complete);
    
    lv_obj_t* describe_label = lv_label_create(parent);
    lv_obj_set_style_text_color(describe_label, lv_color_hex(0xffffff), 0); 
    lv_label_set_long_mode(describe_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(describe_label, 400);
    lv_obj_set_pos(describe_label, 40, 120); 
	set_language_string(describe_label, 24, language_table_device_reset);
    
    lv_obj_t* img_btn_restart = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0x10E807, 0x0A8F04);
    lv_obj_add_event_cb(img_btn_restart, restart_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_restart = lv_label_create(img_btn_restart);
    lv_obj_set_style_text_color(label_restart, lv_color_hex(0xffffff), 0); 
    lv_obj_set_style_text_align(label_restart, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_restart, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_restart, 400); 
	set_language_string(label_restart, 24, language_table_restart);
    lv_obj_center(label_restart);
    lv_obj_add_flag(label_restart, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void settings_complete_start(void)
{
     gui_algo_data_set_pagelocation("settings_complete",0);
    p_settings_complete = (settings_complete_t*)lv_mem_alloc(sizeof(settings_complete_t));
    LV_ASSERT(p_settings_complete);
    lv_memset(p_settings_complete, 0, sizeof(settings_complete_t));

    p_settings_complete->bg_cont = gui_comm_draw_bg();
    settings_complete_bg_cont(p_settings_complete->bg_cont);
}

 void settings_complete_stop(void)
{
    lv_obj_del(p_settings_complete->bg_cont);
    lv_mem_free(p_settings_complete);
    p_settings_complete = NULL;
}
