/*********************
 *      INCLUDES
 *********************/
#ifndef __GUI_DATA_COMM_H__
#define __GUI_DATA_COMM_H__


#include "lvgl/lvgl.h"
#include <string.h>
#include <stdio.h>

#define WALLET_LIB_USED		0

// 语言选项枚举
enum 
{
	LANGUAGE_ENGLISH,                  // 英语
	LANGUAGE_CHINES,                   // 中文
	LANGUAGE_TRADITIONAL_CHINESE,      // 繁体中文
	LANGUAGE_FRANCAIS,                 // 法语
	LANGUAGE_SPANISH,                  // 西班牙语
	LANGUAGE_ARABIC,                   // 阿拉伯语
	LANGUAGE_JAPANESE,                 // 日语
	LANGUAGE_RUSSIAN,                  // 俄语
	LANGUAGE_KOREAN,                   // 韩语
	LANGUAGE_PORTUGUESE,               // 葡萄牙语
	LANGUAGE_PORTUGUESE_BRAZIL,        // 巴西葡萄牙语
	LANGUAGE_ITALIAN,                  // 意大利语
	LANGUAGE_GERMAN,                   // 德语
	LANGUAGE_HINDI,                    // 印地语
	LANGUAGE_MONGOLIAN,                // 蒙古语
	LANGUAGE_THAI,                     // 泰语
	LANGUAGE_UKRAINIAN,                // 乌克兰语
	LANGUAGE_VIETNAMESE,               // 越南语
	LANGUAGE_INDONESIAN,               // 印尼语
	LANGUAGE_TAGALOG,                  // 塔加洛语
	LANGUAGE_BENGALI,                  // 孟加拉语
	LANGUAGE_MAX,                      // 语言选项的最大值
};
typedef uint8_t language_type_t;

typedef struct
{
	uint16_t last_rand;		//随机种子
	uint8_t bg_src_id;		//保存的背景图序号
	void *bg_src;			//背景图资源
	
	char pin[8];			//保存的密码
	char language[32];		//保存的多语言字符串
	language_type_t language_type;	//保存的多语言类型

	bool  word_set_complete;	//助记词设置完成
	uint8_t word_num;		//设置的助记词数量
	char word[24][50];		//保存的助记词内容

	int lock_time;			//锁屏时间，单位min，-1是never
	int shutdown_time;		//关机时间，单位min，-1是never
	uint32_t pin_lock_min;		//密码锁定时间，单位min
	uint32_t pin_error_timestamp;	//密码输入错误时间戳

	uint8_t fingerprint_num;	//指纹数量, 0-3
	uint8_t fingerprint_process;	//指纹数量,0-6
	uint8_t fingerprint_remove_id;	//当前要移除的指纹id,0-3

	uint8_t power_level;		//电量
	uint8_t power_charge;		//充电状态
	uint8_t ble_connect;		//蓝牙链接状态

	uint8_t first_poweron;		//首次开机
	
	uint8_t pin_wrong_times;		//密码输入错误次数
} gui_data_t;


typedef struct
{
	char address_data[100];//地址数据
	char address_datapath[50];//path数据

	char  page_location[50];//页面定位状态
	char pagt_location_save[50];//保存数据页面

} gui_algo_data_t;


uint16_t get_rand_num(uint16_t max);

/*获取modle名称*/
void *gui_data_get_modle_name(void);
/*获取bluetooth名称*/
void *gui_data_get_bluetooth_name(void);
/*获取system*/
void *gui_data_get_system(void);
/*获取system*/
void *gui_data_get_bluetooth(void);
/*获取bootloader*/
void *gui_data_get_bootloader(void);


/*获取Address的标题*/
void *gui_data_get_address_title(void);
/*获取Address的内容*/
void *gui_data_get_address_info(void);
/*获取Address的path*/
void *gui_data_get_address_path(void);

/*获取fee_payer的内容*/
void *gui_data_get_transaction_fee_receiver(void);
/*获取fomat的内容*/
void *gui_data_get_transaction_format(void);
/*获取amount的内容*/
void *gui_data_get_transaction_amount(void);

void savedata(void);

uint8_t gui_data_get_bg_src_id(void);
void *gui_data_get_bg_src(void);
void gui_data_set_bg_src_id(uint8_t id);
language_type_t gui_data_get_language_type(void);
char *gui_data_get_language(void);
void gui_data_set_language(char *language);
char *gui_data_get_pin(void);
void gui_data_set_pin(char *pin);
uint8_t gui_data_get_word_num(void);;
void gui_data_set_word_num(uint8_t word_num);
char *gui_data_get_word(uint8_t word_index);
void gui_data_set_word(uint8_t word_index, char *word);
int gui_data_get_shutdown_time(void);
void gui_data_set_shutdown_time(int shutdown_time);
int gui_data_get_lock_time(void);
void gui_data_set_lock_time(int lock_time);
uint8_t gui_data_get_fingerprint_num(void);
void gui_data_set_fingerprint_num(uint8_t num);

uint8_t gui_data_get_fingerprint_process(void);
void gui_data_set_fingerprint_process(uint8_t process);
uint8_t gui_data_get_fingerprint_remove_id(void);
void gui_data_set_fingerprint_remove_id(uint8_t remove_id);


uint8_t gui_data_get_power_level(void);
void gui_data_set_power_level(uint8_t power_level);
uint8_t gui_data_get_power_charge(void);
void gui_data_set_power_charge(uint8_t power_charge);
uint8_t gui_data_get_ble_connect(void);
void gui_data_set_ble_connect(uint8_t conncet);

/*获取是否是首次启动设备*/
uint8_t gui_data_get_first_poweron(void);
void gui_data_set_first_poweron(uint8_t first_poweron);

uint8_t gui_data_get_pin_wrong_times(void);
void gui_data_set_pin_wrong_times(uint8_t pin_wrong_times);
uint8_t gui_data_get_pin_unlock(void);
void gui_data_set_pin_lock_time(uint32_t lock_time);

bool gui_data_get_remind_word(char* str, char** char_tab);
char *gui_data_get_random_word(char *str);


void gui_data_init(void);
void gui_data_deinit(void);


void gui_comm_do_shake(uint8_t count);
uint8_t wallet_Input_get(void);
void wallet_Input_word(uint8_t count);
uint8_t import_wallet_init(void);

uint8_t gui_algo_data_set_address(char count[100]);
uint8_t gui_algo_data_set_addresspath(char *count);
void gui_algo_data_set_pagelocation(char * count,uint8_t countsave);
uint8_t gui_algo_data_get_pagelocationsave(char *state);
char * gui_algo_data_get_pagelocation(void);
void gui_rest_data(void);
void word_set_completeture(void);

#endif /* __GUI_DATA_COMM_H__ */


