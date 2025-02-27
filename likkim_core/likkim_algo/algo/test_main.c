// #include <string.h>
// #include <stdio.h>
// #include <time.h>
// #include <stdlib.h>
// #include "lib.h"
// #include "stdint.h"

// // 生成一个随机n位 uint8_t 类型的整数
// void generate_random_bit_uint8(int n, u_int8_t *random_bytes)
// {
//     srand((unsigned int)time(NULL));
//     for (int i = 0; i < n; ++i)
//     {
//         random_bytes[i] = rand() & 0xFF;
//     }
// }

// // 将数组转换为十六进制字符串
// void uint8_to_hex_string(const uint8_t *data, size_t len, char *hex_string)
// {
//     for (size_t i = 0; i < len; i++)
//     {
//         sprintf(&hex_string[i * 2], "%02X", data[i]);
//     }
// }

// void uint8_to_hex32(uint8_t *seed, char *hex_str)
// {
//     for (int i = 0; i < 64; i++)
//     {
//         // 使用 snprintf 将每个字节转换为 2 位的十六进制字符
//         snprintf(&hex_str[i * 2], 3, "%02x", seed[i]);
//     }
// }

// // void test_trx_tx(uint8_t *seed, size_t seed_len)
// // {
// //     char *data = "{\"token\":\"\",\"contract_address\":\"TR7NHqjeKQxGTCi8q8ZY4pL8otSzgjLj6t\",\"from\":\"TSGVUARSFeANh1KpWg685E6S3fJSt2TQLj\",\"to\":\"TRsVPdxyrEn9xSFC9EgB2k8KncesQC9yBg\",\"value\":\"1000000\",\"latest_block\":{\"hash\":\"0000000003c7823c8edfa12ea2e01475d5998382abc57f3e8708a4cad0c213db\",\"number\":63406652,\"timestamp\":1720865007000},\"override\":{\"token_short_name\":\"USDT\",\"token_full_name\":\"Tether\",\"decimals\":2},\"fee\":1,\"memo\":\"\"}";
// //     char *hdpath = "m/44'/195'/0'/0/0";

// //     char *result = sign_tx_for_tron(data, seed, seed_len, hdpath);
// //     printf("签名结果 %s\n", result);
// // }

// // 测试交易
// void testTx(uint8_t *seed, size_t seed_len)
// {
//     printf("====btc 交易=====\n");
//     char *btc_sign = sign_tx("bitcoin", "{\"hex\":\"01000000018b3cd6f2ac838c64a17d027eb73132d9f0ae2171162754bde5c820336bb96f980100000000ffffffff02b80b00000000000017a914245614da55321e217171a2ef293d52038c1d2bd28743c800000000000017a914e9ba8601d568f6c9bef04c6c2c7660429c3da4f08700000000\",\"value\":[54774]}", seed, seed_len, "m/49'/0'/0'/0/0");
//     printf("BTC签名结果 %s\n", btc_sign);

//     printf("====eth 交易=====\n");
//     char *coin = "ethereum";
//     char *data = "ec0385011ca3b76b83015f909436f06561b946801dca606842c9701ea3fe850ca287071afd498d000080018080";
//     char *eth_sign = sign_tx(coin, data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", eth_sign);

//     printf("====tron 交易=====\n");
//     char *trx_sign = sign_tx(
//         "tron",
//         "{\"token\":\"\",\"contract_address\":\"TR7NHqjeKQxGTCi8q8ZY4pL8otSzgjLj6t\",\"from\":\"TSGVUARSFeANh1KpWg685E6S3fJSt2TQLj\",\"to\":\"TRsVPdxyrEn9xSFC9EgB2k8KncesQC9yBg\",\"value\":\"1000000\",\"latest_block\":{\"hash\":\"0000000003c7823c8edfa12ea2e01475d5998382abc57f3e8708a4cad0c213db\",\"number\":63406652,\"timestamp\":1720865007000},\"override\":{\"token_short_name\":\"USDT\",\"token_full_name\":\"Tether\",\"decimals\":2},\"fee\":1,\"memo\":\"\"}",
//         seed,
//         seed_len,
//         "m/44'/195'/0'/0/0");
//     printf("TRON签名结果 %s\n", trx_sign);

