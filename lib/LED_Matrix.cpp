/**
  ******************************************************************************
  * @FileName			    LED_Matrix.h
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

#include "LED_Matrix.h"

void LED_Matrix::Handler() {
    static int point_list1[] = {0, 2, 6, 4,
                               0, 4, 5, 1,
                               0, 1, 3, 2, 0};
    static int point_list2[] = {7, 6, 2, 3,
                                7, 3, 1, 5,
                                7, 5, 4, 6, 7};

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 8; j++){
            ws2812_data[i * 8 + j] = data[point_list1[i]][point_list1[i + 1]][j];
        }
    }
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 8; j++){
            ws2812_data[(i + 12) * 8 + j] = data[point_list2[i]][point_list2[i + 1]][j];
        }
    }
}
