/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
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

    //��ʼ��LED����
    led_init();


    //��ʼ��adcͨ����adc���ڲɼ���Դ��ѹ��ĸ�ߵ������������
    //adc_collection_init();

    //������ʼ��
    hall_init();

    //����ƽ���˲���ʼ��
    move_filter_init(&speed_filter);


    //�����ʼ��
    motor_init();

    //PID������ʼ��
    closed_loop_pi_init();

    //��ʼ����ʱ��,�����������PWM
    ccu6_pwm_init();

    //��ʼ����ʱ��,���ڼ���ռ�ձ�
    //pit_interrupt_ms(CCU6_0, PIT_CH0, 5);


    //�û��ڴ˴����ø��ֳ�ʼ��������

    enableInterrupts();
    while (TRUE)
    {
		//�û��ڴ˴���д�������
        //led_output();
        CI.cnst  = OTSU(62,94);//ԽСԽ�� ;
//        CI.cnst  =160;//ԽСԽ�� ;
        //ShowPathOnLine();





    }
}





#pragma section all restore
