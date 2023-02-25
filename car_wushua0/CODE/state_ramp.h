/*
 * state_ramp.h
 *
 *  Created on: 2022年3月8日
 *      Author: 11609
 */

#ifndef CODE_STATE_RAMP_H_
#define CODE_STATE_RAMP_H_
#include "headfile.h"

//坡道状态
void state_31();
void state_32();
void state_33();
void state_34();
void state_35();
uint8 Is_ramp(uint8 type);
boolean Is_ramp_angle();
extern uint8 rampN;


#endif /* CODE_STATE_RAMP_H_ */
