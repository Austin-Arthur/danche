/*
 * state_ramp.c
 *
 *  Created on: 2022年3月8日
 *      Author: 11609
 */
#include "state_ramp.h"
uint8 rampN = 40; //坡道识别主要改此参数

/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-25 01:09:41
 ********************************************************/
//识别坡道
void state_31()
{

  DI.ramp_flag = 0;
  if (DI.Length - DI.tempLength > 45) //延距离45cm进入上坡状态
  {
    DI.tempLength = DI.Length;
    state = 32;
    return;
  }
  if (L_Move.AllMaxY < 56 && Basic_Least_Square(DI.IEX[M_L] + 40, 15) + Basic_Least_Square(DI.IEX[M_R] + 40, 15) > 500)
  { //可视距离变短，远端线性度降低
    DI.tempLength = DI.Length;
    state = 32;
    return;
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-07 09:32:43
 ********************************************************/
//上坡中
void state_32()
{
  if (DI.Length - DI.tempLength > 70) //延距离70cm进入坡顶状态
  {
    DI.tempLength = DI.Length;
    state = 33;
    return;
  }
  if (DI.top_Y < 20)
    return;
  if (DI.Length - DI.tempLength > 25 && DI.ramp_flag == 0)
  {
    float L_line_err = Basic_Least_Square(DI.IEX[M_L], 15);
    float R_line_err = Basic_Least_Square(DI.IEX[M_R], 15);
    if (L_line_err + R_line_err < 15 && DI.IEX[M_R][0] - DI.IEX[M_L][0] < 70 && DI.IEX[M_L][0] > 3 && DI.IEX[M_R][0] < 90)
    { //近处线性度高，近处赛道变窄
      DI.tempLength = DI.Length;
      DI.ramp_flag = 1;
      return;
    }
  }
  if (DI.ramp_flag == 1 && DI.Length - DI.tempLength > 25) //延一个车长的距离
  {
    DI.tempLength = DI.Length;
    DI.rampCnt = 5;
    state = 33;
    return;
  }
}

/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-25 01:09:50
 ********************************************************/
//到达坡顶
void state_33()
{
  if (DI.Length - DI.tempLength > 60)
  {
    DI.tempLength = DI.Length;
    state = 34;
    state_34();
    return;
  }
  if (L_Move.AllMaxY + DI.top_Y > 110 && Is_ramp(1) == 1)
  {
    DI.rampCnt++;
    state = 34;
    state_34();
    return;
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-25 01:09:56
 ********************************************************/
//下坡中  延距离40cm
void state_34()
{

  if (Is_ramp(1) == 1)
  {
    DI.rampCnt++;
    if (DI.rampCnt < 5)
      DI.rampCnt = 5;
    if (DI.rampCnt > 10)
      DI.rampCnt = 10;
  }
  else
    DI.rampCnt--;

  if (DI.rampCnt < 0 && DI.Length - DI.tempLength > 20 && DI.IEX[M_R][0] - DI.IEX[M_L][0] < 81)
  {
//    state = 84;
//    state_84();
    if( GetItemValue(Start_Order, ramp_FK_Order)==1)
    {
      state = 84;
      beep_off();
      state_84();
    }
    else
    {
      state = 0;
      beep_off();
      state_00();
    }
    DI.tempLength = DI.LengthRamp = DI.Length;
    return;
  }
  if (DI.Length - DI.tempLength > 40 || DI.MidLine > 67 || DI.MidLine < 27 || DI.Data[35] > 4.5)
  {
//    state = 84;
//    state_84();
    if( GetItemValue(Start_Order, ramp_FK_Order)==1)
    {
      state = 84;
      beep_off();
      state_84();
    }
    else
    {
      state = 0;
      beep_off();
      state_00();
    }

    beep_off();
    DI.tempLength = DI.LengthRamp = DI.Length;
    return;
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-07 09:33:33
 ********************************************************/
boolean Is_ramp_angle()
{
  if (Angle_pitch < -5 || Angle_pitch > 5)
  {
    return 1;
  }
  return 0;
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-25 01:10:03
 ********************************************************/
void state_35()
{
  if (abs(Servo_PWM) < 60 &&(DI.Length-DI.LengthRamp)>50)
  {
    state = 84;
    state_84();
    return;
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-25 01:10:09
 ********************************************************/
//坡道判断
uint8 Is_ramp(uint8 type)
{
  // if(DI.Length<200)     return 0;//开始两米不判断
  if (DI.Length - DI.LengthRamp < 250 && type == 0 && DI.LengthRamp != 0)
    return 0; //
  if (
      DI.tempLength == 0 || (DI.Length - DI.tempLength > 60) || type == 1) //特殊元素延距离60cm
  {
    uint8 flag = 0;
    for (uint8 i = 10; i < L_Move.AllMaxY - 3; i++) //内边界找拐点
    {
      if (DI.IEX[M_R][i - 1] - DI.IEX[M_R][i] > 7) //有拐点
      {                                            //找到拐点
        flag = 1;
        break;
      }
      if (DI.IEX[M_L][i] - DI.IEX[M_L][i - 1] > 7) //有拐点
      {                                            //找到拐点
        flag = 1;
        break;
      }
    }
    if (flag)
      return 0; //存在拐点不是坡道
    /**/
    if (L_Move.AllMaxY < 55 || DI.MidLine > 67 || DI.MidLine < 27)
      return 0; //可视距离要长，中线要正
    /*十一线竖直扫描*/
    if (DI.MaxY[0] > 55)
      DI.Data[33] = 0; //左边边界
    else
      DI.Data[33] = Is_straight_abs(DI.MaxY[0], 56, DI.IEX[M_L]); //左边边界
    if (DI.MaxY[10] > 55)
      DI.Data[34] = 0; //右边边界
    else
      DI.Data[34] = Is_straight_abs(DI.MaxY[10], 56, DI.IEX[M_R]); //右边边界
    for (uint8 i = 20; i < 55; i += 2)
    { //两边向内
      if (DI.IEX[M_L][i] < DI.IEX[M_L][i - 2])
        return 0;
      if (DI.IEX[M_R][i] > DI.IEX[M_R][i - 2])
        return 0;
    }

    DI.Data[37] = (Get_VerticalHeight(DI.MidLine, 0) + Get_VerticalHeight(DI.MidLine - 13, 0) + Get_VerticalHeight(DI.MidLine + 13, 0)) / 3;
    /**/
    if (DI.MaxY[10] > 40)
    {
      if (DI.MaxY[9] < 48 || DI.MaxY[8] < 48 || DI.MaxY[7] < 48 || DI.MaxY[6] < 48)
        return 0;
    }
    /**/
    if (DI.MaxY[0] > 40)
    {
      if (DI.MaxY[1] < 48 || DI.MaxY[2] < 48 || DI.MaxY[3] < 48 || DI.MaxY[4] < 48)
        return 0;
    }

    if ((DI.Data[33] + DI.Data[34] + DI.Data[35]) < 5 && (DI.Ladder_RBorder[51] - DI.Ladder_LBorder[51]) > rampN && DI.Data[37] >= 15) // 32
    {
      DI.tempLength = DI.Length;
      return 1;
    }
  }
  return 0;
}
