/*********************
 *      INCLUDES
 *********************/

#include "settings_main.h"
#include "gui_comm.h"
#include "gui_data_comm.h"
#include "gui_language_comm.h"

extern void menu_main_start(void);
extern void settings_about_start(void);
extern void settings_security_start(void);
extern void settings_power_off_start(void);


static settings_main_t* p_settings_main = NULL;

static gui_comm_imgbtn_desc_t gui_comm_imgbtn_num_table[] =
{
    {language_table_security, 40, 120},
    {language_table_about_device, 40, 180},
    {language_table_power_off, 40, 240},
};

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        settings_main_stop();
        menu_main_start();
    }
}


static void settings_main_word_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        printf("setting guide:%s\n", (char*)e->user_data);
		settings_main_stop();
		if(0 == strcmp((char*)e->user_data, language_table_security[gui_data_get_language_type()]))
		{
			settings_security_start();
		}
		else if(0 == strcmp((char*)e->user_data, language_table_about_device[gui_data_get_language_type()]))
		{
			settings_about_start();
		}
		else if(0 == strcmp((char*)e->user_data, language_table_power_off[gui_data_get_language_type()]))
		{
			settings_power_off_start();
		}
    }
}
static void settings_main_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_settings, title_cb);

    for (uint8_t i = 0; i < sizeof(gui_comm_imgbtn_num_table) / sizeof(gui_comm_imgbtn_desc_t); i++)
    {
        lv_obj_t* img_btn = gui_comm_draw_obj(parent, gui_comm_imgbtn_num_table[i].x, gui_comm_imgbtn_num_table[i].y, 400, 52, 15, 0x888888, 0x666666);
        lv_obj_add_event_cb(img_btn, settings_main_word_handler, LV_EVENT_SHORT_CLICKED, (void *)gui_comm_imgbtn_num_table[i].str[gui_data_get_language_type()]);

        lv_obj_t* label = lv_label_create(img_btn);
		lv_obj_set_style_text_font(label, &font_24, 0);
        if(strcmp(gui_comm_imgbtn_num_table[i].str[gui_data_get_language_type()], language_table_power_off[gui_data_get_language_type()]) == 0)
			lv_obj_set_style_text_color(label, lv_color_hex(0xff0000), 0);
        else
			lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
        lv_label_set_text(label, gui_comm_imgbtn_num_table[i].str[gui_data_get_language_type()]);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }
}


void settings_main_start(void)
{
     gui_algo_data_set_pagelocation("settings_main",0);
    p_settings_main = (settings_main_t*)lv_mem_alloc(sizeof(settings_main_t));
    LV_ASSERT(p_settings_main);
    lv_memset(p_settings_main, 0, sizeof(settings_main_t));

    p_settings_main->bg_cont = gui_comm_draw_bg();
    settings_main_bg_cont(p_settings_main->bg_cont);
}

void settings_main_stop(void)
{
    lv_obj_del(p_settings_main->bg_cont);
    lv_mem_free(p_settings_main);
    p_settings_main = NULL;
}

