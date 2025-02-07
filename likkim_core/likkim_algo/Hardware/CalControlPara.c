#include "CalControlPara.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
// #include "view_addr_main.h"

// 定义所有币种的地址信息
 AddressInfo address_list[] = {
    {"bitcoin", "m/49'/0'/0'/0/0"},
    {"ethereum", "m/44'/60'/0'/0/0"},
    {"tron", "m/44'/195'/0'/0/0"},
    {"bitcoin_cash", "m/44'/145'/0'/0/0"},
    {"binance", "m/44'/60'/0'/0/0"},
    {"optimism", "m/44'/60'/0'/0/0"},
    {"ethereum_classic", "m/44'/60'/0'/0/0"},
    {"litecoin", "m/49'/2'/0'/0/0"},
    {"ripple", "m/44'/144'/0'/0/0"},
    {"solana", "m/44'/501'/0'/0/0"},
    {"arbitrum", "m/44'/60'/0'/0/0"},

    {"cosmos", "m/44'/118'/0'/0/0"},
    {"celestia", "m/44'/118'/0'/0/0"},
    {"cronos", "m/44'/60'/0'/0/0"},
    {"juno", "m/44'/118'/0'/0/0"},
    {"osmosis", "m/44'/118'/0'/0/0"},

    {"aurora", "m/44'/60'/0'/0/0"},
    {"avalanche", "m/44'/60'/0'/0/0"},
    {"celo", "m/44'/60'/0'/0/0"},
    {"fantom", "m/44'/60'/0'/0/0"},
    {"gnosis", "m/44'/60'/0'/0/0"},
    {"huobi", "m/44'/60'/0'/0/0"},
    {"iotex", "m/44'/60'/0'/0/0"},
    {"okx", "m/44'/60'/0'/0/0"},
    {"polygon", "m/44'/60'/0'/0/0"},
    {"zksync", "m/44'/60'/0'/0/0"},

    {"aptos", "m/44'/637'/0'/0'/0"},
    {"sui", "m/44'/784'/0'/0'/0"},
    {"cardano", "m/1852'/1815'/0'/0/0"},
    {"linea", "m/44'/60'/0'/0/0"},
    {"ronin", "m/44'/60'/0'/0/0"},

};



 extern WalletInfo *infoWallet;//钱包

uint16_t PIN_number=0;//PIN
uint8_t PINFlag =0;
uint8_t entropy[50]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}; //熵
int entropy_Len=0;//熵长度(16/20/24/28/32)
uint8_t AddressFlag =0;//address 标志位
uint8_t walletwordFlag =0; //数据创建成功标志位

 char mnemonicWord[MAX_MNEMONIC_WORDS][MAX_WORD_LENGTH]={0};  // 助记词，每个单词最大 20 个字符，最多 12 个单词
char input[256];

// 全局变量声明
uint8_t adressFlag_read = 0;            // 用于读取地址标志

#define DATA_FILE_PATH "/home/root/wallet_path.bin"

// 使用标准库的随机数生成
uint32_t rng_get_random(void) {
    return rand();
}


char* uint16_to_str(uint16_t PIN_number) {
    // 计算所需的字符数并动态分配内存
    char* charPIN = (char*)malloc(6 * sizeof(char)); // 最大值为 65535，所以 6 字符够用（包括 '\0'）

    if (charPIN == NULL) {
        // 内存分配失败
        return NULL;
    }

    // 使用 sprintf 转换
    sprintf(charPIN, "%d", PIN_number);

    return charPIN; // 返回转换后的字符串
}

// 返回 0000 到 9999 之间的随机数
uint16_t GetRandomPIN(void) {
    uint16_t pin;
    do {
        pin = rand() % 10000; // 生成 0 到 9999 的随机数
    } while (pin < 1000);      // 如果小于 1000，说明第一位是 0，重新生成
    return pin;
}

int get_mnemonic_count(int entropy_Len) {
    switch (entropy_Len) {
        case 16: return 12;
        case 20: return 15;
        case 24: return 18;
        case 28: return 21;
        case 32: return 24;
        default: return 0;  // 错误的熵长度
    }
}

void sanitize_string(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (!isspace((unsigned char)*src) || *src == ' ') { // 保留空格，移除其他空白符
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0'; // 确保字符串以 '\0' 结尾
}


// 返回 0 到 255 的随机数
uint8_t GetRandom0To255(void) {
    uint32_t random_number = rng_get_random();
    return random_number % 256;
}


// 填充数组
void fillArrayWithRandomNumbers(  uint8_t array[], uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        array[i] = GetRandom0To255();
    }
}

