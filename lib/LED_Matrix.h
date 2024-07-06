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

#ifndef PROJECT1_V0_LED_MATRIX_H
#define PROJECT1_V0_LED_MATRIX_H

#include "module.h"

class LED_Matrix {
public:
    Color_t data[8][8][8];

    int edge[12][2] = {
            {0, 2}, {0, 1}, {0, 4},

            {2, 6}, {2, 3},
            {1, 5}, {1, 3},
            {4, 6}, {4, 5},

            {6, 7}, {5, 7}, {3, 7}
    };

    void set_edge_point(int edge_index, int point_index, Color_t color);

    void Handler();
};


#endif //PROJECT1_V0_LED_MATRIX_H
