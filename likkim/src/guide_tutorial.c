/*********************
 *      INCLUDES
 *********************/

#include "guide_tutorial.h"
#include "gui_comm.h"

extern void guide_main_start(void);

static guide_tutorial_t* p_guide_tutorial = NULL;

static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        guide_tutorial_stop();
        guide_main_start();
    }
}

static void guide_tutorial_bg_cont(lv_obj_t* parent)
{
    lv_obj_t* back_icons = lv_img_create(parent);
    lv_img_set_src(back_icons, &img_back);
    lv_obj_set_pos(back_icons, 40, 16);
    lv_obj_add_event_cb(back_icons, title_cb, LV_EVENT_SHORT_CLICKED, NULL);
    lv_obj_add_flag(back_icons, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t *title = lv_label_create(parent);
    lv_obj_set_style_text_color(title, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(title, LV_LABEL_LONG_DOT);
    lv_obj_set_width(title, 400);
    lv_obj_set_pos(title, 40, 60);
	set_language_string(title, 40, language_table_kikkim_app_tutorial);
    lv_obj_add_flag(title, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t *bg_obj = lv_obj_create(parent);
    lv_obj_remove_style_all(bg_obj);
	lv_obj_set_scroll_dir(bg_obj, LV_DIR_VER);
	lv_obj_set_style_bg_color(bg_obj, lv_color_hex(0x888888), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bg_obj, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(bg_obj, 15, 0);
    lv_obj_set_size(bg_obj, 400, 400);
    lv_obj_set_pos(bg_obj, 40, 120);
	
    lv_obj_t *label_describe = lv_label_create(bg_obj);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 320);
	set_language_string(label_describe, 24, language_table_welcome_to_likkim);
    lv_obj_add_flag(label_describe, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_align(label_describe, LV_ALIGN_TOP_MID, 0, 36);
    lv_obj_update_layout(label_describe);
    
    if(lv_obj_get_height(label_describe) + 50 < 400)
    	lv_obj_set_size(bg_obj, 400, 400);
    else
    	lv_obj_set_size(bg_obj, 400, lv_obj_get_height(label_describe) + 72);
}


void guide_tutorial_start(void)
{
    printf("%s\n", __func__);
    gui_algo_data_set_pagelocation("guide_tutorial",0);
    p_guide_tutorial = (guide_tutorial_t*)lv_mem_alloc(sizeof(guide_tutorial_t));
    LV_ASSERT(p_guide_tutorial);
    lv_memset(p_guide_tutorial, 0, sizeof(guide_tutorial_t));

    p_guide_tutorial->bg_cont = gui_comm_draw_bg();
    guide_tutorial_bg_cont(p_guide_tutorial->bg_cont);
}

void guide_tutorial_stop(void)
{
    lv_obj_del(p_guide_tutorial->bg_cont);
    lv_mem_free(p_guide_tutorial);
    p_guide_tutorial = NULL;
}


