/*********************
 *      INCLUDES
 *********************/

#include "finger_place.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


extern void finger_add_start(void);
extern void finger_added_start(void);
extern void finger_poweron_start(void);


static finger_place_t* p_finger_place = NULL;


static void timer_cb(lv_timer_t * tmr)
{
	uint8_t process = gui_data_get_fingerprint_process();

	if(process == 1)
    	lv_img_set_src(p_finger_place->finger_icons, &img_fingerprint_1);
	else if(process == 2)
    	lv_img_set_src(p_finger_place->finger_icons, &img_fingerprint_2);
	else if(process == 3)
    	lv_img_set_src(p_finger_place->finger_icons, &img_fingerprint_3);
	else if(process == 4)
    	lv_img_set_src(p_finger_place->finger_icons, &img_fingerprint_4);
	else if(process == 5)
    	lv_img_set_src(p_finger_place->finger_icons, &img_fingerprint_5);
	else if(process == 6)
    	lv_img_set_src(p_finger_place->finger_icons, &img_fingerprint_6);
	else if(process == 7)
	{
		uint8_t num = gui_data_get_fingerprint_num();
		gui_data_set_fingerprint_num(num + 1);
	    finger_place_stop();
	    finger_added_start();
	}

	/*测试*/
	gui_data_set_fingerprint_process(process + 1);
}

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
	    finger_place_stop();
	    if(gui_data_get_first_poweron())
			finger_poweron_start();
		else
		    finger_add_start();
    }
}

static void finger_place_cancle_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
        finger_place_stop();
	    if(gui_data_get_first_poweron())
			finger_poweron_start();
		else
		    finger_add_start();
    }
}
static void finger_place_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_place_finger, title_cb);

    lv_obj_t* label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 400);
    lv_obj_set_pos(label_describe, 40, 117);
    set_language_string(label_describe, 24, language_table_put_finger_power_button);

    lv_obj_t* finger_icons = lv_img_create(parent);
    lv_img_set_src(finger_icons, &img_fingerprint_1);
    lv_obj_set_pos(finger_icons, 140, 264);
	p_finger_place->finger_icons = finger_icons;
	
    label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xF7E100), 0);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 400);
    lv_obj_set_pos(label_describe, 40, 606);
    set_language_string(label_describe, 24, language_table_lift_and_touch_power_button);

    lv_obj_t* btn_cancle = gui_comm_draw_obj(parent, 40, 684, 400, 80, 0x7FF, 0x888888, 0x666666);
    lv_obj_add_event_cb(btn_cancle, finger_place_cancle_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_cancel = lv_label_create(btn_cancle);
    lv_obj_set_style_text_color(label_cancel, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_cancel, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_cancel, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_cancel, 400);
    set_language_string(label_cancel, 24, language_table_cancel);
    lv_obj_center(label_cancel);
    lv_obj_add_flag(label_cancel, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

}


void finger_place_start(void)
{
    gui_algo_data_set_pagelocation("finger_place",0);
    p_finger_place = (finger_place_t*)lv_mem_alloc(sizeof(finger_place_t));
    LV_ASSERT(p_finger_place);
    lv_memset(p_finger_place, 0, sizeof(finger_place_t));

    p_finger_place->bg_cont = gui_comm_draw_bg();
    finger_place_bg_cont(p_finger_place->bg_cont);
	p_finger_place->timer = lv_timer_create(timer_cb, 1000, NULL);
}

 void finger_place_stop(void)
{
    lv_timer_del(p_finger_place->timer);
    lv_obj_del(p_finger_place->bg_cont);
    lv_mem_free(p_finger_place);
    p_finger_place = NULL;
}
