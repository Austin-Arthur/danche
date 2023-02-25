/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/

#include "headfile.h"

#pragma section all "cpu0_dsram"


void core1_main(void)
{
	disableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());

    led_init();

    //初始化LED引脚
    led_init();


    //初始化adc通道，adc用于采集电源电压、母线电流、相电流的
    //adc_collection_init();

    //霍尔初始化
    hall_init();

    //滑动平均滤波初始化
    move_filter_init(&speed_filter);


    //电机初始化
    motor_init();

    //PID参数初始化
    closed_loop_pi_init();

    //初始化定时器,用于输出互补PWM
    ccu6_pwm_init();

    //初始化定时器,用于计算占空比
    //pit_interrupt_ms(CCU6_0, PIT_CH0, 5);


    //用户在此处调用各种初始化函数等

    enableInterrupts();
    while (TRUE)
    {
		//用户在此处编写任务代码
        //led_output();
        CI.cnst  = OTSU(62,94);//越小越亮 ;
//        CI.cnst  =160;//越小越亮 ;
        //ShowPathOnLine();





    }
}





#pragma section all restore
