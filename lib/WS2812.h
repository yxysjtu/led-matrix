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
} WS2812_color_t;

extern WS2812_color_t ws2812_data[WS2812_LEN];

extern WS2812_color_t violet;

void WS2812_Handler();

#endif //PROJECT1_V0_WS2812_H