// 拆分助记词字符串的函数
int split_string_to_array(const char *input, char output[][50], int max_words) {
    char buffer[256];  // 假设输入字符串不会超过 256 字节
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    // 清空数组
    memset(output, 0, sizeof(char) * max_words * 40);

    int i = 0;
    char *token = strtok(buffer, " \n\r\t");  // 分割字符串，去掉多余空白符
    while (token != NULL && i < max_words) {
        strncpy(output[i], token, 40 - 1);  // 确保不溢出
        output[i][40 - 1] = '\0';           // 确保字符串以 '\0' 结尾
        i++;
        token = strtok(NULL, " \n\r\t");
    }
    return i;  // 返回实际分割的单词数量
}


// 定义一个函数，将多个字符串拼接到一起
int concatenateStrings(char result[], char strs[][50], int numStrings) {
    result[0] = '\0';  // 清空结果字符串
    int resultLength = 0;  // 初始化长度为0
    
    for (int i = 0; i < numStrings; ++i) {
        strcat(result, strs[i]);  // 拼接当前字符串
        resultLength += strlen(strs[i]);  // 更新长度
        
        if (i < numStrings - 1) {
            strcat(result, " ");  // 添加空格
            resultLength += 1;  // 空格也需要计入长度
        }
    }
    
    return resultLength;  // 返回拼接后的字符串长度
}

// 根据命令修改地址路径
void modify_address(const char *command) {
    char coin_name[50];  // 用于存储币种名称
    char new_path[200];  // 用于存储新的路径

    // 解析命令，提取币种名称和新的路径
    if (sscanf(command, "modify:%49[^,],%199s", coin_name, new_path) == 2) {
        // 遍历 address_list 查找对应币种
        for (int i = 0; i < sizeof(address_list) / sizeof(address_list[0]); i++) {
            if (strcmp(address_list[i].name, coin_name) == 0) {
                // 找到匹配的币种，修改其路径
                strncpy(address_list[i].path, new_path, sizeof(address_list[i].path) - 1);
                address_list[i].path[sizeof(address_list[i].path) - 1] = '\0'; // 确保以 NULL 结尾
                printf("Updated %s address path to: %s\n", coin_name, address_list[i].path);
                return;
            }
        }
        // 如果没有找到匹配的币种
        printf("Coin name %s not found in address_list.\n", coin_name);
    } else {
        // 如果命令格式错误
        printf("Invalid command format. Expected format: modify:coin_name,new_path\n");
    }
}

//A < 验证PIN码 和 是否有钱包 < B：PIN:1234,y\n
void PINCodeWalletSend(void)
{
    PIN_number = GetRandomPIN();
    if(infoWallet->is_valid ==0){//没有钱包
        send_serial_data("PIN:%04d,N\r\n", PIN_number);
        PINFlag =1;
    }
    else{
        send_serial_data("PIN:%04d,Y\r\n",PIN_number);
        PINFlag =1;
        adressAllSend();
    }


}


/*****************************Path地址*********************************************/
//保存Path地址

void SaveAddressPathsToEmmc(void) {
    // 定义二维数组用于存储路径

    
    char paths[ADDRESS_COUNT][50];
    // 提取路径到二维数组
    for (size_t i = 0; i < ADDRESS_COUNT; i++) {
        // 确保路径不超过30字节
        if (strlen(address_list[i].path) >= 30) {
            fprintf(stderr, "Path length exceeds 30 characters for %s\n", address_list[i].name);
            continue;
        }
        strcpy(paths[i], address_list[i].path);
        printf("Extracted path[%zu]: %s\n", i, paths[i]);
    }

    // 调用保存函数
    SavePathsToEmmc(paths, ADDRESS_COUNT);
}


void SavePathsToEmmc( char paths[][50], size_t num_paths) {
    FILE *file = fopen(DATA_FILE_PATH, "wb");
    if (!file) {
        perror("Failed to open file for writing SavePathsToEmmc");
        return;
    }

    // 保存路径数量
    fwrite(&num_paths, sizeof(num_paths), 1, file);
    printf("Saving number of paths: %zu\n", num_paths);

    // 保存每个路径的长度和内容
    for (size_t i = 0; i < num_paths; i++) {
        size_t path_len = strlen(paths[i]);
        fwrite(&path_len, sizeof(path_len), 1, file);
        fwrite(paths[i], path_len, 1, file);
        printf("Saving path[%zu]: %s (length: %zu)\n", i, paths[i], path_len);
    }

    // 使用 fsync 确保数据写入磁盘
    if (fsync(fileno(file)) == -1) {
        perror("fsync failed");
    }


    fclose(file);
    printf("Paths successfully saved to %s\n", DATA_FILE_PATH);
}

