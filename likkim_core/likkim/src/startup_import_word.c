/*********************
 *      INCLUDES
 *********************/

#include "startup_import_word.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


extern void startup_import_ready_start(void);
extern void startup_import_wallet_start(void);
extern void view_ready_waiting_start(void);

static void startup_import_word_show_remind_word(lv_obj_t* parent);

static startup_import_word_t* p_startup_import_word = NULL;

static void timer_cb(lv_timer_t * timer)
{
	if(p_startup_import_word->word_index == gui_data_get_word_num())
	{
		startup_import_word_stop();
		view_ready_waiting_start();
		 wallet_Input_word(1);/*导入钱包标志位赋值*/

		return;
	}
	lv_obj_clean(p_startup_import_word->bg_cont2);
	lv_obj_clear_flag(p_startup_import_word->btn_ok, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_set_style_bg_color(p_startup_import_word->btn_ok, lv_color_hex(0x555555), LV_STATE_DEFAULT);
	lv_obj_add_flag(p_startup_import_word->label_word, LV_OBJ_FLAG_HIDDEN);
	lv_memset(p_startup_import_word->word, 0, 32);
	p_startup_import_word->word_index++;	
	lv_label_set_text_fmt(p_startup_import_word->label_title, "%s #%d:", language_table_enter_word[gui_data_get_language_type()], p_startup_import_word->word_index);
    
	lv_timer_del(p_startup_import_word->timer);
	p_startup_import_word->timer = NULL;
}

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        startup_import_word_stop();
        startup_import_wallet_start();
    }
}


static void remind_word_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

	if (LV_EVENT_SHORT_CLICKED == event)
    {
		strcpy(p_startup_import_word->word, (char *)e->user_data);
		lv_label_set_text(p_startup_import_word->label_word, p_startup_import_word->word);
		lv_obj_add_flag(p_startup_import_word->btn_ok, LV_OBJ_FLAG_CLICKABLE);
		lv_obj_set_style_bg_color(p_startup_import_word->btn_ok, lv_color_hex(0xCCB68C), LV_STATE_DEFAULT);
    }
}

static void ok_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
    	if(0 == strlen(p_startup_import_word->word))
    	{
    		return;
    	}
    	
		lv_obj_clean(p_startup_import_word->bg_cont2);
		gui_data_set_word(p_startup_import_word->word_index - 1, p_startup_import_word->word);
		
		lv_obj_t* icons = lv_img_create(p_startup_import_word->bg_cont2);
		lv_img_set_src(icons, &img_success);
		lv_obj_set_pos(icons, 0, 26);
		
		lv_obj_t *label = lv_label_create(p_startup_import_word->bg_cont2);
		lv_obj_set_style_text_color(label, lv_color_hex(0x10E807), 0);
		lv_label_set_long_mode(label, LV_LABEL_LONG_DOT);
		lv_obj_set_width(label, 400);
		lv_obj_set_pos(label, 34, 26);
		set_language_string(label, 24, language_table_submitted);
		
		p_startup_import_word->timer = lv_timer_create(timer_cb, 600, NULL);
    }
}

static void cancle_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        uint8_t ter_len = strlen(p_startup_import_word->word);
        if(ter_len)
        {
	        p_startup_import_word->word[ter_len - 1] = 0;
	        lv_label_set_text(p_startup_import_word->label_word, p_startup_import_word->word);

	        if (ter_len == 1)
	            lv_obj_add_flag(p_startup_import_word->label_word, LV_OBJ_FLAG_HIDDEN);
	        else
				startup_import_word_show_remind_word(p_startup_import_word->bg_cont2);
	    }
    }
}

static void num_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

	if (LV_EVENT_SHORT_CLICKED == event)
    {	
    	gui_comm_imgbtn_desc2_t *desc = e->user_data;
		strcat(p_startup_import_word->word, desc->str);
		lv_label_set_text(p_startup_import_word->label_word, p_startup_import_word->word);
		printf("%s \n", p_startup_import_word->word);
		lv_obj_clear_flag(p_startup_import_word->label_word, LV_OBJ_FLAG_HIDDEN);
		startup_import_word_show_remind_word(p_startup_import_word->bg_cont2);
    }
}

