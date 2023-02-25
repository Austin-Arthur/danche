/*
 * state.h
 *
 *  Created on: 2021��12��30��
 *      Author: 11609
 */

#ifndef CODE_STATE_H_
#define CODE_STATE_H_

#include "headfile.h"
#define ChuKu_left 1
#define ChuKu_right 2

//����״̬
void state_00();
//ֱ��
void state_01();
//����ǰ��Сֱ��
void state_02();
//����ʱ��
void state_03();
//������
void state_06();
void state_41();
void state_42();
//����״̬
void state_99();


uint8 Is_straight();
uint8 Is_zebro();
float Is_straight_abs(uint8 y0,uint8 y1,uint8* line);
uint8 Is_safe();
extern int AD_Fork;
extern uint8 cnt_zebro;
extern uint8 test1_zebor,test2_zebor;
#endif /* CODE_STATE_H_ */
