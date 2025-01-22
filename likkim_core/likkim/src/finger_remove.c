/*********************
 *      INCLUDES
 *********************/

#include "finger_remove.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


extern void finger_add_start(void);
extern void finger_remove2_start(void);

static finger_remove_t* p_finger_remove = NULL;


static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
	    finger_remove_stop();
	    finger_add_start();
    }
}

static void finger_start_remove_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        finger_remove_stop();
	    finger_remove2_start();
    }
}

static void finger_remove_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* back_icons = lv_img_create(parent);
    lv_img_set_src(back_icons, &img_back);
    lv_obj_set_pos(back_icons, 40, 16);
    lv_obj_add_event_cb(back_icons, title_cb, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_add_flag(back_icons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
	
	lv_obj_t *label_title = lv_label_create(parent);
	lv_obj_set_style_text_font(label_title, &font_40, 0);
	lv_obj_set_style_text_color(label_title, lv_color_hex(0xffffff), 0);
	lv_label_set_long_mode(label_title, LV_LABEL_LONG_DOT);
	lv_obj_set_width(label_title, 300);
	lv_obj_set_pos(label_title, 40, 60);
	lv_label_set_text_fmt(label_title, "%s %d", language_table_finger[gui_data_get_language_type()], gui_data_get_fingerprint_remove_id());

    lv_obj_t* btn_remove = gui_comm_draw_obj(parent, 40, 684, 400, 80, 0x7FF, 0xFF2600, 0x771200);
    lv_obj_add_event_cb(btn_remove, finger_start_remove_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_remove = lv_label_create(btn_remove);
    lv_obj_set_style_text_color(label_remove, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_remove, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_remove, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_remove, 190);
    set_language_string(label_remove, 24, language_table_remove);
    lv_obj_center(label_remove);
    lv_obj_add_flag(label_remove, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void finger_remove_start(void)
{
   gui_algo_data_set_pagelocation("finger_remove",0);
    p_finger_remove = (finger_remove_t*)lv_mem_alloc(sizeof(finger_remove_t));
    LV_ASSERT(p_finger_remove);
    lv_memset(p_finger_remove, 0, sizeof(finger_remove_t));

    p_finger_remove->bg_cont = gui_comm_draw_bg();
    finger_remove_bg_cont(p_finger_remove->bg_cont);
}

 void finger_remove_stop(void)
{
    lv_obj_del(p_finger_remove->bg_cont);
    lv_mem_free(p_finger_remove);
    p_finger_remove = NULL;
}