//     printf("====bch 交易=====\n");
//     char *bch_sign = sign_tx("bitcoin_cash", "{\"hex\":\"01000000018b3cd6f2ac838c64a17d027eb73132d9f0ae2171162754bde5c820336bb96f980100000000ffffffff02b80b00000000000017a914245614da55321e217171a2ef293d52038c1d2bd28743c800000000000017a914e9ba8601d568f6c9bef04c6c2c7660429c3da4f08700000000\",\"value\":[54774]}", seed, seed_len, "m/44'/145'/0'/0/0");
//     printf("签名结果 %s\n", bch_sign);

//     printf("====BNB 交易=====\n");
//     char *bnb_sign = sign_tx("binance", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", bnb_sign);

//     printf("====OP 交易=====\n");
//     char *op_sign = sign_tx("optimism", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", op_sign);

//     printf("====ETC 交易=====\n");
//     char *etc_sign = sign_tx("ethereum_classic", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", etc_sign);

//     printf("====ARB 交易=====\n");
//     char *arb_sign = sign_tx("arbitrum", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", arb_sign);

//     printf("====LTC 交易=====\n");
//     char *ltc_sign = sign_tx("litecoin", "{\"hex\":\"01000000018b3cd6f2ac838c64a17d027eb73132d9f0ae2171162754bde5c820336bb96f980100000000ffffffff02b80b00000000000017a914245614da55321e217171a2ef293d52038c1d2bd28743c800000000000017a914e9ba8601d568f6c9bef04c6c2c7660429c3da4f08700000000\",\"value\":[54774]}", seed, seed_len, "m/49'/2'/0'/0/0");
//     printf("签名结果 %s\n", ltc_sign);

//     printf("====XRP 交易=====\n"); // 测试
//     char *xrp_sign = sign_tx("ripple", "7b224163636f756e74223a2272426875566145626639384855626a72444451395154394162593934655874364267222c2244657374696e6174696f6e223a227233746d716162654d4844754c5936644a7778644d534569616b786e335178695538222c22416d6f756e74223a2231303030303030222c22466565223a2235303030222c2253657175656e6365223a39323838393731362c2254786e5369676e6174757265223a22222c225369676e696e675075624b6579223a22303230363831326438373739376165653064623164373164633832666532343062623561623537656630666439326661646431656363316566663735393561353764227d", seed, seed_len, "m/44'/144'/0'/0/0");
//     printf("签名结果 %s\n", xrp_sign);

//     printf("====SOL 交易=====\n");
//     char *tx_data = "0100010307fcf795a76ee4e317ee41f4a22fe12a198ad76dbe41ebed3ce021a25a695ac0c8f7d49aeb3156ea38d776af36c258703ac7537b928736a2f2b488cfe338227f0000000000000000000000000000000000000000000000000000000000000000590a47f7bd3d2ca5996ab97bc7e64ef2456329a11a8954b1b26d373c6186c21201020200010c0200000040420f0000000000";
//     char *sol_sign = sign_tx("solana", tx_data, seed, seed_len, "m/44'/501'/0'/0'");
//     printf("签名结果 %s\n", sol_sign);

//     printf("====Aurora 交易=====\n");
//     char *aurora_sign = sign_tx("aurora", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", aurora_sign);

//     printf("====Avalanche 交易=====\n");
//     char *avalanche_sign = sign_tx("avalanche", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", avalanche_sign);

//     printf("====Celo 交易=====\n");
//     char *celo_sign = sign_tx("celo", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", celo_sign);

//     printf("====Fantom 交易=====\n");
//     char *fantom_sign = sign_tx("fantom", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", fantom_sign);

//     printf("====Gnosis交易=====\n");
//     char *gnosis_sign = sign_tx("gnosis", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", gnosis_sign);

//     printf("====Huobi 交易=====\n");
//     char *huobi_sign = sign_tx("huobi", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", huobi_sign);