static void startup_import_word_show_remind_word(lv_obj_t* parent)
{
	char *str_tab[4] = {0};
	bool match = gui_data_get_remind_word(p_startup_import_word->word, (char**) & str_tab);

	if(match)
	{
		lv_obj_add_flag(p_startup_import_word->btn_ok, LV_OBJ_FLAG_CLICKABLE);
		lv_obj_set_style_bg_color(p_startup_import_word->btn_ok, lv_color_hex(0xCCB68C), LV_STATE_DEFAULT);
	}
	else
	{
		lv_obj_clear_flag(p_startup_import_word->btn_ok, LV_OBJ_FLAG_CLICKABLE);
		lv_obj_set_style_bg_color(p_startup_import_word->btn_ok, lv_color_hex(0x555555), LV_STATE_DEFAULT);
	}
		
    if(str_tab[0])
	    printf("str_tab[%d]:%s\n", 0, str_tab[0]);
	if(str_tab[1])
	    printf("str_tab[%d]:%s\n", 1, str_tab[1]);
	if(str_tab[2])
	    printf("str_tab[%d]:%s\n", 2, str_tab[2]);
    if(str_tab[3])
	    printf("str_tab[%d]:%s\n", 3, str_tab[3]);

	lv_obj_clean(parent);

	lv_obj_t *bg_obj[4];
	uint16_t pos_x = 0;
	uint16_t width = 0;
	
	for(uint8_t i = 0; i < 4; i++)
	{
		if(str_tab[i])
		{
			bg_obj[i] = lv_obj_create(parent);
			lv_obj_remove_style_all(bg_obj[i]);
			lv_obj_set_scrollbar_mode(bg_obj[i], LV_SCROLLBAR_MODE_OFF);
			lv_obj_set_style_bg_color(bg_obj[i], lv_color_hex(0x888888), LV_PART_MAIN);
			lv_obj_set_style_bg_opa(bg_obj[i], LV_OPA_COVER, LV_PART_MAIN);
			lv_obj_set_style_radius(bg_obj[i], 15, LV_PART_MAIN);
			lv_obj_add_event_cb(bg_obj[i], remind_word_cb, LV_EVENT_ALL, str_tab[i]);
			
		    lv_obj_t* label_word = lv_label_create(bg_obj[i]);
		    lv_obj_set_style_text_color(label_word, lv_color_hex(0xffffff), 0);
		    lv_obj_set_style_text_font(label_word, &font_24, 0);
		    lv_obj_set_pos(label_word, 20, 20);
			lv_label_set_text(label_word, str_tab[i]);
			lv_obj_update_layout(label_word);

			width = lv_obj_get_width(label_word) + 26;
			lv_obj_set_pos(bg_obj[i], pos_x, 0);
			lv_obj_set_size(bg_obj[i], width, 60);
			lv_obj_update_layout(bg_obj[i]);
			pos_x += width + 4;

			lv_obj_center(label_word);
			if(pos_x > 440)
			{
				lv_obj_del(bg_obj[i]);
				break;
			}
		}
	}
}

static void startup_import_word_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* back_icons = lv_img_create(parent);
    lv_img_set_src(back_icons, &img_back);
    lv_obj_set_pos(back_icons, 40, 16);
    lv_obj_add_event_cb(back_icons, title_cb, LV_EVENT_SHORT_CLICKED, NULL);
	lv_obj_add_flag(back_icons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
    
    lv_obj_t* title_label = lv_label_create(parent);
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(title_label, &font_40, 0);
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(title_label, 400);
    lv_obj_set_pos(title_label, 40, 60);
    lv_label_set_text_fmt(title_label, "%s #%d:", language_table_enter_word[gui_data_get_language_type()], p_startup_import_word->word_index);
    p_startup_import_word->label_title = title_label;
    
	lv_obj_t *bg_obj = lv_obj_create(parent);
	lv_obj_remove_style_all(bg_obj);
	lv_obj_set_scrollbar_mode(bg_obj, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x888888), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(bg_obj, LV_OPA_COVER, LV_PART_MAIN);
	lv_obj_set_style_radius(bg_obj, 15, LV_PART_MAIN);
	lv_obj_set_pos(bg_obj, 40, 130);
	lv_obj_set_size(bg_obj, 400, 200);
	
    lv_obj_t* label_word = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_word, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_word, &font_40, 0);
    lv_label_set_long_mode(label_word, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_word, 340);
    lv_obj_set_pos(label_word, 20, 20);
	lv_obj_add_flag(label_word, LV_OBJ_FLAG_HIDDEN);
    p_startup_import_word->label_word = label_word;
    
	lv_obj_t *bg_obj_word = lv_obj_create(parent);
	lv_obj_remove_style_all(bg_obj_word);
	lv_obj_set_scrollbar_mode(bg_obj_word, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_bg_color(bg_obj_word, lv_color_hex(0x888888), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(bg_obj_word, LV_OPA_TRANSP, LV_PART_MAIN);
	lv_obj_set_style_radius(bg_obj_word, 15, LV_PART_MAIN);
    lv_obj_set_size(bg_obj_word, 436, 60);
    lv_obj_set_pos(bg_obj_word, 22, 502);
	p_startup_import_word->bg_cont2 = bg_obj_word;

    p_startup_import_word->btn_ok = gui_comm_draw_keypad_letter(parent, num_cb, ok_cb, cancle_cb);
}


void startup_import_word_start(void)
{
    printf("%s\n", __func__);
	gui_algo_data_set_pagelocation("startup_import_word",0);
    p_startup_import_word = (startup_import_word_t*)lv_mem_alloc(sizeof(startup_import_word_t));
    LV_ASSERT(p_startup_import_word);
    lv_memset(p_startup_import_word, 0, sizeof(startup_import_word_t));
	p_startup_import_word->word_index = 1;

    p_startup_import_word->bg_cont = gui_comm_draw_bg();
    startup_import_word_bg_cont(p_startup_import_word->bg_cont);
}

void startup_import_word_stop(void)
{
	if(p_startup_import_word->timer) lv_timer_del(p_startup_import_word->timer);
    lv_obj_del(p_startup_import_word->bg_cont);
    lv_mem_free(p_startup_import_word);
    p_startup_import_word = NULL;
}


