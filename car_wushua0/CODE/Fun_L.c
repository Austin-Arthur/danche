/*
 * Fun_L.c
 *
 *  Created on: 2021年12月30日
 *      Author: 11609
 */
#include "Fun_L.h"
void Deal_firstline();
/************************************************************************
函数名：左右两点爬梯算法
功能：记录爬梯边界
************************************************************************/
void Ladder()
{
  for(uint8 i=1;;i++)
  {
    DI.Ladder_LBorder[i] = DI.Ladder_LBorder[i-1];
    DI.Ladder_RBorder[i] = DI.Ladder_RBorder[i-1];//边沿跟踪
    while(!image[63-i][DI.Ladder_LBorder[i]]&&DI.Ladder_LBorder[i]<92)//当前为黑 往右找到白为止
      DI.Ladder_LBorder[i]++;
    while(!image[63-i][DI.Ladder_RBorder[i]]&&DI.Ladder_RBorder[i]>1)//当前为黑 往左找到白为止
      DI.Ladder_RBorder[i]--;
    if(DI.Ladder_RBorder[i]<= DI.Ladder_LBorder[i]||i==61)//相遇或者找到底
    {
      DI.Ladder_LBorder[i] = DI.Ladder_LBorder[i-1];
      DI.Ladder_RBorder[i] = DI.Ladder_RBorder[i-1];
      L_Move.AllMaxY = i ;
      break;
    }
  }
}
/********************************************************
函数功能：处理第一行图像
说明：从上一次第一行的中值向两边找跳变点
函数功能：获取左右爬梯起点（1-92）
********************************************************/
void Deal_firstline()
{
   if(state==31||state==32||state==33||state==34||state==13||state==14||state==15||state==23||state==24||state==25)
     {
       uint8 max = 0,count=0;
       for(uint8 i=1;i<94;i++)//寻找最大连续白块最多的左右边界，返回中值
       {
         if(image[62][i]==1&&i!=93)//为白
           count++;
         else//为黑
         {
           if(count>max)
           {
             max = count;
             DI.Ladder_LBorder[0] = i-max;
             DI.Ladder_RBorder[0] = i-1;
           }
           count = 0;
         }
       }
       DI.Ladder_MidPoint[0]=(DI.Ladder_LBorder[0] + DI.Ladder_RBorder[0])/2;
       return;
     }
  DI.Ladder_LBorder[0] = DI.Ladder_RBorder[0] = (int)DI.MidLine;
  while(image[62][DI.Ladder_LBorder[0]-1]&&image[62][DI.Ladder_LBorder[0]])  
  {//向左找白变黑的点
    DI.Ladder_LBorder[0]--;
  }
  while(image[62][DI.Ladder_RBorder[0]+1]&&image[62][DI.Ladder_RBorder[0]])
  {//向右找白变黑的点
    DI.Ladder_RBorder[0]++;
  }
  DI.Ladder_MidPoint[0]=(DI.Ladder_LBorder[0] + DI.Ladder_RBorder[0])/2;
}





