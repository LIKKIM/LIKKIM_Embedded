/*********************
 *      INCLUDES
 *********************/

#include "general_homescreen.h"
#include "gui_comm.h"
#include "gui_data_comm.h"


static gui_comm_img_desc_t general_homescreen_img_table[] =
{
    {NULL, 16, 128, &img_small_bg1},
    {NULL, 168, 128, &img_small_bg2},
    {NULL, 320, 128, &img_small_bg3},
    {NULL, 16, 328, &img_small_bg4},
    {NULL, 168, 328, &img_small_bg5},
    {NULL, 320, 328, &img_small_bg6},
    {NULL, 16, 528, &img_small_bg7},
};

extern void general_main_start(void);

static general_homescreen_t* p_general_homescreen = NULL;


static void title_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
	    general_homescreen_stop();
	    general_main_start();
    }
}

static void bg_img_cb(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);

    if (LV_EVENT_SHORT_CLICKED == event)
    {
    	for(uint8_t i = 0; i < 7; i++)
    	{
			if(e->user_data == general_homescreen_img_table[i].src)
			{
				gui_data_set_bg_src_id(i);
			}
    	}
		lv_obj_align_to(p_general_homescreen->img_choosen, e->current_target, LV_ALIGN_TOP_LEFT, 98, 16);
    }
}

static void general_homescreen_bg_cont(lv_obj_t* parent)
{
	gui_comm_draw_title(parent, language_table_homescreen, title_cb);

    for (uint8_t i = 0; i < sizeof(general_homescreen_img_table) / sizeof(gui_comm_img_desc_t); i++)
    {
        lv_obj_t* img_bg = lv_img_create(parent);
        lv_img_set_src(img_bg, general_homescreen_img_table[i].src);
        lv_obj_set_pos(img_bg, general_homescreen_img_table[i].x, general_homescreen_img_table[i].y);
        lv_obj_add_event_cb(img_bg, bg_img_cb, LV_EVENT_SHORT_CLICKED, (void *)general_homescreen_img_table[i].src);
        lv_obj_add_flag(img_bg, LV_OBJ_FLAG_CLICKABLE);
		printf("%p\n", general_homescreen_img_table[i].src);

		if(gui_data_get_bg_src_id() == i)
		{
	        lv_obj_t* img_choosen = lv_img_create(parent);
	        lv_img_set_src(img_choosen, &img_screen_shoosen);
	        lv_obj_align_to(img_choosen, img_bg, LV_ALIGN_TOP_LEFT, 98, 16);
	        p_general_homescreen->img_choosen = img_choosen;
        }
    }
	lv_obj_move_foreground(p_general_homescreen->img_choosen);
}


void general_homescreen_start(void)
{
    gui_algo_data_set_pagelocation("general_homescreen",0);
    p_general_homescreen = (general_homescreen_t*)lv_mem_alloc(sizeof(general_homescreen_t));
    LV_ASSERT(p_general_homescreen);
    lv_memset(p_general_homescreen, 0, sizeof(general_homescreen_t));
    
    p_general_homescreen->bg_cont = gui_comm_draw_bg();
	lv_obj_add_flag(p_general_homescreen->bg_cont, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC);
    general_homescreen_bg_cont(p_general_homescreen->bg_cont);
}

void general_homescreen_stop(void)
{
    lv_obj_del(p_general_homescreen->bg_cont);
    lv_mem_free(p_general_homescreen);
    p_general_homescreen = NULL;
}


