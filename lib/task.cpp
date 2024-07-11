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

//#define TEST1 //点亮所有灯
//#define TEST2 //线性流水
//#define TEST3 //立方体静态
//#define TEST4 //彩虹流水
//#define TEST5 //波浪
#define TEST6

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


void setup(){
    Color_t c;

    for(int i = 0; i < 12; i++){
        c = float2RGB((float)i / 12);
        for(int j = 0; j < 8; j++){
            float brightness = 0.0029 * j * j * j;
            cube.data[cube.edge[i][0]][cube.edge[i][1]][j] = color_mul(c, brightness);
            cube.data[cube.edge[i][1]][cube.edge[i][0]][7 - j] = color_mul(c, brightness);
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

#ifdef TEST4
LED_Matrix cube;

float init_phase = 0, dx = 0.1, dt = 0.002;

void color_flow_next(){
    Color_t c;

    float phase = init_phase;
    for(int i = 0; i < 8; i++){
        c = float2RGB(phase);
        for(int j = 0; j < 3; j++){
            cube.set_edge_point(j, i, c);
        }
        phase += dx;
        if(phase > 2) phase -= 2;
    }

    for(int i = 0; i < 8; i++){
        c = float2RGB(phase);
        for(int j = 3; j < 9; j++){
            cube.set_edge_point(j, i, c);
        }
        phase += dx;
        if(phase > 2) phase -= 2;
    }

    for(int i = 0; i < 8; i++){
        c = float2RGB(phase);
        for(int j = 9; j < 12; j++){
            cube.set_edge_point(j, i, c);
        }
        phase += dx;
        if(phase > 2) phase -= 2;
    }

    init_phase += dt;
    if(init_phase > 2) init_phase -= 2;
}

uint32_t t0, t1;
void setup(){
    t0 = HAL_GetTick();
    color_flow_next();
    t1 = HAL_GetTick() - t0;
}

void loop(){
    t0 = HAL_GetTick();
    color_flow_next();
    t1 = HAL_GetTick() - t0;
}


void task_handler(){ //1ms中断
    if(HAL_GetTick() % 10 == 0) WS2812_Handler();

    if(HAL_GetTick() % 10 == 0) cube.Handler();
}
#endif

#ifdef TEST5
LED_Matrix cube;

float init_phase = 0, phase, dx = 0.1, dt = 0.004;

Color_t next_color(){
    Color_t c0 = violet, c;
    float p1 = phase;
    if(p1 > 1) p1 = 2 - p1;
    c = color_mul(c0, p1 * p1 * p1);
    phase += dx;
    if(phase > 2) phase -= 2;
    return c;
}
void color_flow_next(){
    Color_t c;

    phase = init_phase;
    for(int i = 0; i < 8; i++){
        c = next_color();
        for(int j = 0; j < 3; j++){
            cube.set_edge_point(j, i, c);
        }
    }

    for(int i = 0; i < 8; i++){
        c = next_color();
        for(int j = 3; j < 9; j++){
            cube.set_edge_point(j, i, c);
        }
    }

    for(int i = 0; i < 8; i++){
        c = next_color();
        for(int j = 9; j < 12; j++){
            cube.set_edge_point(j, i, c);
        }
    }

    init_phase += dt;
    if(init_phase > 2) init_phase -= 2;
}

uint32_t t0, t1;
void setup(){
    t0 = HAL_GetTick();
    color_flow_next();
    t1 = HAL_GetTick() - t0;
    //WS2812_color_set(violet,0);

}

void loop(){
    t0 = HAL_GetTick();
    color_flow_next();
    t1 = HAL_GetTick() - t0;
}


void task_handler(){ //1ms中断
    //if(HAL_GetTick() % 10 == 0)
    	WS2812_Handler_DMA();

    if(HAL_GetTick() % 10 == 0) cube.Handler();
}
#endif


#ifdef TEST6
LED_Matrix cube;

float init_phase = 0, dx = 0.1, dt = 0.002;

void color_flow_next(){
    Color_t c;

    float phase = init_phase;
    for(int i = 0; i < 8; i++){
        c = float2RGB(phase);
        for(int j = 0; j < 3; j++){
            cube.set_edge_point(j, i, c);
        }
        phase += dx;
        if(phase > 2) phase -= 2;
    }

    for(int i = 0; i < 8; i++){
        c = float2RGB(phase);
        for(int j = 3; j < 9; j++){
            cube.set_edge_point(j, i, c);
        }
        phase += dx;
        if(phase > 2) phase -= 2;
    }

    for(int i = 0; i < 8; i++){
        c = float2RGB(phase);
        for(int j = 9; j < 12; j++){
            cube.set_edge_point(j, i, c);
        }
        phase += dx;
        if(phase > 2) phase -= 2;
    }

    init_phase += dt;
    if(init_phase > 2) init_phase -= 2;
}

uint32_t t0, t1;
void setup(){
    t0 = HAL_GetTick();
    color_flow_next();
    t1 = HAL_GetTick() - t0;
}

void loop(){
    t0 = HAL_GetTick();
    color_flow_next();
    t1 = HAL_GetTick() - t0;
}


void task_handler(){ //1ms中断
//    if(HAL_GetTick() % 10 == 0){
//    	if(HAL_GetTick() % 20 == 0) cube.Handler();
//    	else WS2812_Handler_DMA();
//
//    }

	if(HAL_GetTick() % 10 == 0) cube.Handler();
	WS2812_Handler_DMA();
}
#endif
