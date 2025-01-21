/*********************
 *      INCLUDES
 *********************/

#include "view_transaction_main.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

extern void settings_security_start(void);
extern void view_transaction_confirm_start(void);


static view_transaction_main_t* p_view_transaction_main = NULL;

static void continue_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        view_transaction_main_stop();
		printf("view_transaction_confirm_start!!!!!!\r\n");
		view_transaction_confirm_start();
    }
}

static void reject_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        view_transaction_main_stop();
		gui_algo_data_get_pagelocationsave("start");
        // settings_security_start();
    }
}

static void view_transaction_main_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* title = lv_label_create(parent);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(title, 400);
    lv_obj_set_pos(title, 40, 60); 
	set_language_string(title, 40, language_table_view_transaction);
/*滑动区域*/

/*第一个滑动框*/
	lv_obj_t *bg_obj = lv_obj_create(parent);
	lv_obj_remove_style_all(bg_obj);
	lv_obj_set_scroll_dir(bg_obj, LV_DIR_VER);
	lv_obj_set_scrollbar_mode(bg_obj, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(bg_obj, LV_OPA_COVER, LV_PART_MAIN);
	lv_obj_set_size(bg_obj, 400, 450);
	lv_obj_set_pos(bg_obj, 40, 128);

	lv_obj_t *bg_obj_directions = lv_obj_create(bg_obj);
	lv_obj_remove_style_all(bg_obj_directions);
	lv_obj_set_scrollbar_mode(bg_obj_directions, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_bg_color(bg_obj_directions, lv_color_hex(0x888888), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(bg_obj_directions, LV_OPA_COVER, LV_PART_MAIN);
	lv_obj_set_style_radius(bg_obj_directions, 15, LV_PART_MAIN);
	lv_obj_set_pos(bg_obj_directions, 0, 0);

	lv_obj_t *obj_line1 = lv_obj_create(bg_obj_directions);
	lv_obj_set_style_bg_color(obj_line1, lv_color_hex(0x475358), LV_PART_MAIN);
	lv_obj_set_size(obj_line1, 320, 2);
	lv_obj_set_pos(obj_line1, 40, 71);

	lv_obj_t* label_directions = lv_label_create(bg_obj_directions);
	lv_obj_set_style_text_color(label_directions, lv_color_hex(0xffffff), 0); 
	lv_label_set_long_mode(label_directions, LV_LABEL_LONG_WRAP);
	lv_obj_set_width(label_directions, 320);
	lv_obj_set_pos(label_directions, 40, 20); 
	set_language_string(label_directions, 24, language_table_directions);
	lv_obj_update_layout(label_directions);

	lv_obj_t* label_fee = lv_label_create(bg_obj_directions);
	lv_obj_set_style_text_color(label_fee, lv_color_hex(0xffffff), 0); 
	lv_label_set_long_mode(label_fee, LV_LABEL_LONG_WRAP);
	lv_obj_set_width(label_fee, 320);
	lv_obj_set_pos(label_fee, 40, 88); 
	set_language_string(label_fee, 24, language_table_fee_payer);
	lv_obj_update_layout(label_fee);

	lv_obj_t* label_fee_content = lv_label_create(bg_obj_directions);
	lv_obj_set_style_text_color(label_fee_content, lv_color_hex(0xffffff), 0);
	lv_obj_set_style_text_font(label_fee_content, &font_24, 0);
	lv_label_set_long_mode(label_fee_content, LV_LABEL_LONG_WRAP);
	lv_obj_set_width(label_fee_content, 320);
	lv_obj_set_pos(label_fee_content, 40, 140);
	lv_label_set_text(label_fee_content, gui_data_get_transaction_fee_payer());
	lv_obj_update_layout(label_fee_content);
	lv_obj_set_size(bg_obj_directions, 400, lv_obj_get_height(label_fee_content) + 140 + 20);

/*第二个滑动框*/
	lv_obj_t *bg_obj_more = lv_obj_create(bg_obj);
	lv_obj_remove_style_all(bg_obj_more);
	lv_obj_set_scrollbar_mode(bg_obj_more, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_bg_color(bg_obj_more, lv_color_hex(0x888888), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(bg_obj_more, LV_OPA_COVER, LV_PART_MAIN);
	lv_obj_set_style_radius(bg_obj_more, 15, LV_PART_MAIN);

	lv_obj_t *obj_line2 = lv_obj_create(bg_obj_more);
	lv_obj_set_style_bg_color(obj_line2, lv_color_hex(0x475358), LV_PART_MAIN);
	lv_obj_set_size(obj_line2, 320, 2);
	lv_obj_set_pos(obj_line2, 40, 71);

	lv_obj_t* label_more = lv_label_create(bg_obj_more);
	lv_obj_set_style_text_color(label_more, lv_color_hex(0xffffff), 0);
	lv_label_set_long_mode(label_more, LV_LABEL_LONG_WRAP);
	lv_obj_set_width(label_more, 320);
	lv_obj_set_pos(label_more, 40, 20); 
	set_language_string(label_more, 24, language_table_more);
	lv_obj_update_layout(label_more);

	lv_obj_t* label_format = lv_label_create(bg_obj_more);
	lv_obj_set_style_text_color(label_format, lv_color_hex(0xffffff), 0);
	lv_label_set_long_mode(label_format, LV_LABEL_LONG_WRAP);
	lv_obj_set_width(label_format, 320);
	lv_obj_set_pos(label_format, 40, 88); 
	set_language_string(label_format, 24, language_table_format);
	lv_obj_update_layout(label_format);

	lv_obj_t* label_format_content = lv_label_create(bg_obj_more);
	lv_obj_set_style_text_color(label_format_content, lv_color_hex(0xffffff), 0);
	lv_obj_set_style_text_font(label_format_content, &font_24, 0);
	lv_label_set_long_mode(label_format_content, LV_LABEL_LONG_WRAP);
	lv_obj_set_width(label_format_content, 320);
	lv_obj_set_pos(label_format_content, 40, 140);
	lv_label_set_text(label_format_content, gui_data_get_transaction_format());
	lv_obj_update_layout(label_format_content);

	lv_obj_t* label_hash = lv_label_create(bg_obj_more);
	lv_obj_set_style_text_color(label_hash, lv_color_hex(0xffffff), 0);
	lv_label_set_long_mode(label_hash, LV_LABEL_LONG_WRAP);
	lv_obj_set_width(label_hash, 320);
	lv_obj_align_to(label_hash, label_format_content, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
	set_language_string(label_hash, 24, language_table_message_hash);
	lv_obj_update_layout(label_hash);

	lv_obj_t* label_hash_content = lv_label_create(bg_obj_more);
	lv_obj_set_style_text_color(label_hash_content, lv_color_hex(0xffffff), 0);
	lv_obj_set_style_text_font(label_hash_content, &font_24, 0);
	lv_label_set_long_mode(label_hash_content, LV_LABEL_LONG_WRAP);
	lv_obj_set_width(label_hash_content, 320);
	lv_obj_align_to(label_hash_content, label_hash, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
	lv_label_set_text(label_hash_content, gui_data_get_transaction_hash());
	lv_obj_update_layout(label_hash_content);

	lv_obj_set_size(bg_obj_more, 400, label_hash_content->coords.y2 + 20);
	lv_obj_align_to(bg_obj_more, bg_obj_directions, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

/*底部按键*/
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


void view_transaction_main_start(void)
{
	gui_algo_data_set_pagelocation("view_transaction_main",0);
    p_view_transaction_main = (view_transaction_main_t*)lv_mem_alloc(sizeof(view_transaction_main_t));
    LV_ASSERT(p_view_transaction_main);
    lv_memset(p_view_transaction_main, 0, sizeof(view_transaction_main_t));

    p_view_transaction_main->bg_cont = gui_comm_draw_bg();
    view_transaction_main_bg_cont(p_view_transaction_main->bg_cont);
}

 void view_transaction_main_stop(void)
{
    lv_obj_del(p_view_transaction_main->bg_cont);
    lv_mem_free(p_view_transaction_main);
    p_view_transaction_main = NULL;
}
