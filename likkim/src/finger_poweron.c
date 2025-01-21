/*********************
 *      INCLUDES
 *********************/

#include "finger_poweron.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


static finger_poweron_t* p_finger_poweron = NULL;

extern void finger_place_start(void);

static void finger_poweron_not_now_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
		finger_poweron_stop();
    }
}

static void finger_poweron_add_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
        finger_poweron_stop();
        finger_place_start();
    }
}
static void finger_poweron_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* title = lv_label_create(parent);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(title, 400);
    lv_obj_set_pos(title, 40, 54);
    set_language_string(title, 40, language_table_fingerprint);

    lv_obj_t* label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 400);
    lv_obj_set_pos(label_describe, 40, 120);
    set_language_string(label_describe, 24, language_table_alternative_pin_unlock);
    
    lv_obj_t* btn_add = gui_comm_draw_obj(parent, 40, 598, 400, 80, 0x7FF, 0xCCB68C, 0xA4916F);
    lv_obj_add_event_cb(btn_add, finger_poweron_add_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_add = lv_label_create(btn_add);
    lv_obj_set_style_text_color(label_add, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_add, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_add, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_add, 400);
    set_language_string(label_add, 24, language_table_add_fingerprint);
    lv_obj_center(label_add);
    lv_obj_add_flag(label_add, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* btn_not_now = gui_comm_draw_obj(parent, 40, 684, 400, 80, 0x7FF, 0x888888, 0x666666);
    lv_obj_add_event_cb(btn_not_now, finger_poweron_not_now_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_not_now = lv_label_create(btn_not_now);
    lv_obj_set_style_text_color(label_not_now, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_not_now, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_not_now, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_not_now, 400);
    set_language_string(label_not_now, 24, language_table_not_now);
    lv_obj_center(label_not_now);
    lv_obj_add_flag(label_not_now, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void finger_poweron_start(app_index_t app_index)
{
   gui_algo_data_set_pagelocation("finger_poweron",0);
    p_finger_poweron = (finger_poweron_t*)lv_mem_alloc(sizeof(finger_poweron_t));
    LV_ASSERT(p_finger_poweron);
    lv_memset(p_finger_poweron, 0, sizeof(finger_poweron_t));

	p_finger_poweron->app_index = app_index;
    p_finger_poweron->bg_cont = gui_comm_draw_bg();
    finger_poweron_bg_cont(p_finger_poweron->bg_cont);
}

 void finger_poweron_stop(void)
{
    lv_obj_del(p_finger_poweron->bg_cont);
    lv_mem_free(p_finger_poweron);
    p_finger_poweron = NULL;
}
