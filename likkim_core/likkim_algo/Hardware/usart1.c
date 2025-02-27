#include  "usart1.h"


#define READ_BUF_SIZE 256
#define CMD_BUF_SIZE 1024


int fd; // 串口文件描述符
volatile int running = 1;  // 控制线程是否继续运行
signdata sign_data; //签名数据
 extern uint8_t walletCreate ;
extern WalletInfo *infoWallet;//钱包
extern uint8_t walletInput;
 char *bch_sign=NULL;//签名数据


// 从串口读取数据并打印
void *read_serial_data(void *arg) {
    char read_buf[256];
    int n;

    while (running) {
        // 从串口读取数据
        n = read(fd, read_buf, sizeof(read_buf) - 1);
        if (n < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // 如果没有数据，跳过
                continue;
            }
            perror("read");
            break;
        }

        // 打印接收到的数据
        read_buf[n] = '\0';  // 确保数据是一个有效的字符串
        printf("Received data: %s\n", read_buf);
    }

    return NULL;
}

// 设置串口为异步 I/O 模式
int setup_serial_port(int fd) {
    struct termios options;

    // 获取当前串口设置
    if (tcgetattr(fd, &options) < 0) {
        perror("tcgetattr");
        return -1;
    }

    // 设置波特率
    cfsetispeed(&options, B115200);  // 输入波特率
    cfsetospeed(&options, B115200);  // 输出波特率

    // 配置数据位、停止位、校验位
    options.c_cflag &= ~PARENB;    // 无校验
    options.c_cflag &= ~CSTOPB;    // 1个停止位
    options.c_cflag &= ~CSIZE;     // 清除数据位设置
    options.c_cflag |= CS8;        // 8个数据位

    // // 设置串口工作模式
    // options.c_cflag |= CLOCAL | CREAD;  // 本地连接，启用接收
    // options.c_iflag &= ~(IXON | IXOFF | IXANY); // 禁用软件流控制
    // options.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // 禁用标准输入模式

        // 设置串口工作模式
    options.c_cflag |= CLOCAL | CREAD;  // 本地连接，启用接收
    options.c_iflag &= ~(IXON | IXOFF | IXANY); // 禁用软件流控制
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // 禁用标准输入模式和回显
    options.c_oflag &= ~OPOST; // 禁用输出处理

    // 设置串口超时
    options.c_cc[VMIN] = 1;       // 最小读取字符数
    options.c_cc[VTIME] = 5;      // 超时时间为 0.5秒

    // 应用设置
    if (tcsetattr(fd, TCSANOW, &options) < 0) {
        perror("tcsetattr");
        return -1;
    }

    return 0;
}




// 解析数据函数
int parse_sign_data(const char *input, ParsedData *parsed) {
    const char *sign_prefix = "sign:";

    // 检查输入格式是否正确
    if (strncmp(input, sign_prefix, strlen(sign_prefix)) != 0) {
        fprintf(stderr, "Invalid sign data format.\n");
        return -1;
    }

    // 跳过 "sign:"
    input += strlen(sign_prefix);

    // 查找第一个逗号（币种和币种路径之间）
    const char *coin_end = strchr(input, ',');
    if (coin_end == NULL) {
        fprintf(stderr, "Coin and path are missing.\n");
        return -1;
    }

    // 提取币种
    size_t coin_len = coin_end - input;
    strncpy(parsed->coin, input, coin_len);
    parsed->coin[coin_len] = '\0';

    // 查找第二个逗号（币种路径和sign数据之间）
    const char *path_end = strchr(coin_end + 1, ',');
    if (path_end == NULL) {
        fprintf(stderr, "Path is missing.\n");
        return -1;
    }

    // 提取币种路径
    size_t path_len = path_end - (coin_end + 1);
    strncpy(parsed->path, coin_end + 1, path_len);
    parsed->path[path_len] = '\0';

    // 提取 sign 数据（从路径后的逗号到末尾）
    const char *sign_data_start = path_end + 1;
    size_t sign_data_len = strlen(sign_data_start);

    // 直接提取 sign 数据
    strncpy(parsed->sign_data, sign_data_start, sign_data_len);
    parsed->sign_data[sign_data_len] = '\0';

    return 0;
}

