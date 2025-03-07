#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include "gui_comm.h"
#include "gui_data_comm.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"

// 自定义头文件
#include <linux/input.h>

#include "CalControlPara.h"
#include "algo_data_comm.h"
#include "lib.h"
#include "startup_import_word.h"
#include "startup_quick_start.h"
#include "startup_ready_check.h"
#include "usart1.h"

// 宏定义
#define DISP_WIDTH      800
#define DISP_HEIGHT     480
#define DISP_BUF_SIZE   (DISP_WIDTH * DISP_HEIGHT)
//  const char *path = "/sys/class/backlight/panel-backlight/bl_power";
#define BUTTON_PATH "/dev/input/event1"  // 按键事件设备文件路径
// 全局变量
#define SCRIPT_PATH1 "./test1.sh"
#define SCRIPT_PATH2 "./test2.sh"

// external decalration
extern char *mnemonic_read;
extern WalletInfo *infoWallet;

// variable
pthread_mutex_t lvgl_mutex = PTHREAD_MUTEX_INITIALIZER;

static void clear_fb(void) {
    lv_area_t area;
    lv_color_t buf[DISP_BUF_SIZE];

    memset(buf, 0, sizeof(buf));
    area.x1 = 0;
    area.y1 = 0;
    area.x2 = DISP_WIDTH;
    area.y2 = DISP_HEIGHT;
    fbdev_flush(NULL, &area, buf);
}

// signal handler
void handle_sigint(int sig) {
    // clean screen after exit
    clear_fb();
    printf("program exit\n");
    exit(0);
}

void handle_sigsegv(int sig) {
    // clean screen after segmentation fault
    clear_fb();
    printf("segmentation fault\n");
    exit(0);
}

// 线程 1
void *thread_ui(void *arg) {

    if (pthread_mutex_init(&lvgl_mutex, NULL) != 0) {
        printf("Mutex init failed\n");
        return -1;
    }
    /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res = 800;
    disp_drv.ver_res = 480;
    disp_drv.rotated = LV_DISP_ROT_90;
    disp_drv.sw_rotate = 1;
    lv_disp_drv_register(&disp_drv);

    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the
     * mouse position and state*/
    indev_drv_1.read_cb = evdev_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

    /////////////////////////////////////////////////////////////////////////////////////////
#if 0   //for test
    /*Create a font*/
    static lv_ft_info_t info;
    /*FreeType uses C standard file system, so no driver letter is required.*/
    info.name = "./NotoSansSC.ttf";
    info.weight = 24;
    info.style = FT_FONT_STYLE_BOLD;
    info.mem = NULL;
    if(!lv_ft_font_init(&info)) {
        LV_LOG_ERROR("create failed.");
    }
    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, info.font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t * label = lv_label_create(lv_layer_top());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "English\n你好世界");
    lv_obj_add_style(label, &style, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align(label, LV_ALIGN_CENTER, -100, -231);
#endif
    /////////////////////////////////////////////////////////////////////////////////////////
    gui_comm_init();
    gui_data_init();

    while (1) {
        GetRandomPIN();
        pthread_mutex_lock(&lvgl_mutex);
        lv_timer_handler();
        pthread_mutex_unlock(&lvgl_mutex);

        usleep(5000);
    }

    return 0;
}

extern uint8_t walletCreate;
extern void startup_screen_start(app_index_t app_index);
extern uint8_t AddressFlag;
extern uint8_t PINFlag;
extern uint8_t WalletSignFlag;
extern void startup_set_pin_start(app_index_t app_index);
extern int fd;              // 声明串口文件描述符.
extern ParsedData parsed;   // 签名数据
extern signdata sign_data;  // 签名数据
extern char **randMneonics;
uint8_t SYNC_INTERVAL = 0;
// 线程 2s
void *thread_func2(void *arg) {
    while (1) {
        if (walletCreate == 12) {  // 创建钱包标志位
            walletCreate = 0;
            walletInit(16, "");
        } else if (walletCreate == 3)  // 蓝牙输入创建钱包标志位
        {
            walletCreate = 0;
            //  startup_set_pin_start(APP_STARTUP_CREATE_WALLET);
            // mark a problem
            pthread_mutex_lock(&lvgl_mutex);
            gui_algo_data_set_pagelocation(gui_algo_data_get_pagelocation(), 1);
            gui_algo_data_get_pagelocationsave("stop");
            startup_language_start(APP_GENERAL);
            pthread_mutex_unlock(&lvgl_mutex);
        } else if (walletCreate == 18) {
            walletCreate = 0;
            walletInit(24, "");
        } else if (walletCreate == 24) {
            walletCreate = 0;
            walletInit(32, "");
        }
        if(wallet_Input_get()==1){        //创建导入钱包标志位 
            if(import_wallet_init()==1){
                gui_data_sueess(1);/*助记词已经创建成功*/
                wallet_Input_word(3);
            }      
            else{
                gui_data_sueess(0);/*助记词已经创建fail*/
                wallet_Input_word(3);
            }
        }
        if (AddressFlag == 1)  // 显示地址
        {
            pthread_mutex_lock(&lvgl_mutex);
            gui_algo_data_set_pagelocation(gui_algo_data_get_pagelocation(), 1);
            gui_algo_data_get_pagelocationsave("stop");
            // send_serial_data("Address_OK\n");
            view_addr_main_start();  // mark a problem
            pthread_mutex_unlock(&lvgl_mutex);
            AddressFlag = 0;

        }

        if (PINFlag == 1) {
            PINFlag = 0;
            pthread_mutex_lock(&lvgl_mutex);
            gui_algo_data_set_pagelocation(gui_algo_data_get_pagelocation(),
                                           1);           // 保存当前页面
            gui_algo_data_get_pagelocationsave("stop");  // 关闭当前页面
            connect_main_start();                        // mark a problem
            pthread_mutex_unlock(&lvgl_mutex);
        }

  
  


        if (WalletSignFlag == 1)  // 签名
        {
           // WalletSignFlag = 0;
            // gui_algo_data_set_pagelocation(gui_algo_data_get_pagelocation(),1);
            // gui_algo_data_get_pagelocationsave("stop");
            // view_transaction_main_start();
            pthread_mutex_lock(&lvgl_mutex);
            view_transaction_main_start();  // mark a problem
            pthread_mutex_unlock(&lvgl_mutex);

        }

        sleep(2);
        SYNC_INTERVAL++;
        if (SYNC_INTERVAL >= 1) {
            SYNC_INTERVAL = 0;
            savedata();
        }
    }
    return NULL;
}

