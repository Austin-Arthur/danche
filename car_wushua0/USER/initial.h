/*
 * initial.h
 *
 *  Created on: 2021年12月29日
 *      Author: 11609
 */

#ifndef USER_INITIAL_H_
#define USER_INITIAL_H_

#include "headfile.h"
/*
#define KEY1        gpio_get(P21_5)
#define KEY2        gpio_get(P21_6)
#define KEY3        gpio_get(P21_7)
#define KEY4        gpio_get(P20_0)
#define KEY5        gpio_get(P20_2)


#define KEY1_PRES   1
#define KEY2_PRES   2
#define KEY3_PRES   3
#define KEY4_PRES   4
#define KEY5_PRES   5
*/
#define Servo_Delta 120            //舵机左右转动的差值，与舵机型号，拉杆和舵机臂长有关
#define Servo_Center_Mid 820      //舵机直行中值，
#define Servo_Left_Max   (Servo_Center_Mid+Servo_Delta)      //舵机左转极限值
#define Servo_Right_Min  (Servo_Center_Mid-Servo_Delta)      //舵机右转极限值，此值跟舵机放置方式有关，立式


/*
int KeyWork1();
void Key_Init();
void KeySwitch();
*/
void beep_on();
void beep_off();
void beep_init();

void ADC_Init();
void Get_ADC_Value();

void motor_Init();
void duoji_Init();
void bianma_Init();
void Get_speed();

void duoji_control(int duty);
void motor_control1(float motor1);
void motor_control2(float motor2);

void initial();

extern uint16 ADC_val[5];
extern int speed,speed_angle;


#endif /* USER_INITIAL_H_ */
