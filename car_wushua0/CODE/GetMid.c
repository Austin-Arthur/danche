/*
 * GetMid.c
 *
 *  Created on: 2021年12月30日
 *      Author: 11609
 */
#include "GetMid.h"
// float WeightBase[7] = {0.7,1.0,1.2,1.5,1.2,0.7,0.3};//前面的代表远处
float WeightBase[7] = {0.2, 0.5, 0.7, 1.0, 1.2, 1.5, 1.8}; //前面的代表远处
float WeightAdd[7] = {1, 1, 1, 1, 1, 1, 1};
float VCK_W = 0.0035;
float HD_ratio[6];
float HD_length[4];
int state_dx = 0;

// uint8 ImageWide[62]=
//{
//   75,75,74,74,73,72,70,69,69,68,
//   67,65,64,63,62,61,59,59,59,57,
//   55,55,54,52,51,50,49,49,47,45,
//   44,43,42,40,40,38,36,36,35,34,
//   32,32,31,28,28,27,26,25,24,23,
//   22,20,20,18,17,16,16,16,16,16,
//   16,16
// };
uint8 ImageWide[62] =
    {
        75, 75, 74, 74, 73, 72, 70, 69, 69, 68, //
        67, 65, 64, 63, 62, 61, 59, 59, 59, 57, //
        55, 55, 54, 52, 51, 50, 49, 49, 47, 45, //
        44, 43, 42, 40, 40, 38, 36, 36, 35, 34, //
        32, 32, 31, 28, 28, 27, 26, 25, 24, 23, //
        22, 20, 20, 18, 17, 16, 16, 16, 16, 16, //
        16, 16};

uint8 RampWide[62] =
    {
        75, 75, 74, 74, 73, 72, 70, 69, 69, 68, //
        57,                                     //
        65, 64, 63, 62, 61, 59, 59, 59, 57,     //
        55, 55, 54, 52, 51, 50, 49, 49, 47, 45, //
        44, 43, 42, 40, 40, 38, 36, 36, 35, 34, //
        32, 32, 31, 28, 28, 27, 26, 25, 24, 23, //
        22, 20, 20, 18, 17, 16, 16, 16, 16, 16, //
        16, 16};
//最远可视2m
//最近可视10cm
//可视宽度
/*
uint8 ImageWide[62] =
    {
        94, 94, 94, 93, 93, 93, 92, 91, 91, 89, //
        88, 86, 85, 84, 82, 81, 79, 78, 76, 75, //
        73, 71, 69, 68, 67, 66, 65, 63, 61, 60, //
        59, 58, 57, 56, 54, 53, 52, 50, 46, 45, //
        43, 41, 40, 39, 37, 35, 33, 32, 31, 29, //
        27, 26, 25, 23, 22, 21, 19, 18, 17, 16, //
        15, 15};                                //
*/
/********************************************************
 *@函数名: 获取图像偏差总流程
 *@说明: none
 *@函数功能: none
 *@Date: 2022-05-12 12:12:35
 ********************************************************/
//获取图像偏差总流程
float getMid()
{
  //  if((state>=31&&state<=35)||(state>=11&&state<=30) || (state>=80&&state<90))//坡道|环内
  // if ((state >= 31 && state <= 35) || (state >= 80 && state < 90)) //坡道||三叉
  if ((state >= 31 && state <= 34) || state == 35 || state == 61 //
  || ((state == 84 || state == 85) && (DI.ForkCnt == fork_left)) //
  || (( state == 81 || state == 82 || state == 83) && (DI.ForkCnt == fork_left))//
      // || ((state == 81 || state == 82 || state == 83)&& (DI.ForkCnt == fork_left))
      // || ((DI.ForkCnt == fork_left) && state == 83)
      // ||state==85
      ) //坡道

  {
    return Midline_in_Ramp();
  }
  else
  {
    return Midline_in_Normal(); //坡道情况会使，丢线补偿紊乱，在解决坡道识别后打开
  }

  //获取坡道中线
  // Midline_in_Ramp();
}
/********************************************************
 *@函数名: 获取坡道中线
 *@说明: none
 *@函数功能: none
 *@Date: 2022-05-12 12:14:27
 ********************************************************/