// 创建线程
int create_thread(pthread_t *thread, void *(*start_routine)(void *),
                  const char *thread_name) {
    int ret = pthread_create(thread, NULL, start_routine, NULL);
    return 0;
}

// 按键事件检测线程的函数
void *check_button_event(void *arg) {
    int fd = open(BUTTON_PATH, O_RDONLY);  // 打开事件设备文件
    if (fd == -1) {
        perror("Failed to open input device");
        return NULL;
    }

    struct input_event ev;  // 用于存储事件
    int screen_on = 1;      // 屏幕初始状态为打开（1为开启，0为关闭）

    FILE *fileback =
        fopen("/sys/class/backlight/panel-backlight/bl_power", "w");
    if (fileback == NULL) {
        perror("Failed to open backlight control file");
        return 1;
    } else {
        printf("00000\r\n");
    }
    while (1) {
        ssize_t bytes = read(fd, &ev, sizeof(struct input_event));  // 读取事件
        if (bytes == sizeof(struct input_event)) {
            if (ev.type == EV_KEY && ev.value == 1) {  // 判断是否按下按键
                // 按键按下时切换屏幕状态
                if (screen_on) {
                    system(SCRIPT_PATH1);
                    printf("show_close\r\n");  // 熄灭屏幕
                    //  gui_algo_data_get_pagelocationsave("stop");
                    screen_on = 0;  // 更新状态为屏幕关闭
                } else {
                    system(SCRIPT_PATH2);
                    printf("show_open\r\n");  // 点亮屏幕
                    screen_on = 1;            // 更新状态为屏幕开启
                    pthread_mutex_lock(&lvgl_mutex);
                    startup_screen_start(APP_GENERAL);
                    pthread_mutex_unlock(&lvgl_mutex);
                    // gui_algo_data_get_pagelocationsave("stop");
                    //    word_set_completeture();
                }
            }
        }
    }
    fclose(fileback);
    close(fd);  // 关闭设备文件
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_t async_thread;
    pthread_t button_thread;  // 按键检测线程的ID

    signal(SIGINT, handle_sigint);
    signal(SIGSEGV, handle_sigsegv);

    // 打开串口设备
    fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    // 配置串口
    if (setup_serial_port(fd) < 0) {
        close(fd);
        return -1;
    }
    // 创建线程 1
    if (create_thread(&thread1, thread_ui, "Failed to create thread 1") <
        0) {
        close(fd);
        return -1;
    }
    // 创建线程 2
    if (create_thread(&thread2, thread_func2, "Failed to create thread 2") <
        0) {
        close(fd);
        return -1;
    }
    // 启动异步 I/O 线程
    if (create_thread(&async_thread, async_io_init, "pthread_create async") <
        0) {
        close(fd);
        return -1;
    }

    // 创建监听按键事件的线程
    // if (pthread_create(&button_thread, NULL, check_button_event, NULL) != 0)
    // {
    //     perror("Failed to create button event thread");
    //     return -1;
    // }

    // 等待所有线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    // pthread_join(read_thread, NULL);
    pthread_join(async_thread, NULL);
    // pthread_join(button_thread, NULL);

    // 关闭串口设备
    close(fd);

    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void) {
    static uint64_t start_ms = 0;
    if (start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}



void * data_get_transaction_amount(void)
{
     char str[20]; 
        sprintf(str, "%.9f",  sign_data.amount);  
        printf("%s\r\n",str);

    return str;
}

void *gui_get_transaction_fee_receiver(void) {
    return sign_data.destinationAddress;

}

void *data_get_transaction_sender(void)
{
    return sign_data.ReceiveAddress;

}