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
* 首先WS2812一个bit宽度是1.25us，分辨率0.25us，所以定时器分频到4M，ARR取5-1。开通道PWM_Generation CHx（注意不是output compare）
  
  ![image](https://github.com/yxysjtu/led-matrix/assets/53338300/da806b90-f650-42cb-a359-f625a229c187)

* 然后配置DMA。开启定时器的DMA_Request（注意这里需要选一个有DMA_Request的定时器。这里DMA_Request的源自动配成OC event。在寄存器里是DIER的OC event触发该通道的DMA Request），配置为mem2periph，halfword，circular传输
  ![image](https://github.com/yxysjtu/led-matrix/assets/53338300/5e59059a-ef53-4a99-88ef-f7283a724245)

* 最后程序里加入`HAL_TIM_PWM_Start_DMA(&htim, TIM_CHANNEL_x, data, data_len);`（这里会发现因为是循环发送，cube默认开启的DMA中断显得没有什么意义，可以把DMA_init里面的NVIC函数关掉，并且把`HAL_TIM_PWM_Start_DMA`里面的`HAL_DMA_Start_IT`改成`HAL_DMA_Start`，不要在传输完成触发中断，开销小一点）
  
### 工程架构
![image](https://github.com/yxysjtu/led-matrix/assets/53338300/55b24ade-14e1-47ab-913b-e3442ca61a4d)

#### 驱动与业务逻辑的解耦
* 在`task.cpp`里写业务逻辑：
	* `setup()`初始化
 	* `loop()`主循环
  	* `task_handler()`1ms中断，用于放每个驱动的`Handler()`
* 用`include.h`放所有头文件
* 驱动分层思想：
  1. `hal.h`放所有跟芯片级的接口
  2. `module.h`放所有基于芯片级接口的驱动，比如WS2812的驱动
  3. `device.h`放所有基于`module.h`的驱动的高层设备，比如光立方的控制类
 
思考：
1. 驱动一般有两种写法，一种是直接命令，就是直接调用通信的函数发送命令/数据；一种是Handler思想，就是用户只是修改状态变量/数据变量，通信函数在定时器中断里定时发送这些数据；请思考这两者的区别，分别优劣势和应用场景
2. 任务逻辑一般有两种写法，一种是阻塞式线性写下来，控制时间间隔的地方加delay；一种是状态机，任务放在定时器中断里，用状态变量控制时序。请比较两者优劣势与应用场景。




