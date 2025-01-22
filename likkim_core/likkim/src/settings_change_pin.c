/*********************
 *      INCLUDES
 *********************/

#include "settings_change_pin.h"
#include "gui_comm.h"

extern void settings_security_start(void);
extern void startup_enter_pin_start(app_index_t app_index);

static settings_change_pin_t* p_settings_change_pin = NULL;


static void confirm_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        settings_change_pin_stop();
		startup_enter_pin_start(APP_SETTINGS_PIN);
    }
}

static void cancel_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        settings_change_pin_stop();
        settings_security_start();
    }
}

static void settings_change_pin_bg_cont(lv_obj_t* parent)
{
	lv_obj_t* img_succ = lv_img_create(parent);
	lv_img_set_src(img_succ, &img_alert);
    lv_obj_set_pos(img_succ, 40, 69);

    lv_obj_t* title_label = lv_label_create(parent);
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xffffff), 0); 
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(title_label, 400);
    lv_obj_set_pos(title_label, 90, 60); 
	set_language_string(title_label, 40, language_table_change_pin);

    lv_obj_t* describe_label = lv_label_create(parent);
    lv_obj_set_style_text_color(describe_label, lv_color_hex(0xffffff), 0); 
    lv_label_set_long_mode(describe_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(describe_label, 400);
    lv_obj_set_pos(describe_label, 40, 120); 
	set_language_string(describe_label, 24, language_table_set_pin_protect_wallet);
    lv_obj_add_flag(describe_label, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* img_btn_confirm = gui_comm_draw_obj(parent, 40, 598, 400, 80, 0x7FF, 0xF7E100, 0x8A7D00);
    lv_obj_add_event_cb(img_btn_confirm, confirm_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_confirm = lv_label_create(img_btn_confirm);
    lv_obj_set_style_text_color(label_confirm, lv_color_hex(0x000000), 0); 
    lv_obj_set_style_text_align(label_confirm, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_confirm, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_confirm, 400); 
	set_language_string(label_confirm, 24, language_table_confirm);
    lv_obj_center(label_confirm);
    lv_obj_add_flag(label_confirm, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* img_btn_cancel = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FF, 0x888888, 0x666666);
    lv_obj_add_event_cb(img_btn_cancel, cancel_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_cancel = lv_label_create(img_btn_cancel);
    lv_obj_set_style_text_color(label_cancel, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_cancel, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_cancel, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_cancel, 400);
	set_language_string(label_cancel, 24, language_table_cancel);
    lv_obj_center(label_cancel);
    lv_obj_add_flag(label_cancel, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

}


void settings_change_pin_start(void)
{
    gui_algo_data_set_pagelocation("settings_change_pin",0);
    p_settings_change_pin = (settings_change_pin_t*)lv_mem_alloc(sizeof(settings_change_pin_t));
    LV_ASSERT(p_settings_change_pin);
    lv_memset(p_settings_change_pin, 0, sizeof(settings_change_pin_t));

    p_settings_change_pin->bg_cont = gui_comm_draw_bg();
    settings_change_pin_bg_cont(p_settings_change_pin->bg_cont);
    gui_comm_set_state_top();
}

void settings_change_pin_stop(void)
{
    lv_obj_del(p_settings_change_pin->bg_cont);
    lv_mem_free(p_settings_change_pin);
    p_settings_change_pin = NULL;
}

