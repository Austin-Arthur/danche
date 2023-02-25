/*
 * Tools.h
 *
 *  Created on: 2022��1��13��
 *      Author: 11609
 */

#ifndef CODE_TOOLS_H_
#define CODE_TOOLS_H_
/*---------------------------------------------------------------------
                          ����ͼ�����ߺ���

��ƽ    ̨��RT1064
����    д�����Ļ�ϲ
����ϵ��ʽ��QQ��320388825 ΢�ţ�LHD0617_
�������¡�2021.11.30
������ƽ̨��MDK 5.28.0
����    �ܡ�����ͼ�����ߺ���
��ע�����������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
---------------------------------------------------------------------*/
#ifndef _ZW_TOOLS_H_
#define _ZW_TOOLS_H_

/*���������������������п�����Ҫ�������UART����ͷ�ļ��ɸ����Լ��Ŀ����и���*/
#include "zf_uart.h"


/*ͼ��ߴ��С        �мǱ�������λ����д�ĳߴ��Ӧ�����޷�ʹ��*/
/*ͼ��ߴ��С        ���ó��� ������<=10000*/
#define     ZW_ImgSize_H        64
#define     ZW_ImgSize_W        94

/*�����ݶ���*/
#define     ZW_NULL                 0

/*UART���ݷ��궨��    ��Ҫ�û�����Ϊ�Լ���UART���ͺ���*/
#define     ZW_Putchar(ZW_data)     uart_putchar(UART_2,ZW_data)

/*��������*/
typedef         unsigned char       ZW_uint8;
typedef         unsigned short      ZW_uint16;

/*��������*/
void ZW_Send_Image(ZW_uint8* ZW_Image);
void ZW_Send_Boundary(ZW_uint8* ZW_Left_Boundary, ZW_uint8* ZW_Right_Boundary);



#endif







#endif /* CODE_TOOLS_H_ */
