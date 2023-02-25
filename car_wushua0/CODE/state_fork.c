/*
 * state_fork.c
 *
 *  Created on: 2022??6??4??
 *      Author: 22878
 */
#include "state_fork.h"

/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-04 16:49:04
 ********************************************************/
uint8 bottom_pointX = 47;
uint8 bottom_pointY;
uint8 fork_L_x, fork_L_y;
uint8 fork_R_x, fork_R_y;
float fork_L_k, fork_R_k;
uint8 corner_Lx, corner_Rx;
int min1 = 15, min2 = 15;
// uint8 minY[94];
uint8 Is_fork3()
{
  Fork_Image(); //图像最低点

  // V在左边
  if (
      (corner_Rx - fork_R_x) > 0 && ((fork_R_x - bottom_pointX) > 5) && (bottom_pointX <= 47
                                                                         // && fork_R_x >= 46
                                                                         ) &&
      (abs(fork_L_k) <= 1 || abs(fork_R_k) <= 1) && (bottom_pointY > 5))
  {
    min1 = 2;
  }
  // V在右边
  else if (
      (fork_L_x - corner_Lx) > 0 && ((bottom_pointX - fork_L_x) > 15) && (bottom_pointX > 50 && fork_R_x > 60
                                                                          // && fork_L_x <= 47
                                                                          ) &&
      (abs(fork_L_k) <= 1 || abs(fork_R_k) <= 1) && (bottom_pointY > 5))
  {
    min2 = 2;
  }
  else
  {
    min1 = 15;
    min2 = 15;
  }
  if (
      (bottom_pointX - fork_L_x) >= min1 && (fork_R_x - bottom_pointX) >= min2 && (abs(fork_L_k) <= 1 || abs(fork_R_k) <= 1) && (fork_L_y > 5 && fork_R_y > 5 && bottom_pointY > 5) && ((DI.Top_edge_Y[fork_R_x] - DI.Top_edge_Y[bottom_pointX]) >= 4 || (DI.Top_edge_Y[fork_L_x] - DI.Top_edge_Y[bottom_pointX]) >= 4))
  {
    return 1;
  }

  // if (((corner_Lx > 0 && (fork_L_x - corner_Lx ) < 15 && (bottom_pointX - fork_L_x) > 10&& (fork_R_x - bottom_pointX) > 10 )
  // || (corner_Rx > 0 && (corner_Rx - fork_R_x) < 15 && (fork_R_x - bottom_pointX) > 15 &&(bottom_pointX - fork_L_x) < 15 )) //存在左拐点
  //     && (((fork_L_k) <= 0 &&(fork_L_k) >= -1) || ((fork_R_k) <= 1&& fork_R_k>=0)) && (fork_L_y > 5 && fork_R_y > 5 && bottom_pointY > 5))
  // {
  //   return 1;
  // }

  return 0;
}
uint8 Is_fork()
{
  for (uint8 i = 1; i < 93; i++)
  {
    if ((Top_edge_Y[i + 1] - Top_edge_Y[i]) > 10)
    {
      return 1;
    }
  }
  return 0;
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-09 13:36:08
 ********************************************************/
uint8 break_p1=0,break_p2=0,break_p3=0;
void state_80()
{
  uint8 x_80 = 0, but_1 = 0, but_2 = 0,flag=0;
  if (DI.ForkCnt == fork_left) //左拉线
  {
    // for(but_1=86;but_1>10;but_1--)
    // {
    //   if(DI.Top_edge_Y[but_1]<60)
    //   {
    //     break;
    //   }
    // }
    // for (uint8 i = 1; i < 93; i++)
    // {
    //   // if (DI.IEX[M_L][3] < 2)
    //   // {
    //   //   x_80 = 0;
    //   //   Fill_line_image(x_80, 0, but_1, DI.Top_edge_Y[but_1]);
    //   //   break;
    //   // }
    //   if (
    //     // abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 1]) < 5 &&
    //   abs(DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i] )> 10
    //   && DI.top_Y > 63)
    //   {
    //     x_80 = i;
    //     Fill_line_image(x_80, DI.Top_edge_Y[x_80], but_1, DI.Top_edge_Y[but_1]);
    //     break;
    //   }
    // }
    if (DI.top_Y >= 58)
    {
      // for (uint8 i = 0; i < 93; i++) //从左往右找第一个跳变点
      // {
      //   // if(DI.Top_edge_Y[2]>20)
      //   // {
      //   //   x_80 = 0;
      //   //   but_1 = x_80;
      //   //   but_2 = 0;
      //   //   break;
      //   // }
      //   if (abs(DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i]) > 5)
      //   {
      //     x_80 = i;
      //     but_1 = x_80;
      //     but_2 = Top_edge_Y[but_1];
      //     break;
      //   }
      // }
      // while (++x_80)
      // {
      //   if (image[63 - but_2 - (x_80 - but_1)][x_80] == 0)
      //     break;
      //   if ((63 - but_2 - (x_80 - but_1)) <= 1)
      //     break;
      //   image[63 - but_2 - (x_80 - but_1)][x_80] = 0;
      // }
      /**/
      for (uint8 i = 1; i < 93; i++)
      {
        if (DI.IEX[M_L][3] < 2)
        {
          x_80 = 0;
          // Fill_line_image(x_80, 0, 86, DI.Top_edge_Y[86]);
          // Fill_line_image(x_80, 0, but_1, Top_edge_Y[but_1]);
          break;
        }
        if (abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 1]) < 5 && abs(DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i]) > 10)
        {
          x_80 = i;
          // Fill_line_image(x_80, DI.Top_edge_Y[x_80], 86, DI.Top_edge_Y[86]);
          // Fill_line_image(x_80, DI.Top_edge_Y[x_80], but_1, Top_edge_Y[but_1]);
          break;
        }
      }
      for (uint8 i = 93; i > 20; i--)
      {
        if(but_1)
        if(but_1!=0&&Top_edge_Y[i]>Top_edge_Y[x_80])//跳变左边满足条件点
        {
          but_1 = i;
          break;
        }
        if (abs(Top_edge_Y[i - 1] - Top_edge_Y[i]) > 5)//找跳变
        {
          but_1 = i - 1;
          // break;
        }
      }
      break_p1=0;break_p2=0;break_p3=0;
      for (uint8 i = 93; i > 0; i--)
      {
        if (abs(Top_edge_Y[i - 1] - Top_edge_Y[i]) > 5)//找跳变
        {
          if(flag==0)
          {
            break_p3=i-1;
            flag++;
          }
          else if(flag==1)
          {
            break_p2=i-1;
            flag++;
          }
          else if(flag==2)
          {
            break_p1=i-1;
            break;
          }
        }
      }
      if((break_p3-break_p2)>25)
      {
       but_1= break_p3;
      }
      else
      {
        but_1= break_p2;
      }
      if (DI.IEX[M_L][3] < 2)
      {
        Fill_line_image(x_80, 0, but_1, Top_edge_Y[but_1]);
      }
      else
        Fill_line_image(x_80, DI.Top_edge_Y[x_80], but_1, Top_edge_Y[but_1]);
      /**/
    }

    // if(DI.top_Y > 63)
    // {
    //   Fill_line_image(DI.IEX[M_L][0] , 0, 86, DI.Top_edge_Y[86]);
    // }
  }
  else if (DI.ForkCnt == fork_right) //右拉线
  {
    for (uint8 i = 92; i > 10; i--)
    {
      if (abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 1]) < 5        //第一个连续点
          && abs(DI.Top_edge_Y[i - 2] - DI.Top_edge_Y[i - 3]) < 5 //
          && abs(DI.Top_edge_Y[i - 4] - DI.Top_edge_Y[i - 5]) < 5 //
          && but_1 == 0)
      {
        but_1 = i;
      }
      if (but_1 != 0)
      {
        if (abs(DI.Top_edge_Y[i - 1] - DI.Top_edge_Y[i]) > 10) //第二个跳变点
        {
          but_2 = i;
        }
      }

      if (DI.IEX[M_R][93 - 3] < 2)
      {
        x_80 = 93;
        //   Fill_line_image(x_80, 0, 47, DI.Top_edge_Y[47]);
      }
      if (abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i + 1]) < 5  //右边连续
          && (DI.Top_edge_Y[i - 1] - DI.Top_edge_Y[i]) > 10 //左边跳变
          && DI.top_Y > 63)
      {
        x_80 = i;
      }

      if (but_1 != 0 && but_2 != 0 && x_80 != 0)
      {
        Fill_line_image(x_80, DI.Top_edge_Y[x_80], (int)(but_1 + but_2) / 2, DI.Top_edge_Y[(int)(but_1 + but_2) / 2]);
        break;
      }
    }
  }

  if (Is_fork3() == 1 
  && bottom_pointY < 50 && DI.top_Y > 57

  )
  {
    state = 81;
    state_81();
    return;
  }
}
/********************************************************
 *@函数名: 入三叉
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-04 16:25:07
 ********************************************************/
