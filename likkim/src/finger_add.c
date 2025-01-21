/*********************
 *      INCLUDES
 *********************/

#include "finger_add.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


static finger_add_t* p_finger_add = NULL;

extern void settings_security_start(void);
extern void finger_start_start(void);
extern void finger_remove_start(void);

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
	    finger_add_stop();
	    settings_security_start();
    }
}

static void finger_add_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        finger_add_stop();
    	finger_start_start();
    }
}

static void finger_remove_handler(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	uint8_t remoev_id = (lv_obj_get_y(e->current_target) - 123) / 90 + 1;
    	gui_data_set_fingerprint_remove_id(remoev_id);
        finger_add_stop();
    	finger_remove_start();
    }
}

static void finger_add_bg_cont(lv_obj_t* parent)
{
    gui_comm_draw_title(parent, language_table_fingerprint, title_cb);

    for (uint8_t i = 0; i < gui_data_get_fingerprint_num(); i++)
    {
        lv_obj_t* btn_finger = gui_comm_draw_obj(parent, 40, 123 + 90 * i, 400, 80, 0x7FF, 0x222222, 0x111111);
        lv_obj_add_event_cb(btn_finger, finger_remove_handler, LV_EVENT_SHORT_CLICKED, NULL);

    	lv_obj_t* add_icons = lv_img_create(btn_finger);
    	lv_img_set_src(add_icons, &img_fingerprint);
    	lv_obj_set_pos(add_icons, 42, 24);

        lv_obj_t *label_add = lv_label_create(btn_finger);
		lv_obj_set_style_text_font(label_add, &font_24, 0);
        lv_obj_set_style_text_color(label_add, lv_color_hex(0xffffff), 0);
        lv_label_set_long_mode(label_add, LV_LABEL_LONG_DOT);
        lv_obj_set_width(label_add, 300);
        lv_obj_set_pos(label_add, 92, 25);
        lv_label_set_text_fmt(label_add, "%s %d", language_table_finger[gui_data_get_language_type()], i +1);
    }

/*添加指纹按键*/
    lv_obj_t* btn_add = gui_comm_draw_obj(parent, 40, 123 + 90 * gui_data_get_fingerprint_num(), 400, 80, 0x7FF, 0x222222, 0x111111);
    lv_obj_add_event_cb(btn_add, finger_add_handler, LV_EVENT_SHORT_CLICKED, NULL);

	lv_obj_t* add_icons = lv_img_create(btn_add);
	lv_img_set_src(add_icons, &img_add);
	lv_obj_set_pos(add_icons, 40, 24);

    lv_obj_t *label_add = lv_label_create(btn_add);
    lv_obj_set_style_text_color(label_add, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_add, LV_LABEL_LONG_DOT);
    lv_obj_set_width(label_add, 300);
    lv_obj_set_pos(label_add, 92, 25);
    set_language_string(label_add, 24, language_table_add_fingerprint);


/*说明文本*/
    lv_obj_t *label_prompt = lv_label_create(parent);
    lv_obj_set_style_text_color(label_prompt, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_prompt, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_prompt, 400);
    lv_obj_set_pos(label_prompt, 40, 223 + 90 * gui_data_get_fingerprint_num());
    set_language_string(label_prompt, 24, language_table_add_finger_prompt);

/*unlock */
    lv_obj_t* btn_unlock = gui_comm_draw_obj(parent, 40, 123 + 90 * gui_data_get_fingerprint_num(), 400, 80, 0x7FF, 0x4B525B, 0x4B525B);
    lv_obj_add_event_cb(btn_unlock, NULL, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_align_to(btn_unlock, label_prompt, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

    lv_obj_t *label_unlock = lv_label_create(btn_unlock);
    lv_obj_set_style_text_color(label_unlock, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_unlock, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_unlock, 400);
    lv_obj_set_pos(label_unlock, 40, 26);
    set_language_string(label_unlock, 24, language_table_unlock_device);

    lv_obj_t *switch_unlock = lv_switch_create(btn_unlock);
    lv_obj_set_style_bg_color(switch_unlock, lv_color_hex(0x222222), 0);
    lv_obj_set_pos(switch_unlock, 300, 20);
    lv_obj_set_size(switch_unlock, 80, 40);
    lv_obj_set_style_bg_color(switch_unlock, lv_color_hex(0x222222), 0);
    lv_obj_set_style_bg_color(switch_unlock, lv_color_hex(0x10E807), LV_PART_INDICATOR | LV_STATE_CHECKED);
}

void finger_add_start(void)
{
     gui_algo_data_set_pagelocation("finger_add",0);
    p_finger_add = (finger_add_t*)lv_mem_alloc(sizeof(finger_add_t));
    LV_ASSERT(p_finger_add);
    lv_memset(p_finger_add, 0, sizeof(finger_add_t));

    p_finger_add->bg_cont = gui_comm_draw_bg();
    finger_add_bg_cont(p_finger_add->bg_cont);
}

 void finger_add_stop(void)
{
    lv_obj_del(p_finger_add->bg_cont);
    lv_mem_free(p_finger_add);
    p_finger_add = NULL;
}