// 解析字符串并分段
extern uint8_t WalletSignFlag;
void parse_destination_address(char *command) {
    // 获取 "destinationAddress:" 后的部分
    char *data = command + 19;

    // 通过逗号分割字符串
    char *token = strtok(data, ",");
    int field_count = 0;

    while (token != NULL) {
        switch (field_count) {
            case 0: // destinationAddress ReceiveAddress
                strncpy(sign_data.destinationAddress, token, sizeof(sign_data.destinationAddress) - 1);
                break;
            case 1: //  ReceiveAddress
                strncpy(sign_data.ReceiveAddress, token, sizeof(sign_data.ReceiveAddress) - 1);
                break;
            case 2: // amount
                sign_data.amount = atof(token);
                break;
            case 3: // coin
                strncpy(sign_data.coin, token, sizeof(sign_data.coin) - 1);
                break;
            case 4: // path
                strncpy(sign_data.path, token, sizeof(sign_data.path) - 1);
                break;
            default:
                printf("Unexpected data: %s\n", token);
                break;
        }
        token = strtok(NULL, ",");
        field_count++;
    }
    WalletSignFlag =1;
}

void parse_pubkey_data(char *command) {
    // 获取 "pubkey:" 后的部分
    char *data = command + 7;  // "pubkey:" 的长度为7

    // 通过逗号分割字符串
    char *token = strtok(data, ",");
    int field_count = 0;
    char coin[20] = {0};  // 清空 coin 数组
    char coinAddress[20] = {0};  // 清空 coinAddress 数组

    while (token != NULL) {
        switch (field_count) {
            case 0: // coin (币种)
                strncpy(coin, token, sizeof(coin) - 1);  // 使用 strncpy 来确保不会溢出
                break;
            case 1: // coinAddress (币种地址)
                strncpy(coinAddress, token, sizeof(coinAddress) - 1);  // 使用 strncpy 来确保不会溢出
                break;
            default:
                printf("Unexpected data: %s\n", token);
                break;
        }
        token = strtok(NULL, ",");
        field_count++;
    }

    if (coin[0] != '\0' && coinAddress[0] != '\0') {
        // 调用 get_chain_pubkey 函数，将解析后的币种和币种地址传递进去
        send_serial_data("pubkeyData:%s,%s\r\n",coin,get_chain_pubkey(coin, infoWallet->seed, infoWallet->seed_len,coinAddress));
    } else {
        printf("Error: coin or coinAddress is missing.\n");
    }

}


// 处理传入的命令
ParsedData parsed; //签名数据
void parse_command(char *command) {
    // 处理包含 sign: 的数据
       if (strncasecmp(command, "sign:", 5) == 0) {
        if (parse_sign_data(command, &parsed) == 0) {
            
            printf("Parsed sign data:\nCoin: %s\nPath: %s\nSign Data: %s\n", 
                   parsed.coin, parsed.path, parsed.sign_data);
            bch_sign = sign_tx( parsed.coin,parsed.sign_data, infoWallet->seed, infoWallet->seed_len, parsed.path);
            // 使用 memcpy 来复制字符串
            memcpy(parsed.bch_sign, bch_sign,strlen(bch_sign)+1); // 留出空间给 '\0'

             send_serial_data("signed_data:%s,%s\n",parsed.coin,  parsed.bch_sign);
            //  send_serial_data("signed_data:%s\n",parsed.coin);
           
        }
    } 
    // 处理其他命令
     else if (strncasecmp(command, "validation", 10) == 0) {
        PINCodeWalletSend();
    } 
    else if (strncasecmp(command, "create:", 7) == 0) {
        const char *entropy_len_str = command + 7;
        int entropy_len = atoi(entropy_len_str);
        if (entropy_len >= 16 && entropy_len <= 32) {
            walletInit(entropy_len, "");
             
            walletCreate = 3;
        } else {
            printf("Invalid entropy_len: %s\n", entropy_len_str);
        }
    } 
    else if (strncasecmp(command, "Import", 6) == 0) {
        printf("Import wallet\n");
        walletInput = 1;
        // 添加 Import wallet 的处理逻辑
    } 
    else if (strncasecmp(command, "address:", 8) == 0) {
        char *address_list = command + 8;
        printf("Calling addressSend with: %s\n", address_list);
        sendCoinAddress(address_list); // 发送当前币种地址
    } 
    else if (strncasecmp(command, "address", 7) == 0) {
        adressAllSend();
    } 
    // 添加新的处理逻辑，用于修改地址路径
    else if (strncasecmp(command, "modify:", 7) == 0) {
        modify_address(command); // 调用修改地址的函数
        SaveAddressPathsToEmmc();
    } 
    else if(strncasecmp(command, "destinationAddress:", 19) == 0){
        parse_destination_address(command);
        // WalletSignFlag =1;
    }
    else if(strncasecmp(command, "pubkey:", 7) == 0){
         parse_pubkey_data(command);
    }
    else if(strncasecmp(command, "ping", 4) == 0){
        send_serial_data("pong\n");
    }
    else {
        printf("Unrecognized command: %s\n", command);
    }
}

