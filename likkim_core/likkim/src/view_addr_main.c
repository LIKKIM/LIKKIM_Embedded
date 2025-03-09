/*********************
 *      INCLUDES
 *********************/

#include "view_addr_main.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

extern void view_addr_qrcode_start(void);
extern void menu_main_start(void);
static void view_text(lv_obj_t* parent);
static void view_qrcode(lv_obj_t* parent);


static view_addr_main_t* p_view_addr_main = NULL;

static void done_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	printf("%s\n", __func__);
    	view_addr_main_stop();
        //  gui_algo_data_get_pagelocationsave("start");
		menu_main_start();

    }
}

static void qrcode_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	if(p_view_addr_main->page_mode == VIEW_ADDR_MODE_TEXT)
    	{
    		view_qrcode(p_view_addr_main->bg_cont);
			set_language_string(p_view_addr_main->label_qrcode, 24, language_table_address);
    	}
    	else if(p_view_addr_main->page_mode == VIEW_ADDR_MODE_QRCODE)
    	{
    		view_text(p_view_addr_main->bg_cont);
			set_language_string(p_view_addr_main->label_qrcode, 24, language_table_qr_code);
    	}

    	p_view_addr_main->page_mode = !p_view_addr_main->page_mode;
    }
}
static void view_text(lv_obj_t* parent)
{
	if(p_view_addr_main->bg_cont_qrcode)
		lv_obj_add_flag(p_view_addr_main->bg_cont_qrcode, LV_OBJ_FLAG_HIDDEN);
		
	if(p_view_addr_main->bg_cont_text)
		lv_obj_clear_flag(p_view_addr_main->bg_cont_text, LV_OBJ_FLAG_HIDDEN);
	else
	{
	    lv_obj_t *bg_obj = lv_obj_create(parent);
	    lv_obj_remove_style_all(bg_obj);
		lv_obj_set_scrollbar_mode(bg_obj, LV_SCROLLBAR_MODE_OFF);
	    lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x000000), LV_PART_MAIN);
		lv_obj_set_style_bg_opa(bg_obj, LV_OPA_TRANSP, LV_PART_MAIN);
	    lv_obj_set_size(bg_obj, 400, 450);
	    lv_obj_set_pos(bg_obj, 40, 128);
		p_view_addr_main->bg_cont_text = bg_obj;
	
	    lv_obj_t *bg_obj_addr = lv_obj_create(bg_obj);
	    lv_obj_remove_style_all(bg_obj_addr);
		lv_obj_set_scrollbar_mode(bg_obj_addr, LV_SCROLLBAR_MODE_OFF);
	    lv_obj_set_style_bg_color(bg_obj_addr, lv_color_hex(0x888888), LV_PART_MAIN);
		lv_obj_set_style_bg_opa(bg_obj_addr, LV_OPA_COVER, LV_PART_MAIN);
	    lv_obj_set_style_radius(bg_obj_addr, 15, LV_PART_MAIN);
		lv_obj_set_pos(bg_obj_addr, 0, 0);

	    lv_obj_t* label_addr = lv_label_create(bg_obj_addr);
	    lv_obj_set_style_text_color(label_addr, lv_color_hex(0xffffff), 0);
	    lv_obj_set_style_text_font(label_addr, &font_24, 0);
	    lv_label_set_long_mode(label_addr, LV_LABEL_LONG_WRAP);
	    lv_obj_set_width(label_addr, 320);
	    lv_obj_set_pos(label_addr, 40, 20);
	    lv_label_set_text(label_addr, gui_data_get_address_info());
		lv_obj_update_layout(label_addr);
		
	    lv_obj_set_size(bg_obj_addr, 400, lv_obj_get_height(label_addr) + 40);

	    lv_obj_t *bg_obj_path = lv_obj_create(bg_obj);
	    lv_obj_remove_style_all(bg_obj_path);
		lv_obj_set_scrollbar_mode(bg_obj_path, LV_SCROLLBAR_MODE_OFF);
	    lv_obj_set_style_bg_color(bg_obj_path, lv_color_hex(0x888888), LV_PART_MAIN);
		lv_obj_set_style_bg_opa(bg_obj_path, LV_OPA_COVER, LV_PART_MAIN);
	    lv_obj_set_style_radius(bg_obj_path, 15, LV_PART_MAIN);
	    
	    lv_obj_t* label_path = lv_label_create(bg_obj_path);
	    lv_obj_set_style_text_color(label_path, lv_color_hex(0xffffff), 0);
	    lv_label_set_long_mode(label_path, LV_LABEL_LONG_WRAP);
	    lv_obj_set_width(label_path, 320);
	    lv_obj_set_pos(label_path, 40, 20);
		set_language_string(label_path, 24, language_table_path);
		lv_obj_update_layout(label_path);
		
	    lv_obj_t* label_path_detail = lv_label_create(bg_obj_path);
	    lv_obj_set_style_text_color(label_path_detail, lv_color_hex(0xffffff), 0);
	    lv_obj_set_style_text_font(label_path_detail, &font_24, 0);
	    lv_label_set_long_mode(label_path_detail, LV_LABEL_LONG_WRAP);
	    lv_obj_set_width(label_path_detail, 320);
	    lv_obj_align_to(label_path_detail, label_path, LV_ALIGN_OUT_BOTTOM_MID, 0, 16);
	    lv_label_set_text(label_path_detail, gui_data_get_address_path());
		lv_obj_update_layout(label_path_detail);

	    lv_obj_set_size(bg_obj_path, 400, lv_obj_get_height(label_path_detail) + 72 + 20);
	    lv_obj_align_to(bg_obj_path, bg_obj_addr, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    }
}

