/*********************
 *      INCLUDES
 *********************/

#include "startup_invalid_recovery.h"
#include "gui_comm.h"
#include "gui_data_comm.h"
#include "gui_language_comm.h"


static startup_invalid_recovery_t* p_startup_invalid_recovery = NULL;
extern void startup_ready_check_start(void);


static void finger_start_try_again_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
	    startup_invalid_recovery_stop();
	    startup_ready_check_start();
    }
}

static void startup_invalid_recovery_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* error_icons = lv_img_create(parent);
    lv_img_set_src(error_icons, &img_error);
    lv_obj_set_pos(error_icons, 40, 69);

    lv_obj_t* title = lv_label_create(parent);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(title, 400);
    lv_obj_set_pos(title, 90, 60);
    set_language_string(title, 40, language_table_invalid_recovery_phrase);

    lv_obj_t* label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 400);
    lv_obj_set_pos(label_describe, 40, 168);
    set_language_string(label_describe, 24, language_table_recovery_phrase_invalid);

    lv_obj_t* btn_try_again = gui_comm_draw_obj(parent, 40, 684, 400, 80, 0x7FF, 0xCCB68C, 0xA4916F);
    lv_obj_add_event_cb(btn_try_again, finger_start_try_again_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_try_again = lv_label_create(btn_try_again);
    lv_obj_set_style_text_color(label_try_again, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_try_again, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_try_again, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_try_again, 400);
    set_language_string(label_try_again, 24, language_table_try_again);
    lv_obj_center(label_try_again);
    lv_obj_add_flag(label_try_again, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}

void startup_invalid_recovery_start(void)
{
    gui_algo_data_set_pagelocation("startup_invalid_recovery",0);
    p_startup_invalid_recovery = (startup_invalid_recovery_t*)lv_mem_alloc(sizeof(startup_invalid_recovery_t));
    LV_ASSERT(p_startup_invalid_recovery);
    lv_memset(p_startup_invalid_recovery, 0, sizeof(startup_invalid_recovery_t));

    p_startup_invalid_recovery->bg_cont = gui_comm_draw_bg();
    startup_invalid_recovery_bg_cont(p_startup_invalid_recovery->bg_cont);
}

 void startup_invalid_recovery_stop(void)
{
    lv_obj_del(p_startup_invalid_recovery->bg_cont);
    lv_mem_free(p_startup_invalid_recovery);
    p_startup_invalid_recovery = NULL;
}
