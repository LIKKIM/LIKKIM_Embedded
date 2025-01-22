/*********************
 *      INCLUDES
 *********************/

#include "startup_incorrect_word.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

extern void startup_recovery_start(void);

static startup_incorrect_word_t* p_startup_incorrect_word = NULL;


static void try_again_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	startup_incorrect_word_stop();
		startup_recovery_start();
    }
}
static void startup_incorrect_word_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* img_err = lv_img_create(parent);
	lv_img_set_src(img_err, &img_error);
    lv_obj_set_pos(img_err, 40, 69);
	
    lv_obj_t* label_title = lv_label_create(parent);
	lv_obj_set_style_text_color(label_title, lv_color_hex(0xffffff), 0);
	set_language_string(label_title, 40, language_table_incorrect_word);
    lv_obj_set_pos(label_title, 90, 60);

    lv_obj_t* label_describe1 = lv_label_create(parent);
	lv_obj_set_style_text_color(label_describe1, lv_color_hex(0xffffff), 0);
	set_language_string(label_describe1, 24, language_table_wrong_word_check_again);
    lv_label_set_long_mode(label_describe1, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe1, 400);
    lv_obj_set_pos(label_describe1, 40, 120);

    lv_obj_t* img_btn_try_again = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0xCCB68C, 0xA4916F);
    lv_obj_add_event_cb(img_btn_try_again, try_again_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_try_again = lv_label_create(img_btn_try_again);
	lv_obj_set_style_text_color(label_try_again, lv_color_hex(0xffffff), 0);
	set_language_string(label_try_again, 24, language_table_try_again);
    lv_obj_align(label_try_again, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(label_try_again, LV_OBJ_FLAG_EVENT_BUBBLE);
}


void startup_incorrect_word_start(void)
{
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("startup_incorrect_word",0);
    p_startup_incorrect_word = (startup_incorrect_word_t*)lv_mem_alloc(sizeof(startup_incorrect_word_t));
    LV_ASSERT(p_startup_incorrect_word);
    lv_memset(p_startup_incorrect_word, 0, sizeof(startup_incorrect_word_t));

    p_startup_incorrect_word->bg_cont = gui_comm_draw_bg();
    startup_incorrect_word_bg_cont(p_startup_incorrect_word->bg_cont);
}

void startup_incorrect_word_stop(void)
{
    lv_obj_del(p_startup_incorrect_word->bg_cont);
    lv_mem_free(p_startup_incorrect_word);
    p_startup_incorrect_word = NULL;
}


