/*
 * state_ring.h
 *
 *  Created on: 2022年3月8日
 *      Author: 11609
 */

#ifndef CODE_STATE_RING_H_
#define CODE_STATE_RING_H_
#include "headfile.h"
//左边圆环
void state_10();
void state_11();
void state_12();
void state_13();
void state_14();
void state_15();
void state_16();
//右边圆环
void state_20();
void state_21();
void state_22();
void state_23();
void state_24();
void state_25();
extern uint8 ringSize[6];
extern uint8 circleLx,circleLy,ringCnt,circleLx_temp;

uint8 Is_circleL();
uint8 Is_circleR();

extern int8 RingIn_50[94];
extern int8 RingIn_60[94];
extern int8 RingIn_80[94];
 
extern uint8 circleLx,circleLy,circleLx_temp;
extern uint8 flag_cir;
float getLine(uint8* A);

void RingInPatchLine_angle(uint8 x,uint8 y,int8 Str[94],float rato);


#endif /* CODE_STATE_RING_H_ */