static void view_qrcode(lv_obj_t* parent)
{	
	if(p_view_addr_main->bg_cont_text)
		lv_obj_add_flag(p_view_addr_main->bg_cont_text, LV_OBJ_FLAG_HIDDEN);
		
	if(p_view_addr_main->bg_cont_qrcode)
		lv_obj_clear_flag(p_view_addr_main->bg_cont_qrcode, LV_OBJ_FLAG_HIDDEN);
	else
	{
		lv_obj_t *bg_obj = lv_obj_create(parent);
		lv_obj_remove_style_all(bg_obj);
		lv_obj_set_scrollbar_mode(bg_obj, LV_SCROLLBAR_MODE_OFF);
		lv_obj_set_style_bg_opa(bg_obj, LV_OPA_COVER, LV_PART_MAIN);
		lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0xffffff), LV_PART_MAIN);
		lv_obj_set_style_radius(bg_obj, 16, LV_PART_MAIN);
		lv_obj_set_size(bg_obj, 354, 354);
		lv_obj_set_pos(bg_obj, 63, 128);
		p_view_addr_main->bg_cont_qrcode = bg_obj;

#if (LVGL_VERSION_MINOR == 2)
		lv_obj_t *qrcode = lv_qrcode_create(bg_obj, 320, lv_color_hex(0x000000), lv_color_hex(0xffffff));
#elif(LVGL_VERSION_MINOR == 3)
		lv_obj_t *qrcode = lv_qrcode_create(bg_obj);
		lv_qrcode_setparam(qrcode, 320, lv_color_hex(0x000000), lv_color_hex(0xffffff));
#endif
		
		lv_qrcode_update(qrcode, "faefawefawef", 12);
		lv_obj_center(qrcode);
	}
}

static void view_addr_main_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* title = lv_label_create(parent);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(title, &font_40, 0);
    lv_label_set_long_mode(title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(title, 400);
    lv_obj_set_pos(title, 40, 60);
    lv_label_set_text(title, gui_data_get_address_title());

	view_qrcode(parent);
    view_text(parent);

    lv_obj_t* img_btn_confirm = gui_comm_draw_obj(parent, 40, 598, 400, 80, 0x7FFF, 0xCCB68C, 0xA4916F);
    lv_obj_add_event_cb(img_btn_confirm, done_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_confirm = lv_label_create(img_btn_confirm);
    lv_obj_set_style_text_color(label_confirm, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_confirm, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_confirm, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_confirm, 400);
	set_language_string(label_confirm, 24, language_table_done);
    lv_obj_center(label_confirm);
    lv_obj_add_flag(label_confirm, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t* img_btn_qrcode = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0x888888, 0x666666);
    lv_obj_add_event_cb(img_btn_qrcode, qrcode_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_qrcode = lv_label_create(img_btn_qrcode);
    lv_obj_set_style_text_color(label_qrcode, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label_qrcode, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(label_qrcode, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_qrcode, 400);
	set_language_string(label_qrcode, 24, language_table_qr_code);
    lv_obj_center(label_qrcode);
    lv_obj_add_flag(label_qrcode, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
    p_view_addr_main->label_qrcode = label_qrcode;
}


void view_addr_main_start(void)
{
	gui_algo_data_set_pagelocation("view_addr_main",0);
    p_view_addr_main = (view_addr_main_t*)lv_mem_alloc(sizeof(view_addr_main_t));
    LV_ASSERT(p_view_addr_main);
    lv_memset(p_view_addr_main, 0, sizeof(view_addr_main_t));

    p_view_addr_main->bg_cont = gui_comm_draw_bg();
    view_addr_main_bg_cont(p_view_addr_main->bg_cont);
}

 void view_addr_main_stop(void)
{
    lv_obj_del(p_view_addr_main->bg_cont);
    lv_mem_free(p_view_addr_main);
    p_view_addr_main = NULL;
}
