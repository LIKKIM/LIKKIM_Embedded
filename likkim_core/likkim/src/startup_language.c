/*********************
 *      INCLUDES
 *********************/

#include "startup_language.h"
#include "gui_comm.h"
#include "gui_data_comm.h"
#include "gui_language_comm.h"

static gui_comm_imgbtn_desc2_t startup_language_desc_table[] =
{
    {"English", 40, 128},
    {"简体中文", 40, 188},
    {"繁體中文", 40, 248},
    {"Français", 40, 308},
    {"Español", 40, 368},
    {"العربية", 40, 428},
    {"日本語", 40, 488},
    {"Русский", 40, 548},
};
extern void general_main_start(void);
extern void startup_quick_start_start(void);

static startup_language_t* p_startup_language = NULL;

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        if(APP_GENERAL == p_startup_language->app_index)
		{
            startup_language_stop();
        	general_main_start();
		}
		else if(APP_STARTUP == p_startup_language->app_index)
		{
            startup_language_stop();
	        startup_quick_start_start();
        }
    }
}

static void startup_language_event_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        printf("setting language:%s\n", (char *)e->user_data);
		gui_data_set_language((char *)e->user_data);
		if(APP_GENERAL == p_startup_language->app_index)
		{
            startup_language_stop();
        	general_main_start();
		}
		else if(APP_STARTUP == p_startup_language->app_index)
		{
            startup_language_stop();
	        startup_quick_start_start();
        }
    }
}

static void startup_language_bg_cont(lv_obj_t* parent)
{
	gui_comm_draw_title(parent, language_table_language, title_cb);
	    
    for (int i = 0; i < sizeof(startup_language_desc_table) / sizeof(gui_comm_imgbtn_desc2_t); i++)
    {
        lv_obj_t* btn = gui_comm_draw_obj(parent, startup_language_desc_table[i].x, startup_language_desc_table[i].y, 400, 52, 15, 0x888888, 0x666666);
        lv_obj_add_event_cb(btn, startup_language_event_handler, LV_EVENT_SHORT_CLICKED, (void *)startup_language_desc_table[i].str);
        lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC);

        lv_obj_t* label = lv_label_create(btn);
		lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
		
		lv_obj_set_style_text_font(label, &font_24, 0);
		lv_label_set_text(label, language_table_mul_language[i]);
        lv_obj_center(label);
    }
}

void startup_language_start(app_index_t app_index)
{
    if(p_startup_language != NULL)
        return;
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("startup_language",0);
    p_startup_language = (startup_language_t*)lv_mem_alloc(sizeof(startup_language_t));
    LV_ASSERT(p_startup_language);
    lv_memset(p_startup_language, 0, sizeof(startup_language_t));

	p_startup_language->app_index = app_index;
    p_startup_language->bg_cont = gui_comm_draw_bg();
	lv_obj_add_flag(p_startup_language->bg_cont, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC);
    startup_language_bg_cont(p_startup_language->bg_cont);
}

void startup_language_stop(void)
{
    lv_obj_del(p_startup_language->bg_cont);
    lv_mem_free(p_startup_language);
    p_startup_language = NULL;
}


