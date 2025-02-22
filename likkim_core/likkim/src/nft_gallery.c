/*********************
 *      INCLUDES
 *********************/

#include "nft_gallery.h"
#include "gui_comm.h"
#include "menu_main.h"

static nft_gallery_t* p_nft_gallery = NULL;


static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
        nft_gallery_stop();
        menu_main_start();
    }
}

static void nft_gallery_bg_cont(lv_obj_t* parent)
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
	set_language_string(title, 40, language_table_nft_gallery);
    lv_obj_add_flag(title, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t *label_describe = lv_label_create(parent);
    lv_obj_set_style_text_color(label_describe, lv_color_hex(0xffffff), 0);
    lv_label_set_long_mode(label_describe, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_describe, 420);
	set_language_string(label_describe, 24, language_table_nft_gallery_infomation);
    lv_obj_add_flag(label_describe, LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_pos(label_describe, 40, 120);
    lv_obj_update_layout(label_describe);
}

void nft_gallery_start(void)
{
    gui_algo_data_set_pagelocation("nft_gallery",0);
    p_nft_gallery = (nft_gallery_t*)lv_mem_alloc(sizeof(nft_gallery_t));
    LV_ASSERT(p_nft_gallery);
    lv_memset(p_nft_gallery, 0, sizeof(nft_gallery_t));

    p_nft_gallery->bg_cont = gui_comm_draw_bg();
    nft_gallery_bg_cont(p_nft_gallery->bg_cont);
}

void nft_gallery_stop(void)
{
    lv_obj_del(p_nft_gallery->bg_cont);
    lv_mem_free(p_nft_gallery);
    p_nft_gallery = NULL;
}