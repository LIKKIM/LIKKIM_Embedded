﻿/*********************
 *      INCLUDES
 *********************/

#include "menu_main.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

extern void connect_main_start(void);
extern void general_main_start(void);
extern void guide_main_start(void);
extern void settings_main_start(void);

static menu_main_t* p_menu_main = NULL;

static gui_comm_img_desc_t menu_main_img_table[] =
{
    {language_table_general, 36, 60, &img_menu_general},
    {language_table_guide, 252, 60, &img_menu_guide},
    {language_table_settings, 36, 276, &img_menu_guide},
    //{language_table_conection_app_wallet, 252, 276, &img_menu_connect},
    //{language_table_balances, 252, 276, &img_menu_balances},
};

static void menu_main_word_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        printf("setting menu:%s\n", (char*)e->user_data);
        
		menu_main_stop();
		if(0 == strcmp((char*)e->user_data, language_table_conection_app_wallet[gui_data_get_language_type()]))
		{
			connect_main_start();
		}
		else if(0 == strcmp((char*)e->user_data, language_table_general[gui_data_get_language_type()]))
		{
			general_main_start();
		}
		else if(0 == strcmp((char*)e->user_data, language_table_guide[gui_data_get_language_type()]))
		{
			guide_main_start();
		}
		else if(0 == strcmp((char*)e->user_data, language_table_settings[gui_data_get_language_type()]))
		{
			settings_main_start();
		}
    }
}

static void menu_main_bg_cont(lv_obj_t* parent)
{
    for (uint8_t i = 0; i < sizeof(menu_main_img_table) / sizeof(gui_comm_img_desc_t); i++)
    {
        lv_obj_t* img_btn = lv_img_create(parent);
        lv_img_set_src(img_btn, menu_main_img_table[i].src);
        lv_obj_set_pos(img_btn, menu_main_img_table[i].x, menu_main_img_table[i].y);
        lv_obj_add_event_cb(img_btn, menu_main_word_handler, LV_EVENT_SHORT_CLICKED, (void *)menu_main_img_table[i].str[gui_data_get_language_type()]);
        lv_obj_add_flag(img_btn, LV_OBJ_FLAG_CLICKABLE);

        lv_obj_t* label = lv_label_create(img_btn);
		lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
        lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
        lv_obj_set_width(label, 144);
        lv_obj_set_pos(label, 28, 90);
		set_language_string(label, 24, menu_main_img_table[i].str);
        lv_obj_update_layout(label);
    }
}

void menu_main_start(void)
{
    gui_algo_data_set_pagelocation("menu_main",0);
    p_menu_main = (menu_main_t*)lv_mem_alloc(sizeof(menu_main_t));
    LV_ASSERT(p_menu_main);
    lv_memset(p_menu_main, 0, sizeof(menu_main_t));

    p_menu_main->bg_cont = gui_comm_draw_bg();
    menu_main_bg_cont(p_menu_main->bg_cont);

    gui_data_set_first_poweron(0);
}

void menu_main_stop(void)
{
    lv_obj_del(p_menu_main->bg_cont);
    lv_mem_free(p_menu_main);
    p_menu_main = NULL;
}