void *async_io_init(void *arg) {
    fd_set readfds;
    char command_buf[CMD_BUF_SIZE] = {0};  // 拼接命令的缓冲区
    int command_len = 0;
   
    while (running) {
        // 配置文件描述符集
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        // 阻塞直到串口数据可读
        int ret = select(fd + 1, &readfds, NULL, NULL, NULL);  // NULL表示无限阻塞
        if (ret == -1) {
            perror("select");
            continue;
        }

        if (FD_ISSET(fd, &readfds)) {
            char read_buf[READ_BUF_SIZE];
            memset(read_buf, 0, sizeof(read_buf));

            // 读取数据
            int n = read(fd, read_buf, sizeof(read_buf) - 1);
            if (n < 0) {
                perror("read");
                continue;
            }

            read_buf[n] = '\0'; // 确保是有效字符串

            // 将读取到的数据拼接到命令缓冲区
            if (command_len + n < CMD_BUF_SIZE) {
                memcpy(command_buf + command_len, read_buf, n);
                command_len += n;
                command_buf[command_len] = '\0';
            } else {
                fprintf(stderr, "Command buffer overflow. Clearing buffer.\n");
                command_len = 0;
                memset(command_buf, 0, CMD_BUF_SIZE);
            }

            // 检查是否接收到完整命令（假设以 '\n' 为结束标志）
            char *newline_pos = strchr(command_buf, '\n');
            while (newline_pos != NULL) {
                *newline_pos = '\0'; // 替换换行符为字符串结束符

                // 解析完整命令
                parse_command(command_buf);

                // 移动未处理的数据到缓冲区开头
                int remaining_len = command_len - (newline_pos - command_buf + 1);
                memmove(command_buf, newline_pos + 1, remaining_len);
                command_len = remaining_len;
                command_buf[command_len] = '\0';

                // 检查是否还有新的命令
                newline_pos = strchr(command_buf, '\n');
            }
        }
    }

    return NULL;
}

    //发送数据到串口
// void send_serial_data(const char *data) {
//     int n = write(fd, data, strlen(data));
//     if (n < 0) {
//         perror("write");
//     } else {
//         printf("Sent data: %s\n", data);
//     }
// }


void send_serial_data(const char *format, ...) {
    char buffer[256]; // 调整缓冲区大小，适应较长字符串

    // 可变参数处理
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // 检查缓冲区溢出（vsnprintf 返回值）
    if (strlen(buffer) >= sizeof(buffer)) {
        fprintf(stderr, "Warning: Data truncated during formatting.\n");
    }

    // 发送数据到串口
    int n = write(fd, buffer, strlen(buffer));
    if (n < 0) {
        perror("write");
    } else {
        printf(" %s\n", buffer);
    }
}