void ReadPathsFromEmmc(void) {
    FILE *file = fopen(DATA_FILE_PATH, "rb");
    if (!file) {
        perror("Failed to open file for reading ReadPathsFromEmmc");
        return;
    }

    // 读取路径数量
    size_t num_paths;
    if (fread(&num_paths, sizeof(num_paths), 1, file) != 1) {
        perror("Failed to read number of paths");
        fclose(file);
        return;
    }
    printf("Number of paths in file: %zu\n", num_paths);

    if (num_paths > ADDRESS_COUNT) {
        fprintf(stderr, "Warning: Number of paths in file exceeds address_list size (%zu > %zu). Truncating.\n", num_paths, ADDRESS_COUNT);
        num_paths = ADDRESS_COUNT;
    }

    // 逐个读取路径并更新到 address_list
    for (size_t i = 0; i < num_paths; i++) {
        size_t path_len;
        if (fread(&path_len, sizeof(path_len), 1, file) != 1) {
            perror("Failed to read path length");
            fclose(file);
            return;
        }

        if (path_len >= sizeof(address_list[i].path)) {
            fprintf(stderr, "Path length for address_list[%zu] exceeds buffer size. Truncating.\n", i);
            path_len = sizeof(address_list[i].path) - 1;
        }

        if (fread(address_list[i].path, path_len, 1, file) != 1) {
            perror("Failed to read path data");
            fclose(file);
            return;
        }

        address_list[i].path[path_len] = '\0'; // 添加字符串结束符
        printf("Updated address_list[%zu].path: %s\n", i, address_list[i].path);
    }

    fclose(file);
    printf("Paths successfully updated in address_list from %s\n", DATA_FILE_PATH);
}

/********************************************************************************************/




//创建钱包
// entropy 熵
// entropyLen 熵长度(16/20/24/28/32) ->对应助记词长度(12, 15, 18, 21, 24)
// passphrase 密码(可选)
void walletInit(int entropyLen, char *passphrase) {
    entropy_Len = entropyLen;
    if (strcmp(passphrase, "0") == 0) {
        passphrase = "";
    }
    fillArrayWithRandomNumbers(entropy, entropyLen);
    infoWallet = init_wallet(entropy, entropyLen, passphrase);

    if (infoWallet == NULL || infoWallet->mnemonic == NULL) {
        printf("Error: wallet initialization failed.\n");
        return;
    }
    printf("Mnemonic before sanitizing: %s\n", infoWallet->mnemonic);

    // 清理输入字符串
    sanitize_string(infoWallet->mnemonic);
    printf("Mnemonic after sanitizing: %s\n", infoWallet->mnemonic);

    // 分割 mnemonic 到单词数组
    int word_count = split_string_to_array(infoWallet->mnemonic, mnemonicWord, entropyLen);

    SaveWalletToEmmc(infoWallet->mnemonic, PIN_number, 1, entropy, entropy_Len);
    walletwordFlag =1;



}

// 获取地址的数量
// 根据币种名称发送对应的地址
int addressnumber =0;
void sendCoinAddress(char *coin) {
    // 检查是否是普通币种请求
    for (size_t i = 0; i < ADDRESS_COUNT; i++) {
        if (strcasecmp(coin, address_list[i].name) == 0) { // 忽略大小写匹配
            printf("get_chain_address::address_list[i].name:%s,address_list[i].pub_path:%s\n",
                   address_list[i].name, address_list[i].path);
            // 添加换行符后发送数据
            send_serial_data("%s: %s\n",  address_list[i].name,  get_chain_address((char *)address_list[i].name, (char *)address_list[i].path));
            
           
            if(gui_algo_data_set_address(get_chain_address((char *)address_list[i].name, (char *)address_list[i].path))&& gui_algo_data_set_addresspath(address_list[i].path))
             AddressFlag=1;
            addressnumber=i;

            return;
        }
    }

    // 未知地址类型
    printf("Unsupported address type: %s\n", coin);
}



// 解析输入字符串并发送对应的地址
void adressSend(char *address_list_input) {
    char input_copy[256]; // 假设输入字符串最大长度为 255 字节
    strncpy(input_copy, address_list_input, sizeof(input_copy) - 1); // 拷贝输入字符串，防止溢出
    input_copy[sizeof(input_copy) - 1] = '\0'; // 确保字符串以 '\0' 结尾

    char *token = strtok(input_copy, ","); // 按逗号分割
    while (token != NULL) {
        sendCoinAddress(token); // 发送当前币种地址
        token = strtok(NULL, ","); // 获取下一个币种
    }
}


// 发送所有收款地址
void adressAllSend(void) {
    for (size_t i = 0; i < ADDRESS_COUNT; i++) {
        send_serial_data("%s: %s\n", address_list[i].name,get_chain_address((char *)address_list[i].name, (char *)address_list[i].path));
         printf("%s: %s\n", address_list[i].name,address_list[i].path);
    }
}


