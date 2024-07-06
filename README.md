![1](https://github.com/yxysjtu/led-matrix/assets/53338300/2c73584a-ae29-4b71-adb9-f9ddc497dbf6)
# 无限深渊光立方体

难度：⭐ （难度全点在灯带焊接上了）

炫酷：⭐⭐⭐⭐⭐

技能点：
* 项目需求分析
* 原理图，PCB绘制，下单打板采购流程
* PCB焊接，硬件调试方法
* 嵌入式C++工程建立，层级驱动与任务逻辑解耦的框架书写
* 软件调试方法
* 单片机中断使用，SPI驱动，定时器DMA PWM

## 简介
* 这是什么：利用半透镜来回反射带来的无穷空间感
* 为什么要做这个项目：帅是一辈子的事

## 效果展示
波浪流水灯：

https://github.com/yxysjtu/led-matrix/assets/53338300/cab65b39-d6d0-44a8-b14f-c08d955454b7

第一人称空间感：

https://github.com/yxysjtu/led-matrix/assets/53338300/0877f13f-39b3-478c-a3bc-682470a3867d

## 需求分析
### 机械
* 150x150x150(mm)的立方体，60/m灯珠的WS2812灯带5m
* 需要12根150mm长度1515铝型材，角码连接；
* 需要6片150x150mm的半透镜
### 硬件
* 5V电源输入（3A输出能力）
* 3.3V稳压电路（5V稳压到3.3V给单片机供电）
* 单片机最小系统，要留出下面的接口：
	1. SWD
	2. UART
	3. WS2812的DIN
	4. I2C（可选接OLED）
	5. 一个按键，一个指示LED：两个GPIO
## 机械搭建
* 灯带信号流向：
![3](https://github.com/yxysjtu/led-matrix/assets/53338300/21b3d004-62f7-4160-85c5-7730f2577a8c)
![6](https://github.com/yxysjtu/led-matrix/assets/53338300/833c5066-c5a1-4236-bca8-725d2edc674f)
* 焊接的一个角
![4](https://github.com/yxysjtu/led-matrix/assets/53338300/1139310c-6334-4196-b6b5-114529cd74dd)
* 完成的整个框
![5](https://github.com/yxysjtu/led-matrix/assets/53338300/6b2e8f8c-e5d9-45f9-b2fb-d099180f6278)
* 贴上半透镜的最终效果
![7](https://github.com/yxysjtu/led-matrix/assets/53338300/cf19c65e-cfa3-47e8-a610-819f8ca074d2)

## 硬件
### 原理图设计

### PCB设计

### 焊接

## 软件
### 驱动原理
#### WS2812通信

#### SPI驱动WS2812

#### 定时器DMA PWM驱动WS2812

### 工程架构
#### 驱动与业务逻辑的解耦





