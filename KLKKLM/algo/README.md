## 结构说明
```
lib.h 头文件
libnetwork.a 静态库
libwallet_algo.a 静态库
Makefile 运行测试make
test_main.c 测试程序
```

## 启动测试

1. 编译
```
make
```
2. 运行
```
./test_main
```

## 支持链
| 名称 | chain_name |
| -- | -- |
| Bitcoin | bitcoin |
| Ethereum | ethereum |
| Tron | tron |



## 备注
#### tron json格式
```
{
    "token":"", // trc10使用
    "contract_address":"TR7NHqjeKQxGTCi8q8ZY4pL8otSzgjLj6t", // TRC20使用 币种合约地址，当前为USDT "from":"TSGVUARSFeANh1KpWg685E6S3fJSt2TQLj", // 发送地址
    "to":"TRsVPdxyrEn9xSFC9EgB2k8KncesQC9yBg",  // 目标地址
    "value":"1000000", // USDT单位为0.000001，即当前值为1USDT, 其他还需要确认
    "latest_block": {
        "hash":"0000000003c774511755d1edd57f100c4adf0b39eb2ec5de165ae8f199fcc346", // 最新区块hash
        "number":63403089, // 最新区块高度
        "timestamp":1720854318000 // 最新区块时间（毫秒级）
    },
    "override": { // 只展示使用
        "token_short_name":"USDT", // 币种简称
        "token_full_name":"Tether", // 币种全称
        "decimals":2 // 小数位
    },
    "fee":1, // 手续费
    "memo":"" // 交易备注
}
```

#### ETH json格式
```
{
    "nonce":1, // 交易次数 链上数据获取
    "gas_price":20, // 价格
    "gas_limit":10000, // 限制数量
    "to":"0x742d35Cc6634C0532925a3b844Bc454e4438f44e", // 目标地址 或如果是合约交易则为合约地址
    "value":1, // 数量
    "data":"" // 合约数据
}
备注，data生成
const data = web3.eth.abi.encodeFunctionCall({
    name: 'transfer',
    type: 'function',
    inputs: [{
        type: 'address',
        name: 'recipient'
    },{
        type: 'uint256',
        name: 'amount'
    }]
}, ['地址', '10000000']);
```

#### BTC json格式
原始交易格式
参考
eg: 01000000017ddf68c1f2b268d6183981b8783885b59a6558e73b7a15b8c399a0910c2f5d360100000000ffffffff0250c30000000000001600145d048d118fd904ee65ca292d72f409d8a260ddde31be020000000000225120308e81e6e06c53b34f68b82bd015ebd33d7108bb75c025598b873d590f9cb9ed00000000