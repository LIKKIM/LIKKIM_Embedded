/*********************
 *      INCLUDES
 *********************/

#include "view_transaction_confirm.h"
#include "gui_comm.h"

extern void view_transaction_main_start(void);
extern void view_transaction_waiting_start(void);


static view_transaction_confirm_t* p_view_transaction_confirm = NULL;


static void timer_cb(lv_timer_t * tmr)
{
    if(1)
    {
        view_transaction_confirm_stop();
        view_transaction_waiting_start();
    }
}

static void slider_cb(void)
{
	lv_obj_clear_flag(p_view_transaction_confirm->slider, LV_OBJ_FLAG_CLICKABLE);
	p_view_transaction_confirm->timer = lv_timer_create(timer_cb, 100, NULL);
}

static void reject_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        view_transaction_confirm_stop();
        view_transaction_main_start();
        printf("Signed_OK");
        send_serial_data("Signed_OK");
    }
}

static void view_transaction_confirm_bg_cont(lv_obj_t* parent)
{
    lv_obj_t *title = lv_label_create(parent);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(title, LV_LABEL_LONG_DOT);
    lv_obj_set_width(title, 400);
    lv_obj_set_pos(title, 40, 60);
	set_language_string(title, 40, language_table_confirm_transaction);
    
    lv_obj_t* describe_label = lv_label_create(parent);
    lv_obj_set_style_text_color(describe_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(describe_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(describe_label, 400);
    lv_obj_set_pos(describe_label, 40, 120);
	set_language_string(describe_label, 24, language_table_sign_transaction);
    
	p_view_transaction_confirm->slider = gui_comm_draw_slider(parent, 598, slider_cb);
	
    lv_obj_t* img_btn_reject = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0x888888, 0x666666);
    lv_obj_add_event_cb(img_btn_reject, reject_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_reject = lv_label_create(img_btn_reject);
    lv_obj_set_style_text_color(label_reject, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_reject, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_reject, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_reject, 400);
	set_language_string(label_reject, 24, language_table_reject);
    lv_obj_center(label_reject);
    lv_obj_add_flag(label_reject, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

}


void view_transaction_confirm_start(void)
{
    gui_algo_data_set_pagelocation("view_transaction_confirm",0);
    p_view_transaction_confirm = (view_transaction_confirm_t*)lv_mem_alloc(sizeof(view_transaction_confirm_t));
    LV_ASSERT(p_view_transaction_confirm);
    lv_memset(p_view_transaction_confirm, 0, sizeof(view_transaction_confirm_t));

    p_view_transaction_confirm->bg_cont = gui_comm_draw_bg();
    view_transaction_confirm_bg_cont(p_view_transaction_confirm->bg_cont);
}

 void view_transaction_confirm_stop(void)
{
    if(p_view_transaction_confirm->timer != NULL)
        lv_timer_del(p_view_transaction_confirm->timer);
    lv_obj_del(p_view_transaction_confirm->bg_cont);
    p_view_transaction_confirm->bg_cont = NULL;
    lv_mem_free(p_view_transaction_confirm);
    p_view_transaction_confirm = NULL;
}
