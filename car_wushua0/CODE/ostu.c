/*
 * ostu.c
 *
 *  Created on: 2022��6��19��
 *      Author: 11609
 */


#include"ostu.h"

uint8 OTSU(uint16 x,uint16 y)
//��򷨼���ȫ�������ֵ
{
  CI.Bright_cnt = 0;
  int pixelCnt[256];//���ظ���
  float pixel_P[256];  //��һ��ֱ��ͼ
  float  P1[256];      //�ۼƸ���
  float Mk[256];      //�ۼƻҶȾ�ֵ
  float g,maxG = 0;
  float MG = 0;

  int i,j,begin_i,end_i;
  uint8 threshold;
  uint8 num;

  /* ���ֱ��ͼ */
  for(i=0;i<256;i++)
  {
    pixelCnt[i]=0;//ÿ���Ҷ�ֵ�µ����ص����
    pixel_P[i] = 0;
  }
  /* ����ֱ��ͼ */
  for(i=0;i<x;i++)//��������ͼƬ
  {
     for(j=0;j<y;j++)
     {
         num = mt9v03x_image[i][j]; //ȡ���Ҷ�ֵ
         pixelCnt[num]++;  //�ûҶ�ֵ���ظ�����1
     }

  }
  // �����һ��ֱ��ͼ
  for(i=0;i<256;i++)
  {
    pixel_P[i] = ((float)pixelCnt[i])/(x*y);
  }
  float temp_sumP = 0;
  float temp_sumMk = 0;
  //�����ۼƸ���
  for(i=0;i<256;i++)
  {
      temp_sumMk += i*pixel_P[i];
      temp_sumP +=pixel_P[i];
      P1[i] = temp_sumP;
      Mk[i] = temp_sumMk;
  }
  MG = Mk[255];
  //������䷽��
  float Sigema_g = 0;
  float Sigema_g_last = 0;

  //������ʼ����ֹ��Χ���˳����ţ����͸��Ӷ�
  begin_i = 120;
  end_i = 200;
  for(i=begin_i;i<end_i;i++)
  {
      Sigema_g = (MG*P1[i]-Mk[i])*(MG*P1[i]-Mk[i]);
      Sigema_g = Sigema_g/(P1[i]*(1-P1[i]));
      if(Sigema_g>maxG)  //�������������
      {
          maxG = Sigema_g;
          threshold = i;
      }

      if(Sigema_g<Sigema_g_last)//�ҵ���壬��ǰ�˳�
      {
          threshold = i;
          break;
      }

      Sigema_g_last = Sigema_g;
  }
  return threshold;
}








