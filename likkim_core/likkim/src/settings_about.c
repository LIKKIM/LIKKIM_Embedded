/*********************
 *      INCLUDES
 *********************/

#include "settings_about.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

extern void settings_main_start(void);

static settings_about_t* p_settings_about = NULL;

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        settings_about_stop();
        settings_main_start();
    }
}

static void settings_about_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_about_device, title_cb);

    lv_obj_t *bg_obj = lv_obj_create(parent);
    lv_obj_remove_style_all(bg_obj);
	lv_obj_set_scroll_dir(bg_obj, LV_DIR_VER);
    lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x888888), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bg_obj, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(bg_obj, 15, LV_PART_MAIN);
    lv_obj_set_size(bg_obj, 400, 642);
    lv_obj_set_pos(bg_obj, 40, 128);

    lv_obj_t *label_model = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_model, lv_color_hex(0xffffff), 0);
    lv_obj_set_pos(label_model, 40, 36);
	set_language_string(label_model, 24, language_table_model);
    lv_obj_add_flag(label_model, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
    
    lv_obj_t *label_model_info = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_model_info, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_model_info, &font_24, 0);
    lv_obj_set_pos(label_model_info, 40, 70);
    lv_label_set_text(label_model_info, gui_data_get_modle_name());
    lv_obj_add_flag(label_model_info, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
    
    lv_obj_t *label_bluetooth_name = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_bluetooth_name, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_bluetooth_name, &font_24, 0);
    lv_obj_set_pos(label_bluetooth_name, 40, 116);
	set_language_string(label_bluetooth_name, 24, language_table_bluetooth_name);
    lv_obj_add_flag(label_bluetooth_name, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
	
    lv_obj_t *label_bluetooth_name_info = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_bluetooth_name_info, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_bluetooth_name_info, &font_24, 0);
    lv_obj_set_pos(label_bluetooth_name_info, 40, 150);
    lv_label_set_text(label_bluetooth_name_info, gui_data_get_bluetooth_name());
    lv_obj_add_flag(label_bluetooth_name_info, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
	
    lv_obj_t *label_system = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_system, lv_color_hex(0xffffff), 0);
    lv_obj_set_pos(label_system, 40, 196);
	set_language_string(label_system, 24, language_table_system);
    lv_obj_add_flag(label_system, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
	
    lv_obj_t *label_system_info = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_system_info, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_system_info, &font_24, 0);
    lv_obj_set_pos(label_system_info, 40, 230);
    lv_label_set_text(label_system_info, gui_data_get_system());
    lv_obj_add_flag(label_system_info, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
	
    lv_obj_t *label_bluetooth = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_bluetooth, lv_color_hex(0xffffff), 0);
    lv_obj_set_pos(label_bluetooth, 40, 276);
	set_language_string(label_bluetooth, 24, language_table_bluetooth);
    lv_obj_add_flag(label_bluetooth, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
	
    lv_obj_t *label_bluetooth_info = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_bluetooth_info, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_bluetooth_info, &font_24, 0);
    lv_obj_set_pos(label_bluetooth_info, 40, 310);
    lv_label_set_text(label_bluetooth_info, gui_data_get_bluetooth());
    lv_obj_add_flag(label_bluetooth_info, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
    
    lv_obj_t *label_bootloader = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_bootloader, lv_color_hex(0xffffff), 0);
    lv_obj_set_pos(label_bootloader, 40, 356);
	set_language_string(label_bootloader, 24, language_table_bootloader);
    lv_obj_add_flag(label_bootloader, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
	
    lv_obj_t *label_bootloader_info = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_bootloader_info, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label_bootloader_info, &font_24, 0);
    lv_obj_set_pos(label_bootloader_info, 40, 390);
    lv_label_set_text(label_bootloader_info, gui_data_get_bootloader());
    lv_obj_add_flag(label_bootloader_info, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
}


void settings_about_start(void)
{
    gui_algo_data_set_pagelocation("settings_about",0);
    p_settings_about = (settings_about_t*)lv_mem_alloc(sizeof(settings_about_t));
    LV_ASSERT(p_settings_about);
    lv_memset(p_settings_about, 0, sizeof(settings_about_t));

    p_settings_about->bg_cont = gui_comm_draw_bg();
    settings_about_bg_cont(p_settings_about->bg_cont);
}

 void settings_about_stop(void)
{
    lv_obj_del(p_settings_about->bg_cont);
    lv_mem_free(p_settings_about);
    p_settings_about = NULL;
}
