/*********************
 *      INCLUDES
 *********************/

#include "startup_recovery.h"
#include "gui_comm.h"
#include "gui_data_comm.h"
#include "gui_language_comm.h"
#include "CalControlPara.h"

static gui_comm_imgbtn_desc_t startup_imgbtn_num_table[] =
{
    {NULL, 38, 0},
    {NULL, 246, 0},
    {NULL, 38, 60},
    {NULL, 246, 60},
    {NULL, 38, 120},
    {NULL, 246, 120},
    {NULL, 38, 180},
    {NULL, 246, 180},
    {NULL, 38, 240},
    {NULL, 246, 240},
    {NULL, 38, 300},
    {NULL, 246, 300},
    {NULL, 38, 360},
    {NULL, 246, 360},
    {NULL, 38, 420},
    {NULL, 246, 420},
    {NULL, 38, 480},
    {NULL, 246, 480},
    {NULL, 38, 540},
    {NULL, 246, 540},
    {NULL, 38, 600},
    {NULL, 246, 600},
    {NULL, 38, 660},
    {NULL, 246, 660},
};

extern void startup_done_start(void);
extern void startup_ready_check_start(void);


static startup_recovery_t* p_startup_recovery = NULL;

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        startup_recovery_stop();
        startup_ready_check_start();
    }
}

static void startup_recovery_word_btn_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        printf("%s\n", (char *)e->user_data);
    }
}

static void startup_recovery_continue_btn_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
        startup_recovery_stop();
        startup_done_start();
    }
}
static void startup_recovery_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_recovery_phrase, title_cb);

    lv_obj_t* label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_describe, &font_24, 0);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
	lv_label_set_text_fmt(label_describe, language_table_write_down_following[gui_data_get_language_type()], gui_data_get_word_num());
    lv_obj_set_width(label_describe, 400);
    lv_obj_set_pos(label_describe, 40, 120);
    lv_obj_update_layout(label_describe);

    lv_obj_t* img_btn_continue = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0xCCB68C, 0xA4916F);
    lv_obj_add_event_cb(img_btn_continue, startup_recovery_continue_btn_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_continue = lv_label_create(img_btn_continue);
    lv_obj_set_style_text_color(label_continue, lv_color_hex(0xffffff), 0);
	set_language_string(label_continue, 24, language_table_continue);
    lv_obj_align(label_continue, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(label_continue, LV_OBJ_FLAG_EVENT_BUBBLE);
    
    lv_obj_t *bg_obj = lv_obj_create(parent);
    lv_obj_remove_style_all(bg_obj);
	lv_obj_set_scroll_dir(bg_obj, LV_DIR_VER);
	lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bg_obj, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_size(bg_obj, 480, 650 - 20 - label_describe->coords.y2 + 20);
    lv_obj_set_pos(bg_obj, 0, label_describe->coords.y2 + 20);

    for (uint8_t i = 0; i < gui_data_get_word_num(); i++)
    {
        lv_obj_t* img_btn = gui_comm_draw_obj(bg_obj, startup_imgbtn_num_table[i].x, startup_imgbtn_num_table[i].y, 196, 52, 15, 0x888888, 0x666666);

        lv_obj_t* label = lv_label_create(img_btn);
		lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
		lv_obj_set_style_text_font(label, &font_24, 0);
        printf("startup_recovery:%d. %s", i + 1,gui_data_get_word(i));
        lv_label_set_text_fmt(label, "%d. %s", i + 1,gui_data_get_word(i));
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }
}


void startup_recovery_start(void)
{
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("startup_recovery",0);
    p_startup_recovery = (startup_recovery_t*)lv_mem_alloc(sizeof(startup_recovery_t));
    LV_ASSERT(p_startup_recovery);
    lv_memset(p_startup_recovery, 0, sizeof(startup_recovery_t));

    p_startup_recovery->bg_cont = gui_comm_draw_bg();
    startup_recovery_bg_cont(p_startup_recovery->bg_cont);
}

void startup_recovery_stop(void)
{
    lv_obj_del(p_startup_recovery->bg_cont);
    lv_mem_free(p_startup_recovery);
    p_startup_recovery = NULL;
}