//     printf("====IoTeX 交易=====\n");
//     char *iotex_sign = sign_tx("iotex", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", iotex_sign);

//     printf("====OKX 交易=====\n");
//     char *okx_sign = sign_tx("okx", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", okx_sign);

//     printf("====Polygon 交易=====\n");
//     char *polygon_sign = sign_tx("polygon", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", polygon_sign);

//     printf("====ZkSync 交易=====\n");
//     char *zksync_sign = sign_tx("zksync", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", zksync_sign);

//     printf("====Linea 交易=====\n");
//     char *linea_sign = sign_tx("linea", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", linea_sign);

//     printf("====Ronin 交易=====\n");
//     char *ronin_sign = sign_tx("ronin", data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", ronin_sign);

//     printf("====Cosmos 交易=====\n");
//     char *cosmos_data = "0a91010a8e010a1c2f636f736d6f732e62616e6b2e763162657461312e4d736753656e64126e0a2d636f736d6f7331716b386464756868753975396e6168716d706d7966633374357776336679336b336e75357333122d636f736d6f7331797063376672327a3266727a616861736b3065706a776e6e64746734347278676e617a776e391a0e0a057561746f6d1205333030303012650a4e0a460a1f2f636f736d6f732e63727970746f2e736563703235366b312e5075624b657912230a21029ea04bc320f3eeaed43ca041837fc646f450e4c277c8fdffe9bbe8396a508e7412040a02080112130a0d0a057561746f6d12043130303010c09a0c1a0b636f736d6f736875622d3420ec82c101";
//     char *cosmos_sign = sign_tx("cosmos", cosmos_data, seed, seed_len, "m/44'/118'/0'/0/0");
//     printf("签名结果 %s\n", cosmos_sign);

//     printf("====celestia 交易=====\n");
//     char *celestia_data = "0A9D010A9A010A1C2F636F736D6F732E62616E6B2E763162657461312E4D736753656E64127A0A2C65766D6F7331747173647A37383573716A6E6C67676565306C77786A77666B36646C33366165327566396572122C65766D6F73316C637A71773934766674616D357A387777676C6E373337346D713230636A78706739387039661A1C0A07617465766D6F7312113130303030303030303030303030303030127C0A570A4F0A282F65746865726D696E742E63727970746F2E76312E657468736563703235366B312E5075624B657912230A21039F4E693730F116E7AB01DAC46B94AD4FCABC3CA7D91A6B121CC26782A8F2B8B212040A02080112210A1B0A07617465766D6F7312103236323530303030303030303030303010A8B4061A0C65766D6F735F393030302D3420DEC08D01";
//     char *celestia_sign = sign_tx("celestia", celestia_data, seed, seed_len, "m/44'/118'/0'/0/0");
//     printf("签名结果 %s\n", celestia_sign);

//     printf("====juno 交易=====\n");
//     char *juno_data = "0A9D010A9A010A1C2F636F736D6F732E62616E6B2E763162657461312E4D736753656E64127A0A2C65766D6F7331747173647A37383573716A6E6C67676565306C77786A77666B36646C33366165327566396572122C65766D6F73316C637A71773934766674616D357A387777676C6E373337346D713230636A78706739387039661A1C0A07617465766D6F7312113130303030303030303030303030303030127C0A570A4F0A282F65746865726D696E742E63727970746F2E76312E657468736563703235366B312E5075624B657912230A21039F4E693730F116E7AB01DAC46B94AD4FCABC3CA7D91A6B121CC26782A8F2B8B212040A02080112210A1B0A07617465766D6F7312103236323530303030303030303030303010A8B4061A0C65766D6F735F393030302D3420DEC08D01";
//     char *juno_sign = sign_tx("juno", juno_data, seed, seed_len, "m/44'/118'/0'/0/0");
//     printf("签名结果 %s\n", juno_sign);

