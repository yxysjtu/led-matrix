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

    void Handler();
};


#endif //PROJECT1_V0_LED_MATRIX_H
