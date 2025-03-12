/*********************
 *      INCLUDES
 *********************/
// Include headers for using other modules in the project
#include "general_main.h"
#include "gui_comm.h"
#include "gui_data_comm.h"
#include "gui_language_comm.h"

// Declare external functions from other parts of the project
extern void menu_main_start(void);
extern void general_lock_start(void);
extern void general_shutdown_start(void);
extern void general_homescreen_start(void);
extern void startup_language_start(app_index_t app_index);
extern void startup_screen_start(app_index_t app_index);

// Static pointer to store main interface data
static general_main_t* p_general_main = NULL;

// Static array to define buttons with their labels and positions
static gui_comm_imgbtn_desc_t gui_comm_imgbtn_num_table[] = {
    {language_table_auto_lock, 40, 128},
    {language_table_language, 40, 188},
    {language_table_shutdown, 40, 248},
    {language_table_homescreen, 40, 308},
    {language_table_lock_screen, 40, 368},
};

// Callback function for title click events
static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        general_main_stop();
        menu_main_start();
    }
}

static void general_main_word_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        printf("setting general:%s\n", (char*)e->user_data);
        
		general_main_stop();
		if(0 == strcmp((char*)e->user_data, language_table_auto_lock[gui_data_get_language_type()]))
		{
			general_lock_start();
		}
		else if(0 == strcmp((char*)e->user_data, language_table_language[gui_data_get_language_type()]))
		{
			startup_language_start(APP_GENERAL);
		}
		else if(0 == strcmp((char*)e->user_data, language_table_shutdown[gui_data_get_language_type()]))
		{
			general_shutdown_start();
		}
		else if(0 == strcmp((char*)e->user_data, language_table_homescreen[gui_data_get_language_type()]))
		{
			general_homescreen_start();
		}
		else if(0 == strcmp((char*)e->user_data, language_table_lock_screen[gui_data_get_language_type()]))
		{
			startup_screen_start(APP_GENERAL);
		}
    }
}

static void general_main_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_general, title_cb);

    for (uint8_t i = 0; i < sizeof(gui_comm_imgbtn_num_table) / sizeof(gui_comm_imgbtn_desc_t); i++)
    {
        lv_obj_t* img_btn = gui_comm_draw_obj(parent, gui_comm_imgbtn_num_table[i].x, gui_comm_imgbtn_num_table[i].y, 400, 52, 15, 0x888888, 0x666666);
        lv_obj_add_event_cb(img_btn, general_main_word_handler, LV_EVENT_SHORT_CLICKED, (void *)gui_comm_imgbtn_num_table[i].str[gui_data_get_language_type()]);

        lv_obj_t* label = lv_label_create(img_btn);
		lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
		lv_obj_set_style_text_font(label, &font_24, 0);
        lv_label_set_text(label, gui_comm_imgbtn_num_table[i].str[gui_data_get_language_type()]);
        lv_obj_align(label, LV_ALIGN_LEFT_MID, 44, 2);

        if (0 == i)
        {
            lv_obj_t* labe_detail = lv_label_create(img_btn);
			lv_obj_set_style_text_color(labe_detail, lv_color_hex(0xffffff), 0);
			lv_obj_set_style_text_font(labe_detail, &font_24, 0);

			int time = gui_data_get_lock_time();
			if(time > 0)
    	        lv_label_set_text_fmt(labe_detail, "%d %s", time, language_table_minute[gui_data_get_language_type()]);
            else
	            lv_label_set_text(labe_detail, language_table_never[gui_data_get_language_type()]);
            lv_obj_align(labe_detail, LV_ALIGN_RIGHT_MID, -40, 2);
        }
        else if (1 == i)
        {
            lv_obj_t* labe_detail = lv_label_create(img_btn);
			lv_obj_set_style_text_color(labe_detail, lv_color_hex(0xffffff), 0);
			lv_obj_set_style_text_font(labe_detail, &font_24, 0);
            lv_label_set_text_fmt(labe_detail, "%s", gui_data_get_language());
            lv_obj_align(labe_detail, LV_ALIGN_RIGHT_MID, -40, 2);
        }
        else if (2 == i)
        {
            lv_obj_t* labe_detail = lv_label_create(img_btn);
			lv_obj_set_style_text_color(labe_detail, lv_color_hex(0xffffff), 0);
			lv_obj_set_style_text_font(labe_detail, &font_24, 0);
			
			int time = gui_data_get_shutdown_time();
			if(time > 0)
    	        lv_label_set_text_fmt(labe_detail, "%d %s", time, language_table_minute[gui_data_get_language_type()]);
            else
	            lv_label_set_text(labe_detail, language_table_never[gui_data_get_language_type()]);
            lv_obj_align(labe_detail, LV_ALIGN_RIGHT_MID, -40, 2);
        }
        else
            lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }
}


void general_main_start(void)
{
    gui_algo_data_set_pagelocation("general_main_stop",0);
    p_general_main = (general_main_t*)lv_mem_alloc(sizeof(general_main_t));
    LV_ASSERT(p_general_main);
    lv_memset(p_general_main, 0, sizeof(general_main_t));

    p_general_main->bg_cont = gui_comm_draw_bg();
    general_main_bg_cont(p_general_main->bg_cont);
}

void general_main_stop(void)
{
    lv_obj_del(p_general_main->bg_cont);
    lv_mem_free(p_general_main);
    p_general_main = NULL;
}


