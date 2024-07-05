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

uint8_t ws2812_data[WS2812_LEN][3];

void WS2812_reset(){
    static uint8_t buffer[200] = {0};
    HAL_SPI_Transmit(&hspi1, buffer, 200, 10);
}

void WS2812_send(){

}
