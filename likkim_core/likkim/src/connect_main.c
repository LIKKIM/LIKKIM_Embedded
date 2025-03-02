/*********************
 *      INCLUDES
 *********************/

#include "connect_main.h"
#include "gui_comm.h"
#include "CalControlPara.h"

extern void menu_main_start(void);
extern uint16_t PIN_number;//PIN

static connect_main_t* p_connect_main = NULL;

static void connect_main_word_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        connect_main_stop();
        gui_algo_data_get_pagelocationsave("start");
        // menu_main_start();

    }
}
static void connect_main_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* label_title = lv_label_create(parent);
    lv_obj_set_style_text_color(label_title, lv_color_hex(0xffffff), 0);
    set_language_string(label_title, 40, language_table_conection_app_wallet);
    lv_label_set_long_mode(label_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_title, 400);
    lv_obj_set_pos(label_title, 40, 60);

    lv_obj_t* label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
    set_language_string(label_describe, 24, language_table_bluetooth_pairing);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 400);
    lv_obj_set_pos(label_describe, 40, 120);

    lv_obj_t* img_btn_pair = gui_comm_draw_obj(parent, 40, 238, 400, 160, 15, 0xCCB68C, 0xA4916F);
    lv_obj_add_event_cb(img_btn_pair, connect_main_word_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_pair = lv_label_create(img_btn_pair);
    lv_obj_set_style_text_color(label_pair, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_pair, &font_40, 0);
    lv_label_set_text(label_pair, uint16_to_str(PIN_number));
    lv_obj_align(label_pair, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(label_pair, LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* img_btn_close = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0x888888, 0x666666);
    lv_obj_add_event_cb(img_btn_close, connect_main_word_handler, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_close = lv_label_create(img_btn_close);
    lv_obj_set_style_text_color(label_close, lv_color_hex(0xffffff), 0);
    set_language_string(label_close, 24, language_table_close);
    lv_obj_align(label_close, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(label_close, LV_OBJ_FLAG_EVENT_BUBBLE);
}


void connect_main_start(void)
{
    gui_algo_data_set_pagelocation("connect_main",0);
    p_connect_main = (connect_main_t*)lv_mem_alloc(sizeof(connect_main_t));
    LV_ASSERT(p_connect_main);
    lv_memset(p_connect_main, 0, sizeof(connect_main_t));

    p_connect_main->bg_cont = gui_comm_draw_bg();
    connect_main_bg_cont(p_connect_main->bg_cont);
}

 void connect_main_stop(void)
{
    lv_obj_del(p_connect_main->bg_cont);
    p_connect_main->bg_cont = NULL;
    lv_mem_free(p_connect_main);
    p_connect_main = NULL;
}
