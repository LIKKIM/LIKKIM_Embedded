/*********************
 *      INCLUDES
 *********************/

#include "startup_verification.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

extern void startup_import_ready_start(void);
extern void startup_incorrect_word_start(void);


static startup_verification_t* p_startup_verification = NULL;

static gui_comm_imgbtn_desc2_t startup_imgbtn_num_table[] =
{
    {"word", 38, 147},
    {"word", 246, 147},
    {"word", 38, 207},
    {"word", 246, 207},
    {"word", 38, 328},
    {"word", 246, 328},
    {"word", 38, 388},
    {"word", 246, 388},
};

static void timer_cb(lv_timer_t * tmr)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if(i == p_startup_verification->rand_num1)
		{
			lv_label_set_text(p_startup_verification->label_word[i], gui_data_get_word(p_startup_verification->page_id));
		}
		if(i == p_startup_verification->rand_num2)
		{
			lv_label_set_text(p_startup_verification->label_word[i], gui_data_get_word(p_startup_verification->page_id + 1));
		}
	}
}

static void word_cb1(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
		printf("e->user_data : %s\n", (char *)e->user_data);
		if (0 == strcmp(gui_data_get_word(p_startup_verification->page_id), e->user_data))
		{
	        p_startup_verification->state |= WORD_VERIFACATION_STATE_1;
		    lv_obj_set_style_bg_color(e->current_target, lv_color_hex(0xCCB68C), LV_STATE_DEFAULT);
		    lv_obj_set_style_bg_color(e->current_target, lv_color_hex(0xA4916F), LV_STATE_PRESSED);
	    }
	    else
	    {
	    	p_startup_verification->state &= ~WORD_VERIFACATION_STATE_1;
	    	startup_verification_stop();
	    	startup_incorrect_word_start();
	    }
    }
}
static void word_cb2(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
		printf("e->user_data : %s\n", (char *)e->user_data);
		if (0 == strcmp(gui_data_get_word(p_startup_verification->page_id + 1), e->user_data))
		{
			p_startup_verification->state |= WORD_VERIFACATION_STATE_2;
		    lv_obj_set_style_bg_color(e->current_target, lv_color_hex(0xCCB68C), LV_STATE_DEFAULT);
		    lv_obj_set_style_bg_color(e->current_target, lv_color_hex(0xA4916F), LV_STATE_PRESSED);
		}
	    else
	    {
	    	p_startup_verification->state &= ~WORD_VERIFACATION_STATE_2;
	    	startup_verification_stop();
	    	startup_incorrect_word_start();
	    }
    }
}
static void continue_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	if(p_startup_verification->state != WORD_VERIFACATION_STATE_ALL)
    		return;

    	p_startup_verification->state = 0;
        p_startup_verification->page_id += 2;
