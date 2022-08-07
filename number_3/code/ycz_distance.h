/*
 * @Author: Ptisak
 * @Date: 2022-07-27 20:25:34
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-07-27 22:10:52
 * @Version: Do not edit
 */
#ifndef __ycz_dis_h
#define __ycz_dis_h

#include "psk_ALL.h"

extern float others_speed;
extern float disLoop_speed;
float calc_my_speed(void);
float calc_distance(float ultrasonic_distance, float my_speed, float others_speed);
float calc_disLoop_speed(float dis);

#endif
