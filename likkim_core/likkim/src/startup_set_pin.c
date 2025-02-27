/*********************
 *      INCLUDES
 *********************/

#include "startup_set_pin.h"
#include "gui_comm.h"
#include "gui_data_comm.h"

extern void startup_ready_check_start(void);
extern void finger_poweron_start(app_index_t app_index);
extern void settings_security_start(void);
extern void settings_pin_changed_start(void);
extern void startup_quick_start_start(void);
extern void settings_change_pin_start(void);
extern void startup_import_wallet_start(void);


uint8_t  App_Startup_Flag =0;


static startup_set_pin_t* p_startup_set_pin = NULL;

static void startup_keypad_ok_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	gui_comm_do_shake(1);
        if (STARTUP_SET_PIN_MODE_SET == p_startup_set_pin->mode)
        {
            if (strlen(p_startup_set_pin->set_pin) < 6)
                return;

            p_startup_set_pin->mode = STARTUP_SET_PIN_MODE_CONFIRM;
			set_language_string(p_startup_set_pin->title_label, 40, language_table_confirm_pin);
            lv_obj_add_flag(p_startup_set_pin->pin_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(p_startup_set_pin->num_label, LV_OBJ_FLAG_HIDDEN);
			lv_obj_set_style_bg_color(p_startup_set_pin->btn_ok, lv_color_hex(0x555555), LV_STATE_DEFAULT);
			lv_memset(p_startup_set_pin->pin_temp, 0, 25);
        }
        else if (STARTUP_SET_PIN_MODE_CONFIRM == p_startup_set_pin->mode)
        {
            if (strlen(p_startup_set_pin->confirm_pin) < 6)
                return;
            if (0 == strcmp(p_startup_set_pin->set_pin, p_startup_set_pin->confirm_pin))
            {
				gui_data_set_pin(p_startup_set_pin->confirm_pin);
				if(APP_STARTUP_CREATE_WALLET == p_startup_set_pin->app_index)
				{
                    uint8_t app_index = p_startup_set_pin->app_index;
                    App_Startup_Flag =APP_STARTUP_CREATE_WALLET;
                    startup_set_pin_stop();
					startup_ready_check_start();
                    if(gui_data_get_first_poweron())
						finger_poweron_start(app_index);
				}
				else if(APP_STARTUP_IMPORT_WALLET == p_startup_set_pin->app_index)
				{
                    uint8_t app_index = p_startup_set_pin->app_index;
                    App_Startup_Flag =APP_STARTUP_IMPORT_WALLET;
                    startup_set_pin_stop();
					// startup_import_wallet_start();
                    startup_ready_check_start();
                    if(gui_data_get_first_poweron())
						finger_poweron_start(app_index);
				}
				else if(APP_SETTINGS_PIN == p_startup_set_pin->app_index)
				{
                    startup_set_pin_stop();
					settings_pin_changed_start();
				}
            }
            else
            {
			    if(APP_STARTUP_CREATE_WALLET == p_startup_set_pin->app_index || 
			    	APP_STARTUP_IMPORT_WALLET == p_startup_set_pin->app_index)
					set_language_string(p_startup_set_pin->title_label, 40, language_table_enter_new_pin);
			    else if(APP_SETTINGS_PIN == p_startup_set_pin->app_index)
					set_language_string(p_startup_set_pin->title_label, 40, language_table_set_new_pin);

                p_startup_set_pin->mode = STARTUP_SET_PIN_MODE_SET;
                lv_memset(p_startup_set_pin->set_pin, 0, sizeof(p_startup_set_pin->set_pin));
                lv_memset(p_startup_set_pin->confirm_pin, 0, sizeof(p_startup_set_pin->confirm_pin));
				lv_memset(p_startup_set_pin->pin_temp, 0, 25);
                lv_obj_add_flag(p_startup_set_pin->pin_label, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(p_startup_set_pin->num_label, LV_OBJ_FLAG_HIDDEN);
            }
        }
    }
}

