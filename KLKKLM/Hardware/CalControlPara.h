#ifndef _CALCON_H_
#define _CALCON_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"
#include  "usart1.h"

#define ADDRESS_COUNT (sizeof(address_list) / sizeof(address_list[0]))
// 地址信息结构体
typedef struct {
    char *name;     // 币种名称
    char path[200];     // 地址路径，固定大小数组
} AddressInfo;

#define MAX_MNEMONIC_WORDS 24  // 最大单词数
#define MAX_WORD_LENGTH 50     // 每个单词的最大长度
uint16_t GetRandomPIN(void);
void PINCodeWalletSend(void);

void walletInit(int entropyLen,char *passphrase);
void adressSend( char *address_list_input);
void ReadWalletForEmmc(void);
void SaveWalletToEmmc(const char *mnemonic, uint16_t PIN_number, uint8_t adressFlag, const uint8_t *entropy, int entropy_Len);
void adressAllSend(void);
void SavePathsToEmmc( char paths[][50], size_t num_paths);
void modify_address(const char *command);
void loadWalletAndAddressList(void);
void SaveAddressPathsToEmmc(void);
void ReadPathsFromEmmc();
char *pathToLvglAdress(void);
void sendCoinAddress(char *coin);
int split_string_to_array(const char *input, char output[][50], int max_words);
int concatenateStrings(char result[], char strs[][50], int numStrings);
char* uint16_to_str(uint16_t PIN_number);

#endif

