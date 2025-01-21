/*********************
 *      INCLUDES
 *********************/
#ifndef __STARTUP_VERIFICATION_H__
#define __STARTUP_VERIFICATION_H__


#include "lvgl/lvgl.h"

enum
{
	WORD_VERIFACATION_STATE_1 = 0x01,
	WORD_VERIFACATION_STATE_2 = 0x02,
	WORD_VERIFACATION_STATE_ALL = 0x03,
};
typedef uint8_t word_verification_state_t;


typedef struct
{
	lv_obj_t* bg_cont;
	lv_obj_t* label_describe1;
	lv_obj_t* label_describe2;

	lv_obj_t* btn_word[8];
	lv_obj_t* label_word[8];

	word_verification_state_t state;
	uint8_t page_id;

	uint16_t rand_num1;		//第一个随机值
	uint16_t rand_num2;		//第二个随机值
	
	lv_timer_t *timer;
} startup_verification_t;


void startup_verification_start(void);
void startup_verification_stop(void);

#endif /* __STARTUP_VERIFICATION_H__ */


