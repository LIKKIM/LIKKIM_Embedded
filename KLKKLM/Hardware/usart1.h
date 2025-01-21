#ifndef  USART_H_
#define USART_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <pthread.h>  // 需要引入 pthread 库
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <assert.h>
#include <stdarg.h>
#include "lib.h"
#include "CalControlPara.h"

#define SERIAL_PORT "/dev/ttySTM0"

#define CMD_BUF_SIZE 1024
#define READ_BUF_SIZE 256

// 保存解析后的数据结构
typedef struct {
    char coin[100];       // 币种
    char path[200];       // 币种路径
    char sign_data[CMD_BUF_SIZE];  // sign数据
} ParsedData;

typedef struct {
    char destinationAddress[256];
    float amount;
    char coin[32];
    char path[64];
} signdata ;



void *read_serial_data(void *arg);
void *async_io_init(void *arg);
int setup_serial_port(int fd);
// void send_serial_data(const char *data);
void send_serial_data (const char *format, ...);
#endif
