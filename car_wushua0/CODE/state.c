/*
 * state.c
 *
 *  Created on: 2021年12月30日
 *      Author: 11609
 */
#include "state.h"
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-25 00:27:54
 ********************************************************/
int AD_Fork=0;
extern int Test;
//正常状态  入弯
void state_00()
{
  /*出库*/
  if (is_ChuKu != 0)
  {
    // if (Is_OutGarage() == 1)
    // {
      if (is_ChuKu == ChuKu_left)
      {
        state = 61;
        state_61();
        return;
      }
      else if (is_ChuKu == ChuKu_right)
      {
        state = 71;
        state_71();
        return;
      }
    // }
  }
  if(Test==8)
  {
    state=80;
    DI.ForkCnt=0;
    state_80();
    return;
  }
  if(Test==7)
  {
    state=80;
    DI.ForkCnt=1;
    state_80();
    return;
  }
  if(Test==9)
  {
    state=84;
    DI.ForkCnt=1;
    state_84();
    return;
  }
  if(Test==11)
  {
    state=83;
    DI.ForkCnt=0;
    state_83();
    return;
  }
  if(Test==10)
  {
    state=84;
    DI.ForkCnt=0;
    state_84();
    return;
  }
  // if (Is_fork3() 
  // // && bottom_pointY < 55 && DI.top_Y > 57
  //     //  && bottom_pointY<xzttt
  //     // &&((DI.Length - DI.tempLength) > 80)//元素间距离大于80
  // )
  // {
  //   state = 81;
  //   state_81();
  //   return;
  // }

  // if (AD_Fork==0&&(DI.AD_L + DI.AD_M + DI.AD_R) < 3500&&abs(DI.AD_L - DI.AD_R) < 1000 && state < 10 && DI.Length > 20)
  // {
  //   state = 83;
  //   state_83();
  //   return;
  // }

  /*圆环*/
  if (Is_circleL() == 6
      // &&((DI.Length - DI.tempLength) > 80//元素间距离大于80
      ) //左圆环
  {
    state = 11;
    state_11();
    return;
  }
//  if (Is_circleR() == 6
//      // &&((DI.Length - DI.tempLength) > 80//元素间距离大于80
//      ) //右圆环
//  {
//    state = 21;
//    state_21();
//    return;
//  }

  // /*入库*/
  // if (is_checkZebro != 0)
  // {
  //   if (Is_zebro() == 1) //斑马线
  //   {
  //     if (DI.ZebroNum != DI.Two_Cam)
  //     {
  //       state = 40;
  //       state_40();
  //     }
  //     else
  //     {
  //       if (is_checkZebro == 1 && DI.ZebroNum == DI.Two_Cam)
  //       {
  //         state = 41;
  //         state_41();
  //       }
  //       else if (is_checkZebro == 2 && DI.ZebroNum == DI.Two_Cam)
  //       {
  //         state = 51;
  //         state_51();
  //       }
  //     }
  //     return;
  //   }
  // }
  if (state != 35)
  {
    if (Is_straight() || Is_safe()) //直道
    {

      state = 1;
    }
    else
      state = 0;
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-25 00:27:48
 ********************************************************/
//直道
void state_01()
{
  state_00();
  if (state == 0) //直线入弯
  {
    DI.LengthBend = DI.Length;
    state = 2;
  }

}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-25 00:27:43
 ********************************************************/
//入弯前的直道
void state_02()
{
  state_00();
  if (state == 0)
    state = 2;
  if (DI.Length - DI.LengthBend >= 10 && state == 2)
  {
    DI.LengthBend = DI.Length;
    state = 3;
  }

}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-06 19:23:30
 ********************************************************/
//入弯时刻
void state_03()
{
  state_00();
  if (state == 0)
    state = 3;
  if (DI.Length - DI.LengthBend > 50 && state == 3)
    state = 0;

}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-05-11 12:43:58
 ********************************************************/
void state_06()
{
}
//错误状态
void state_99()
{
  return;
}
/********************************************************
函数功能：判断赛道是否足够安全
********************************************************/
uint8 Is_safe()
{
  uint8 cnt = 0;
  DI.maxCnt = 0;
  for (uint8 i = 20; i < 74; i++)
  {
    if (DI.Top_edge_Y[i] >= 56)
    {
      cnt++;
      DI.maxCnt = cnt;
    }
    else
      cnt = 0;
  }
  if (DI.maxCnt > 10)
    return 1;
  return 0;
}

/********************************************************
函数功能：判断是否为长直道
说明：斜率方差判断法
********************************************************/
uint8 Is_straight()
{
  if (L_Move.AllMaxY < 54)
    return 0;
  float k, sum = 0, kb, temp = 0, variance;
  if (DI.top_Y > 56)
  {
    k = GetSlope(DI.Ladder_MidPoint[0], 0, DI.Ladder_MidPoint[50], 50); //斜率
    kb = DI.Ladder_MidPoint[0];                                         //截距
    for (uint8 i = 0; i <= 50; i++)
    {
      temp = kb + i * k;
      sum += (temp - DI.Ladder_MidPoint[i]);
    }
    variance = sum / 50.0;
    DI.Data[26] = variance * 10;
    float S_L = Is_straight_abs(0, 50, DI.IEX[M_L]); //左边边界
    float S_R = Is_straight_abs(0, 50, DI.IEX[M_R]); //右边边界
    DI.Data[27] = (S_L + S_R) * 10;
    if (variance < 1.3 && variance > -1.3 && DI.Ladder_MidPoint[40] < 58 && DI.Ladder_MidPoint[40] > 36 && S_L + S_R < 3.0)
      return 1;
  }
  return 0;
}
/********************************************************
函数功能：判断是否有斑马线
说明：二值化图像黑白跳跃点个数
灰度图像差比和阈值个数联合判断
延距屏蔽起点的斑马线
********************************************************/
uint8 test1_zebor,test2_zebor;
uint8 Is_zebro()
{
  //  if(is_checkZebro==0)  return 0;

  if (
      // DI.Length < 1000 ||
      L_Move.AllMaxY < 50 || DI.top_Y < 50) //开始30m不判断
    return 0;

  uint8 cnt;
  int temp = 0;
  for (int i = 5; i <= 45; i += 3)
  {
    cnt = 0;
    for (uint8 j = DI.Ladder_LBorder[i]; j < DI.Ladder_RBorder[i]; j++)
    {
      if (image[63 - i][j] == 0 && image[63 - i][j + 1] == 1) //黑白跳变
      {
        cnt++;
      }
      test1_zebor=cnt;
    }
    // if (cnt > 6)
    if (cnt > 5)
    {
      DI.tempLength = DI.Length;
      return 1;
    }
    else if (cnt > 4)
    {
      for (uint8 j = DI.Ladder_LBorder[i] > 2 ? DI.Ladder_LBorder[i] : 2; j < DI.Ladder_RBorder[i]; j++)
      {
        temp = ((mt9v03x_image[(62 - i)][j] - mt9v03x_image[(62 - i)][j - 2]) * 100) / (mt9v03x_image[(62 - i)][j] + mt9v03x_image[(62 - i)][j - 2]);
        if (temp > 12 || temp < -12)
          cnt++;
      }
      test2_zebor=cnt;

      if (cnt > 25)
      {
        DI.tempLength = DI.Length;
        return 1;
      }
    }
  }
  return 0;
}
/********************************************************
函数功能：判断是否为直道
说明： 斜率绝对值累计误差判断法
********************************************************/
float Is_straight_abs(uint8 y0, uint8 y1, uint8 *line)
{
  float k, sum = 0, kb, temp = 0;
  k = GetSlope(line[y0], y0, line[y1], y1); //斜率
  kb = line[y0];                            //截距
  for (uint8 i = y0; i < y1; i++)
  {
    temp = kb + (i - y0) * k;
    sum += abs(temp - line[i]);
  }
  sum /= y1 - y0;
  return sum;
}
