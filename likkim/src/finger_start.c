/*********************
 *      INCLUDES
 *********************/

#include "finger_start.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


extern void finger_add_start(void);
extern void finger_place_start(void);

static finger_start_t* p_finger_start = NULL;

static void timer_cb(lv_timer_t * tmr)
{
	if(gui_data_get_fingerprint_process())
	{
	    finger_start_stop();
	    finger_place_start();
	}
	/*测试*/
	gui_data_set_fingerprint_process(1);
}

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
	    finger_start_stop();
	    finger_add_start();
    }
}

static void finger_start_cancle_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
        finger_start_stop();
        finger_add_start();
    }
}
static void finger_start_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_get_started, title_cb);

    lv_obj_t* label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 400);
    set_language_string(label_describe, 24, language_table_add_finger_prompt);
    lv_obj_set_pos(label_describe, 40, 114);

    lv_obj_t* add_icons = lv_img_create(parent);
    lv_img_set_src(add_icons, &img_fingerprint_add_tip);
    lv_obj_set_pos(add_icons, 40, 264);

    lv_obj_t* btn_cancle = gui_comm_draw_obj(parent, 40, 684, 400, 80, 0x7FF, 0x888888, 0x666666);
    lv_obj_add_event_cb(btn_cancle, finger_start_cancle_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_cancel = lv_label_create(btn_cancle);
    lv_obj_set_style_text_color(label_cancel, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_cancel, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_cancel, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_cancel, 400);
    set_language_string(label_cancel, 24, language_table_cancel);
    lv_obj_center(label_cancel);
    lv_obj_add_flag(label_cancel, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void finger_start_start(void)
{
    gui_algo_data_set_pagelocation("finger_start",0);
    p_finger_start = (finger_start_t*)lv_mem_alloc(sizeof(finger_start_t));
    LV_ASSERT(p_finger_start);
    lv_memset(p_finger_start, 0, sizeof(finger_start_t));

    p_finger_start->bg_cont = gui_comm_draw_bg();
    finger_start_bg_cont(p_finger_start->bg_cont);
    
	p_finger_start->timer = lv_timer_create(timer_cb, 1000, NULL);
}

 void finger_start_stop(void)
{
    lv_timer_del(p_finger_start->timer);
    lv_obj_del(p_finger_start->bg_cont);
    lv_mem_free(p_finger_start);
    p_finger_start = NULL;
}
