/*********************
 *      INCLUDES
 *********************/

#include "gui_comm.h"
#include "gui_data_comm.h"

// keyboard
static gui_comm_imgbtn_desc2_t gui_comm_keypad_table[] =
{
	{"back", 22, 710},
	{"confirm", 396, 710},
	{"q", 22, 582},
	{"w", 66, 582},
	{"e", 110, 582},
	{"r", 154, 582},
	{"t", 198, 582},
	{"y", 242, 582},
	{"u", 286, 582},
	{"i", 330, 582},
	{"o", 374, 582},
	{"p", 418, 582},
	{"a", 44, 646},
	{"s", 88, 646},
	{"d", 132, 646},
	{"f", 176, 646},
	{"g", 220, 646},
	{"h", 264, 646},
	{"j", 308, 646},
	{"k", 352, 646},
	{"l", 396, 646},
	{"z", 88, 710},
	{"x", 132, 710},
	{"c", 176, 710},
	{"v", 220, 710},
	{"b", 264, 710},
	{"n", 308, 710},
	{"m", 352, 710},
};

// number keyboard
static gui_comm_imgbtn_desc2_t gui_imgbtn_num_table[] =
{
    {"1", 40, 420},
    {"2", 176, 420},
    {"3", 312, 420},
    {"4", 40, 508},
    {"5", 176, 508},
    {"6", 312, 508},
    {"7", 40, 596},
    {"8", 176, 596},
    {"9", 312, 596},
    {"0", 176, 684},
};

static gui_comm_t* p_gui_comm = NULL;

