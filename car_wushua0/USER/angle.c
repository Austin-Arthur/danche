#include"angle.h"
#include "SEEKFREE_ICM20602.h"



float acc_pitch,acc_roll,acc_yaw;
float gyro_pitch,Angle_pitch,gyro_yaw;


float Angle = 0;
float Angle_yaw = 0;
float Angle_pitch = 0;

float gyro_roll = 0;
float gyro_y_offest = 0;
float gyro_x_offest = 16;
float gyro_z_offest = 0;
float acc_x_offest = 0;
float acc_y_offest = 0;
float acc_z_offest = 0;

float K1 = 0.002;//0.012

#define ACC_FILTER_NUM 1        // 加速度计滤波深度  3
#define GYRO_FILTER_NUM 1       // 陀螺仪滤波深度  2

int32 ACC_X_BUF[ACC_FILTER_NUM]={0}, ACC_Y_BUF[ACC_FILTER_NUM]={0}, ACC_Z_BUF[ACC_FILTER_NUM]={0};  //滤波缓存数组
int32 GYRO_X_BUF[GYRO_FILTER_NUM]={0}, GYRO_Y_BUF[GYRO_FILTER_NUM]={0}, GYRO_Z_BUF[GYRO_FILTER_NUM]={0};

FLOAT_XYZ GYRO_Real,ACC_Real;    // 当前角度
int abs(int x)
{
    if(x<0)
        x = -x;
    return x;
}

/*
功能：互补滤波
返回值：void
形参：Accel 输入加速度；Gyro 输入角速度
k越小 加速度占比就越小
*/
void Complementary_Filter(float Accel,float Gyro,int x)
{
  if(x==3)
    Angle = (float)(K1 * Accel+ (1-K1) * (Angle + Gyro * 0.005));//0.005秒;为周期时间，对应5ms
  if(x==2)
    Angle_yaw = (float)(K1 * Accel+ (1-K1) * (Angle_yaw + Gyro * 0.005));//0.005秒;为周期时间，对应5ms
  if(x==1)
    Angle_pitch = (float)(K1 * Accel+ (1-K1) * (Angle_pitch + Gyro * 0.005));//0.005秒;为周期时间，对应5ms
}

void Data_Filter(void)  // 数据滤波
{
    uint8 i;
    int32 temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0, temp5 = 0, temp6 = 0;

    ACC_X_BUF[0] = icm_acc_x-acc_x_offest;   // 更新滑动窗口数组
    ACC_Z_BUF[0] = icm_acc_z-acc_z_offest;
    ACC_Y_BUF[0] = icm_acc_y-acc_y_offest;
    GYRO_Y_BUF[0] = icm_gyro_y-gyro_y_offest;
    GYRO_Z_BUF[0] = icm_gyro_z-gyro_z_offest;
    GYRO_X_BUF[0] = icm_gyro_x-gyro_x_offest;

    for(i=0;i<ACC_FILTER_NUM;i++)
    {
        temp1 += ACC_X_BUF[i];
    }
    for(i=0;i<ACC_FILTER_NUM;i++)
    {
        temp3 += ACC_Z_BUF[i];
    }
    for(i=0;i<ACC_FILTER_NUM;i++)
    {
        temp4 += ACC_Y_BUF[i];
    }
    for(i=0;i<GYRO_FILTER_NUM;i++)
    {
        temp5 += GYRO_Y_BUF[i];
    }
    for(i=0;i<GYRO_FILTER_NUM;i++)
    {
        temp2 += GYRO_Z_BUF[i];
    }
    for(i=0;i<GYRO_FILTER_NUM;i++)
    {
        temp6 += GYRO_X_BUF[i];
    }

    GYRO_Real.X = temp6 / GYRO_FILTER_NUM*1.0;
    GYRO_Real.Y = temp5 / GYRO_FILTER_NUM*1.0;
    GYRO_Real.Z = temp2 / GYRO_FILTER_NUM*1.0;

    ACC_Real.X = temp1 / ACC_FILTER_NUM*1.0;
    ACC_Real.Z = temp3 / ACC_FILTER_NUM*1.0;
    ACC_Real.Y = temp4 / ACC_FILTER_NUM*1.0;
    for(i = 0; i < ACC_FILTER_NUM - 1; i++)
    {
        ACC_X_BUF[ACC_FILTER_NUM-1-i] = ACC_X_BUF[ACC_FILTER_NUM-2-i];
    }
    for(i = 0; i < ACC_FILTER_NUM - 1; i++)
    {
        ACC_Z_BUF[ACC_FILTER_NUM-1-i] = ACC_Z_BUF[ACC_FILTER_NUM-2-i];
    }
    for(i = 0; i < ACC_FILTER_NUM - 1; i++)
    {
        ACC_Y_BUF[ACC_FILTER_NUM-1-i] = ACC_Y_BUF[ACC_FILTER_NUM-2-i];
    }
    for(i = 0; i < GYRO_FILTER_NUM - 1; i++)
    {
        GYRO_Y_BUF[GYRO_FILTER_NUM-1-i] = GYRO_Y_BUF[GYRO_FILTER_NUM-2-i];
    }
    for(i = 0; i < GYRO_FILTER_NUM - 1; i++)
    {
        GYRO_Z_BUF[GYRO_FILTER_NUM-1-i] = GYRO_Z_BUF[GYRO_FILTER_NUM-2-i];
    }
}
/**
 * 函数：GetAngle
 * 说明：mpu6050数据融合
 * 参数：无
 * 输出：无
 * acc    加速度计
 * gyro   陀螺仪
 * roll   以x轴为旋转轴
 * yaw    以z轴为旋转轴
 * pitch  以y轴为旋转轴
 */
void GetAngle(int x){

    get_icm20602_accdata();//加速度
    get_icm20602_gyro();//陀螺仪
    Data_Filter();

    if(x==1)
    {
        acc_pitch = (float)(atan2(( ACC_Real.X),( ACC_Real.Z))*57.297);//比例值，无须矫正
        gyro_pitch = (( GYRO_Real.Y)/16.4);//那一时刻的角速度作为增加量，够用
        //采用互补滤波 角度融合

          Complementary_Filter(-acc_pitch,gyro_pitch,x);

    }
    if(x==3)
    {
        acc_roll = (float)(atan2((ACC_Real.Y),(ACC_Real.Z))*57.297);//比例值，无须矫正
        gyro_roll = ((GYRO_Real.X)/16.4);//那一时刻的角速度作为增加量，够用
        //采用互补滤波 角度融合

          Complementary_Filter(acc_roll,gyro_roll,x);

          //Kalman_Filter(acc_roll,acc_roll);
    }
    if(x==2)
    {
        acc_yaw = (float)(atan2((ACC_Real.X),(ACC_Real.Y))*57.297);//比例值，无须矫正
        gyro_yaw = ((GYRO_Real.Z)/16.4);//那一时刻的角速度作为增加量，够用
        //采用互补滤波 角度融合

          Complementary_Filter(acc_yaw,gyro_yaw,x);

    }



}
