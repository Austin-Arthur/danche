/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            main
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ3184284598)
 * @version         查看doc内version文件 版本说明
 * @Software        ADS v1.2.2
 * @Target core     TC264D
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#pragma section all "cpu0_dsram"
/*
TxPack txpack;
RxPack rxpack;
STATE State = INITING;
*/
int flag = 0;
int xxx = 0;
extern float acc_pitch,acc_roll,acc_yaw;
extern float gyro_pitch,gyro_roll,gyro_yaw;
extern int motor_pwm;
extern int test1,test2;
extern float angle_klm, angle_dot_klm;
extern int test_x[10];
extern int MotorDutyB;
extern short  Motor_Bias, Motor_Last_Bias, Motor_Integration; // 电机所用参数

extern int time_measure;

extern float pwm_v,pwm_a_v,pwm_a ;
extern float gyro_lpf;

extern int16 motor_PWM;;
extern float gyro_pitch,gyro_roll,gyro_yaw;
extern float Angle_Zero;      //角度零点

/************************************************************************
*功能：主函数
*************************************************************************/
/************************************************************************
// shiyan
/// @brief 
/// @param  
/// @return 
*************************************************************************/
int core0_main(void)
{

    State_Init();
    DI.MidLine = 47;
    DI.LengthCheku=0;
    while (TRUE)
    {
        TaskProcess();


        
         //beep_on();
        //CI.cnst  = OTSU(62,94);//越小越亮 ;

        //ShowPathOnLine();

        //printf("%f,%f,%f,%f\n",(float)speed_filter.data_average,(float)gyro_roll*100,(float)(gyro_lpf-3)*100,(float)Angle*test_y[3]*test_y[0] );//Angle Motor_Bias
        //printf("%f,%f,%f,%f\n",(float)gyro_roll,(float)pwm_a_v,(float)pwm_a,(float)Angle*100 );//Angle Motor_Bias
       // printf("%f,%f,%f,%f\n",(float)PWM_X,(float)test1,(float)test2,(float)(Angle-0.5)*1000);// p   d
/*
        beep_off();
        ShowPathOnLine();
        beep_on();
*/
//        uart_putchar(UART_1,'A');
//        oled_printf_int32(0,4,speed,5);

        //ShowPath();
        //Show8Path();
 //       LCD_MT9V032(image);




//        Get_ADC_Value();
/*
        if(readValuePack(&rxpack))
            {
               test_y[0] = rxpack.integers[0];
               test_y[1] = rxpack.integers[1];
               test_y[2] = rxpack.integers[2];
               test_y[3] = rxpack.integers[3];
               test_y[4] = rxpack.integers[4];
               test_y[5] = rxpack.integers[5];
               test_y[6] = rxpack.integers[6];

            }
            */


    }
}

#pragma section all restore