void state_81()
{

  DI.tempLength = DI.Length; //沿距
                             //  }
  beep_on();
  state = 82;
  state_82();

  /*三叉减速*/
  return;
}
/********************************************************
 *@函数名:补线
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-04 16:25:13
 ********************************************************/
uint8 x_82 = 0, btn_82 = 0;
void state_82()
{
  //补线
  // Fill_line_image
  DI.ForkLength = DI.Length - DI.tempLength;
  static int last_X;
  uint8 max = 10, left_point;
  for (uint8 left_bottom = 0; left_bottom < 92; left_bottom++)
  {
    if ((DI.Top_edge_Y[left_bottom + 1] - DI.Top_edge_Y[left_bottom]) > max && (DI.Top_edge_Y[left_bottom] < DI.Top_edge_Y[bottom_pointX]))
    {
      left_point = left_bottom;
      break;
    }
  }

  /*先右后左*/
  // if (DI.ForkCnt == fork_right)
  // {
  //   if ((DI.Top_edge_Y[(int)(fork_L_x + fork_R_x) / 2]) < 55 && (fork_L_x < fork_R_x))
  //   {
  //     Fill_line_image((int)(fork_L_x + fork_R_x) / 2, DI.Top_edge_Y[(int)(fork_L_x + fork_R_x) / 2], 92 - 10, 0); //右拉线
  //     last_X = (int)(fork_L_x + fork_R_x) / 2;
  //   }
  //   else
  //   {
  //     Fill_line_image(last_X, DI.Top_edge_Y[last_X], 92 - 10, 0); //右拉线
  //   }
  // }
  // else if (DI.ForkCnt== fork_left) //左拉线
  // {
  //   if ((DI.Top_edge_Y[(int)(fork_L_x + fork_R_x) / 2]) < 60 && (fork_L_x < fork_R_x))
  //   {
  //     Fill_line_image(left_point, DI.Top_edge_Y[left_point], ((int)(fork_L_x + fork_R_x) / 2) + 1, DI.Top_edge_Y[((int)(fork_L_x + fork_R_x) / 2) + 1]);
  //     last_X = ((int)(fork_L_x + fork_R_x) / 2) + 1;
  //   }
  //   else
  //   {
  //     Fill_line_image(left_point, DI.Top_edge_Y[left_point], last_X, DI.Top_edge_Y[last_X]);
  //   }
  // }

  if (DI.ForkCnt == fork_left)
  {
    // if (Is_fork3() == 0 && DI.Ladder_LBorder[0] < 5)
    if (Is_fork3() == 0 && DI.Top_edge_Y[5] <= DI.Top_edge_Y[10] && DI.Top_edge_Y[10] <= DI.Top_edge_Y[15] && DI.Top_edge_Y[15] <= DI.Top_edge_Y[20] && Top_edge_Y[92] > 20 && DI.ForkLength > 20)
    {
      beep_off();
      state = 83;
      DI.tempLength = DI.Length;
      state_83();
      return;
    }
  }
  else if (DI.ForkCnt == fork_right)
  {
    // if (Is_fork3() == 0 && DI.Ladder_LBorder[0] < 5)
    if (Is_fork3() == 0 && DI.IEX[M_L][10] < DI.IEX[M_L][20] && DI.IEX[M_L][20] < DI.IEX[M_L][30]
        // &&DI.ForkLength>20
    )
    {
      beep_off();
      state = 83;
      DI.tempLength = DI.Length;
      state_83();
      return;
    }
  }
  /**/
  uint8 x_80 = 0, but_1 = 0, but_2 = 0;
  if (DI.ForkCnt == fork_left) //左拉线
  {
    // for(but_1=47;but_1<92;but_1++)
    // {
    //   if(DI.Top_edge_Y[but_1]<60&&abs(DI.Top_edge_Y[but_1 + 1] - DI.Top_edge_Y[but_1]) > 5)
    //   {
    //     break;
    //   }
    // }
    // for (uint8 i = 1; i < 93; i++)
    // {
    //   if (DI.IEX[M_L][3] < 2)
    //   {
    //     x_80 = 0;
    //     Fill_line_image(x_80, 0, but_1, DI.Top_edge_Y[but_1]);
    //     break;
    //   }
    //   if (abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 1]) < 5 && abs(DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i] )> 10)
    //   {
    //     x_80 = i;
    //     Fill_line_image(x_80, DI.Top_edge_Y[x_80], but_1, DI.Top_edge_Y[but_1]);
    //     break;
    //   }
    // }
    /**/
    // for (but_1 = 86; but_1 > 10; but_1--)
    // {
    //   if (DI.Top_edge_Y[but_1] < 50)
    //   {
    //     break;
    //   }
    // }
    // for (uint8 i = 0; i < 93; i++)
    // {
    //   // if (DI.IEX[M_L][3] < 2)
    //   // {
    //   //   x_80 = 0;
    //   //   Fill_line_image(x_80, 0, but_1, DI.Top_edge_Y[but_1]);
    //   //   break;
    //   // }
    //   if (
    //       // abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 1]) < 5 &&
    //       abs(DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i]) > 10 && DI.top_Y > 63)
    //   {
    //     x_80 = i;
    //     Fill_line_image(x_80, DI.Top_edge_Y[x_80], but_1, DI.Top_edge_Y[but_1]);
    //     break;
    //   }
    // }
    /**/
    // for (uint8 i = 47; i < 93; i++)//从左往右找第一个跳变点
    // {
    //   if (abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 1]) < 5 && abs(DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i] > 10) && DI.top_Y > 63)
    //   {
    //     x_80 = i;
    //     break;
    //   }
    // }
    // if(DI.top_Y > 63&&x_80!=0)
    // {
    //   Fill_line_image(DI.IEX[M_L][0] , 0, x_80, DI.Top_edge_Y[x_80]);
    // }
    /**/
    // if (DI.top_Y > 63)
    {
      //   for (uint8 i = 0; i < 93; i++) //从左往右找第一个跳变点
      //   {
      //     // if(DI.Top_edge_Y[2]>20)
      //     // {
      //     //   x_80 = 0;
      //     //   but_1 = x_80;
      //     //   but_2 = 0;
      //     //   break;
      //     // }
      //     if (abs(DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i]) > 5)
      //     {
      //       x_82 = i;
      //       x_80 = i;
      //       but_1 = x_80;
      //       but_2 = Top_edge_Y[but_1];
      //       break;
      //     }
      //   }
      //   Fill_line_image(x_80, but_2, bottom_pointX, Top_edge_Y[bottom_pointX]);
      //   // while (++x_80)
      //   // {
      //   //   if (image[63 - but_2 - (x_80 - but_1)][x_80] == 0)
      //   //     break;
      //   //   if ((63 - but_2 - (x_80 - but_1)) <= 1)
      //   //     break;
      //   //   image[63 - but_2 - (x_80 - but_1)][x_80] = 0;
      //   // }
      // }
      /**/

      for (uint8 i = 0; i < 93; i++)
      {
        // if (DI.IEX[M_L][3] < 2)
        // {
        //   x_80 = 0;
        //   break;
        // //   Fill_line_image(x_80, 0, but_1, DI.Top_edge_Y[but_1]);
        // }
        if ((DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i]) > 10)
        {
          x_82 = i;
          break;
        }
      }
      // for (uint8 j = 80; j > 20; j--) //从右往左找
      // {
      //   if ((Top_edge_Y[j]) <= 50 && Top_edge_Y[j] > 30)
      //   {
      //     btn_82 = j;
      //     break;
      //   }
      //   // but_1 = j;
      // }
      for (uint8 i = 47; i < 93; i++)
      {
        if (abs(DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i]) > 5
            // && DI.Top_edge_Y[i] < 60
            && abs(x_82 - i) > 10)
        {
          btn_82 = i;
          break;
        }
      }
      if (x_82 == 0)
      {
        Fill_line_image(0, 0, btn_82, Top_edge_Y[btn_82]);
      }
      else
        Fill_line_image(x_82, Top_edge_Y[x_82], btn_82, Top_edge_Y[btn_82]);
      // Fill_line_image(DI.IEX[M_L][0], 0, btn_82, DI.Top_edge_Y[btn_82]);

      /**/
      // for (uint8 j = 40; j < 93; j++)//从左往右找
      // {
      //   if (abs(Top_edge_Y[j+1] -Top_edge_Y[j]) > 5)
      //   {
      //     but_1 = j;
      //     break;
      //   }
      //   // but_1 = j;
      // }
      // for (uint8 i = 0; i < 93; i++)
      // {
      //   // if (DI.IEX[M_L][3] < 2)
      //   // {
      //   //   x_80 = 0;
      //   //   Fill_line_image(x_80, 0, but_1, DI.Top_edge_Y[but_1]);
      //   // }
      //   if ((DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i]) > 5)
      //   {
      //     x_80 = i;
      //     break;
      //   }
      // }
      // Fill_line_image(x_80, DI.Top_edge_Y[x_80], but_1, DI.Top_edge_Y[but_1]);
    }
  }
  else if (DI.ForkCnt == fork_right) //右拉线
  {

    for (uint8 i = 92; i > 10; i--)
    {
      if (abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 1]) > 10 //
          && but_1 == 0)
      {
        but_1 = i;
      }

      if (but_1 != 0 && DI.Top_edge_Y[but_1] > 20)
      {
        Fill_line_image(93, 0, (int)(but_1 + 93) / 2, DI.Top_edge_Y[(int)(but_1 + 93) / 2]);
        break;
      }
    }
  }
}
/********************************************************
 *@函数名:三叉内
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-04 16:25:31
 ********************************************************/
