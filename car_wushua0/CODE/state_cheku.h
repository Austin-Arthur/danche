/*
 * state_cheku.h
 *
 *  Created on: 2022��3��14��
 *      Author: 11609
 */

#ifndef CODE_STATE_CHEKU_H_
#define CODE_STATE_CHEKU_H_
#include "headfile.h"
void Deal_zebro(void);          //���������߶����ݡ��˽��ڵ�Ӱ��

uint8 Is_InGarageL(void);       //�ж��Ƿ�Ϊ�����
void state_40();
void state_41(void);            //ʶ���󳵿�Ԫ�أ���ʶ�������
void state_42(void);            //ʶ�𵽰����ߣ����������
void state_43(void);            //�������ɣ�����LCD��ʾ�����

uint8 Is_InGarageR(void);       //�ж��Ƿ�Ϊ�����
void state_51(void);            //ʶ���ҳ���Ԫ�أ���ʶ�������
void state_52(void);            //ʶ�𵽰����ߣ��������ҿ�
void state_53(void);            //�������ɣ�����LCD��ʾ�����

uint8 Is_OutGarage(void);       //�ж��Ƿ�Ϊ����
void state_61(void);            //ʶ���ҳ���Ԫ�أ���ʶ�������
void state_62(void);            //ʶ�𵽰����ߣ��������ҿ�

void state_71(void);            //ʶ���ҳ���Ԫ�أ���ʶ�������
void state_72(void);            //ʶ�𵽰����ߣ��������ҿ�

void GarageInPatchLine(uint8 x,uint8 y,int8 Str[94]);           //��ⲹ��

extern uint8 CheKu_AD;
extern int8 cheku_line[94];
extern uint8 Z_point[2][2];
extern uint8 CheKuL_Y;
extern uint8 chuku_p,chuku_p2;
#endif /* CODE_STATE_CHEKU_H_ */
