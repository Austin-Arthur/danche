/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：联系淘宝客服
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            motor
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ3184284598)
 * @version         查看doc内version文件 版本说明
 * @Software        ADS v1.5.2
 * @Target core     TC264D
 * @Taobao          https://seekfree.taobao.com/
 * @date            2021-12-10
 ********************************************************************************************************************/

#include "zf_gpio.h"
#include "gpio.h"
#include "hall.h"
#include "pid.h"
#include "bldc_config.h"
#include "IfxCcu6.h"

#include "ccu6_pwm.h"
#include "zf_gtm_pwm.h"
#include "move_filter.h"
#include "SEEKFREE_FUN.h"
#include "motor.h"

int duty = 0;           //PWM初值

motor_struct motor_control;


//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机参数初始化
//  @param      void
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void motor_init(void)
{
    #if BLDC_BRAKE_ENABLE==1
        motor_control.brake_flag = 1;   //刹车使能
    #else
        motor_control.brake_flag = 0;   //刹车关闭
    #endif
    motor_control.dir = FORWARD;                    //设置默认的方向
    #if BLDC_CLOSE_LOOP_ENABLE
    motor_control.set_speed = 0;
    motor_control.max_speed = BLDC_MAX_SPEED;       //设置最大正转速度
    motor_control.min_speed = -BLDC_MAX_SPEED;      //设置最大反转速度
    #endif
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      开启A相上桥，B相下桥     其他关闭
//  @param      duty    ：  PWM占空比
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q1q4_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x0b;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      开启A相上桥，C相下桥     其他关闭
//  @param      duty    ：  PWM占空比
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q1q6_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x23;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      开启B相上桥，A相下桥     其他关闭
//  @param      duty    ：  PWM占空比
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q3q2_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x0e;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      开启B相上桥，C相下桥     其他关闭
//  @param      duty    ：  PWM占空比
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q3q6_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x2c;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      开启C相上桥，A相下桥     其他关闭
//  @param      duty    ：  PWM占空比
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q5q2_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x32;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      开启C相上桥，B相下桥     其他关闭
//  @param      duty    ：  PWM占空比
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_q5q4_open(uint16 duty)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x38;

    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, duty);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      关闭所有上桥，开启所有下桥，使电机在线圈的自感电动势的作用下自己完成刹车
//  @param      void
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void mos_close(void)
{
    ccu6SFR->MODCTR.B.T12MODEN = 0x2A;
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_0, 0);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_1, 0);
    IfxCcu6_setT12CompareValue(ccu6SFR, IfxCcu6_T12Channel_2, 0);
    IfxCcu6_enableShadowTransfer(ccu6SFR, TRUE, FALSE);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机换相控制
//  @param      void
//  @return     void
//  @since      根据计算出来的目标相位进行相位输出
//-------------------------------------------------------------------------------------------------------------------
void motor_commutation(int8 except_hall)
{
    //使能开关关闭时 无论如何都关闭输出
    if(!gpio_get(EN_PIN))
    {
        duty=0;
    }
    #if BLDC_CLOSE_LOOP_ENABLE
        if(motor_control.set_speed){
    #else
        if(duty){
    #endif
            switch(except_hall)
               {
                   case 1:     mos_q1q6_open(duty);    break;//a+  c-
                   case 2:     mos_q1q4_open(duty);    break;//a+ b-
                   case 3:     mos_q5q4_open(duty);    break;//c+ b-
                   case 4:     mos_q5q2_open(duty);    break;//c+ a-
                   case 5:     mos_q3q2_open(duty);    break;//b+ a-
                   case 6:     mos_q3q6_open(duty);    break;//b+ c-
                   default:    mos_close();            break;
               }
        }
        else {
            mos_close();
        }



}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      电机转动方向输出
//  @param      void
//  @return     void
//  @since
//-------------------------------------------------------------------------------------------------------------------
void motor_dir_out(void)
{
    if((hall_value_last < hall_value_now && (hall_value_last!=1 && hall_value_now!=6)) || (hall_value_last==6 &&  hall_value_now==1))
    {
        motor_control.nowdir = FORWARD;
    }
    if((hall_value_last > hall_value_now && (hall_value_last!=6 &&  hall_value_now!=1)) || (hall_value_last==1 &&  hall_value_now==6))
    {
        motor_control.nowdir = REVERSE;
    }
}
