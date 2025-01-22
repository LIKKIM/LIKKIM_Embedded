/*********************
 *      INCLUDES
 *********************/

#include "settings_security.h"
#include "gui_comm.h"
#include "gui_data_comm.h"
#include "gui_language_comm.h"

extern void settings_main_start(void);
extern void settings_reset_start(void);
extern void settings_change_pin_start(void);
extern void finger_add_start(void);




static settings_security_t* p_settings_security = NULL;

static gui_comm_imgbtn_desc_t gui_comm_imgbtn_num_table[] =
{
    {language_table_change_password, 40, 120},
    {language_table_fingerprint, 40, 180},
    {language_table_reset_device, 40, 240},
};


static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        settings_security_stop();
        settings_main_start();
    }
}

static void settings_security_word_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        printf("setting guide:%s\n", (char*)e->user_data);
        settings_security_stop();
		if(0 == strcmp((char*)e->user_data, language_table_change_password[gui_data_get_language_type()]))
		{
			settings_change_pin_start();
		}
		else if(0 == strcmp((char*)e->user_data, language_table_fingerprint[gui_data_get_language_type()]))
		{
			finger_add_start();
		}
		else if(0 == strcmp((char*)e->user_data, language_table_reset_device[gui_data_get_language_type()]))
		{
			settings_reset_start();
		}
    }
}
static void settings_security_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_security, title_cb);

    for (uint8_t i = 0; i < sizeof(gui_comm_imgbtn_num_table) / sizeof(gui_comm_imgbtn_desc_t); i++)
    {
        lv_obj_t* img_btn = gui_comm_draw_obj(parent, gui_comm_imgbtn_num_table[i].x, gui_comm_imgbtn_num_table[i].y, 400, 52, 15, 0x888888, 0x666666);
        lv_obj_add_event_cb(img_btn, settings_security_word_handler, LV_EVENT_SHORT_CLICKED, (void *)gui_comm_imgbtn_num_table[i].str[gui_data_get_language_type()]);

        lv_obj_t* label = lv_label_create(img_btn);
		lv_obj_set_style_text_font(label, &font_24, 0);
		lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
        lv_label_set_text(label, gui_comm_imgbtn_num_table[i].str[gui_data_get_language_type()]);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }
}


void settings_security_start(void)
{
    gui_algo_data_set_pagelocation("settings_security",0);
    p_settings_security = (settings_security_t*)lv_mem_alloc(sizeof(settings_security_t));
    LV_ASSERT(p_settings_security);
    lv_memset(p_settings_security, 0, sizeof(settings_security_t));

    p_settings_security->bg_cont = gui_comm_draw_bg();
    settings_security_bg_cont(p_settings_security->bg_cont);
}

void settings_security_stop(void)
{
    lv_obj_del(p_settings_security->bg_cont);
    lv_mem_free(p_settings_security);
    p_settings_security = NULL;
}

