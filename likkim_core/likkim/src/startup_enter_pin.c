/*********************
 *      INCLUDES
 *********************/


#include "startup_enter_pin.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


extern void settings_erase_start(void);

extern void startup_language_start(app_index_t app_index);
extern void startup_set_pin_start(app_index_t app_index);
static void startup_wrong_pin_bg_cont(lv_obj_t* parent);
static void startup_enter_pin_bg_cont(lv_obj_t* parent);
extern void menu_main_start(void);


static startup_enter_pin_t* p_startup_enter_pin = NULL;

static void startup_keypad_ok_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	if(strlen(p_startup_enter_pin->pin) < 6) return;
    	
    	gui_comm_do_shake(1);
        if (0 == strcmp(p_startup_enter_pin->pin, gui_data_get_pin()))
        {
            if (p_startup_enter_pin->app_index == APP_SETTINGS_ERASE)
            {
                startup_enter_pin_stop();
                settings_erase_start();
            }
            else if (p_startup_enter_pin->app_index == APP_STARTUP)
            {
                startup_enter_pin_stop();
                menu_main_start();
            }            
        	else
            {
                uint8_t app_index = p_startup_enter_pin->app_index;
                startup_enter_pin_stop();
                startup_set_pin_start(app_index);
            }
            gui_data_set_pin_wrong_times(0);
        }
        else
        {
        	lv_memset(p_startup_enter_pin->pin, 0, sizeof(p_startup_enter_pin->pin));
        	lv_memset(p_startup_enter_pin->pin_temp, 0, sizeof(p_startup_enter_pin->pin_temp));
			lv_obj_add_flag(p_startup_enter_pin->pin_label, LV_OBJ_FLAG_HIDDEN);
			
            uint8_t pin_wrong_times = gui_data_get_pin_wrong_times() + 1;
			gui_data_set_pin_wrong_times(pin_wrong_times);

            if(pin_wrong_times == 1)
            {
				set_language_string(p_startup_enter_pin->num_label, 24, language_table_incorrect_password);
            }
            if(pin_wrong_times == 2)
            {
            	gui_data_set_pin_lock_time(1);
				set_language_string(p_startup_enter_pin->num_label, 24, language_table_incorrect_password_locked_1_min);
            }
            if(pin_wrong_times == 3)
            {
            	gui_data_set_pin_lock_time(5);
				set_language_string(p_startup_enter_pin->num_label, 24, language_table_incorrect_password_locked_5_min);
            }
            if(pin_wrong_times == 4)
            {
            	gui_data_set_pin_lock_time(60);
				set_language_string(p_startup_enter_pin->num_label, 24, language_table_incorrect_password_locked_1_hours);
            }
            if(pin_wrong_times == 5)
            {
            	gui_data_set_pin_lock_time(120);
				set_language_string(p_startup_enter_pin->num_label, 24, language_table_incorrect_password_locked_2_hours);
            }
            if(pin_wrong_times == 6)
            {
            	gui_data_set_pin_lock_time(240);
				set_language_string(p_startup_enter_pin->num_label, 24, language_table_incorrect_password_locked_4_hours);
            }
            if(pin_wrong_times == 7)
            {
            	gui_data_set_pin_lock_time(480);
				set_language_string(p_startup_enter_pin->num_label, 24, language_table_incorrect_password_locked_8_hours);
            }
            if(pin_wrong_times == 8)
            {
            	gui_data_set_pin_lock_time(480);
				set_language_string(p_startup_enter_pin->num_label, 24, language_table_incorrect_password_2_attempts);
            }
            if(pin_wrong_times == 9)
            {
            	gui_data_set_pin_lock_time(480);
				set_language_string(p_startup_enter_pin->num_label, 24, language_table_incorrect_password_1_attempt);
            }
            if(pin_wrong_times == 10)
            {
            /*这里添加接口擦除所有数据*/
            }
			lv_obj_clear_flag(p_startup_enter_pin->num_label, LV_OBJ_FLAG_HIDDEN);
			lv_obj_set_style_text_color(p_startup_enter_pin->num_label, lv_color_hex(0xff0000), 0);
        }
    }
}


