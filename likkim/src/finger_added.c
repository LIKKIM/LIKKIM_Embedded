/*********************
 *      INCLUDES
 *********************/

#include "finger_added.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


static finger_added_t* p_finger_added = NULL;


extern void finger_add_start(void);

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
	    finger_added_stop();
		if(0 == gui_data_get_first_poweron())
	    	finger_add_start();
    }
}

static void finger_start_continue_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
	    finger_added_stop();
		if(0 == gui_data_get_first_poweron())
	    	finger_add_start();
    }
}

static void finger_added_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* back_icons = lv_img_create(parent);
    lv_img_set_src(back_icons, &img_back);
    lv_obj_set_pos(back_icons, 40, 16);
    lv_obj_add_event_cb(back_icons, title_cb, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_add_flag(back_icons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* success_icons = lv_img_create(parent);
    lv_img_set_src(success_icons, &img_success);
    lv_obj_set_pos(success_icons, 40, 63);

    lv_obj_t* title = lv_label_create(parent);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(title, 350);
    lv_obj_set_pos(title, 90, 54);
    set_language_string(title, 40, language_table_fingerprint_added);
    lv_label_set_text_fmt(title, language_table_fingerprint_added[gui_data_get_language_type()], gui_data_get_fingerprint_num());

    lv_obj_t* btn_continue = gui_comm_draw_obj(parent, 40, 684, 400, 80, 0x7FF, 0x10E807, 0x0A8F04);
    lv_obj_add_event_cb(btn_continue, finger_start_continue_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_cancel = lv_label_create(btn_continue);
    lv_obj_set_style_text_color(label_cancel, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_cancel, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_cancel, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_cancel, 400);
    set_language_string(label_cancel, 24, language_table_continue);
    lv_obj_center(label_cancel);
    lv_obj_add_flag(label_cancel, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void finger_added_start(void)
{
    gui_algo_data_set_pagelocation("finger_added",0);
    p_finger_added = (finger_added_t*)lv_mem_alloc(sizeof(finger_added_t));
    LV_ASSERT(p_finger_added);
    lv_memset(p_finger_added, 0, sizeof(finger_added_t));

    p_finger_added->bg_cont = gui_comm_draw_bg();
    finger_added_bg_cont(p_finger_added->bg_cont);
}

 void finger_added_stop(void)
{
    lv_obj_del(p_finger_added->bg_cont);
    lv_mem_free(p_finger_added);
    p_finger_added = NULL;
}
