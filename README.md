### 使用手册

#### 1. 运行环境
1. jdk8环境

#### 2. 获取压测工具包，描述如下
```text
platon-press-1.0.0
├── application.yaml                 //配置文件
├── platon-press-1.0.0.jar           //执行程序
├── platon-press-config              //配置数据
│   └── to-address.txt               //转账的接收地址列表
└── README.md                        //帮助文档
```

#### 3. 获得私钥文件
1. 线下获取私钥文件，如：节点id.csv

#### 4. 配置压测工具
1. 将私钥文件配置到压测工具中。放到platon-press-config目录下，并且名称为keys.csv
```text
platon-press-1.0.0
├── application.yaml                 //配置文件
├── platon-press-1.0.0.jar           //执行程序
├── platon-press-config              //配置数据
│   ├── keys.csv                     //私钥文件
│   └── to-address.txt               //转账的接收地址列表
└── README.md                        //帮助文档

```

2. 修改配置文件 application.yaml。需要设置节点rpc端口（ node-url） 和 节点公钥（node-public-key）。节点公钥必须0x开头。

```yaml
spring:
    application:
        name: platon-press
    main:
        banner-mode: off
press:
    #节点rpc端口
    node-url: http://192.168.112.141:6789        
    #节点公钥（必须0x开头）
    node-public-key: "0x28f95bee4ce1cb0d7523e430a85349f12897c29cc431f294078a27a6f950a6df8ef9b25c2143e72f6ad525d992c913503e2715b5b2768587d633dd9fa102f61b"
    #evm测试合约地址
    evm-addr: "0xfbdf3c5bf983cdf67685883f8eaabfd4e31249ec"
    #wasm测试合约地址
    wasm-addr: "0xaedf3c5bf983cdf67685883f8eaabfd4e31249ec"
    #链id
    chain-id: 102
logging:
    pattern:
        console: "%date %msg%n"
        file: "%date %msg%n"
    level:
        root: error
        spring: error
        org.web3j: error
        com.platon.tools: info
    file:
        name: ./logs/press.log
```

#### 5. 启动或停止
1. 启动，必须cd到工具的目录下执行启动命令
```shell script
cd platon-press-1.0.0;

nohup java -jar platon-press-1.0.0.jar &
```

2. 停止
```shell script
ps -ef | grep platon-press-1.0.0.jar | grep -v "grep"  | awk '{print $2}' | xargs kill -9
```

#### 6. 自定义配置，可以调整压测工具的属性。属于高级用法。非必须
```yaml
spring:
    application:
        name: platon-press
    main:
        banner-mode: off
press:
    #节点rpc端口
    node-url: http://192.168.112.141:6789        
    #节点公钥（必须0x开头）
    node-public-key: "0x28f95bee4ce1cb0d7523e430a85349f12897c29cc431f294078a27a6f950a6df8ef9b25c2143e72f6ad525d992c913503e2715b5b2768587d633dd9fa102f61b"
    
    # -------------------------------------------自定义设置开始--------------------------------------------
    #压测交易类型  TRANFER：转账；WASM：WASM合约；EVM：EVM合约
    tx-type: TRANFER,WASM,EVM
    #每种交易类型占比，数值对应tx-type配置中相同的位置
    tx-rate: 5,3,2
    #链id
    chain-id: 102
    #发起交易的私钥文件
    keys-file: ./platon-press-config/keys.csv
    #私钥文件加载索引
    key-index: 0
    #私钥文件加载大小
    key-size: 10000
    #消费线程sleep的时间，单位毫秒
    consumer-thread-sleep-duration: 0

    #转账交易的gasPrice
    tranfer-gas-price: 10000000000
    #转账交易的gasLimit
    tranfer-gas-limit: 21000
    #转账的接收文件
    tranfer-to-addrs-file: ./platon-press-config/to-address.txt
    #转账的金额，单位VON
    tranfer-value: 1

    #evm交易的gasPrice
    evm-gas-price: 10000000000
    #evm交易的gasLimit
    evm-gas-limit: 300000
    #evm测试合约地址
    evm-addr: "0xfbdf3c5bf983cdf67685883f8eaabfd4e31249ec"

    #wasm交易的gasPrice
    wasm-gas-price: 10000000000
    #wasm交易的gasLimit
    wasm-gas-limit: 3000000
    #wasm测试合约地址
    wasm-addr: "0xaedf3c5bf983cdf67685883f8eaabfd4e31249ec"
 
    # -------------------------------------------自定义设置结束--------------------------------------------
logging:
    pattern:
        console: "%date %msg%n"
        file: "%date %msg%n"
    level:
        root: error
        spring: error
        org.web3j: error
        com.platon.tools: info
    file:
        name: ./logs/press.log
```