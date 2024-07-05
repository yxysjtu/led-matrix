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

WS2812_color_t color_mul(WS2812_color_t color, float a){
    color.g = (int)((float)color.g * a);
    color.r = (int)((float)color.r * a);
    color.b = (int)((float)color.b * a);
    return color;
}

void setup(){
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 4; j++){
            ws2812_data[i * 8 + j] = color_mul(violet, 0.33 * (float)j);
            ws2812_data
        }
    }

}

void loop(){

}


void task_handler(){ //1ms中断
    if(HAL_GetTick() % 10 == 0) WS2812_Handler();
}