//     printf("====osmosis 交易=====\n");
//     char *osmosis_data = "0A9D010A9A010A1C2F636F736D6F732E62616E6B2E763162657461312E4D736753656E64127A0A2C65766D6F7331747173647A37383573716A6E6C67676565306C77786A77666B36646C33366165327566396572122C65766D6F73316C637A71773934766674616D357A387777676C6E373337346D713230636A78706739387039661A1C0A07617465766D6F7312113130303030303030303030303030303030127C0A570A4F0A282F65746865726D696E742E63727970746F2E76312E657468736563703235366B312E5075624B657912230A21039F4E693730F116E7AB01DAC46B94AD4FCABC3CA7D91A6B121CC26782A8F2B8B212040A02080112210A1B0A07617465766D6F7312103236323530303030303030303030303010A8B4061A0C65766D6F735F393030302D3420DEC08D01";
//     char *osmosis_sign = sign_tx("osmosis", osmosis_data, seed, seed_len, "m/44'/118'/0'/0/0");
//     printf("签名结果 %s\n", osmosis_sign);

//     printf("====cronos 交易=====\n");
//     char *cronos_data = "0A9D010A9A010A1C2F636F736D6F732E62616E6B2E763162657461312E4D736753656E64127A0A2C65766D6F7331747173647A37383573716A6E6C67676565306C77786A77666B36646C33366165327566396572122C65766D6F73316C637A71773934766674616D357A387777676C6E373337346D713230636A78706739387039661A1C0A07617465766D6F7312113130303030303030303030303030303030127C0A570A4F0A282F65746865726D696E742E63727970746F2E76312E657468736563703235366B312E5075624B657912230A21039F4E693730F116E7AB01DAC46B94AD4FCABC3CA7D91A6B121CC26782A8F2B8B212040A02080112210A1B0A07617465766D6F7312103236323530303030303030303030303010A8B4061A0C65766D6F735F393030302D3420DEC08D01";
//     char *cronos_sign = sign_tx("cronos", cronos_data, seed, seed_len, "m/44'/60'/0'/0/0");
//     printf("签名结果 %s\n", cronos_sign);
//     // char *secret_network_data = "b5e97db07fa0bd0e5598aa3643a9bc6f6693bddc1a9fec9e674a461eaa00b193f007dbb60994463db95b80fad4259ec18767a5bb507f9e048da84b75ea793ef500000000000000000200000000000000000000000000000000000000000000000000000000000000010d6170746f735f6163636f756e740e7472616e736665725f636f696e73010700000000000000000000000000000000000000000000000000000000000000010a6170746f735f636f696e094170746f73436f696e000220f007dbb60994463db95b80fad4259ec18767a5bb507f9e048da84b75ea793ef50800000000000000000a00000000000000640000000000000061242e650000000002";
//     // char *secret_network_sign = sign_tx("secret_network", aptos_data, seed, seed_len, "m/44'/637'/0'/0'/0'");
//     // printf("签名结果 %s\n", secret_network_sign);

//     printf("====Aptos 交易=====\n"); // 测试
//     char *aptos_data = "b5e97db07fa0bd0e5598aa3643a9bc6f6693bddc1a9fec9e674a461eaa00b1939a563d3ea6a17193486858f75f189f6c2e408252955cc0cef519e9ee55d66490010000000000000002000000000000000000000000000000000000000000000000000000000000000104636f696e087472616e73666572010700000000000000000000000000000000000000000000000000000000000000010a6170746f735f636f696e094170746f73436f696e0002201fe380fa96227033cad8df110f3845aa34b5288a94bc32d57503b28f458ea9ed0840420f000000000040420f00000000006400000000000000a07a6e670000000001";
//     char *aptos_sign = sign_tx("aptos", aptos_data, seed, seed_len, "m/44'/637'/0'/0'/0'");
//     printf("签名结果 %s\n", aptos_sign);

