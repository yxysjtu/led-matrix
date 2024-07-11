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

Color_t ws2812_data[WS2812_LEN];
uint8_t ws2812_data_DMA[WS2812_LEN*3*4];
Color_t violet = {238, 20, 255};



void WS2812_reset(){
    static uint8_t buffer[200] = {0};
    HAL_SPI_Transmit(&hspi1, buffer, 200, 10);
}

void WS2812_send(Color_t color){
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


void WS2812_Handler_DMA()
{
	HAL_SPI_Transmit_DMA(&hspi1, ws2812_data_DMA, WS2812_LEN*3*4);
}

void WS2812_color_set(Color_t color, uint8_t num)
{
	int i;
	i = 0;
	for(int j = 0; j != 4; ++j)
	{
		ws2812_data_DMA[12*num+4*i+j] = (color.g & 1 << (7 - 2*j) ? 0b1100 : 0b1000)  << 4;
		ws2812_data_DMA[12*num+4*i+j] |= color.g & 1 << (6 - 2*j) ? 0b1100 : 0b1000;
	}
	i = 1;
	for(int j = 0; j != 4; ++j)
	{
		ws2812_data_DMA[12*num+4*i+j] = (color.r & 1 << (7 - 2*j) ? 0b1100 : 0b1000)  << 4;
		ws2812_data_DMA[12*num+4*i+j] |= color.r & 1 << (6 - 2*j) ? 0b1100 : 0b1000;
	}
	i = 2;
	for(int j = 0; j != 4; ++j)
	{
		ws2812_data_DMA[12*num+4*i+j] = (color.b & 1 << (7 - 2*j) ? 0b1100 : 0b1000)  << 4;
		ws2812_data_DMA[12*num+4*i+j] |= color.b & 1 << (6 - 2*j) ? 0b1100 : 0b1000;
	}
}

void WS2812_Handler(){
    for(int i = 0; i < WS2812_LEN; i++){
        WS2812_send(ws2812_data[i]);
    }
    WS2812_reset();
}


Color_t float2RGB(float x)
{
    Color_t color;
    //x = x - (int)(x / 2) * 2;
    if(x > 1) x = 2 - x;
    //x = 1.0 - x;
    // x由小到大的依次为：赤、橙、黄、绿、青、蓝，注意没有紫色
    //定义红色通道
    if (x < 5.0 / 12.0)
    {
        color.r = 255;
    }
    else if (x >= 5.0 / 12.0 && x < 7.0 / 12.0)
    {
        color.r = (int)(-1530 * (x - 7.0 / 12.0));
    }
    else
    {
        color.r = 0;
    }
    //定义绿色通道
    if (x < 1.0 / 12.0)
    {
        color.g = 0;
    }
    else if (x >= 1.0 / 12.0 && x < 3.0 / 12.0)
    {
        color.g = (int)(990 * (x - 1.0 / 12.0));
    }
    else if (x >= 3.0 / 12.0 && x < 5.0 / 12.0)
    {
        color.g = (int)(540 * (x - 5.0 / 12.0) + 255);
    }
    else if (x >= 5.0 / 12.0 && x < 7.0 / 12.0)
    {
        color.g = 255;
    }
    else if (x >= 7.0 / 12.0 && x < 9.0 / 12.0)
    {
        color.g = (int)(-768 * (x - 7.0 / 12.0) + 255);
    }
    else if (x >= 9.0 / 12.0 && x < 11.0 / 12.0)
    {
        color.g = (int)(-762 * (x - 11.0 / 12.0));
    }
    else
    {
        color.g = 0;
    }
    //定义蓝色通道
    if (x < 7.0 / 12.0)
    {
        color.b = 0;
    }
    else if (x >= 7.0 / 12.0 && x < 9.0 / 12.0)
    {
        color.b = (int)(1530 * (x - 7.0 / 12.0));
    }
    else
    {
        color.b = 255;
    }

    return color;
}

Color_t color_mul(Color_t color, float a){
    color.g = (int)((float)color.g * a);
    color.r = (int)((float)color.r * a);
    color.b = (int)((float)color.b * a);
    return color;
}