//获取坡道中线
float Midline_in_Ramp()
{
  if (
      // state == 31 ||
      //    state == 85 ||
      state == 52 || state == 16) //坡道
  {
    Err_Select_Line();     //选择7条等距离的横线
    Err_DetermineWeight(); //获取每条线的权重
    float sum = 0, midLine = 0, sum_W = 0;
    for (uint8 i = 4; i < 7; i++) // 4   7
    {
      float true_Center;
      uint8 Needed_Y = DI.Line_Selected_Y[i];
      uint8 L_border = DI.Ladder_LBorder[Needed_Y]; //获取左右扫线边界
      uint8 R_border = DI.Ladder_RBorder[Needed_Y];
      true_Center = 1.0 * (L_border + R_border) / 2;

      /*标记黑点*/
      for (int i = DI.IEX[M_L][Needed_Y] + 1; i < DI.IEX[M_R][Needed_Y] - 1; i += 2)
      {
        image[62 - Needed_Y][i] = 0;
      }
      for (int i = Needed_Y; i < Needed_Y + 3; i++)
      {
        image[62 - i][(int)true_Center] = 0;
      }
      sum += true_Center * WeightAdd[i];
      sum_W += WeightAdd[i];
    }
    midLine = (sum / sum_W - 47) * 1.4 + 47;

    /*显示中点*/
    for (int i = 0; i < 5; i++)
    {
      image[62 - i][(int)midLine] = 0;
    }
    return midLine;
  }
  else if (
      ((state == 81 || state == 82 || state == 83
      ) && ((DI.ForkCnt == fork_left))) ||state == 61)
  {
    Err_Select_Line();     //选择7条等距离的横线
    Err_DetermineWeight(); //获取每条线的权重
    float sum = 0, midLine = 0, sum_W = 0;
    uint8 Line_Selected_Y[] = {10, 15, 21, 28, 36, 45, 55};
    for (uint8 i = 2; i < 5; i++) // 4   7
    {
      float true_Center;
      uint8 Needed_Y = Line_Selected_Y[i];
      uint8 L_border = DI.Ladder_LBorder[Needed_Y]; //获取左右扫线边界
      uint8 R_border = DI.Ladder_RBorder[Needed_Y];
      true_Center = 1.0 * (L_border + R_border) / 2;
      /*标记黑点*/
      for (int j = DI.IEX[M_L][Needed_Y] + 1; j < DI.IEX[M_R][Needed_Y] - 1; j += 2)
      {
        image[62 - Needed_Y][j] = 0;
      }
      for (int k = Needed_Y; k < Needed_Y + 3; k++)
      {
        image[62 - k][(int)true_Center] = 0;
      }
      if(((DI.ForkCnt == fork_left)&&state==83))
      {
        if (DI.IEX[M_R][Needed_Y] > 80 && DI.IEX[M_L][Needed_Y] > 14 && DI.Ladder_LBorder[Needed_Y] > 14) //右转丢线
        {
          true_Center = 1.0 * (L_border + ImageWide[Needed_Y] / 2);
        }
        else if (DI.IEX[M_L][Needed_Y] < 14 && DI.IEX[M_R][Needed_Y] < 80 && DI.Ladder_RBorder[Needed_Y] < 83) //左转丢线根据赛道宽度来补偿
        {
          true_Center = 1.0 * (R_border - ImageWide[Needed_Y] / 2);
        }
      }
      for (int k = Needed_Y; k < Needed_Y + 5; k++)
      {
        image[62 - k][(int)true_Center] = 0;
      }

      sum += true_Center * WeightAdd[i];
      sum_W += WeightAdd[i];
    }
    midLine = (sum / sum_W - 47) * 1.4 + 47;

    /*显示中点*/
    for (int i = 0; i < 5; i++)
    {
      image[62 - i][(int)midLine] = 0;
    }
    return midLine;
  }
  else if (state == 80 || state == 81 || state == 82 || state == 83
           //  || ((DI.ForkCnt == fork_right) && state == 85)
           || state == 87 || state == 31) //坡道
  {
    Err_Select_Line();     //选择7条等距离的横线
    Err_DetermineWeight(); //获取每条线的权重
    float sum = 0, midLine = 0, sum_W = 0;
    for (uint8 i = 2; i < 5; i++) // 4   7
    {
      float true_Center;
      uint8 Needed_Y = DI.Line_Selected_Y[i];
      uint8 L_border = DI.Ladder_LBorder[Needed_Y]; //获取左右扫线边界
      uint8 R_border = DI.Ladder_RBorder[Needed_Y];
      true_Center = 1.0 * (L_border + R_border) / 2;
      /*标记黑点*/
      for (int j = DI.IEX[M_L][Needed_Y] + 1; j < DI.IEX[M_R][Needed_Y] - 1; j += 2)
      {
        image[62 - Needed_Y][j] = 0;
      }
      for (int k = Needed_Y; k < Needed_Y + 3; k++)
      {
        image[62 - k][(int)true_Center] = 0;
      }
      // if(((DI.ForkCnt == fork_left)&&state==83))
      // {
      //   if (DI.IEX[M_R][Needed_Y] > 80 && DI.IEX[M_L][Needed_Y] > 14 && DI.Ladder_LBorder[Needed_Y] > 14) //右转丢线
      //   {
      //     true_Center = 1.0 * (L_border + ImageWide[Needed_Y] / 2);
      //   }
      //   else if (DI.IEX[M_L][Needed_Y] < 14 && DI.IEX[M_R][Needed_Y] < 80 && DI.Ladder_RBorder[Needed_Y] < 83) //左转丢线根据赛道宽度来补偿
      //   {
      //     true_Center = 1.0 * (R_border - ImageWide[Needed_Y] / 2);
      //   }
      // }
      // for (int k = Needed_Y; k < Needed_Y + 5; k++)
      // {
      //   image[62 - k][(int)true_Center] = 0;
      // }

      sum += true_Center * WeightAdd[i];
      sum_W += WeightAdd[i];
    }
    midLine = (sum / sum_W - 47) * 1.4 + 47;

    /*显示中点*/
    for (int i = 0; i < 5; i++)
    {
      image[62 - i][(int)midLine] = 0;
    }
    return midLine;
  }

  else
  {
    float midLine;
    uint8 Needed_Y = 10;                          //
    uint8 L_border = DI.Ladder_LBorder[Needed_Y]; //获取左右扫线边界
    uint8 R_border = DI.Ladder_RBorder[Needed_Y];

    midLine = 1.0 * (L_border + R_border) / 2;

    /*标记虚线*/
    for (int i = DI.IEX[M_L][Needed_Y] + 1; i < DI.IEX[M_R][Needed_Y] - 1; i += 2)
    {
      image[62 - Needed_Y][i] = 0;
    }
    /*数据规约*/
    if (midLine > 92)
      midLine = 92;
    else if (midLine < 1)
      midLine = 1;
    /*标记未补线中点*/
    for (int i = Needed_Y; i < Needed_Y + 3; i++)
    {
      image[62 - i][(int)midLine] = 0;
    }
    /*补线*/
    // if(state==84){
    //   if (R_border > 80 && L_border > 13) //右边丢线
    //   {
    //     true_Center = 1.0 * (L_border + ImageWide[Needed_Y] / 2);
    //   }
    //   else if (L_border < 13 && R_border < 80) //左边丢线
    //   {
    //     true_Center = 1.0 * (R_border - ImageWide[Needed_Y] / 2);
    //   }
    //  }

    /*数据规约*/
    if (midLine > 92)
      midLine = 92;
    else if (midLine < 1)
      midLine = 1;
    /*标记补线中点*/
    // for (int i = Needed_Y; i < Needed_Y + 5; i++)
    // {
    //   image[62 - i][(int)true_Center] = 0;
    // }
    /*显示中点*/
    for (int i = 0; i < 5; i++)
    {
      image[62 - i][(int)midLine] = 0;
    }
    return midLine;
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-04 11:46:30
 ********************************************************/
//获取正常情况下的中线
float Midline_in_Normal()
{

  Err_Select_Line();     //根据最远可视距离，选择7条等距离的横线  Y
  Err_DetermineWeight(); //根据速度，获取每条线的权重
  DetermineScanLine();   //确定扫描行边界 X
  float sum = 0, midLine = 0, sum_W = 0;
  state_dx = 0;
  for (uint8 i = 0; i < 7; i++)
  {
    float true_Center;
    uint8 Needed_Y = DI.Line_Selected_Y[i];       // i = 0 时，选中最后一行
    uint8 L_border = DI.Ladder_LBorder[Needed_Y]; //获取左右爬梯边界
    uint8 R_border = DI.Ladder_RBorder[Needed_Y];
    true_Center = 1.0 * (L_border + R_border) / 2; //中点等于爬梯中值
    //补线前标记中点
    for (int i = Needed_Y; i < Needed_Y + 3; i++)
    {
      image[62 - i][(int)true_Center] = 0;
    }

    //丢线补偿
    {
      // if (state < 10 || (state >= 80 && state < 90 && state != 83) || state == 35 || state == 52) //直道
      if (state < 10 || (state >= 80 && state < 90) || state == 35 || state == 52) //直道
      {
        if (DI.IEX[M_R][Needed_Y] > 80 && DI.IEX[M_L][Needed_Y] > 14 && DI.Ladder_LBorder[Needed_Y] > 14) //右转丢线
        {
          true_Center = 1.0 * (L_border + ImageWide[Needed_Y] / 2);
          state_dx = 12;
        }
        else if (DI.IEX[M_L][Needed_Y] < 14 && DI.IEX[M_R][Needed_Y] < 80 && DI.Ladder_RBorder[Needed_Y] < 83) //左转丢线根据赛道宽度来补偿
        {
          true_Center = 1.0 * (R_border - ImageWide[Needed_Y] / 2);
          state_dx = 11;
        }
      }
      else
      {
        {
          if (R_border > 80 && L_border > 13) //右边丢线
          {
            true_Center = 1.0 * (L_border + ImageWide[Needed_Y] / 2);
            state_dx = 2;
          }
          else if (L_border < 13 && R_border < 80) //左边丢线
          {
            true_Center = 1.0 * (R_border - ImageWide[Needed_Y] / 2);
            state_dx = 1;
          }
        }
      }
    }

    /*数据规约*/
    if (true_Center > 92)
      true_Center = 92;
    else if (true_Center < 1)
      true_Center = 1;
    /*标记虚线*/
    for (int i = DI.IEX[M_L][Needed_Y] + 1; i < DI.IEX[M_R][Needed_Y] - 1; i += 2)
    {
      image[62 - Needed_Y][i] = 0;
    }
    /*标记中点*/
    for (int i = Needed_Y; i < Needed_Y + 5; i++)
    {
      image[62 - i][(int)true_Center] = 0;
    }

    sum += true_Center * WeightAdd[i];
    sum_W += WeightAdd[i];
  }

  midLine = sum / sum_W;
  /*显示中点*/
  for (int i = 0; i < 5; i++)
  {
    image[62 - i][(int)midLine] = 0;
  }
  return midLine;
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-04 11:46:20
 ********************************************************/
//根据速度，确定权重
void Err_DetermineWeight()
{
  if (speed >= 0 && speed < 250)
  // if (speed >= 0 && speed < 125)
  {
    float kv = VCK_W * speed + 1;
    //    float kv = VCK_W * speed*2 + 1;
    if (kv > 0)
    {
      float AddWeight = 1;
      for (uint8 i = 0; i < 7; i++)
      {
        AddWeight *= kv;
        WeightAdd[6 - i] = WeightBase[6 - i] + AddWeight - 1;
      }
    }
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-04 11:46:14
 ********************************************************/
//误差选择行 （选择7条）
void Err_Select_Line()
{
  uint8 start = 5;
  uint8 end = 35;
  // /*根据速度匹配*/
  // if (speed < 60)
  // {
  //   start = 10;
  //   end = 40;
  // }
  // else if (speed > 90)
  // {
  //   start = 15;
  //   end = 45;
  // }
  // else
  // {
  //   end = 40 + (speed - 60) / 6;
  //   start = 10 + (speed - 60) / 6;
  //   ;
  // }

  // /*根据最远可视距离匹配*/
  // if (L_Move.AllMaxY < 50)
  // {
  //   start = 10;
  //   end = 40;
  // }
  // else //弯道
  // {
  //   end = 40 + (L_Move.AllMaxY - 50) / 2;
  //   start = 10 + (L_Move.AllMaxY - 50) / 2;
  //   ;
  // }
  // if (state == 16 || state == 80)
  // {
  //   start = 10;
  //   end = 40;
  // }

  /*根据最远可视距离匹配*/
  if (L_Move.AllMaxY < 50
      // || error_xunxian>15
      ) //弯道
  {
    start = 5;
    end = 35;
  }
  else
  {
    end = 35 + (L_Move.AllMaxY - 50) / 2;
    start = 5 + (L_Move.AllMaxY - 50) / 2;
  }
  /*若入库*/

  if (state > 50 && state < 55)
    end = DI.Top_edge_Y[(uint8)DI.MidLine];
  /**/
  if (end > L_Move.AllMaxY)
    end = L_Move.AllMaxY; // end取小

  if (start < end) //可以取到
  {
    for (uint8 i = 1; i < 8; i++)
    {
      DI.Line_Selected_Y[i - 1] = end - (uint8)(i * i * (float)(end - start) / 49.0);
    }
  }
  else //取不到,选择最远行
  {
    for (uint8 i = 0; i < 7; i++)
    {
      DI.Line_Selected_Y[i] = end;
    }
  }
}

/************************************************************************
函数名：确定扫描行
功能：7条误差行与爬梯线交点
************************************************************************/
void DetermineScanLine(void)
{
  for (int i = 0; i < 7; i++)
  {
    DI.ui8_ScanLineL[i] = DI.Ladder_LBorder[DI.Line_Selected_Y[i]]; //左右爬梯边界点
    DI.ui8_ScanLineR[i] = DI.Ladder_RBorder[DI.Line_Selected_Y[i]];
  }
}
/*********************************************************
 *函数名：小S判断处理函数 (不推荐)
 **********************************************************/
float SmallS()
{
  uint8 LMax = 0, RMin = 93;
  float RealMid = 0;
  for (uint8 i = 10; i <= 55; i += 2)
  {
    if (DI.IEX[M_L][i] > LMax)
      LMax = DI.IEX[M_L][i]; //内边界找靠近中线的点
    if (DI.IEX[M_R][i] < RMin)
      RMin = DI.IEX[M_R][i];
  }
  if (RMin - LMax >= 8 && RMin - LMax <= 24 && RMin <= 63 && LMax >= 30)
    RealMid = (RMin + LMax) / 2;
  else
    return 0;
  return RealMid;
}
uint8 Is_SmallS()
{
  float mid = SmallS();

  if (mid != 0 && state < 10 && L_Move.AllMaxY > 50 && (DI.Top_edge_Y[39] > 45 || DI.Top_edge_Y[47] > 45 || DI.Top_edge_Y[55] > 45))
    return 1;
  else
    return 0;
}