static void startup_keypad_cancle_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        uint8_t pin_len = strlen(p_startup_enter_pin->pin);

        if (pin_len == 0)
        {
            return;
        }
		p_startup_enter_pin->pin[pin_len - 1] = 0;
        if (pin_len <= 6)
        {
			lv_obj_set_style_bg_color(p_startup_enter_pin->btn_ok, lv_color_hex(0x555555), LV_STATE_DEFAULT);
        }
        if (pin_len < 9)
        {
            lv_memset(p_startup_enter_pin->pin_temp, 0, 25);
            lv_memset(p_startup_enter_pin->pin_temp, '*', pin_len - 1);
            lv_obj_add_flag(p_startup_enter_pin->num_label, LV_OBJ_FLAG_HIDDEN);
        }
        else if (pin_len >= 9)
        {
            lv_memset(p_startup_enter_pin->pin_temp, '*', 8);
            lv_label_set_text_fmt(p_startup_enter_pin->num_label, "%d/24", pin_len - 1);
        }
		
		if(pin_len == 1)
			lv_obj_add_flag(p_startup_enter_pin->pin_label, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text(p_startup_enter_pin->pin_label, p_startup_enter_pin->pin_temp);
    }
}
static void startup_keypad_num_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_clear_flag(p_startup_enter_pin->pin_label, LV_OBJ_FLAG_HIDDEN);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	if(false == gui_data_get_pin_unlock())
        {
            return;
        }
        
        uint8_t pin_len = strlen(p_startup_enter_pin->pin);

        if (pin_len == 24)
        {
            return;
        }
        strcat(p_startup_enter_pin->pin, (char*)(e->user_data));
        if (pin_len >= 5)
        {
            lv_obj_set_style_bg_color(p_startup_enter_pin->btn_ok, lv_color_hex(0xCCB68C), LV_STATE_DEFAULT);
        }
        else
        {
			lv_obj_set_style_bg_color(p_startup_enter_pin->btn_ok, lv_color_hex(0x555555), LV_STATE_DEFAULT);
		}
        if (pin_len < 8)
        {
            lv_memset(p_startup_enter_pin->pin_temp, '*', pin_len);
            strcat(p_startup_enter_pin->pin_temp, (char*)(e->user_data));
            lv_obj_add_flag(p_startup_enter_pin->num_label, LV_OBJ_FLAG_HIDDEN);
        }
        else if (pin_len >= 8)
        {
            lv_memset(p_startup_enter_pin->pin_temp, '*', 7);
            p_startup_enter_pin->pin_temp[7] = *(char*)(e->user_data);
            lv_obj_clear_flag(p_startup_enter_pin->num_label, LV_OBJ_FLAG_HIDDEN);
			lv_obj_set_style_text_color(p_startup_enter_pin->num_label, lv_color_hex(0xffffff), 0);
            lv_label_set_text_fmt(p_startup_enter_pin->num_label, "%d/24", pin_len + 1);
        }

        lv_label_set_text(p_startup_enter_pin->pin_label, p_startup_enter_pin->pin_temp);
    }
}

