/*********************
 *      INCLUDES
 *********************/

#include "startup_quick_start.h"
#include "gui_comm.h"
#include "gui_data_comm.h"
#include "CalControlPara.h"

extern void startup_set_pin_start(app_index_t app_index);
extern void startup_language_start(app_index_t app_index);


uint8_t WalletSignFlag =0;

static startup_quick_start_t* p_startup_quick_start = NULL;

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        startup_quick_start_stop();
        startup_language_start(APP_STARTUP);
    }
}

static void startup_create_wallet_event_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        //创建钱包
    	gui_comm_do_shake(1);
        startup_quick_start_stop();
        startup_set_pin_start(APP_STARTUP_CREATE_WALLET);
    }
}

static void startup_import_wallet_event_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        //导入钱包
    	gui_comm_do_shake(1);
        startup_quick_start_stop();
        startup_set_pin_start(APP_STARTUP_IMPORT_WALLET);
    }
}

static void startup_quick_start_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_quick_start, title_cb);

    lv_obj_t* describe_label = lv_label_create(parent);
    lv_obj_set_style_text_color(describe_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(describe_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(describe_label, 400);
    lv_obj_set_pos(describe_label, 40, 120);
    set_language_string(describe_label, 24, language_table_create_wallet_or_restore);
    lv_obj_add_flag(describe_label, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* img_btn_create = gui_comm_draw_obj(parent, 40, 598, 400, 80, 0x7FFF, 0xCCB68C, 0xA4916F);
    lv_obj_add_event_cb(img_btn_create, startup_create_wallet_event_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* create_label = lv_label_create(img_btn_create);
    lv_obj_set_style_text_color(create_label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(create_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(create_label, LV_LABEL_LONG_DOT);
    lv_obj_set_width(create_label, 400);
    set_language_string(create_label, 24, language_table_create_wallet);
    lv_obj_center(create_label);
    lv_obj_add_flag(create_label, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* img_btn_import = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0x888888, 0x666666);
    lv_obj_add_event_cb(img_btn_import, startup_import_wallet_event_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* import_label = lv_label_create(img_btn_import);
    lv_obj_set_style_text_color(import_label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(import_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(import_label, LV_LABEL_LONG_DOT);
    lv_obj_set_width(import_label, 400);
    set_language_string(import_label, 24, language_table_import_wallet);
    lv_obj_center(import_label);
    lv_obj_add_flag(import_label, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void startup_quick_start_start(void)
{
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("startup_quick_start",0);
    p_startup_quick_start = (startup_quick_start_t*)lv_mem_alloc(sizeof(startup_quick_start_t));
    LV_ASSERT(p_startup_quick_start);
    lv_memset(p_startup_quick_start, 0, sizeof(startup_quick_start_t));

    p_startup_quick_start->bg_cont = gui_comm_draw_bg();
    startup_quick_start_bg_cont(p_startup_quick_start->bg_cont);
}

void startup_quick_start_stop(void)
{
    lv_obj_del(p_startup_quick_start->bg_cont);
    lv_mem_free(p_startup_quick_start);
    p_startup_quick_start = NULL;
}

