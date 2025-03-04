/*********************
 *      INCLUDES
 *********************/

#include "view_ready_waiting.h"
#include "view_transaction_waiting.h"
#include "gui_comm.h"
#include "CalControlPara.h"

extern uint8_t walletwordFlag; //数据创建成功标志位
extern char mnemonicWord[MAX_MNEMONIC_WORDS][MAX_WORD_LENGTH];
extern  void startup_invalid_recovery_start(void);
extern  void startup_import_ready_start(void);
extern uint8_t  App_Startup_Flag ;
static view_transaction_waiting_t* p_view_transaction_waiting = NULL;

static void timer_cb(lv_timer_t * tmr)
{
	p_view_transaction_waiting->angle += 100;

	lv_img_set_angle(p_view_transaction_waiting->img_waiting, p_view_transaction_waiting->angle);
    if(walletwordFlag == 1)
    {
        walletwordFlag =0;
        for(uint8_t i = 0; i < gui_data_get_word_num(); i++)
            {
                gui_data_set_word(i, mnemonicWord[i]);
            }
            view_ready_waiting_stop();
            startup_recovery_start();
    }
    if(wallet_Input_get()==3)
    {
        wallet_Input_word(0);
        if(gui_word_set_complete_state()==true)
        {
            view_ready_waiting_stop();
            startup_import_ready_start();
        }
        else if(gui_word_set_complete_state() ==false)
        {
            App_Startup_Flag =APP_STARTUP_IMPORT_WALLET;
            view_ready_waiting_stop();
            startup_invalid_recovery_start();
            

        }

    }
}

static void view_transaction_waiting_bg_cont(lv_obj_t* parent)
{
	lv_obj_t* img = lv_img_create(parent);
	lv_img_set_src(img, &img_loading);
    lv_obj_center(img);
	p_view_transaction_waiting->img_waiting = img;
	
	p_view_transaction_waiting->timer = lv_timer_create(timer_cb, 100, NULL);
}


void view_ready_waiting_start(void)
{
    gui_algo_data_set_pagelocation("view_ready_waiting",0);
    p_view_transaction_waiting = (view_transaction_waiting_t*)lv_mem_alloc(sizeof(view_transaction_waiting_t));
    LV_ASSERT(p_view_transaction_waiting);
    lv_memset(p_view_transaction_waiting, 0, sizeof(view_transaction_waiting_t));

    p_view_transaction_waiting->bg_cont = gui_comm_draw_bg();
    view_transaction_waiting_bg_cont(p_view_transaction_waiting->bg_cont);
}

 void view_ready_waiting_stop(void)
{
    lv_timer_del(p_view_transaction_waiting->timer);
    lv_obj_del(p_view_transaction_waiting->bg_cont);
    lv_mem_free(p_view_transaction_waiting);
    p_view_transaction_waiting = NULL;
}
