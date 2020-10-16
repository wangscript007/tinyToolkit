# 简介

  * tinyToolkit是为减少编码工作而封装的简易工具套件，可单独提取源码嵌入项目代码中，最低支持c++11

# 依赖

  * fmtlib

# 安装

  * 如若自动编译，可运行script目录下各平台安装脚本 (脚本中会自动编译安装3rd/fmt库，如环境中已存在，可手动去除)
  * 如若手动编译，需先安装fmtlib库 (3rd目录有中提供，也可前往官网下载最新版)

# 功能

  * id  (序号处理)
    * unique  全局唯一序号生成器
    * snowflakes  分布式唯一序号生成器

  * net
    * tcpClient tcp客户端
    * tcpServer tcp服务端
    * tcpSession tcp会话

  * hash  (散列/哈希处理)
    * md5
    * sha1
    * sha224
    * sha256
    * sha384
    * sha512
    * hmac_md5
    * hmac_sha1
    * hmac_sha224
    * hmac_sha256
    * hmac_sha384
    * hmac_sha512

  * pool  (池化处理)
    * taskPool  任务(线程)池
    * objectPool  对象池

  * util  (实用工具)
    * math  数学处理
    * time  时间处理
    * latch 闭锁处理
    * regex 常用正则
    * signal  信号处理
    * string  内容处理
    * system  系统信息
    * singleton  单例模式
    * filesystem  文件处理
    * application  应用信息

  * debug  (崩溃信息)
    * dump  崩溃转储 (当前仅支持windows)
    * stackTrace  堆栈信息

  * timer  (定时器处理)
    * task  定时任务
    * timer  定时器

  * crypto  (编码/解码/加解密处理)
    * url
    * base64

  * logger  (日志处理)
    * syncLogger  同步日志
    * asyncLogger  异步日志
    * fileSink 文件输出节点
    * dailyFileSink  滚动文件输出节点 (按日期分割)
    * rotatingFileSink  滚动文件输出节点 (按大小分割)
    * syslogSink  系统事件输出节点
    * consoleSink  控制台输出节点
    * simpleLayout  默认布局
    * patternLayout  自定义布局
    * regexFilter  正则过滤器
    * priorityFilter  日志等级过滤器

  * option  (命令行参数解析)
    * description 描述信息
    * option  参数解析

  * container  (容器实现)
    * any  任意类型存储
    * queue  有锁队列

# 使用

  * 详细请看example



