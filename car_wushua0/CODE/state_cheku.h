/*
 * state_cheku.h
 *
 *  Created on: 2022年3月14日
 *      Author: 11609
 */

#ifndef CODE_STATE_CHEKU_H_
#define CODE_STATE_CHEKU_H_
#include "headfile.h"
void Deal_zebro(void);          //消除斑马线对爬梯、八近邻的影响

uint8 Is_InGarageL(void);       //判断是否为左入库
void state_40();
void state_41(void);            //识别左车库元素，等识别斑马线
void state_42(void);            //识别到斑马线，补线入左库
void state_43(void);            //左入库完成，并且LCD显示左入库

uint8 Is_InGarageR(void);       //判断是否为右入库
void state_51(void);            //识别右车库元素，等识别斑马线
void state_52(void);            //识别到斑马线，补线入右库
void state_53(void);            //右入库完成，并且LCD显示右入库

uint8 Is_OutGarage(void);       //判断是否为出库
void state_61(void);            //识别右车库元素，等识别斑马线
void state_62(void);            //识别到斑马线，补线入右库

void state_71(void);            //识别右车库元素，等识别斑马线
void state_72(void);            //识别到斑马线，补线入右库

void GarageInPatchLine(uint8 x,uint8 y,int8 Str[94]);           //入库补线

extern uint8 CheKu_AD;
extern int8 cheku_line[94];
extern uint8 Z_point[2][2];
extern uint8 CheKuL_Y;
extern uint8 chuku_p,chuku_p2;
#endif /* CODE_STATE_CHEKU_H_ */
