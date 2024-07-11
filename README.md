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
* 单片机最小系统：
  1. MCU:STM32G030K8T6(LQFP32封装)
  2. 电源:5V转3.3V线性稳压器
  3. 时钟:8Mhz外部晶振
  4. 复位电路
     
* 其他外设：
  1. 调试接口：2*5P简易牛角座接ST-LINK32，3.3V供电
  2. 调试外设：LED、按键
  3. 串口及控制信号线

* 原理图
![image](https://github.com/yxysjtu/led-matrix/assets/110826577/757f6ee4-f713-4962-a031-fe59a367e9e5)

### PCB设计
* 设计思路
	* 元件布局
		1. 功能模块化：将功能相近或关联的元件尽可能集中布置，减少走线长度，提高电路稳定性。
  		2. 机械结构：考虑PCB的尺寸、形状、安装孔位置等与实际产品的匹配。
  	* 走线设计
		1. 优先布置电源线，确保电源的低阻抗和可靠性。使用较宽的走线或铜箔平面。
  		2. 高频信号线与其他信号线或电源线保持足够的间距，避免相互干扰。
* 经验与反思
	1. 将重心放在PCB布局上，极大减轻布线难度，如将2×10排针换为左右两侧的1×10排针可避免交叉走线，走线更合理（左图修改前，右图修改后）

	   <center class="half">
	    <img src="https://github.com/yxysjtu/led-matrix/assets/110826577/070525e4-fc38-4607-9a9c-d458177b719f" width="400"/><img src="https://github.com/yxysjtu/led-matrix/assets/110826577/d4327cb7-e5bc-4dbc-8f81-14f93c36982c" width="400"/>
	   </center>
	2. 避免换层/打过孔
 	3. 避免直角布线。因为线宽改变会引起阻抗改变，阻抗不连续造成信号反射。（该问题在高频电路中需着重考虑，但出于设计规范尽量还是45°拐角走线）
	4. 信号传输线尽可能短

* PCB设计图
<center class="half">
    <img src="https://github.com/yxysjtu/led-matrix/assets/110826577/79ded06f-657a-4457-b15c-2b08f0575682" width="400"/><img src="https://github.com/yxysjtu/led-matrix/assets/110826577/ae93919e-f0da-4b59-9062-5ca092447f0c" width="400"/>
</center>



### 焊接
* 错误及解决方法
	* 错误：轻触开关两脚的买错成四脚的
 	* 解决方法：利用万用表的二极管蜂鸣档检测轻触开关四脚的连通情况，将未按下开关时断开的两脚焊接在两个焊盘上
    	![image](https://github.com/yxysjtu/led-matrix/assets/110826577/ae343e28-c4a1-43fc-a17f-59ab125f8feb)

* 注意点
  1. 首先焊接难度较高的主控芯片，注意避免引脚连锡
  2. 尽量先焊接贴式元件
  3. 使用锡膏后记得用电烙铁吸去多余的锡
  4. 确保芯片放置方向正确
  5. 焊接排针时确保焊盘与锡完全贴合，避免上锡过于饱满
   ![a1a945c6e6465872397e519ada0f4c2](https://github.com/yxysjtu/led-matrix/assets/110826577/14af6123-ac3d-45ed-861c-2bfbf7a931fe)


* 焊接成果图
![f8195295d962d2e131820562d57f187](https://github.com/yxysjtu/led-matrix/assets/110826577/0cc76ebf-4192-4722-8b5f-2ee842635fe7)

* 焊接完成后用点灯实验测试，单片机正常运行
![672c5d9aec70102060e3a62bca5ef2a](https://github.com/yxysjtu/led-matrix/assets/110826577/a08dd33d-375a-4896-916e-b0c137d4bc17)


## 软件
### 驱动原理
#### WS2812通信
![image](https://github.com/yxysjtu/led-matrix/assets/53338300/b90b431f-3e89-4d45-bceb-23eb05493eb6)

图1 WS2812B电气结构
WS2812B单个LED灯的结构如图1，VDD为+5V电源，VSS接地，DIN为信号输入，DOUT为信号输出。根据WS2812B的数据手册，RGB的二进制编码通过不同长度的波形来表示，具体要求如图2所示。
![image](https://github.com/yxysjtu/led-matrix/assets/53338300/8b6df388-7ccd-42de-b30b-0ad6da202eb0)

图2 WS2812B信号波形
其中T0H和T1L的持续时间为0.25µs，T0L和T1H的持续时间为1µs，都允许有±150ns的误差，RESET码为持续50µs以上的低电平。对于每一个LED灯，需要传输表示GRB的3字节数据，即24位二进制信息，用上述的波形进行表示。我们的项目采用的WS2812B灯带采用级联的方法连接，在电气上，192个LED灯为并联连接，在信号传输上，采用串联连接。控制信号从第一个LED的DIN传入，锁存前24位信息，并将剩下的信息从DOUT传输到下一个灯的DIN每次，即控制信号每经过一个灯，减少24位。当WS2812B检测到50µs以上的低电平，即RESET码时，数据停止传输，当前的RGB信息将被锁存在所有的LED灯上，灯带的状态保持不变。对于用户而言，我们只需要对每一个灯带依次进行GRB编码，编码结束后传输RESET码锁存信号，即可改变灯带中所有LED的状态。

#### SPI驱动WS2812
本项目通过SPI通信总线驱动WS2812。在MCU处于SPI通信的主模式时，MOSI信号线实际为受SCK时钟信号控制时序的比特流，通过调整SCK时钟信号的频率，即MCU的主频，并进行适当的分频，即可产生符合图2所示的波形。本项目使用的MCU为STM32G030K8T6，使用16MHz的内部晶振，通过PLL倍频和分频，设定系统的主频为50MHz。

![image](https://github.com/yxysjtu/led-matrix/assets/53338300/e12aab93-46ab-4dcd-b120-7ad27913363c)

图3 STM32G030K8T6的时钟树设置

在SPI配置中，设定每次8位传输，高位先发，SPI时钟16倍预分频，CPOL=0，CPHA=1，以满足WS2812的通信要求。此时SPI的波特率为3.125Mbit/s，即每一位传输需要的时间为0.32µs。

![image](https://github.com/yxysjtu/led-matrix/assets/53338300/23472fab-aa6d-4725-b04f-c7464921e3ea)

图4 SPI通信配置

在该通信协议下，WS2812的0码可表示为1000B，1码可表示为0001B，即1位数据膨胀为SPI中的4位。
接下来编写驱动库。先定义结构体`Color_t`，存储每一个LED的RGB数据。由此可以编写函数`WS2812_send`和`WS2812_reset`，`WS2812_send`的参数为`Color_t`类型的数据，用于向灯带传输一个LED灯的RGB数据，24位一起传输，从而避免了调用函数时的时间间隔导致WS2812误认成RESET码。`WS2812_reset`无参数，传输一段低电平，锁存信号。在这两个函数的基础上，可以编写`WS2812_Handler`函数。创建`Color_t`类型的数组`ws2812_data`，存储灯带192个WS2812灯的RGB数据。WS2812_Handler函数调用WS2812_send依次传输每个LED灯的数据，最后调用WS2812_reset锁存数据。根据SPI通信设置，调用一次WS2812_Handler需要的时间为：24*192*4*0.32µs+50µs = 5948.24µs至此，驱动函数编写完成，在systick中断服务程序中每10ms调用。上层用户只需要在业务逻辑程序中改变ws2812_data中的数据内容，即可实现深渊镜显示效果的变化。

### SPI DMA

#### 定时器DMA PWM驱动WS2812
* 首先WS2812一个bit宽度是1.25us，分辨率0.25us，所以定时器分频到4M，ARR取5-1。开通道PWM_Generation CHx（注意不是output compare）
  
  ![image](https://github.com/yxysjtu/led-matrix/assets/53338300/da806b90-f650-42cb-a359-f625a229c187)

* 然后配置DMA。开启定时器的DMA_Request（注意这里需要选一个有DMA_Request的定时器。这里DMA_Request的源自动配成OC event。在寄存器里是DIER的OC event触发该通道的DMA Request），配置为mem2periph，halfword，circular传输
  ![image](https://github.com/yxysjtu/led-matrix/assets/53338300/5e59059a-ef53-4a99-88ef-f7283a724245)

* 最后程序里加入`HAL_TIM_PWM_Start_DMA(&htim, TIM_CHANNEL_x, data, data_len);`（这里会发现因为是循环发送，cube默认开启的DMA中断显得没有什么意义，可以把DMA_init里面的NVIC函数关掉，并且把`HAL_TIM_PWM_Start_DMA`里面的`HAL_DMA_Start_IT`改成`HAL_DMA_Start`，不要在传输完成触发中断，开销小一点）

**测试产生不同宽度的脉冲**：
  ![3563cbb056b3a688bff2a0871152ec5](https://github.com/yxysjtu/led-matrix/assets/53338300/7840a741-c7b5-4498-9ce0-c619669e7957)

  
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