static void startup_wrong_btn_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        startup_enter_pin_bg_cont(p_startup_enter_pin->bg_cont2);
    }
}
static void startup_enter_pin_bg_cont(lv_obj_t* parent)
{
    lv_obj_clean(parent);
    p_startup_enter_pin->btn_ok = gui_comm_draw_keypad_num(parent, startup_keypad_num_cb, startup_keypad_ok_cb, startup_keypad_cancle_cb);

    lv_obj_t* tip_label = lv_label_create(parent);
    lv_obj_set_style_text_color(tip_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(tip_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(tip_label, 400);

    if(APP_STARTUP_CREATE_WALLET == p_startup_enter_pin->app_index || 
    	APP_STARTUP_IMPORT_WALLET == p_startup_enter_pin->app_index)
		set_language_string(tip_label, 40, language_table_enter_new_pin);
    else if(APP_SETTINGS_PIN == p_startup_enter_pin->app_index)
		set_language_string(tip_label, 40, language_table_enter_old_pin);
    else if(APP_SETTINGS_ERASE == p_startup_enter_pin->app_index)
		set_language_string(tip_label, 40, language_table_enter_pin);
    else if(APP_STARTUP == p_startup_enter_pin->app_index)
		set_language_string(tip_label, 40, language_table_enter_pin);
    	
    lv_obj_set_style_text_align(tip_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(tip_label, LV_ALIGN_TOP_MID, 0, 54);
    lv_obj_update_layout(tip_label);

    lv_obj_t* pin_label = lv_label_create(parent);
    lv_obj_set_style_text_color(pin_label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(pin_label, &font_40, 0);
    lv_label_set_long_mode(pin_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(pin_label, 400);
    lv_label_set_text(pin_label, "1");
    lv_obj_set_style_text_align(pin_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(pin_label, LV_ALIGN_TOP_MID, 0, 200);
    lv_obj_add_flag(pin_label, LV_OBJ_FLAG_HIDDEN);
    p_startup_enter_pin->pin_label = pin_label;
    
    lv_obj_t* num_label = lv_label_create(parent);
    lv_obj_set_style_text_color(num_label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(num_label, &font_24, 0);
    lv_label_set_long_mode(num_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(num_label, 400);
    lv_obj_set_style_text_align(num_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(num_label, LV_ALIGN_TOP_MID, 0, 286);
    lv_obj_add_flag(num_label, LV_OBJ_FLAG_HIDDEN);
    p_startup_enter_pin->num_label = num_label;
}

static void startup_wrong_pin_bg_cont(lv_obj_t* parent)
{
    lv_obj_clean(parent);

    lv_obj_t *label_title = lv_label_create(parent);
    lv_obj_set_style_text_color(label_title, lv_color_hex(0xffffff), 0);
	set_language_string(label_title, 40, language_table_wrong_pin);
    lv_obj_set_pos(label_title, 40, 60);

    lv_obj_t* label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
	set_language_string(label_describe, 24, language_table_entered_incorrect);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_SCROLL);
    lv_obj_set_width(label_describe, 400);
    lv_obj_set_pos(label_describe, 40, 120);

    lv_obj_t* imgbtn_close = gui_comm_draw_obj(parent, 40, 690, 400, 80, 0x7FFF, 0x888888, 0x666666);
    lv_obj_add_event_cb(imgbtn_close, startup_wrong_btn_cb, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t* label_close = lv_label_create(imgbtn_close);
    lv_obj_set_style_text_color(label_close, lv_color_hex(0xffffff), 0);
	set_language_string(label_close, 24, language_table_close);
    lv_obj_center(label_close);
}

void startup_enter_pin_start(app_index_t app_index)
{
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("startup_enter_pin",0);
    p_startup_enter_pin = (startup_enter_pin_t*)lv_mem_alloc(sizeof(startup_enter_pin_t));
    LV_ASSERT(p_startup_enter_pin);
    lv_memset(p_startup_enter_pin, 0, sizeof(startup_enter_pin_t));

	p_startup_enter_pin->app_index = app_index;
    p_startup_enter_pin->bg_cont = gui_comm_draw_bg();
    
    lv_obj_t *bg_obj = lv_obj_create(p_startup_enter_pin->bg_cont);
    lv_obj_remove_style_all(bg_obj);
	lv_obj_set_scrollbar_mode(bg_obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(bg_obj, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bg_obj, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_size(bg_obj, 480, 800);
    lv_obj_center(bg_obj);
	lv_obj_update_layout(bg_obj);
	p_startup_enter_pin->bg_cont2 = bg_obj;
	
    startup_enter_pin_bg_cont(p_startup_enter_pin->bg_cont2);
    gui_comm_set_state_top();
}

void startup_enter_pin_stop(void)
{
    lv_obj_del(p_startup_enter_pin->bg_cont);
    lv_mem_free(p_startup_enter_pin);
    p_startup_enter_pin = NULL;
}

