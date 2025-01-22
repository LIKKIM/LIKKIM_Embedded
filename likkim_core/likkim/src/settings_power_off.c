/*********************
 *      INCLUDES
 *********************/

#include "settings_power_off.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

extern void settings_main_start(void);

static settings_power_off_t* p_settings_power_off = NULL;


static void power_off_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
		
    }
}
static void cancel_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	settings_power_off_stop();
		settings_main_start();
    }
}
static void settings_power_off_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* label_title = lv_label_create(parent);
	lv_obj_set_style_text_color(label_title, lv_color_hex(0xffffff), 0);
	set_language_string(label_title, 40, language_table_power_off);
    lv_obj_align(label_title, LV_ALIGN_TOP_MID, 0, 60);
	
    lv_obj_t* img_btn_power_off = gui_comm_draw_obj(parent, 40, 598, 400, 80, 0x7FFF, 0xFF2600, 0x771200);
    lv_obj_add_event_cb(img_btn_power_off, power_off_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_power_off = lv_label_create(img_btn_power_off);
	lv_obj_set_style_text_color(label_power_off, lv_color_hex(0xffffff), 0);
	set_language_string(label_power_off, 24, language_table_power_off);
    lv_obj_align(label_power_off, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(label_power_off, LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* img_btn_cancel = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0x888888, 0x666666);
    lv_obj_add_event_cb(img_btn_cancel, cancel_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_cancel = lv_label_create(img_btn_cancel);
	lv_obj_set_style_text_color(label_cancel, lv_color_hex(0xffffff), 0);
	set_language_string(label_cancel, 24, language_table_cancel);
    lv_obj_align(label_cancel, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(label_cancel, LV_OBJ_FLAG_EVENT_BUBBLE);

}


void settings_power_off_start(void)
{
    gui_algo_data_set_pagelocation("settings_power_off",0);
    p_settings_power_off = (settings_power_off_t*)lv_mem_alloc(sizeof(settings_power_off_t));
    LV_ASSERT(p_settings_power_off);
    lv_memset(p_settings_power_off, 0, sizeof(settings_power_off_t));

    p_settings_power_off->bg_cont = gui_comm_draw_bg();
    settings_power_off_bg_cont(p_settings_power_off->bg_cont);
}

void settings_power_off_stop(void)
{
    lv_obj_del(p_settings_power_off->bg_cont);
    lv_mem_free(p_settings_power_off);
    p_settings_power_off = NULL;
}