static void gui_comm_timer_cb(lv_timer_t * tmr)
{
	gui_comm_state_obj_t *p_state_obj = tmr->user_data;

	if(gui_data_get_ble_connect())
		lv_img_set_src(p_state_obj->img_connect, &img_ble_connect);
	else
		lv_img_set_src(p_state_obj->img_connect, &img_ble_unconnect);
		
	if(gui_data_get_power_level() <= 10)
		lv_img_set_src(p_state_obj->img_power, &img_power_10);
	else if(gui_data_get_power_level() <= 25)
		lv_img_set_src(p_state_obj->img_power, &img_power_25);
	else if(gui_data_get_power_level() <= 50)
		lv_img_set_src(p_state_obj->img_power, &img_power_50);
	else if(gui_data_get_power_level() <= 75)
		lv_img_set_src(p_state_obj->img_power, &img_power_75);
	else if(gui_data_get_power_level() <= 100)
		lv_img_set_src(p_state_obj->img_power, &img_power_100);

	lv_label_set_text_fmt(p_state_obj->label_power, "%d%%", gui_data_get_power_level());
	
	if(gui_data_get_power_charge())
	{
		lv_obj_clear_flag(p_state_obj->img_charge, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_pos(p_state_obj->img_power, 410, 10);
	}
	else
	{
		lv_obj_add_flag(p_state_obj->img_charge, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_pos(p_state_obj->img_power, 431, 10);
	}
	
	lv_obj_align_to(p_state_obj->label_power, p_state_obj->img_power, LV_ALIGN_OUT_LEFT_MID, -10, 0);
	lv_obj_align_to(p_state_obj->img_connect, p_state_obj->label_power, LV_ALIGN_OUT_LEFT_MID, -10, 0);
}

static void gui_comm_state_bg_event_cb(lv_event_t* e)
{ 
    if (LV_EVENT_DELETE == e->code)
    {
		gui_comm_state_obj_t *p_state_obj = e->user_data;
    	lv_timer_del(p_state_obj->timer);
    }
}


lv_obj_t* gui_comm_draw_keypad_letter(lv_obj_t* parent, lv_event_cb_t num_cb, lv_event_cb_t ok_cb, lv_event_cb_t cancle_cb)
{
    for (uint8_t i = 2; i < sizeof(gui_comm_keypad_table) / sizeof(gui_comm_imgbtn_desc2_t); i++)
    {
        lv_obj_t* btn = gui_comm_draw_obj(parent, gui_comm_keypad_table[i].x, gui_comm_keypad_table[i].y, 40, 60, 15, 0x888888, 0x666666);
        lv_obj_add_event_cb(btn, num_cb, LV_EVENT_ALL, (void *)&gui_comm_keypad_table[i]);

        lv_obj_t *label = lv_label_create(btn);
        lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
        lv_obj_set_style_text_font(label, &font_24, 0);
        lv_label_set_text(label, gui_comm_keypad_table[i].str);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }
    
    lv_obj_t* btn_delete = gui_comm_draw_obj(parent, gui_comm_keypad_table[0].x, gui_comm_keypad_table[0].y, 62, 60, 15, 0xFF2600, 0x771200);
    lv_obj_add_event_cb(btn_delete, cancle_cb, LV_EVENT_ALL, (void *)&gui_comm_keypad_table[0]);
    
    lv_obj_t *img_delete = lv_img_create(btn_delete);
    lv_img_set_src(img_delete, &img_keypad2_delete);
    lv_obj_center(img_delete);
    
    lv_obj_t* btn_ok = gui_comm_draw_obj(parent, gui_comm_keypad_table[1].x, gui_comm_keypad_table[1].y, 62, 60, 15, 0x555555, 0xA4916F);
    lv_obj_add_event_cb(btn_ok, ok_cb, LV_EVENT_ALL, (void *)&gui_comm_keypad_table[1]);
	lv_obj_clear_flag(btn_ok, LV_OBJ_FLAG_CLICKABLE);
    
    lv_obj_t *img_ok = lv_img_create(btn_ok);
    lv_img_set_src(img_ok, &img_keypad_ok);
    lv_obj_center(img_ok);

    return btn_ok;
}

lv_obj_t* gui_comm_draw_keypad_num(lv_obj_t* parent, lv_event_cb_t num_cb, lv_event_cb_t ok_cb, lv_event_cb_t cancle_cb)
{
    for (uint8_t i = 0; i < sizeof(gui_imgbtn_num_table) / sizeof(gui_comm_imgbtn_desc2_t); i++)
    {
		lv_obj_t* img_btn = gui_comm_draw_obj(parent, gui_imgbtn_num_table[i].x, gui_imgbtn_num_table[i].y, 128, 80, 15, 0x888888, 0x666666);
        lv_obj_add_event_cb(img_btn, num_cb, LV_EVENT_SHORT_CLICKED, (void *)gui_imgbtn_num_table[i].str);

        lv_obj_t *label = lv_label_create(img_btn);
        lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
        lv_obj_set_style_text_font(label, &font_24, 0);
        lv_label_set_text(label, gui_imgbtn_num_table[i].str);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }
	
	lv_obj_t* img_btn_ok = lv_obj_create(parent);
    lv_obj_remove_style_all(img_btn_ok);
	lv_obj_set_size(img_btn_ok, 128, 80);
	lv_obj_set_style_bg_color(img_btn_ok, lv_color_hex(0x555555), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(img_btn_ok, LV_OPA_COVER, LV_PART_MAIN);
	lv_obj_set_style_radius(img_btn_ok, 15, 0);
    // Move the 'img_btn_ok' button to the position (312, 684).
	lv_obj_set_pos(img_btn_ok, 312, 684);
	lv_obj_add_event_cb(img_btn_ok, ok_cb, LV_EVENT_SHORT_CLICKED, NULL);
	lv_obj_add_flag(img_btn_ok, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *img_ok = lv_img_create(img_btn_ok);
    lv_img_set_src(img_ok, &img_keypad_ok);
    lv_obj_center(img_ok);

	lv_obj_t* img_btn_cancle = lv_obj_create(parent);
    lv_obj_remove_style_all(img_btn_cancle);
	lv_obj_set_size(img_btn_cancle, 128, 80);
	lv_obj_set_style_bg_color(img_btn_cancle, lv_color_hex(0xFF2600), LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(img_btn_cancle, lv_color_hex(0xFF593C), LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(img_btn_cancle, LV_OPA_COVER, LV_PART_MAIN);
	lv_obj_set_style_radius(img_btn_cancle, 15, 0);
	lv_obj_set_pos(img_btn_cancle, 40, 684);
	lv_obj_add_event_cb(img_btn_cancle, cancle_cb, LV_EVENT_SHORT_CLICKED, NULL);
	lv_obj_add_flag(img_btn_cancle, LV_OBJ_FLAG_CLICKABLE);
	
    lv_obj_t* img_canle = lv_img_create(img_btn_cancle);
    lv_img_set_src(img_canle, &img_keypad_delete);
    lv_obj_center(img_canle);

    return img_btn_ok;
}

static void slider_knob_cb(lv_event_t* e)
{
	lv_obj_t *knob = lv_event_get_target(e);
    lv_event_code_t event = lv_event_get_code(e);
    gui_comm_slider_t *slider_data = e->user_data;

    if (LV_EVENT_PRESSING == event)
    {
    	if(NULL == slider_data->cb) return;
    	
    	lv_point_t point;
    	lv_indev_t *indev = lv_indev_get_act();
    	lv_indev_get_vect(indev, &point);
    	
    	slider_data->x += point.x;

    	if(slider_data->x < 10)
    		slider_data->x = 10;
    	else if(slider_data->x >= 330)
    	{
    		slider_data->x = 330;
    		lv_img_set_src(knob, &img_slider_knob_2);
    		lv_obj_t* label = knob->user_data;
			lv_label_set_text(label, "Processing...");
			slider_data->cb();
			slider_data->cb = NULL;
    	}
		lv_obj_set_x(knob, slider_data->x);
    	
    }
    else if (LV_EVENT_RELEASED == event)
    {
    	if(slider_data->x != 185)
    	{
    		slider_data->x = 10;
			lv_obj_set_x(knob, slider_data->x);
    		lv_img_set_src(knob, &img_slider_knob_1);
    	}
    }
    else if (LV_EVENT_DELETE == event)
    {
    	printf("%s LV_EVENT_DELETE\n", __func__);
    	lv_mem_free(e->user_data);
    }
}

lv_obj_t * gui_comm_draw_slider(lv_obj_t* parent, lv_coord_t y, gui_comm_callback cb)
{
	gui_comm_slider_t *slider_data = lv_mem_alloc(sizeof(gui_comm_slider_t));
	lv_memset(slider_data, 0, sizeof(gui_comm_slider_t));
	slider_data->x = 10;
	slider_data->cb = cb;
	
    lv_obj_t *bg_obj = lv_obj_create(parent);
	lv_obj_remove_style_all(bg_obj);
	lv_obj_set_style_bg_opa(bg_obj, 255, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x4B525B), LV_PART_MAIN);
    lv_obj_set_style_radius(bg_obj, 0x7FFF, LV_PART_MAIN);
    lv_obj_set_size(bg_obj, 400, 80);
    lv_obj_set_pos(bg_obj, 40, y);

    lv_obj_t* label= lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
	set_language_string(label, 24, language_table_slide_to_reset);
	lv_obj_center(label);

    lv_obj_t* img_knob = lv_img_create(bg_obj);
	lv_img_set_src(img_knob, &img_slider_knob_1);
    lv_obj_set_pos(img_knob, slider_data->x, 10);
    lv_obj_add_event_cb(img_knob, slider_knob_cb, LV_EVENT_ALL, slider_data);
    lv_obj_add_flag(img_knob, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_user_data(img_knob, label);

	return img_knob;
}

lv_obj_t *gui_comm_draw_bg(void)
{
    lv_obj_t *bg_obj = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(bg_obj);
	lv_obj_set_scrollbar_mode(bg_obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(bg_obj, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bg_obj, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_size(bg_obj, 480, 800);
    lv_obj_center(bg_obj);
	lv_obj_update_layout(bg_obj);

    gui_comm_draw_state(bg_obj);
    
    return bg_obj;
}

lv_obj_t* gui_comm_draw_title(lv_obj_t *parent, const char **str_tab, lv_event_cb_t event_cb)
{
    if (event_cb)
    {
        lv_obj_t* back_icons = lv_img_create(parent);
        lv_img_set_src(back_icons, &img_back);
        lv_obj_set_pos(back_icons, 40, 16);
        lv_obj_add_event_cb(back_icons, event_cb, LV_EVENT_SHORT_CLICKED, NULL);
        lv_obj_add_flag(back_icons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
    }

    lv_obj_t *title = lv_label_create(parent);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(title, LV_LABEL_LONG_DOT);
    lv_obj_set_width(title, 440);
    lv_obj_set_pos(title, 40, 60);
    set_language_string(title, 40, str_tab);
    
    lv_obj_add_flag(title, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    return title;
}

lv_obj_t *gui_comm_draw_obj(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, int32_t radius, uint32_t color_default, uint32_t color_pressed)
{
    lv_obj_t* obj = lv_obj_create(parent);
	lv_obj_remove_style_all(obj);
	lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

	lv_obj_set_size(obj, w, h);
	lv_obj_set_pos(obj, x, y);
    lv_obj_set_style_bg_color(obj, lv_color_hex(color_default), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(color_pressed), LV_STATE_PRESSED);
	lv_obj_set_style_border_width(obj, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(obj, 255, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, radius, 0);

	
	return obj;
}

void gui_comm_set_state_top(void)
{
	lv_obj_move_foreground(p_gui_comm->state_bg);
}

lv_obj_t *gui_comm_draw_state(lv_obj_t *parent)
{	
	gui_comm_state_obj_t *p_state_obj = (gui_comm_state_obj_t*)lv_mem_alloc(sizeof(gui_comm_state_obj_t));
    LV_ASSERT(p_state_obj);
    lv_memset(p_state_obj, 0, sizeof(gui_comm_state_obj_t));

    lv_obj_t *bg_obj = lv_obj_create(parent);
    lv_obj_remove_style_all(bg_obj);
	lv_obj_set_scrollbar_mode(bg_obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(bg_obj, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bg_obj, LV_OPA_0, LV_PART_MAIN);
    lv_obj_set_size(bg_obj, 480, 50);
	lv_obj_update_layout(bg_obj);
	lv_obj_add_event_cb(bg_obj, gui_comm_state_bg_event_cb, LV_EVENT_ALL, p_state_obj);

    lv_obj_t* img_charge = lv_img_create(bg_obj);
    lv_img_set_src(img_charge, &img_power_charge);
    lv_obj_set_pos(img_charge, 444, 8);
    p_state_obj->img_charge = img_charge;

    lv_obj_t* img_power = lv_img_create(bg_obj);
    p_state_obj->img_power = img_power;
    
    lv_obj_t* img_connect = lv_img_create(bg_obj);
    p_state_obj->img_connect = img_connect;
    
    lv_obj_t* label_power = lv_label_create(bg_obj);
    //lv_obj_set_style_text_font(label_power, &lv_font_montserrat_12, 0);
	lv_obj_set_style_text_color(label_power, lv_color_hex(0xffffff), 0);
	p_state_obj->label_power = label_power;

	p_state_obj->timer = lv_timer_create(gui_comm_timer_cb, 1000, p_state_obj);
    lv_timer_ready(p_state_obj->timer);

    p_gui_comm->state_bg = bg_obj;

    return bg_obj;
}

void gui_comm_init(void)
{
    p_gui_comm = (gui_comm_t*)lv_mem_alloc(sizeof(gui_comm_t));
    LV_ASSERT(p_gui_comm);
    lv_memset(p_gui_comm, 0, sizeof(gui_comm_t));
}



