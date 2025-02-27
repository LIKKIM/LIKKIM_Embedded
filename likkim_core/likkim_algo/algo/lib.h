#ifndef _LIB_H_
#define _LIB_H_
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
// 钱包信息结构
typedef struct
{
    uint8_t *entropy;
    size_t entropyLen;
    char *passphrase;
    char *mnemonic;
    uint8_t *seed;
    size_t seed_len;
    int is_valid; // 是否有效生成，1: 正常, -1/-2: 助记词错误 -3: 熵错误,生成助记词失败
} WalletInfo;

// 支持链
typedef enum
{
    CHAIN_TYPE_BTC,
    CHAIN_TYPE_BTC_LEGACY,
    CHAIN_TYPE_BTC_NATIVE_SEGWIT,
    CHAIN_TYPE_BTC_TAPROOT,
    CHAIN_TYPE_ETH_BIP44_STANDARD,
    CHAIN_TYPE_TRX,
    CHAIN_TYPE_LTC,
    CHAIN_TYPE_DASH,
    CHAIN_TYPE_BCH,
    CHAIN_TYPE_COSMOS,
    CHAIN_TYPE_SCRT,
    CHAIN_TYPE_CRO,
    CHAIN_TYPE_IOV,
    CHAIN_TYPE_BLD,
    CHAIN_TYPE_KAVA,
    CHAIN_TYPE_TERRA,
    CHAIN_TYPE_XRP,
    CHAIN_TYPE_SOL_BIP44_0,
    CHAIN_TYPE_SUI_0,
    CHAIN_TYPE_APT_0,
    CHAIN_TYPE_ADA_0,
    CHAIN_TYPE_ARWEAVE,
    CHAIN_TYPE_NUM, // 链数量
} ChainTypeEnum;

typedef struct
{
    char *chainName;
    char *address;
} ChainAddressStruct;

typedef struct
{
    ChainAddressStruct **chainAddressList;
    size_t count;
} AllChainAddressStruct;

// 初始化，生成种子
// entropy 熵
// entropy_len 熵长度(16/20/24/28/32) ->对应助记词长度(12, 15, 18, 21, 24)
// passphrase 密码(可选)
WalletInfo *init_wallet(uint8_t *entropy, size_t entropy_len, char *passphrase);

// 初始化钱包通过助记词
// mnemonic 助记词
// passphrase 密码(可选)
WalletInfo *init_wallet_by_mnemonic(char *mnemonic, char *passphrase);

// 获取随机助记词
// size 数量
// 助记词列表
int get_rand_mneonics(int size, char ***output);

// 随机助记词释放内存
// 助记词列表
// size 数量
void free_rand_mneonics(char **output, int size);

// 检测助记词是否存在
// mneonic 待检测助记词
// return 0 不存在，其他存在
size_t exist_mneonic(char *mneonic);

// 获取收款地址(已弃用，请使用 get_chain_address 方法)
char *get_pub_address(ChainTypeEnum type, char *hd_path);

// 获取收款地址
char *get_chain_address(char *chain_name, char *hd_path);

// 获取支持的所有收款地址
AllChainAddressStruct *get_all_pub_address();

char *get_chain_pubkey(char *chain_name, uint8_t *seed, size_t seed_len, char *hd_path);

// btc交易签名
char *sign_tx_for_btc(char *tx, uint8_t *seed, size_t seed_len, char *hd_path, char *chain_code);

// tron交易签名
// data 交易数据，json格式 见readme.md
// seed 种子
// seed_len 种子长度
// hd_path 分派地址
char *sign_tx_for_tron(char *data, uint8_t *seed, size_t seed_len, char *hd_path);

// eth交易签名
// data 交易数据，json格式 见readme.md
// seed 种子
// seed_len 种子长度
// hd_path 分派地址
char *sign_tx_for_eth(char *chain_key, char *data, uint8_t *seed, size_t seed_len, char *hd_path);

// 签名交易
char *sign_tx(char *chain_key, char *data, uint8_t *seed, size_t seed_len, char *hd_path);

void LogRustPanic(char *panic_info);
void LogRustMalloc(void *p, uint32_t size);
void LogRustFree(void *p);
#endif

