/*
 * ostu.c
 *
 *  Created on: 2022年6月19日
 *      Author: 11609
 */


#include"ostu.h"

uint8 OTSU(uint16 x,uint16 y)
//大津法计算全局最佳阈值
{
  CI.Bright_cnt = 0;
  int pixelCnt[256];//像素个数
  float pixel_P[256];  //归一化直方图
  float  P1[256];      //累计概率
  float Mk[256];      //累计灰度均值
  float g,maxG = 0;
  float MG = 0;

  int i,j,begin_i,end_i;
  uint8 threshold;
  uint8 num;

  /* 清空直方图 */
  for(i=0;i<256;i++)
  {
    pixelCnt[i]=0;//每个灰度值下的像素点个数
    pixel_P[i] = 0;
  }
  /* 更新直方图 */
  for(i=0;i<x;i++)//遍历整个图片
  {
     for(j=0;j<y;j++)
     {
         num = mt9v03x_image[i][j]; //取出灰度值
         pixelCnt[num]++;  //该灰度值像素个数加1
     }

  }
  // 计算归一化直方图
  for(i=0;i<256;i++)
  {
    pixel_P[i] = ((float)pixelCnt[i])/(x*y);
  }
  float temp_sumP = 0;
  float temp_sumMk = 0;
  //计算累计概率
  for(i=0;i<256;i++)
  {
      temp_sumMk += i*pixel_P[i];
      temp_sumP +=pixel_P[i];
      P1[i] = temp_sumP;
      Mk[i] = temp_sumMk;
  }
  MG = Mk[255];
  //计算类间方差
  float Sigema_g = 0;
  float Sigema_g_last = 0;

  //设置起始，终止范围，滤除干扰，降低复杂度
  begin_i = 120;
  end_i = 200;
  for(i=begin_i;i<end_i;i++)
  {
      Sigema_g = (MG*P1[i]-Mk[i])*(MG*P1[i]-Mk[i]);
      Sigema_g = Sigema_g/(P1[i]*(1-P1[i]));
      if(Sigema_g>maxG)  //计算最大类间误差
      {
          maxG = Sigema_g;
          threshold = i;
      }

      if(Sigema_g<Sigema_g_last)//找到尖峰，提前退出
      {
          threshold = i;
          break;
      }

      Sigema_g_last = Sigema_g;
  }
  return threshold;
}








