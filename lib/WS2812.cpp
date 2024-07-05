/**
  ******************************************************************************
  * @FileName			    WS2812.h
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

#include "WS2812.h"

WS2812_color_t ws2812_data[WS2812_LEN];

WS2812_color_t violet = {238, 20, 255};

void WS2812_reset(){
    static uint8_t buffer[200] = {0};
    HAL_SPI_Transmit(&hspi1, buffer, 200, 10);
}

void WS2812_send(WS2812_color_t color){
    uint8_t buffer[12];
    int i;

    i = 0;
    for(int j = 0; j != 4; ++j){
        buffer[4*i+j] = (color.g & 1 << (7 - 2*j) ? 0b1100 : 0b1000)  << 4;
        buffer[4*i+j] |= color.g & 1 << (6 - 2*j) ? 0b1100 : 0b1000;
    }
    i = 1;
    for(int j = 0; j != 4; ++j){
        buffer[4*i+j] = (color.r & 1 << (7 - 2*j) ? 0b1100 : 0b1000)  << 4;
        buffer[4*i+j] |= color.r & 1 << (6 - 2*j) ? 0b1100 : 0b1000;
    }
    i = 2;
    for(int j = 0; j != 4; ++j){
        buffer[4*i+j] = (color.b & 1 << (7 - 2*j) ? 0b1100 : 0b1000)  << 4;
        buffer[4*i+j] |= color.b & 1 << (6 - 2*j) ? 0b1100 : 0b1000;
    }

    HAL_SPI_Transmit(&hspi1, buffer, 12, 10);
}

void WS2812_Handler(){
    for(int i = 0; i < WS2812_LEN; i++){
        WS2812_send(ws2812_data[i]);
    }
    WS2812_reset();
}
