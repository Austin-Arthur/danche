/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            headfile
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ3184284598)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        ADS v1.2.2
 * @Target core     TC264D
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-3-23
 ********************************************************************************************************************/
 
#ifndef _headfile_h
#define _headfile_h




#include "SEEKFREE_PRINTF.h"

#include "zf_assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
//�ٷ�ͷ�ļ�
#include "ifxAsclin_reg.h"
#include "SysSe/Bsp/Bsp.h"
#include "IfxCcu6_Timer.h"
#include "IfxScuEru.h"

//------��ɿƼ���Ƭ����������ͷ�ļ�
#include "zf_gpio.h"
#include "zf_gtm_pwm.h"
#include "zf_uart.h"
#include "zf_ccu6_pit.h"
#include "zf_stm_systick.h"
#include "zf_spi.h"
#include "zf_eru.h"
#include "zf_eru_dma.h"
#include "zf_vadc.h"
#include "zf_gpt12.h"
#include "zf_eeprom.h"

//------��ɿƼ���Ʒ����ͷ�ļ�
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_FUN.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_IPS114_SPI.h"
#include "SEEKFREE_OLED.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_MPU6050.h"
#include "SEEKFREE_MMA8451.h"
#include "SEEKFREE_L3G4200D.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
#include "SEEKFREE_7725.h"
#include "SEEKFREE_RDA5807.h"
#include "SEEKFREE_7725_UART.h"


//------�Լ�������ļ�

#include "angle.h"
#include "control.h"
#include "initial.h"
#include "isr.h"
#include "isr_config.h"
#include "LCD_Show.h"
#include "State.h"
#include "filter.h"
#include "state_ring.h"
#include "state_cheku.h"
#include "state_fork.h"
#include "state_ramp.h"
#include "MFuzzy.h"


#include "Deal.h"
#include "Fun_8.h"
#include "Fun_L.h"
#include "GetMid.h"
#include "state.h"
#include "valuepack.h"
#include "Variables.h"
#include "MyMenu.h"
#include "Tools.h"
#include "ostu.h"


#include "gpio.h"
#include "adc.h"
#include "hall.h"
#include "move_filter.h"
#include "motor.h"
#include "pid.h"
#include "ccu6_pwm.h"

#include "fuse.h"
#include "PID.h"

#include "fuzzy.h"
//-------------------

#define M_L  0
#define M_R  1



#endif