static void startup_keypad_cancle_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        uint8_t pin_len = 0;

        if (STARTUP_SET_PIN_MODE_SET == p_startup_set_pin->mode)
        {
            pin_len = strlen(p_startup_set_pin->set_pin);
	        if (pin_len == 0)
	        {
				if(APP_STARTUP_CREATE_WALLET == p_startup_set_pin->app_index || 
    				APP_STARTUP_IMPORT_WALLET == p_startup_set_pin->app_index)
				{
                    startup_set_pin_stop();
					startup_quick_start_start();
					return;
				}
				else if(APP_SETTINGS_PIN == p_startup_set_pin->app_index)
				{
                    startup_set_pin_stop();
					settings_change_pin_start();
					return;
				}
	        }
	        p_startup_set_pin->set_pin[pin_len - 1] = 0;
        }
        else if (STARTUP_SET_PIN_MODE_CONFIRM == p_startup_set_pin->mode)
        {
            pin_len = strlen(p_startup_set_pin->confirm_pin);
	        p_startup_set_pin->confirm_pin[pin_len - 1] = 0;
        }
        
        if (pin_len <= 6)
        {
			lv_obj_set_style_bg_color(p_startup_set_pin->btn_ok, lv_color_hex(0x555555), LV_STATE_DEFAULT);
        }
        if (pin_len < 9)
        {
            lv_memset(p_startup_set_pin->pin_temp, 0, 25);
            lv_memset(p_startup_set_pin->pin_temp, '*', pin_len - 1);
            lv_obj_add_flag(p_startup_set_pin->num_label, LV_OBJ_FLAG_HIDDEN);
        }
        else if (pin_len >= 9)
        {
            lv_memset(p_startup_set_pin->pin_temp, '*', 8);
            lv_label_set_text_fmt(p_startup_set_pin->num_label, "%d/24", pin_len - 1);
        }
		
		if(pin_len == 1)
			lv_obj_add_flag(p_startup_set_pin->pin_label, LV_OBJ_FLAG_HIDDEN);

        lv_label_set_text(p_startup_set_pin->pin_label, p_startup_set_pin->pin_temp);
    }
}
static void startup_keypad_num_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_clear_flag(p_startup_set_pin->pin_label, LV_OBJ_FLAG_HIDDEN);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        uint8_t pin_len = 0;
        if (STARTUP_SET_PIN_MODE_SET == p_startup_set_pin->mode)
        {
        	pin_len = strlen(p_startup_set_pin->set_pin);
	        if (pin_len == 24)
	        {
	            return;
	        }
			strcat(p_startup_set_pin->set_pin, (char*)(e->user_data));
        }
        else if (STARTUP_SET_PIN_MODE_CONFIRM == p_startup_set_pin->mode)
        {
        	pin_len = strlen(p_startup_set_pin->confirm_pin);
	        if (pin_len == 24)
	        {
	            return;
	        }
			strcat(p_startup_set_pin->confirm_pin, (char*)(e->user_data));
        }

        if (pin_len >= 5)
        {
            lv_obj_set_style_bg_color(p_startup_set_pin->btn_ok, lv_color_hex(0xCCB68C), LV_STATE_DEFAULT);
        }
        if (pin_len < 8)
        {
            lv_memset(p_startup_set_pin->pin_temp, '*', pin_len);
            strcat(p_startup_set_pin->pin_temp, (char*)(e->user_data));
        }
        else if (pin_len >= 8)
        {
            lv_memset(p_startup_set_pin->pin_temp, '*', 7);
            p_startup_set_pin->pin_temp[7] = *(char*)(e->user_data);
            lv_obj_clear_flag(p_startup_set_pin->num_label, LV_OBJ_FLAG_HIDDEN);
            lv_label_set_text_fmt(p_startup_set_pin->num_label, "%d/24", pin_len + 1);
        }

        lv_label_set_text(p_startup_set_pin->pin_label, p_startup_set_pin->pin_temp);
    }
}

static void startup_set_pin_bg_cont(lv_obj_t* parent)
{
    p_startup_set_pin->btn_ok = gui_comm_draw_keypad_num(parent, startup_keypad_num_cb, startup_keypad_ok_cb, startup_keypad_cancle_cb);

    lv_obj_t* title_label = lv_label_create(parent);
	lv_obj_set_style_text_color(title_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_DOT);
    lv_obj_set_width(title_label, 400);
    if(APP_STARTUP_CREATE_WALLET == p_startup_set_pin->app_index || 
    	APP_STARTUP_IMPORT_WALLET == p_startup_set_pin->app_index)
		set_language_string(title_label, 40, language_table_enter_new_pin);
    else if(APP_SETTINGS_PIN == p_startup_set_pin->app_index)
		set_language_string(title_label, 40, language_table_set_new_pin);
    	
    lv_obj_set_style_text_align(title_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 54);
    lv_obj_update_layout(title_label);
    p_startup_set_pin->title_label = title_label;

    lv_obj_t* pin_label = lv_label_create(parent);
	lv_obj_set_style_text_font(pin_label, &font_40, 0);
	lv_obj_set_style_text_color(pin_label, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(pin_label, LV_LABEL_LONG_DOT);
    lv_obj_set_width(pin_label, 400);
    lv_label_set_text(pin_label, "1");
    lv_obj_set_style_text_align(pin_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(pin_label, LV_ALIGN_TOP_MID, 0, 200);
    lv_obj_add_flag(pin_label, LV_OBJ_FLAG_HIDDEN);
    p_startup_set_pin->pin_label = pin_label;
    
    lv_obj_t* num_label = lv_label_create(parent);
    lv_obj_set_style_text_color(num_label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(num_label, &font_24, 0);
    lv_label_set_long_mode(num_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(num_label, 400);
    lv_obj_set_style_text_align(num_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(num_label, LV_ALIGN_TOP_MID, 0, 286);
    lv_obj_add_flag(num_label, LV_OBJ_FLAG_HIDDEN);
    p_startup_set_pin->num_label = num_label;
}

void startup_set_pin_start(app_index_t app_index)
{
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("startup_set_pin",0);
    p_startup_set_pin = (startup_set_pin_t*)lv_mem_alloc(sizeof(startup_set_pin_t));
    LV_ASSERT(p_startup_set_pin);
    lv_memset(p_startup_set_pin, 0, sizeof(startup_set_pin_t));

	p_startup_set_pin->app_index = app_index;
    p_startup_set_pin->bg_cont = gui_comm_draw_bg();
    startup_set_pin_bg_cont(p_startup_set_pin->bg_cont);
    gui_comm_set_state_top();
}

void startup_set_pin_stop(void)
{
    lv_obj_del(p_startup_set_pin->bg_cont);
    lv_mem_free(p_startup_set_pin);
    p_startup_set_pin = NULL;
}


