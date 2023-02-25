/*
 * filter.h
 *
 *  Created on: 2022年2月21日
 *      Author: 11609
 */

#ifndef USER_FILTER_H_
#define USER_FILTER_H_
#include "headfile.h"
extern float angle, angle_dot;
typedef struct
{
    /*不用动*/
    double LastP;//上次估算协方差
    double Now_P;//当前估算协方差
    double out;//卡尔曼滤波器输出
    double Kg;//卡尔曼增益
    double Q;
    double R;
}Kalman_Typedef;

void Kalman_Init(Kalman_Typedef *klm, const double klm_Q, const double klm_R);
double KalmanFilter(Kalman_Typedef *klm, double input);
void Kalman_Filter(float Accel,float Gyro);
void Yijielvbo(float angle_m, float gyro_m);
float lpf(float thr,float fc);



#endif /* USER_FILTER_H_ */
