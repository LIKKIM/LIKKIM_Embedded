#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>   
#include <errno.h>    
#include "usart1.h"   
#include "lib.h"
#include "CalControlPara.h"
#include <stdint.h>
#include <string.h>


WalletInfo *infoWallet;
// 线程函数 1
void *thread_func1(void *arg) {

    while (1) {
         sleep(2);  // 每两秒打印一次

    }
    return NULL;
}

// 线程函数 2
void *thread_func2(void *arg) {

    while (1) {
        printf("Thread 2 running...\n");
        
        // send_serial_data("Hello, UART!\n");
        GetRandomPIN();
        sleep(2);  // 每两秒打印一次
    }
    return NULL;
}

// 启动线程的通用函数，减少重复代码
int create_thread(pthread_t *thread, void *(*start_routine)(void *), const char *thread_name) {
    int ret = pthread_create(thread, NULL, start_routine, NULL);
    if (ret != 0) {
        perror(thread_name);
        return -1;
    }
    return 0;
}

extern int fd;  // 声明串口文件描述符.

#if 0
int main() {
        pthread_t thread1, thread2;
    // pthread_t read_thread;
    pthread_t  async_thread;

    // 为 WalletInfo 分配内存并初始化
    infoWallet = (WalletInfo *)malloc(sizeof(WalletInfo));
    if (infoWallet == NULL) {
        perror("Failed to allocate memory for WalletInfo");
        return -1;
    }
   memset(infoWallet, 0, sizeof(WalletInfo)); // 初始化为 0
   
    // 调用读取函数
    ReadWalletForEmmc();
/*******************************************************************/
    // 读取路径
    ReadPathsFromEmmc();
/*******************************************************************/


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

    // 启动读取串口数据的线程
    // if (create_thread(&read_thread, read_serial_data, "pthread_create read") < 0) {
    //     close(fd);
    //     return -1;
    // }

    // 创建线程 2
    if (create_thread(&thread2, thread_func2, "Failed to create thread 2") < 0) {
        close(fd);
        return -1;
    }

        // 创建线程 1
    if (create_thread(&thread1, thread_func1, "Failed to create thread 1") < 0) {
        close(fd);
        return -1;
    }

        // 启动异步 I/O 线程
    if (create_thread(&async_thread, async_io_init, "pthread_create async") < 0) {
        close(fd);
        return -1;
    }

    // 等待所有线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    // pthread_join(read_thread, NULL);
    pthread_join(async_thread, NULL);

    // 关闭串口设备
    close(fd);

    return 0;
}
#endif