//     printf("====Sui 交易=====\n");
//     char *sui_data = "000000000002000880f0fa020000000000209e4881b5d1988e78254dbc35ffc058c294cda9f6674a649330b26d8de61a964602020001010000010102000001010041607b560d833712be1aa5926ea34b8b3bef8a4a35d6147b15782ecfaea2189901547423ba9528ab3bc240338331ebf62c9e73e44080d01c52a024e8c0ead37c00c90fcc1a0000000020597ebe65f40851ebaf9d1501b27267c57dfd064cdc3d91ce8b0526a46704086441607b560d833712be1aa5926ea34b8b3bef8a4a35d6147b15782ecfaea21899ee0200000000000000e1f50500000000016f02000000000000";
//     char *sui_sign = sign_tx("sui", sui_data, seed, seed_len, "m/44'/784'/0'/0'/0'");
//     printf("签名结果 %s\n", sui_sign);

//     // printf("====Cardano 交易=====\n");
// }

// int main()
// {
//     // int entropy_len = 16;
//     // uint8_t entropy[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//     // char *passphrase = "";
//     // // generate_random_bit_uint8(entropy_len, entropy);
//     // // 生成钱包
//     // WalletInfo *info = init_wallet(entropy, 16, "");
//     // printf("助记词: %s\n", info->mnemonic);

//     // char seed_hex[info->seed_len * 2 + 1];
//     // uint8_to_hex_string(info->seed, info->seed_len, seed_hex);
//     // printf("种子（十六进制）：%s\n\n", seed_hex);

//     char *importMnemonic = "invite exact chicken chef name body fury entire filter riot cargo rail"; // LKKIM 1
//     // 助记词导入钱包
//     WalletInfo *import_info = init_wallet_by_mnemonic(importMnemonic, "");
//     printf("导入助记词: %s\n", import_info->mnemonic);
//     printf("导入助记词结果: %d\n", import_info->is_valid);
//     // char import_info_seed_hex[import_info->seed_len * 2 + 1];
//     // uint8_to_hex_string(import_info->seed, 32, import_info_seed_hex);
//     // printf("种子（十六进制）：%s\n", import_info_seed_hex);

//     // 收款地址(新版本实现)
//     printf("BTC收款地址 %s\n", get_chain_address("bitcoin", "m/49'/0'/0'/0/0"));
//     char *btc_pubkey = get_chain_pubkey("bitcoin", import_info->seed, import_info->seed_len, "m/49'/0'/0'/0/0");
//     printf("btc public key: %s\n", btc_pubkey);
//     printf("ETH收款地址 %s\n", get_chain_address("ethereum", "m/44'/60'/0'/0/0"));
//     printf("Tron收款地址 %s\n", get_chain_address("tron", "m/44'/195'/0'/0/0"));
//     printf("BCH收款地址 %s\n", get_chain_address("bitcoin_cash", "m/44'/145'/0'/0/0"));
//     printf("BNB收款地址 %s\n", get_chain_address("binance", "m/44'/60'/0'/0/0"));
//     printf("OP收款地址 %s\n", get_chain_address("optimism", "m/44'/60'/0'/0/0"));
//     printf("ETC收款地址 %s\n", get_chain_address("ethereum_classic", "m/44'/60'/0'/0/0"));
//     printf("LTC收款地址 %s\n", get_chain_address("litecoin", "m/49'/2'/0'/0/0"));
//     printf("XRP收款地址 %s\n", get_chain_address("ripple", "m/44'/144'/0'/0/0"));
//     char *xrp_pubkey = get_chain_pubkey("ripple", import_info->seed, import_info->seed_len, "m/44'/144'/0'/0/0");
//     printf("XRP public key: %s\n", xrp_pubkey);
//     printf("SOL收款地址 %s\n", get_chain_address("solana", "m/44'/501'/0'/0'/0'"));
//     printf("ARB收款地址 %s\n", get_chain_address("arbitrum", "m/44'/60'/0'/0/0"));

