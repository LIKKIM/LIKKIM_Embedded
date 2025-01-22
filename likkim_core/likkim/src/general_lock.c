/*********************
 *      INCLUDES
 *********************/

#include "general_lock.h"
#include "gui_comm.h"
#include "gui_data_comm.h"
#include "gui_language_comm.h"

extern void general_main_start(void);

static general_lock_t* p_general_lock = NULL;

static gui_comm_imgbtn_desc2_t gui_comm_imgbtn_num_table[] =
{
    {"1", 40, 128},
    {"2", 40, 188},
    {"5", 40, 248},
    {"10", 40, 308},
    {"30", 40, 368},
    {"Never", 40, 428},
};

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        general_lock_stop();
        general_main_start();
    }
}

static void general_lock_word_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        printf("lock time:%s\n", (char*)e->user_data);
		if(0 == strcmp((char*)e->user_data, "1"))
		{
			p_general_lock->lock_time = 1;
		}
		else if(0 == strcmp((char*)e->user_data, "2"))
		{
			p_general_lock->lock_time = 2;
		}
		else if(0 == strcmp((char*)e->user_data, "5"))
		{
			p_general_lock->lock_time = 5;
		}
		else if(0 == strcmp((char*)e->user_data, "10"))
		{
			p_general_lock->lock_time = 10;
		}
		else if(0 == strcmp((char*)e->user_data, "30"))
		{
			p_general_lock->lock_time = 30;
		}
		else if(0 == strcmp((char*)e->user_data, "Never"))
		{
			p_general_lock->lock_time = -1;
		}
		gui_data_set_lock_time(p_general_lock->lock_time);
        
		lv_obj_set_style_bg_color(e->current_target, lv_color_hex(0xCCB68C), LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(e->current_target, lv_color_hex(0xA4916F), LV_STATE_PRESSED);
		
	    lv_obj_set_style_bg_color(p_general_lock->choosen_btn, lv_color_hex(0x888888), LV_STATE_DEFAULT);
	    lv_obj_set_style_bg_color(p_general_lock->choosen_btn, lv_color_hex(0x666666), LV_STATE_PRESSED);

		if(-1 == p_general_lock->lock_time)
		{
			set_language_string(p_general_lock->label_describe, 24, language_table_screen_never_turn_off);
		}
		else
		{
			lv_obj_set_style_text_font(p_general_lock->label_describe, &font_24, 0);
			lv_label_set_text_fmt(p_general_lock->label_describe, language_table_after_10_minutes_screen_off[gui_data_get_language_type()], p_general_lock->lock_time);
		}
        p_general_lock->choosen_btn = e->current_target;
    }
}

static void general_lock_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_auto_lock, title_cb);
    uint8_t choosen = 0;
	if(1 == p_general_lock->lock_time)
		choosen = 0;
	else if(2 == p_general_lock->lock_time)
		choosen = 1;
	else if(5 == p_general_lock->lock_time)
		choosen = 2;
	else if(10 == p_general_lock->lock_time)
		choosen = 3;
	else if(30 == p_general_lock->lock_time)
		choosen = 4;
	else if(-1 == p_general_lock->lock_time)
		choosen = 5;
	
    for (uint8_t i = 0; i < sizeof(gui_comm_imgbtn_num_table) / sizeof(gui_comm_imgbtn_desc2_t); i++)
    {
        lv_obj_t* img_btn = gui_comm_draw_obj(parent, gui_comm_imgbtn_num_table[i].x, gui_comm_imgbtn_num_table[i].y, 400, 52, 0x7FFF, 0x888888, 0x666666);
        if(choosen == i)
        {
        	p_general_lock->choosen_btn = img_btn;
		    lv_obj_set_style_bg_color(img_btn, lv_color_hex(0xCCB68C), LV_STATE_DEFAULT);
		    lv_obj_set_style_bg_color(img_btn, lv_color_hex(0xA4916F), LV_STATE_PRESSED);
		}
        lv_obj_add_event_cb(img_btn, general_lock_word_handler, LV_EVENT_SHORT_CLICKED, (void *)gui_comm_imgbtn_num_table[i].str);

        lv_obj_t* label = lv_label_create(img_btn);
		lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
		lv_obj_set_style_text_font(label, &font_24, 0);
		if(i != sizeof(gui_comm_imgbtn_num_table) / sizeof(gui_comm_imgbtn_desc2_t) - 1)
        	lv_label_set_text_fmt(label, "%s %s", gui_comm_imgbtn_num_table[i].str, language_table_minute[gui_data_get_language_type()]);
        else
			lv_label_set_text_fmt(label, "%s", language_table_never[gui_data_get_language_type()]);
			
        lv_obj_center(label);
    }
    lv_obj_t* label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_describe, &font_24, 0);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 400);
    lv_obj_set_pos(label_describe, 40, 500);
    if(-1 == p_general_lock->lock_time)
		set_language_string(p_general_lock->label_describe, 24, language_table_screen_never_turn_off);
    else
	    lv_label_set_text_fmt(label_describe, language_table_after_10_minutes_screen_off[gui_data_get_language_type()], p_general_lock->lock_time);
	lv_obj_update_layout(label_describe);
	p_general_lock->label_describe = label_describe;
}


void general_lock_start(void)
{
	gui_algo_data_set_pagelocation("general_lock",0);
    p_general_lock = (general_lock_t*)lv_mem_alloc(sizeof(general_lock_t));
    LV_ASSERT(p_general_lock);
    lv_memset(p_general_lock, 0, sizeof(general_lock_t));
	p_general_lock->lock_time = gui_data_get_lock_time();

    p_general_lock->bg_cont = gui_comm_draw_bg();
    general_lock_bg_cont(p_general_lock->bg_cont);
}

void general_lock_stop(void)
{
    lv_obj_del(p_general_lock->bg_cont);
    lv_mem_free(p_general_lock);
    p_general_lock = NULL;
}


