/*********************
 *      INCLUDES
 *********************/

#include "startup_import_ready.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

extern void menu_main_start(void);

static startup_import_ready_t* p_startup_import_ready = NULL;

static void continue_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
        wallet_Input_word(1);/*导入钱包标志位赋值*/
        gui_data_sueess(1);//錢包生成成功標志位
    	startup_import_ready_stop();
		menu_main_start();
    }
}
static void startup_import_ready_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* img_succ = lv_img_create(parent);
	lv_img_set_src(img_succ, &img_success);
    lv_obj_set_pos(img_succ, 40, 69);

    lv_obj_t* title_label = lv_label_create(parent);
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(title_label, 400);
    lv_obj_set_pos(title_label, 90, 60);
	set_language_string(title_label, 40, language_table_wallet_ready);
    
    lv_obj_t* describe_label = lv_label_create(parent);
    lv_obj_set_style_text_color(describe_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(describe_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(describe_label, 400);
    lv_obj_set_pos(describe_label, 40, 120);
	set_language_string(describe_label, 24, language_table_successfully_recovered_wallet);
    
    lv_obj_t* img_btn_continue = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0x10E807, 0x0A8F04);
    lv_obj_add_event_cb(img_btn_continue, continue_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_continue = lv_label_create(img_btn_continue);
    lv_obj_set_style_text_color(label_continue, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_continue, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_continue, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_continue, 400);
	set_language_string(label_continue, 24, language_table_continue);
    lv_obj_center(label_continue);
    lv_obj_add_flag(label_continue, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void startup_import_ready_start(void)
{
    gui_algo_data_set_pagelocation("startup_import_ready",0);
    p_startup_import_ready = (startup_import_ready_t*)lv_mem_alloc(sizeof(startup_import_ready_t));
    LV_ASSERT(p_startup_import_ready);
    lv_memset(p_startup_import_ready, 0, sizeof(startup_import_ready_t));

    p_startup_import_ready->bg_cont = gui_comm_draw_bg();
    startup_import_ready_bg_cont(p_startup_import_ready->bg_cont);
}

void startup_import_ready_stop(void)
{
    lv_obj_del(p_startup_import_ready->bg_cont);
    lv_mem_free(p_startup_import_ready);
    p_startup_import_ready = NULL;
}


