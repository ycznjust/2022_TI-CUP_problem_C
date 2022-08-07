/*
 * @Author: Ptisak
 * @Date: 2022-07-23 20:02:32
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-07-28 22:12:45
 * @Version: Do not edit
 */
#include "psk_ALL.h"
#ifndef PSK_MISSION
#define PSK_MISSION
void Mission_1(void);
void Mission_2(void);
void Mission_3(void);
void Mission_4(void);
void Mission_5(void);
void slave_task(void);
extern uint8 task_start_flag ;
extern uint8 stop_flag ;
#endif