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

#ifndef PROJECT1_V0_WS2812_H
#define PROJECT1_V0_WS2812_H

#include "hal.h"

#define WS2812_LEN 192

typedef struct{
    uint8_t g;
    uint8_t r;
    uint8_t b;
} Color_t;

extern Color_t ws2812_data[WS2812_LEN];

extern Color_t violet;

Color_t float2RGB(float x); //x 0-1
Color_t color_mul(Color_t color, float a);

void WS2812_Handler();

#endif //PROJECT1_V0_WS2812_H
