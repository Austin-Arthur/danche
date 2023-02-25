/*
 * PID.h
 *
 *  Created on: 2022年5月19日
 *      Author: 11609
 */

#ifndef USER_PID_H_
#define USER_PID_H_

#include "headfile.h"
#include "common.h"

typedef struct
{
    float SumError;  //误差累积

    float Kp;      //比例系数
    float Ki;      //积分系数
    float Kd;      //微分系数

    int32 LastError;  //上一次误差
    int32 LLastError; //上上次误差
}PID;

extern PID SpeedPID,rampPID;
extern PID Ang_Vel_PID,Angle_PID,MOTOR_PID;

//函数声明
extern int16 LocP_DCalc(PID*sptr,int16 Setpoint,int16 Turepoint);
extern int16 IncPIDCalc(PID *sptr,int16 Setpoint,int16 Turepoint);//增量式PID控制
extern float Balance_Sudu_PID(PID*sptr,float Setpoint,float Turepoint);
extern float Balance_nei_PID(PID*sptr,float Setpoint,float Turepoint);
extern float Balance_wai_PID(PID*sptr,float Setpoint,float Turepoint);



#endif /* USER_PID_H_ */
