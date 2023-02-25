/*
 * control.h
 *
 *  Created on: 2021��10��7��
 *      Author: 11609
 */

#ifndef USER_CONTROL_H_
#define USER_CONTROL_H_
#include "headfile.h"

#define ACC_FILTER_NUM 10


extern int Target_Speed;
extern unsigned char Flag_Stop;
extern float X_Balance_KP ,X_Balance_KI,X_Balance_KD,X_Velocity_KP,X_Velocity_KI;       // ���PID����
extern int MotorDutyA ;
extern int PWM_X,PWM_accel;
extern float error_Integral;
extern int stop ;
extern float error_xunxian;
extern int Servo_PWM,Servo_PWM1,Servo_PWM2; // ���PID
extern uint8 AD_flag;
extern float ramp_yingshe;
void Balance(void);

/**************************************************************************
Y��ƽ��PID����,�ǶȻ�
**************************************************************************/
float X_balance_Control(float Angle,float Angle_Zero,float Gyro);
/**************************************************************************
�ٶ�PI����,�ٶ���������
**************************************************************************/
float Velocity_Control(float encoder);
int SBB_Get_BalancePID(float error);
int AD_Get_BalancePID(float AD_err);
float ditui(float input);
int SBB_Get_MotorPI (int Encoder,int Target);

#endif /* USER_CONTROL_H_ */
