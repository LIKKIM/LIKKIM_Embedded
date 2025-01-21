/*********************
 *      INCLUDES
 *********************/

#include "startup_import_wallet.h"
#include "gui_comm.h"



extern void startup_import_abort_start(void);
extern void startup_import_word_start(void);

static startup_import_wallet_t* p_startup_import_wallet = NULL;


static void continue_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        startup_import_wallet_stop();
		startup_import_word_start();
    }
}

static void cancel_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        startup_import_wallet_stop();
		startup_import_abort_start();
    }
}

static void startup_import_wallet_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* title_label = lv_label_create(parent);
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(title_label, 400);
    lv_obj_set_pos(title_label, 40, 60);
	set_language_string(title_label, 40, language_table_import_wallet);
    
    lv_obj_t* describe_label = lv_label_create(parent);
    lv_obj_set_style_text_color(describe_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(describe_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(describe_label, 400);
    lv_obj_set_pos(describe_label, 40, 120);
	set_language_string(describe_label, 24, language_table_import_recovery_phrase);
	
    lv_obj_t* img_btn_continue = gui_comm_draw_obj(parent, 40, 598, 400, 80, 0x7FFF, 0xCCB68C, 0xA4916F);
    lv_obj_add_event_cb(img_btn_continue, continue_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_continue = lv_label_create(img_btn_continue);
    lv_obj_set_style_text_color(label_continue, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_continue, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_continue, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_continue, 400);
	set_language_string(label_continue, 24, language_table_continue);
    lv_obj_center(label_continue);
    lv_obj_add_flag(label_continue, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
    
    lv_obj_t* img_btn_cancel = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0x888888, 0x666666);
    lv_obj_add_event_cb(img_btn_cancel, cancel_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_cancel = lv_label_create(img_btn_cancel);
    lv_obj_set_style_text_color(label_cancel, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_cancel, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_cancel, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_cancel, 400);
	set_language_string(label_cancel, 24, language_table_cancel);
    lv_obj_center(label_cancel);
    lv_obj_add_flag(label_cancel, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void startup_import_wallet_start(void)
{
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("startup_import_wallet",0);
    p_startup_import_wallet = (startup_import_wallet_t*)lv_mem_alloc(sizeof(startup_import_wallet_t));
    LV_ASSERT(p_startup_import_wallet);
    lv_memset(p_startup_import_wallet, 0, sizeof(startup_import_wallet_t));

    p_startup_import_wallet->bg_cont = gui_comm_draw_bg();
    startup_import_wallet_bg_cont(p_startup_import_wallet->bg_cont);
}

void startup_import_wallet_stop(void)
{
    lv_obj_del(p_startup_import_wallet->bg_cont);
    lv_mem_free(p_startup_import_wallet);
    p_startup_import_wallet = NULL;
}


