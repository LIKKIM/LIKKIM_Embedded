/*********************
 *      INCLUDES
 *********************/

#include "startup_done.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

extern void startup_recovery_start(void);
extern void startup_verification_start(void);

static startup_done_t* p_startup_done = NULL;


static void startup_done_back_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        startup_done_stop();
        startup_recovery_start();
    }
}
static void startup_done_continue_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
        startup_done_stop();
        startup_verification_start();
    }
}
static void startup_done_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_almost_done, NULL);

    lv_obj_t* label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
	set_language_string(label_describe, 24, language_table_follow_the_guide);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 400);
    lv_obj_set_pos(label_describe, 40, 120);

    lv_obj_t* img_btn_back = gui_comm_draw_obj(parent, 40, 690, 192, 80, 0x7FFF, 0x888888, 0x666666);
    lv_obj_add_event_cb(img_btn_back, startup_done_back_handler, LV_EVENT_SHORT_CLICKED, NULL);
    
    lv_obj_t* label_back = lv_label_create(img_btn_back);
    lv_obj_set_style_text_color(label_back, lv_color_hex(0xffffff), 0);
	set_language_string(label_back, 24, language_table_back);
    lv_obj_align(label_back, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(label_back, LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* img_btn_continue = gui_comm_draw_obj(parent, 248, 690, 192, 80, 0x7FFF, 0xCCB68C, 0xA4916F);
    lv_obj_add_event_cb(img_btn_continue, startup_done_continue_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_continue = lv_label_create(img_btn_continue);
    lv_obj_set_style_text_color(label_continue, lv_color_hex(0xffffff), 0);
	set_language_string(label_continue, 24, language_table_continue);
    lv_obj_align(label_continue, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(label_continue, LV_OBJ_FLAG_EVENT_BUBBLE);
}


void startup_done_start(void)
{
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("startup_done",0);
    p_startup_done = (startup_done_t*)lv_mem_alloc(sizeof(startup_done_t));
    LV_ASSERT(p_startup_done);
    lv_memset(p_startup_done, 0, sizeof(startup_done_t));

    p_startup_done->bg_cont = gui_comm_draw_bg();
    startup_done_bg_cont(p_startup_done->bg_cont);
}

void startup_done_stop(void)
{
    lv_obj_del(p_startup_done->bg_cont);
    lv_mem_free(p_startup_done);
    p_startup_done = NULL;
}

