/*********************
 *      INCLUDES
 *********************/

#include "settings_erase.h"
#include "gui_comm.h"

extern void settings_complete_start(void);
extern void settings_security_start(void);

static settings_erase_t* p_settings_erase = NULL;

static void check_options_selected(void)
{
    if(p_settings_erase->check1 || p_settings_erase->check2)
    {
        lv_obj_add_flag(p_settings_erase->slider, LV_OBJ_FLAG_CLICKABLE);
    }
    else
    {
        lv_obj_clear_flag(p_settings_erase->slider, LV_OBJ_FLAG_CLICKABLE);
    }
}

static void timer_cb(lv_timer_t * tmr)
{
    if(1)
    {
    	printf("timer_cb\n");
        settings_erase_stop();
        settings_complete_start();
    }
}

static void slider_cb(void)
{
	lv_obj_clear_flag(p_settings_erase->slider, LV_OBJ_FLAG_CLICKABLE);
	p_settings_erase->timer = lv_timer_create(timer_cb, 100, NULL);
}

static void img_check1_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	p_settings_erase->check1 = !p_settings_erase->check1;
    	if(p_settings_erase->check1)
			lv_img_set_src(p_settings_erase->img_check1, &img_chosen);
		else
			lv_img_set_src(p_settings_erase->img_check1, &img_unchosen);
        
        check_options_selected();
    }
}

static void img_check2_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	p_settings_erase->check2 = !p_settings_erase->check2;
    	if(p_settings_erase->check2)
			lv_img_set_src(p_settings_erase->img_check2, &img_chosen);
		else
			lv_img_set_src(p_settings_erase->img_check2, &img_unchosen);
        
        check_options_selected();
    }
}




static void cancel_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        settings_erase_stop();
        settings_security_start();
    }
}

static void settings_erase_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_erase_this_device, NULL);

    lv_obj_t* describe_label = lv_label_create(parent);
    lv_obj_set_style_text_color(describe_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(describe_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(describe_label, 400);
    lv_obj_set_pos(describe_label, 40, 120);
	set_language_string(describe_label, 24, language_table_this_will_erase_all_data);
    lv_obj_add_flag(describe_label, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
	
    lv_obj_t *bg_obj_check1 = lv_obj_create(parent);
    lv_obj_remove_style_all(bg_obj_check1);
    lv_obj_set_style_bg_color(bg_obj_check1, lv_color_hex(0x222222), LV_PART_MAIN);
    lv_obj_set_style_border_color(bg_obj_check1, lv_color_hex(0xCCB68C), LV_PART_MAIN);
    lv_obj_set_style_border_width(bg_obj_check1, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(bg_obj_check1, 15, 0);
    lv_obj_set_size(bg_obj_check1, 400, 100);
    lv_obj_set_pos(bg_obj_check1, 40, 227);
    lv_obj_add_event_cb(bg_obj_check1, img_check1_cb, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_add_flag(bg_obj_check1, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t* img_check1 = lv_img_create(bg_obj_check1);
	lv_img_set_src(img_check1, &img_unchosen);
	lv_obj_align_to(img_check1, bg_obj_check1, LV_ALIGN_LEFT_MID, 14, 0);
	p_settings_erase->img_check1 = img_check1;

    lv_obj_t* label_check1= lv_label_create(bg_obj_check1);
    lv_obj_set_style_text_color(label_check1, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_check1, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_check1, 320);
	set_language_string(label_check1, 24, language_table_after_reset_phrase_will_be_deleted);
	lv_obj_align_to(label_check1, bg_obj_check1, LV_ALIGN_LEFT_MID, 60, 0);
    lv_obj_add_flag(label_check1, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t *bg_obj_check2 = lv_obj_create(parent);
    lv_obj_remove_style_all(bg_obj_check2);
    lv_obj_set_style_bg_color(bg_obj_check2, lv_color_hex(0x222222), LV_PART_MAIN);
    lv_obj_set_style_border_color(bg_obj_check2, lv_color_hex(0xCCB68C), LV_PART_MAIN);
    lv_obj_set_style_border_width(bg_obj_check2, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(bg_obj_check2, 15, 0);
    lv_obj_set_size(bg_obj_check2, 400, 100);
    lv_obj_set_pos(bg_obj_check2, 40, 343);
    lv_obj_add_event_cb(bg_obj_check2, img_check2_cb, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_add_flag(bg_obj_check2, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t* img_check2 = lv_img_create(bg_obj_check2);
	lv_img_set_src(img_check2, &img_unchosen);
	lv_obj_align_to(img_check2, bg_obj_check2, LV_ALIGN_LEFT_MID, 14, 0);
	p_settings_erase->img_check2 = img_check2;

    lv_obj_t* label_check2= lv_label_create(bg_obj_check2);
    lv_obj_set_style_text_color(label_check2, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_check2, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_check2, 320);
	set_language_string(label_check2, 24, language_table_restore_funds);
	lv_obj_align_to(label_check2, bg_obj_check2, LV_ALIGN_LEFT_MID, 60, 0);
    lv_obj_add_flag(label_check2, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

	p_settings_erase->slider = gui_comm_draw_slider(parent, 598, slider_cb);
	
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

void settings_erase_start(void)
{
    gui_algo_data_set_pagelocation("settings_erase",0);
    p_settings_erase = (settings_erase_t*)lv_mem_alloc(sizeof(settings_erase_t));
    LV_ASSERT(p_settings_erase);
    lv_memset(p_settings_erase, 0, sizeof(settings_erase_t));

    p_settings_erase->bg_cont = gui_comm_draw_bg();
    settings_erase_bg_cont(p_settings_erase->bg_cont);

    // 初始化时将滑块设置为不可滑动
    lv_obj_clear_flag(p_settings_erase->slider, LV_OBJ_FLAG_CLICKABLE);
}

 void settings_erase_stop(void)
{
    if(p_settings_erase->timer != NULL)
        lv_timer_del(p_settings_erase->timer);
    lv_obj_del(p_settings_erase->bg_cont);
    lv_mem_free(p_settings_erase);
    p_settings_erase = NULL;
}