//				
				        // 计算当前页对应的条目组起始索引
		uint8_t group_start_index = 0;// (p_startup_verification->page_id / 2) * 8;

        if (gui_data_get_word_num() == p_startup_verification->page_id)
        {
            startup_verification_stop();
            startup_import_ready_start();
            return;
        }

        p_startup_verification->rand_num1 = get_rand_num(4);
        p_startup_verification->rand_num2 = get_rand_num(4) + 4;
        lv_label_set_text_fmt(p_startup_verification->label_describe1, "%s#%d", language_table_verification_phrase[gui_data_get_language_type()], p_startup_verification->page_id + 1);
        lv_label_set_text_fmt(p_startup_verification->label_describe2, "%s#%d", language_table_verification_phrase[gui_data_get_language_type()], p_startup_verification->page_id + 2);
        
		for (uint8_t i = 0; i < 8; i++)
		{
			 uint8_t current_index = group_start_index + i; // 计算当前按钮使用的条目索引
			if(i < 4)
			{
				if(i == p_startup_verification->rand_num1)
				{
					lv_label_set_text(p_startup_verification->label_word[i], gui_data_get_word(p_startup_verification->page_id));
					lv_obj_remove_event_cb(p_startup_verification->btn_word[i], word_cb1);
					lv_obj_add_event_cb(p_startup_verification->btn_word[i], word_cb1, LV_EVENT_SHORT_CLICKED, gui_data_get_word(p_startup_verification->page_id));
				}
				else
				{
					lv_label_set_text(p_startup_verification->label_word[i], gui_data_get_random_word(gui_data_get_word(p_startup_verification->page_id)));
					lv_obj_remove_event_cb(p_startup_verification->btn_word[i], word_cb1);
					lv_obj_add_event_cb(p_startup_verification->btn_word[i], word_cb1, LV_EVENT_SHORT_CLICKED, (void *)startup_imgbtn_num_table[current_index].str);
				}
			}
			else
			{
				if(i == p_startup_verification->rand_num2)
				{
					lv_label_set_text(p_startup_verification->label_word[i], gui_data_get_word(p_startup_verification->page_id + 1));
					lv_obj_remove_event_cb(p_startup_verification->btn_word[i], word_cb2);
					lv_obj_add_event_cb(p_startup_verification->btn_word[i], word_cb2, LV_EVENT_SHORT_CLICKED, gui_data_get_word(p_startup_verification->page_id + 1));
				}
				else
				{
					lv_label_set_text(p_startup_verification->label_word[i], gui_data_get_random_word(gui_data_get_word(p_startup_verification->page_id + 1)));
					lv_obj_remove_event_cb(p_startup_verification->btn_word[i], word_cb2);
					lv_obj_add_event_cb(p_startup_verification->btn_word[i], word_cb2, LV_EVENT_SHORT_CLICKED, (void *)startup_imgbtn_num_table[current_index].str);
				}
			}
		    lv_obj_set_style_bg_color(p_startup_verification->btn_word[i], lv_color_hex(0x888888), LV_STATE_DEFAULT);
		    lv_obj_set_style_bg_color(p_startup_verification->btn_word[i], lv_color_hex(0x666666), LV_STATE_PRESSED);
			lv_obj_update_layout(p_startup_verification->label_word[i]);
		}
    }
}
static void startup_verification_bg_cont(lv_obj_t* parent)
{
    p_startup_verification->rand_num1 = get_rand_num(4);
    p_startup_verification->rand_num2 = get_rand_num(4) + 4;
    printf("rand_num1 : %d, rand_num2 : %d\n", p_startup_verification->rand_num1, p_startup_verification->rand_num2);

    lv_obj_t* label_title = lv_label_create(parent);
	lv_obj_set_style_text_color(label_title, lv_color_hex(0xffffff), 0);
	set_language_string(label_title, 40, language_table_verification_phrase);
    lv_obj_set_width(label_title, 400);
    lv_obj_set_pos(label_title, 38, 42);

    lv_obj_t* label_describe1 = lv_label_create(parent);
	lv_obj_set_style_text_font(label_describe1, &font_24, 0);
	lv_obj_set_style_text_color(label_describe1, lv_color_hex(0xffffff), 0);
    lv_label_set_text_fmt(label_describe1, "%s#%d", language_table_verification_phrase[gui_data_get_language_type()], p_startup_verification->page_id + 1);
    lv_label_set_long_mode(label_describe1, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe1, 400);
    lv_obj_set_pos(label_describe1, 38, 98);
    p_startup_verification->label_describe1 = label_describe1;
	
    lv_obj_t* label_describe2 = lv_label_create(parent);
	lv_obj_set_style_text_font(label_describe2, &font_24, 0);
	lv_obj_set_style_text_color(label_describe2, lv_color_hex(0xffffff), 0);
    lv_label_set_text_fmt(label_describe2, "%s#%d", language_table_verification_phrase[gui_data_get_language_type()], p_startup_verification->page_id + 2);
    lv_label_set_long_mode(label_describe2, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe2, 400);
    lv_obj_set_pos(label_describe2, 38, 279);
    p_startup_verification->label_describe2 = label_describe2;

    for (uint8_t i = 0; i < 8; i++)
    {
        lv_obj_t* img_btn = gui_comm_draw_obj(parent, startup_imgbtn_num_table[i].x, startup_imgbtn_num_table[i].y, 192, 50, 15, 0x888888, 0x666666);

        lv_obj_t* label = lv_label_create(img_btn);
		lv_obj_set_style_text_font(label, &font_24, 0);
		lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);    
		lv_obj_set_style_text_align(label, LV_ALIGN_CENTER, 0);
        lv_obj_add_flag(label, LV_OBJ_FLAG_EVENT_BUBBLE);

        if(i < 4)
		{
			if(i == p_startup_verification->rand_num1)
			{
				lv_label_set_text(label, gui_data_get_word(0));
				lv_obj_add_event_cb(img_btn, word_cb1, LV_EVENT_SHORT_CLICKED, gui_data_get_word(p_startup_verification->page_id));
			}
			else
			{
				lv_label_set_text(label, gui_data_get_random_word(gui_data_get_word(0)));
		        lv_obj_add_event_cb(img_btn, word_cb1, LV_EVENT_SHORT_CLICKED, (void *)startup_imgbtn_num_table[i].str);
			}
		}
        else
		{
			if(i == p_startup_verification->rand_num2)
			{
				lv_label_set_text(label, gui_data_get_word(1));
	        	lv_obj_add_event_cb(img_btn, word_cb2, LV_EVENT_SHORT_CLICKED, gui_data_get_word(p_startup_verification->page_id + 1));
			}
			else
			{
				lv_label_set_text(label, gui_data_get_random_word(gui_data_get_word(1)));
		        lv_obj_add_event_cb(img_btn, word_cb2, LV_EVENT_SHORT_CLICKED, (void *)startup_imgbtn_num_table[i].str);
			}
		}
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
        lv_obj_update_layout(label);
        p_startup_verification->label_word[i] = label;
		p_startup_verification->btn_word[i] = img_btn;
    }

    lv_obj_t* img_btn_continue = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0xCCB68C, 0xA4916F);
    lv_obj_add_event_cb(img_btn_continue, continue_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_continue = lv_label_create(img_btn_continue);
	lv_obj_set_style_text_color(label_continue, lv_color_hex(0xffffff), 0);
	set_language_string(label_continue, 24, language_table_continue);
    lv_obj_align(label_continue, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(label_continue, LV_OBJ_FLAG_EVENT_BUBBLE);
}


void startup_verification_start(void)
{
    printf("%s\n", __func__);
	gui_algo_data_set_pagelocation("startup_verification",0);
    p_startup_verification = (startup_verification_t*)lv_mem_alloc(sizeof(startup_verification_t));
    LV_ASSERT(p_startup_verification);
    lv_memset(p_startup_verification, 0, sizeof(startup_verification_t));

    p_startup_verification->bg_cont = gui_comm_draw_bg();
    startup_verification_bg_cont(p_startup_verification->bg_cont);
	p_startup_verification->timer = lv_timer_create(timer_cb, 1000, NULL);
}

void startup_verification_stop(void)
{
	lv_timer_del(p_startup_verification->timer);
    lv_obj_del(p_startup_verification->bg_cont);
    lv_mem_free(p_startup_verification);
    p_startup_verification = NULL;
}