//     printf("COSMOS 收款地址 %s\n", get_chain_address("cosmos", "m/44'/118'/0'/0/0"));
//     char *cosmos_pubkey = get_chain_pubkey("cosmos", import_info->seed, import_info->seed_len, "m/44'/118'/0'/0/0");
//     printf("Cosmos public key: %s\n", cosmos_pubkey);
//     printf("Celestia 收款地址 %s\n", get_chain_address("celestia", "m/44'/118'/0'/0/0"));
//     printf("Cronos 收款地址 %s\n", get_chain_address("cronos", "m/44'/60'/0'/0/0"));
//     printf("Juno 收款地址 %s\n", get_chain_address("juno", "m/44'/118'/0'/0/0"));
//     printf("Osmosis 收款地址 %s\n", get_chain_address("osmosis", "m/44'/118'/0'/0/0"));
//     // printf("Secret Network 收款地址 %s\n", get_chain_address("secret_network", "m/44'/529'/0'/0/0"));

//     printf("Aurora 收款地址 %s\n", get_chain_address("aurora", "m/44'/60'/0'/0/0"));
//     printf("Avalanche 收款地址 %s\n", get_chain_address("avalanche", "m/44'/60'/0'/0/0"));
//     printf("Celo 收款地址 %s\n", get_chain_address("celo", "m/44'/60'/0'/0/0"));
//     printf("Fantom 收款地址 %s\n", get_chain_address("fantom", "m/44'/60'/0'/0/0"));
//     printf("Gnosis 收款地址 %s\n", get_chain_address("gnosis", "m/44'/60'/0'/0/0"));
//     printf("Huobi ECO 收款地址 %s\n", get_chain_address("huobi", "m/44'/60'/0'/0/0"));
//     printf("IoTeX 收款地址 %s\n", get_chain_address("iotex", "m/44'/60'/0'/0/0"));
//     printf("OKX Chain 收款地址 %s\n", get_chain_address("okx", "m/44'/60'/0'/0/0"));
//     printf("Polygon 收款地址 %s\n", get_chain_address("polygon", "m/44'/60'/0'/0/0"));
//     printf("ZkSync 收款地址 %s\n", get_chain_address("zksync", "m/44'/60'/0'/0/0"));
//     printf("Linea 收款地址 %s\n", get_chain_address("linea", "m/44'/60'/0'/0/0"));
//     printf("Ronin 收款地址 %s\n", get_chain_address("ronin", "m/44'/60'/0'/0/0"));

//     printf("Aptos 收款地址 %s\n", get_chain_address("aptos", "m/44'/637'/0'/0'/0'"));
//     char *aptos_pubkey = get_chain_pubkey("aptos", import_info->seed, import_info->seed_len, "m/44'/637'/0'/0'/0'");
//     printf("Aptos public key: %s\n", aptos_pubkey);
//     printf("SUI 收款地址 %s\n", get_chain_address("sui", "m/44'/784'/0'/0'/0'"));
//     // printf("Cardano 收款地址 %s\n", get_chain_address("cardano", "m/1852'/1815'/0'/0/0"));

//     AllChainAddressStruct *all_chain = get_all_pub_address();
//     printf("\n测试所有链地址 数量%d\n", all_chain->count);
//     for (size_t i = 0; i < 6; i++)
//     {
//         printf("名称 %zu: %s\n", i, all_chain->chainAddressList[i]->chainName);
//         printf("地址 %zu: %s\n", i, all_chain->chainAddressList[i]->address);
//     }

//     printf("\n测试交易\n");
//     testTx(import_info->seed, import_info->seed_len);

//     // 随机提取助记词
//     char **output;
//     int size = 5;
//     int result = get_rand_mneonics(size, &output);
//     printf("随机助记词结果: %d\n", result);
//     for (size_t i = 0; i < size; i++)
//     {
//         printf("%s\n", output[i]);
//     }
//     free_rand_mneonics(output, size); // 释放内存

//     // 测试助记词是否存在
//     char *word1 = "apple1";
//     int exist_result1 = exist_mneonic(word1);
//     printf("%s是助记词吗 %d\n", word1, exist_result1);

//     char *word2 = "crush";
//     printf("助记词吗0\n");
//     int exist_result2 = exist_mneonic(word2);
//     printf("助记词吗1\n");
//     printf("%s是助记词吗 %d\n", word2, exist_result2);
//     printf("助记词吗2\n");
//     return 0;
// }