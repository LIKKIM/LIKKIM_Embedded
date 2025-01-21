#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lib.h"
#include <stdint.h>

#if 0
int main()
{
    int entropy_len = 16;
    uint8_t entropy[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    char *passphrase = "";
    // generate_random_bit_uint8(entropy_len, entropy);
    // 生成钱包
    WalletInfo *info = init_wallet(entropy, entropy_len, passphrase);
    printf("助记词: %s\n", info->mnemonic);

    char seed_hex[info->seed_len * 2 + 1];
    uint8_to_hex_string(info->seed, info->seed_len, seed_hex);
    printf("种子（十六进制）：%s\n\n", seed_hex);

    // info->mnemonic = "bullet spoil relief dignity swamp fish basic1 timber rice layer uphold ticket"; // 错误助记词
    // 助记词导入钱包
    WalletInfo *import_info = init_wallet_by_mnemonic(info->mnemonic, passphrase);
    printf("导入助记词: %s\n", import_info->mnemonic);
    printf("导入助记词结果: %d\n", import_info->is_valid);
    char import_info_seed_hex[import_info->seed_len * 2 + 1];
    uint8_to_hex_string(import_info->seed, import_info->seed_len, import_info_seed_hex);
    printf("种子（十六进制）：%s\n", seed_hex);

    // 收款地址(旧版本实现)
    printf("BTC收款地址 %s\n", get_pub_address(CHAIN_TYPE_BTC, "m/49'/0'/0'/0/0"));
    printf("ETH收款地址 %s\n", get_pub_address(CHAIN_TYPE_ETH_BIP44_STANDARD, "m/44'/60'/0'/0/0"));
    printf("TRX收款地址 %s\n", get_pub_address(CHAIN_TYPE_TRX, "m/44'/195'/0'/0/0"));
    printf("\r\n\r\n");

    // 收款地址(新版本实现)
    printf("BTC收款地址 %s\n", get_chain_address("bitcoin", "m/49'/0'/0'/0/0"));
    printf("ETH收款地址 %s\n", get_chain_address("ethereum", "m/44'/60'/0'/0/0"));
    printf("Tron收款地址 %s\n", get_chain_address("tron", "m/44'/195'/0'/0/0"));
    printf("BCH收款地址 %s\n", get_chain_address("bitcoin_cash", "m/44'/145'/0'/0/0"));
    printf("BNB收款地址 %s\n", get_chain_address("binance", "m/44'/60'/0'/0/0"));
    printf("OP收款地址 %s\n", get_chain_address("optimism", "m/44'/60'/0'/0/0"));
    printf("ETC收款地址 %s\n", get_chain_address("ethereum_classic", "m/44'/60'/0'/0/0"));
    printf("LTC收款地址 %s\n", get_chain_address("litecoin", "m/49'/2'/0'/0/0"));
    printf("XRP收款地址 %s\n", get_chain_address("ripple", "m/44'/144'/0'/0/0"));
    printf("SOL收款地址 %s\n", get_chain_address("solana", "m/44'/501'/0'/0/0"));
    printf("ARB收款地址 %s\n", get_chain_address("arbitrum", "m/44'/60'/0'/0/0"));

    printf("COSMOS 收款地址 %s\n", get_chain_address("cosmos", "m/44'/118'/0'/0/0"));
    printf("Celestia 收款地址 %s\n", get_chain_address("celestia", "m/44'/118'/0'/0/0"));
    printf("Cronos 收款地址 %s\n", get_chain_address("cronos", "m/44'/60'/0'/0/0"));
    printf("Juno 收款地址 %s\n", get_chain_address("juno", "m/44'/118'/0'/0/0"));
    printf("Osmosis 收款地址 %s\n", get_chain_address("osmosis", "m/44'/118'/0'/0/0"));
    // printf("Secret Network 收款地址 %s\n", get_chain_address("secret_network", "m/44'/529'/0'/0/0"));

    printf("Aurora 收款地址 %s\n", get_chain_address("aurora", "m/44'/60'/0'/0/0"));
    printf("Avalanche 收款地址 %s\n", get_chain_address("avalanche", "m/44'/60'/0'/0/0"));
    printf("Celo 收款地址 %s\n", get_chain_address("celo", "m/44'/60'/0'/0/0"));
    printf("Fantom 收款地址 %s\n", get_chain_address("fantom", "m/44'/60'/0'/0/0"));
    printf("Gnosis 收款地址 %s\n", get_chain_address("gnosis", "m/44'/60'/0'/0/0"));
    printf("Huobi ECO 收款地址 %s\n", get_chain_address("huobi", "m/44'/60'/0'/0/0"));
    printf("IoTeX 收款地址 %s\n", get_chain_address("iotex", "m/44'/60'/0'/0/0"));
    printf("OKX Chain 收款地址 %s\n", get_chain_address("okx", "m/44'/60'/0'/0/0"));
    printf("Polygon 收款地址 %s\n", get_chain_address("polygon", "m/44'/60'/0'/0/0"));
    printf("ZkSync 收款地址 %s\n", get_chain_address("zksync", "m/44'/60'/0'/0/0"));
    printf("Linea 收款地址 %s\n", get_chain_address("linea", "m/44'/60'/0'/0/0"));
    printf("Ronin 收款地址 %s\n", get_chain_address("ronin", "m/44'/60'/0'/0/0"));

    printf("Aptos 收款地址 %s\n", get_chain_address("aptos", "m/44'/637'/0'/0'/0"));
    printf("SUI 收款地址 %s\n", get_chain_address("sui", "m/44'/784'/0'/0'/0'"));
    // printf("Cardano 收款地址 %s\n", get_chain_address("cardano", "m/1852'/1815'/0'/0/0"));

    AllChainAddressStruct *all_chain = get_all_pub_address();
    printf("\n测试所有链地址 数量%d\n", all_chain->count);
    for (size_t i = 0; i < 6; i++)
    {
        printf("名称 %zu: %s\n", i, all_chain->chainAddressList[i]->chainName);
        printf("地址 %zu: %s\n", i, all_chain->chainAddressList[i]->address);
    }

    printf("\n测试交易\n");
    testTx(info->seed, info->seed_len);

    // 随机提取助记词
    char **output;
    int size = 5;
    int result = get_rand_mneonics(size, &output);
    printf("随机助记词结果: %d\n", result);
    for (size_t i = 0; i < size; i++)
    {
        printf("%s\n", output[i]);
    }
    free_rand_mneonics(output, size); // 释放内存

    // 测试助记词是否存在
    char *word1 = "apple1";
    int exist_result1 = exist_mneonic(word1);
    printf("%s是助记词吗 %d\n", word1, exist_result1);

    char *word2 = "crush";
    int exist_result2 = exist_mneonic(word2);
    printf("%s是助记词吗 %d\n", word2, exist_result2);
}
#endif