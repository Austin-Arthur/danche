#ifndef USER_ANGLE_H_
#define USER_ANGLE_H_
#include "headfile.h"

#define pitch   1
#define yaw     2
#define roll    3

#define kerman    1
#define hubu    2

extern float Angle,Angle_pitch;
extern float acc_pitch,acc_roll,acc_yaw;
extern float gyro_pitch,gyro_roll,gyro_yaw;
typedef struct
{
    float X;
    float Y;
    float Z;
}FLOAT_XYZ;
extern FLOAT_XYZ GYRO_Real,ACC_Real;    // µ±Ç°½Ç¶È
#endif /* USER_ANGLE_H_ */
