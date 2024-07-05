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

//#define TEST1
//#define TEST2
#define TEST3


#ifdef TEST1
void setup(){
	for(int i = 0; i < WS2812_LEN; i++)
	{
		ws2812_data[i] = violet;
	}

}

void loop(){

}


void task_handler(){ //1ms中断
    if(HAL_GetTick() % 10 == 0) WS2812_Handler();
}
#endif

#ifdef TEST2
uint32_t delay_t = 100;
Color_t color_mul(Color_t color, float a){
    color.g = (int)((float)color.g * a);
    color.r = (int)((float)color.r * a);
    color.b = (int)((float)color.b * a);
    return color;
}

void LED_flow_set()
{
	Color_t temp = ws2812_data[WS2812_LEN-1];
	for(int i = WS2812_LEN-1; i > 0; i--)
	{
		ws2812_data[i] = ws2812_data[i-1];
	}
	ws2812_data[0] = temp;
    HAL_Delay(delay_t);
}

void setup(){
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 4; j++){
            ws2812_data[i * 8 + j] = color_mul(violet, 0.33 * (float)j);
            ws2812_data[(i + 1) * 8 - j - 1] = color_mul(violet, 0.33 * (float)j);
        }
    }

}

void loop(){
	LED_flow_set();
}


void task_handler(){ //1ms中断
    if(HAL_GetTick() % 10 == 0) WS2812_Handler();
}

#endif

#ifdef TEST3
LED_Matrix cube;

int edge[12][2] = {
        {0, 2}, {0, 1}, {0, 4},

        {2, 6}, {2, 3},
        {1, 5}, {1, 3},
        {4, 6}, {4, 5},

        {6, 7}, {5, 7}, {3, 7}
};


Color_t color_mul(Color_t color, float a){
    color.g = (int)((float)color.g * a);
    color.r = (int)((float)color.r * a);
    color.b = (int)((float)color.b * a);
    return color;
}

void setup(){
    Color_t c;

    for(int i = 0; i < 12; i++){
        c = float2RGB((float)i / 12);
        for(int j = 0; j < 8; j++){
            float brightness = 0.0029 * j * j * j;
            cube.data[edge[i][0]][edge[i][1]][j] = color_mul(c, brightness);
            cube.data[edge[i][1]][edge[i][0]][7 - j] = color_mul(c, brightness);
        }
    }

}

void loop(){

}


void task_handler(){ //1ms中断
    if(HAL_GetTick() % 10 == 0) WS2812_Handler();

    if(HAL_GetTick() % 10 == 0) cube.Handler();
}
#endif