/**
  ******************************************************************************
  * @FileName			    task.h
  * @Description
  * @author                 Yu Xinyi
  * @note
  ******************************************************************************
  *
  * Copyright (c) 2023 Team JiaoLong-ShanghaiJiaoTong University
  * All rights reserved.
  *
  ******************************************************************************
**/

#include "include.h"

//LED_Matrix led;

void setup(){
    for(int i = 0; i < WS2812_LEN; i++){
        ws2812_data[i] = violet;
    }
}

void loop(){

}


void task_handler(){ //1ms中断
    if(HAL_GetTick() % 10 == 0) WS2812_Handler();
}