void state_83()
{
  // beep_on();
  if (DI.ForkCnt == fork_right && (DI.Length - DI.tempLength) > 50)
  {
    state = 84;
    state_84();
    DI.tempLength = DI.LengthRamp = DI.Length;
    return;
  }
  if ((Is_ramp(1) == 1 || (DI.Length - DI.tempLength) > 100) && DI.ForkCnt == fork_left) //坡道
  {
    beep_on();
    state = 31;
    AD_Fork++;
    state_31();
    DI.ForkLength = DI.Length;
    return;
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-09 11:11:53
 ********************************************************/
/************************************************************************
 *函数名：入环补线(从上面往下面画弧线)
 *参数：拐点坐标
 ************************************************************************/
int8 Diffff = 0;
// void ForkInPatchLine()
// {
//   int8 Dif = 0;
//   int8 FinalY = 0;
//   for (int8 i = 87; i > 6; i--)
//   {
//     if (
//         DI.Top_max_Y[i - 1] >= DI.Top_max_Y[i]        //左边不递减
//         && DI.Top_max_Y[i - 3] >= DI.Top_max_Y[i - 1] //左边不递减
//         && DI.Top_max_Y[i - 5] >= DI.Top_max_Y[i - 3] //左边不递减
//         && DI.Top_max_Y[i + 1] >= DI.Top_max_Y[i]     //右边递增
//         && DI.Top_max_Y[i + 3] > DI.Top_max_Y[i + 1]  //
//         && DI.Top_max_Y[i + 5] > DI.Top_max_Y[i + 3])
//     {
//       Dif = i;
//       Diffff = Dif;
//       FinalY = DI.Top_max_Y[i];
//       while (Dif--)
//       {
//         if (Dif <= 0)
//           break;
//         FinalY -= 1;
//         image[62 - FinalY][Dif] = 0;
//       }
//       break;
//     }
//   }
// }
uint8 btnF1 = 0, btnF2 = 0, BTN = 0;
void ForkInPatchLine()
{
  int8 Dif = 0;
  int8 flag = 0;
  int8 FinalY = 0;
  for (uint8 i = 0; i < 86; i++)
  {
    if (flag == 1 && abs(Top_edge_Y[i + 1] - Top_edge_Y[i]) > 5)
    {
      btnF2 = i;
      flag = 2;
      break;
    }
    if (abs(Top_edge_Y[i + 1] - Top_edge_Y[i]) > 5 && flag == 0)
    {
      btnF1 = i + 1;
      flag = 1;
    }
  }
  // btnF1=0;
  // btnF2=20;
  if (btnF2 > 0 && btnF1 < btnF2)
  {
    BTN = btnF1;
    for (int8 i = btnF1; i < btnF2; i++)
    {
      if (Top_edge_Y[i] < Top_edge_Y[BTN])
      {
        BTN = i;
      }
    }
    Dif = BTN;
    Diffff = Dif;
    FinalY = DI.Top_edge_Y[BTN];
    while (--Dif)
    {
      if (Dif <= 0)
        break;
      if ((63 - FinalY) <= 0)
        break;
      FinalY -= 1;
      image[63 - FinalY][Dif] = 0;
    }
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-20 16:20:16
 ********************************************************/

void state_84()
{
  uint8 x_84;
  uint8 left = -1, right = -1, button;
  if (DI.ForkCnt == fork_left)
  {
    ForkInPatchLine();
  }

  // for (uint8 i = 0; i > 94; i++)
  // {
  //   // if ((DI.IEX[M_L][i+1] -DI.IEX[M_L][i])>=5&&(DI.IEX[M_L][i]<47)&&DI.Top_edge_Y[i+1]>30)
  //   // {
  //   //   x_84 = DI.IEX[M_L][i+1];
  //   //   Fill_line_image(x_84-1, DI.Top_edge_Y[x_84-1]-10, x_84, DI.Top_edge_Y[x_84]);
  //   //   // ForkInPatchLine(x_84,DI.Top_edge_Y[x_84],RingIn_50);//补线
  //   //   break;
  //   // }
  //   // if (abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 1]) < 5 && abs(DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i] > 10))
  //   // {
  //   //   x_80 = i;
  //   //   Fill_line_image(x_80, DI.Top_edge_Y[x_80], 86, DI.Top_edge_Y[86]);
  //   //   break;
  //   // }

  //   if(abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i + 1]) < 5
  //   && DI.Top_edge_Y[i] >30
  //   && left==-1
  //   )
  //   {
  //     left = i;
  //   }
  //   if(left!=-1
  //   && right==-1
  //   &&  abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i + 1]) > 5
  //   &&  abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 1]) < 5
  //   )
  //   {
  //     right = i;
  //   }
  //   if(left!=-1&&right!=-1)
  //   {
  //     button = (int)(left+right)/2;
  //     Fill_line_image(0, DI.Top_edge_Y[left]-20, button, DI.Top_edge_Y[button]);
  //     break;
  //   }
  // }
  // uint8 x_80=0, but_1 = 0, but_2 = 0;
  // if (DI.ForkCnt == fork_left) //左拉线
  // {
  //   for(but_1=86;but_1>10;but_1--)
  //   {
  //     if(DI.Top_edge_Y[but_1]<55)
  //     {
  //       break;
  //     }
  //   }
  //    Fill_line_image(DI.IEX[M_L][0], 0, 93, DI.Top_edge_Y[93]);
  // }

  if (
      Is_fork3()
      // &&
      // (DI.Length - DI.LengthRamp) > 20
  )
  {
    beep_on();
    DI.tempLength = DI.Length;
    state = 85;
    state_85();
    return;
  }
  // if ((DI.Length - DI.ForkLength) > 300) //出三岔未检测到
  // {
  //   state = 0;
  //   return;
  // }
}

/********************************************************
 *@函数名: 出三叉识别补线
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-17 16:21:59
 ********************************************************/
uint8 Dif_85 = 0;
void state_85()
{
  beep_off();
  //补线
  // ForkInPatchLine();
  // ForkInPatchLine();
  // Fill_line_image
  DI.ForkLength = DI.Length - DI.tempLength;

  static int last2_X;
  uint8 max = 10, left_point, right_point;
  for (uint8 right_bottom = 92; right_bottom > 0; right_bottom--)
  {
    if ((DI.Top_edge_Y[right_bottom - 1] - DI.Top_edge_Y[right_bottom]) > max //
        && (DI.Top_edge_Y[right_bottom] < DI.Top_edge_Y[bottom_pointX]))
    {
      right_point = right_bottom; // X
      left_point = DI.IEX[M_L][DI.Top_edge_Y[right_point]];
      Dif_85 = DI.Top_edge_Y[right_point];
      break;
    }
  }

  /*先右后左*/
  // if (DI.ForkCnt % 1 == fork_right)
  // {
  //   // if ((DI.Top_edge_Y[(int)(fork_L_x + fork_R_x) / 2]) < 55 && (fork_L_x < fork_R_x))
  //   // {
  //   //   Fill_line_image((int)(fork_L_x + fork_R_x) / 2, DI.Top_edge_Y[(int)(fork_L_x + fork_R_x) / 2], 92 - 10, 0); //右拉线
  //   //   last2_X = (int)(fork_L_x + fork_R_x) / 2;
  //   // }
  //   // else
  //   // {
  //   //   Fill_line_image(last2_X, DI.Top_edge_Y[last2_X], 92 - 10, 0); //右拉线
  //   // }

  //   if ((DI.Top_edge_Y[(int)(fork_L_x + fork_R_x) / 2]) < 55 //
  //   && (fork_L_x < fork_R_x) //
  //   && (left_point < ((int)(fork_L_x + fork_R_x) / 2)) //
  //   && (DI.Top_edge_Y[(int)(fork_L_x + fork_R_x) / 2]) > 10)//
  //   {
  //     Fill_line_image(left_point, DI.Top_edge_Y[right_point], ((int)(fork_L_x + fork_R_x) / 2), DI.Top_edge_Y[((int)(fork_L_x + fork_R_x) / 2)]);
  //     last2_X = ((int)(fork_L_x + fork_R_x) / 2);
  //   }
  //   else
  //   {
  //     if (left_point < last2_X)
  //       Fill_line_image(left_point, DI.Top_edge_Y[right_point], last2_X, DI.Top_edge_Y[last2_X]);
  //   }
  // }
  // else if (DI.ForkCnt % 1 == fork_left) //左拉线
  // {
  //   if ((DI.Top_edge_Y[(int)(fork_L_x + fork_R_x) / 2]) < 55 && (fork_L_x < fork_R_x) && (left_point < ((int)(fork_L_x + fork_R_x) / 2)) && (DI.Top_edge_Y[(int)(fork_L_x + fork_R_x) / 2]) > 10)
  //   {
  //     Fill_line_image(left_point, DI.Top_edge_Y[right_point], ((int)(fork_L_x + fork_R_x) / 2), DI.Top_edge_Y[((int)(fork_L_x + fork_R_x) / 2)]);
  //     last2_X = ((int)(fork_L_x + fork_R_x) / 2);
  //   }
  //   else
  //   {
  //     if (left_point < last2_X)
  //       Fill_line_image(left_point, DI.Top_edge_Y[right_point], last2_X, DI.Top_edge_Y[last2_X]);
  //   }
  // }

  // uint8 x_80;
  // if (DI.ForkCnt == fork_left) //左拉线
  // {
  //   for (uint8 i = 1; i < 93; i++)
  //   {
  //     if (DI.IEX[M_L][3] < 2)
  //     {
  //       x_80 = 0;
  //       Fill_line_image(x_80, 0, 86, DI.Top_edge_Y[86]);
  //     }
  //     if (abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 1]) < 5 && abs(DI.Top_edge_Y[i + 1] - DI.Top_edge_Y[i] > 10))
  //     {
  //       x_80 = i;
  //       Fill_line_image(x_80, DI.Top_edge_Y[x_80], 86, DI.Top_edge_Y[86]);
  //       break;
  //     }
  //   }
  // }
  if (DI.ForkCnt == fork_left)
  {
    ForkInPatchLine();
  }
  uint8 x_80 = 0, but_1 = 0, but_2 = 0;
  //  if (DI.ForkCnt == fork_left) //左拉线
  //  {
  //    for(but_1=86;but_1>10;but_1--)
  //    {
  //      if(DI.Top_edge_Y[but_1]<55)
  //      {
  //        break;
  //      }
  //    }
  //    Fill_line_image(DI.IEX[M_L][0], 0, but_1, DI.Top_edge_Y[but_1]);
  //  }
  if (DI.ForkCnt == fork_right) //右拉线
  {
    for (uint8 i = 93; i > 10; i--)
    {
      if (but_1 != 0 && abs(Top_edge_Y[i] - Top_edge_Y[i - 1]) > 5
          // &&Top_edge_Y[i]>10
      )
      {
        but_2 = i;
        break;
      }
      if ((Top_edge_Y[i - 1] - Top_edge_Y[i]) > 5
          // &&Top_edge_Y[i]>10
      )
      {
        but_1 = i - 1;
      }
    }
    Dif_85 = (int)(but_1 + but_2) / 2;
    if (Dif_85 > 0 && Dif_85 < 93 && but_1 != 0 && but_2 != 0)
      for (uint8 j = Dif_85; j < 94; j++)
      {
        image[63 - Top_edge_Y[Dif_85] + (j - Dif_85)][j] = 0;
      }
    // for (uint8 i = 93; i > 0; i--)
    // {
    //   if (DI.IEX[M_R][93 - 3] < 2)
    //   {
    //     x_80 = 93;
    //     Fill_line_image(x_80, 0, 47, DI.Top_edge_Y[47]);
    //   }
    //   if (abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i + 1]) < 5 && abs(DI.Top_edge_Y[i - 1] - DI.Top_edge_Y[i] > 10))
    //   {
    //     x_80 = i;
    //     Fill_line_image(x_80, DI.Top_edge_Y[x_80], 47, DI.Top_edge_Y[47]);
    //     break;
    //   }
    // }
  }

  // if(Servo_PWM>=0)beep_off();
  // else beep_on();
  //状态切换判断
  // if ((Is_fork3() == 0 && DI.ForkLength >= 100)

  //     // ||(DI.IEX[M_L][5])>2
  //     // || (DI.Top_edge_Y[1] < 5 && DI.ForkLength > 60)
  //     )
  if (Is_fork3() == 0 && Top_edge_Y[2] < 5 && DI.ForkCnt == fork_left)
  {
    DI.tempLength = DI.Length;
    beep_on();
    state = 86;
    state_86();
    return;
  }
  if (Is_fork3() == 0 && Top_edge_Y[80] < 5 && DI.ForkCnt == fork_right)
  {
    DI.tempLength = DI.Length;
    beep_on();
    state = 86;
    state_86();
    return;
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-17 16:22:05
 ********************************************************/
void state_86()
{
  //状态切换判断
  // if (Is_fork3() == 0)
  if ((DI.Length - DI.tempLength) > 100)
  {
    beep_off();
    // DI.ForkCnt++;
    state = 87;
    state_87();
    return;
  }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-18 09:07:29
 ********************************************************/
void state_87()
{
  /*入库*/

  //  if (is_checkZebro != 0)
  //  {
  //    if (Is_zebro() == 1) //斑马线
  //    {
  //      if(DI.ZebroNum!=DI.Two_Cam)
  //      {
  //        DI.ZebroNum++;
  //        state = 0;
  //        state_00();
  //      }
  //      if (is_checkZebro == 1&&DI.ZebroNum==DI.Two_Cam)
  //      {
  //        state = 41;
  //        state_41();
  //      }
  //      else if (is_checkZebro == 2&&DI.ZebroNum==DI.Two_Cam)
  //      {
  //        state = 51;
  //        state_51();
  //      }
  //      return;
  //    }
  //  }
  if (is_checkZebro != 0)
  {
    if (Is_zebro() == 1) //斑马线
    {
          DI.ForkCnt++;
      if (DI.ZebroNum != DI.Two_Cam)
      {
        state = 40;
        state_40();
      }
      else
      {
        if (is_checkZebro == 1 && DI.ZebroNum == DI.Two_Cam)
        {
          state = 41;
          state_41();
        }
        else if (is_checkZebro == 2 && DI.ZebroNum == DI.Two_Cam)
        {
          state = 51;
          state_51();
        }
      }
      return;
    }
  }
}
