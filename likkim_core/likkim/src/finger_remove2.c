/*********************
 *      INCLUDES
 *********************/

#include "finger_remove2.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


static finger_remove2_t* p_finger_remove2 = NULL;

extern void finger_add_start(void);

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
	    finger_remove2_stop();
	    finger_add_start();
    }
}

static void finger_start_remove2_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
		gui_data_set_fingerprint_num(gui_data_get_fingerprint_num() - 1);
        finger_remove2_stop();
	    finger_add_start();
    }
}

static void finger_start_cancle_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        finger_remove2_stop();
	    finger_add_start();
    }
}

static void finger_remove2_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* title = gui_comm_draw_title(parent, language_table_remove_fingerprints, title_cb);

    lv_obj_t* label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 400);
    set_language_string(label_describe, 24, language_table_confirm_remove_fingerprint);
    lv_obj_align_to(label_describe, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

    lv_obj_t* btn_cancle = gui_comm_draw_obj(parent, 40, 684, 192, 80, 0x7FF, 0x888888, 0x666666);
    lv_obj_add_event_cb(btn_cancle, finger_start_cancle_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_cancel = lv_label_create(btn_cancle);
    lv_obj_set_style_text_color(label_cancel, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_cancel, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_cancel, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_cancel, 190);
    set_language_string(label_cancel, 24, language_table_cancel);
    lv_obj_center(label_cancel);
    lv_obj_add_flag(label_cancel, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* btn_remove2 = gui_comm_draw_obj(parent, 248, 684, 192, 80, 0x7FF, 0xFF2600, 0x771200);
    lv_obj_add_event_cb(btn_remove2, finger_start_remove2_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_remove2 = lv_label_create(btn_remove2);
    lv_obj_set_style_text_color(label_remove2, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_remove2, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_remove2, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_remove2, 190);
    set_language_string(label_remove2, 24, language_table_remove);
    lv_obj_center(label_remove2);
    lv_obj_add_flag(label_remove2, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void finger_remove2_start(void)
{
    gui_algo_data_set_pagelocation("finger_remove2",0);
    p_finger_remove2 = (finger_remove2_t*)lv_mem_alloc(sizeof(finger_remove2_t));
    LV_ASSERT(p_finger_remove2);
    lv_memset(p_finger_remove2, 0, sizeof(finger_remove2_t));

    p_finger_remove2->bg_cont = gui_comm_draw_bg();
    finger_remove2_bg_cont(p_finger_remove2->bg_cont);
}

 void finger_remove2_stop(void)
{
    lv_obj_del(p_finger_remove2->bg_cont);
    lv_mem_free(p_finger_remove2);
    p_finger_remove2 = NULL;
}
