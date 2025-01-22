/*********************
 *      INCLUDES
 *********************/

#include "startup_ready_check.h"
#include "gui_comm.h"
#include "gui_data_comm.h"
#include "gui_language_comm.h"
#include "CalControlPara.h"

extern void startup_quick_start_start(void);
extern void startup_recovery_start(void);
extern void view_ready_waiting_start(void);

uint8_t walletCreate =0;



static startup_ready_check_t* p_startup_ready_check = NULL;


static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        startup_ready_check_stop();
        startup_quick_start_start();
    }
}

static void startup_btn_event_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);
    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
		int ret = atoi(e->user_data);

		printf("%s, ret : %d\n", (char *)e->user_data, ret);
		gui_data_set_word_num(ret);
        
        if(ret ==12||ret==18||ret==24)  //判断单词数量
        walletCreate =ret;

        startup_ready_check_stop();
        view_ready_waiting_start();

            
        
    }
}

static void startup_ready_check_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_ready_to_check, title_cb);

    lv_obj_t* describe_label = lv_label_create(parent);
    lv_obj_set_style_text_color(describe_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(describe_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(describe_label, 400);
    lv_obj_set_pos(describe_label, 40, 120);
	set_language_string(describe_label, 24, language_table_select_number_of_words);
    lv_obj_add_flag(describe_label, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* btn_word12 = gui_comm_draw_obj(parent, 40, 169, 400, 52, 15, 0x888888, 0x666666);
    lv_obj_add_event_cb(btn_word12, startup_btn_event_handler, LV_EVENT_SHORT_CLICKED, "12");

    lv_obj_t* label_words12 = lv_label_create(btn_word12);
    lv_obj_set_style_text_color(label_words12, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_words12, &font_24, 0);
    lv_obj_set_style_text_align(label_words12, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_words12, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_words12, 400);

    lv_label_set_text_fmt(label_words12, "12 %s", (char *)language_table_words[gui_data_get_language_type()]);
    lv_obj_center(label_words12);
    lv_obj_add_flag(label_words12, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* btn_word18 = gui_comm_draw_obj(parent, 40, 229, 400, 52, 15, 0x888888, 0x666666);
    lv_obj_add_event_cb(btn_word18, startup_btn_event_handler, LV_EVENT_SHORT_CLICKED, "18");

    lv_obj_t* label_words18 = lv_label_create(btn_word18);
    lv_obj_set_style_text_color(label_words18, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_words18, &font_24, 0);
    lv_obj_set_style_text_align(label_words18, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_words18, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_words18, 400);
    lv_label_set_text_fmt(label_words18, "18 %s", (char *)language_table_words[gui_data_get_language_type()]);
    lv_obj_center(label_words18);
    lv_obj_add_flag(label_words18, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* btn_word24 = gui_comm_draw_obj(parent, 40, 289, 400, 52, 15, 0x888888, 0x666666);
    lv_obj_add_event_cb(btn_word24, startup_btn_event_handler, LV_EVENT_SHORT_CLICKED, "24");

    lv_obj_t* label_words24 = lv_label_create(btn_word24);
    lv_obj_set_style_text_color(label_words24, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_words24, &font_24, 0);
    lv_obj_set_style_text_align(label_words24, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_words24, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_words24, 400);
    lv_label_set_text_fmt(label_words24, "24 %s", language_table_words[gui_data_get_language_type()]);
    lv_obj_center(label_words24);
    lv_obj_add_flag(label_words24, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void startup_ready_check_start(void)
{
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("startup_ready_check",0);
    p_startup_ready_check = (startup_ready_check_t*)lv_mem_alloc(sizeof(startup_ready_check_t));
    LV_ASSERT(p_startup_ready_check);
    lv_memset(p_startup_ready_check, 0, sizeof(startup_ready_check_t));

    p_startup_ready_check->bg_cont = gui_comm_draw_bg();
    startup_ready_check_bg_cont(p_startup_ready_check->bg_cont);
}

void startup_ready_check_stop(void)
{
    lv_obj_del(p_startup_ready_check->bg_cont);
    lv_mem_free(p_startup_ready_check);
    p_startup_ready_check = NULL;
}


