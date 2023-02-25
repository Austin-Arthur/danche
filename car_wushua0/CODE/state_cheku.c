/*
 * state_cheku.c
 *
 *  Created on: 2022��3��14��
 *      Author: 11609
 */
#include "state_cheku.h"

uint8 CheKuL_X = 0, CheKuL_Y = 0;
// uint8 CheKuL_X2=0,CheKuL_Y2=0;
uint8 CheKu_AD = 0;
uint8 Z_point[2][2];
int8 cheku_line[94] =
    // {
    //     // 0  1  2  3  4  5  6  7  8  9
    //     43, 43, 43, 42, 42, 42, 41, 41, //
    //     41, 40, 40, 40, 39, 39, 39, 38, //
    //     38, 38, 37, 37, 36, 36, 35, 35, //
    //     34, 34, 33, 33, 32, 32, 31, 31, //
    //     30, 30, 29, 29, 28, 28, 27, 27, //
    //     26, 26, 25, 25, 24, 24, 23, 23, //
    //     22, 22, 21, 21, 20, 20, 19, 19, //
    //     18, 18, 17, 17, 16, 16, 15, 15, //
    //     14, 14, 13, 12, 11, 10, 9, 8,   //
    //     7, 6, 5, 4, 3, 2, 1, 0,         //
    //     -1, -2, -3, -4, -5, -6, -7, -8, //
    //     -9, -10, -11, -12};
    // {
    // 43,43,43,43,43,42,42,42,42,42,41,41,
    // 41,41,40,40,40,40,39,39,39,39,38,38,
    // 38,37,37,37,36,36,36,35,35,35,34,34,
    // 33,33,32,32,31,31,30,30,29,29,28,28,
    // 27,27,26,26,25,25,24,24,23,23,22,22,
    // 21,21,20,19,19,18,17,16,15,14,13,12,
    // 11,10,9,8,7,6,5,4,3,2,1,0,-1,-2,-3,
    // -4,-5,-6,-7,-8,-9
    // };
    {
        // 0 1  2  3  4  5  6  7  8  9
        42, 42, 42, 42, 42, 42, 42, 42, 42, 42,     // 0
        42, 42, 42, 42, 42, 42, 41, 41, 41, 41,     // 1
        41, 41, 41, 41, 41, 40, 40, 40, 40, 40,     // 2
        39, 39, 39, 39, 38, 38, 38, 38, 37, 37,     // 3
        37, 36, 36, 36, 35, 35, 34, 34, 33, 32,     // 4
        31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, // 5
        20, 19, 19, 18, 17, 16, 15, 14, 13, 12,     // 6
        11, 10, 9, 8, 7, 6, 5, 4, 3, 2,             // 7
        1, 0, -1, -2, -3, -4, -5, -6, -7, -8,       // 8
        -9, -10, -11                                // 9
};
/************************************************************************
�������ܣ����������߶����ݡ��˽��ڵ�Ӱ��
************************************************************************/
void Deal_zebro(void)
{
  if (state >= 40 && state <= 79)
  {

    uint8 Lpoint = 1, Rpoint = 92; //��¼���������
    while (!(image[62][Lpoint] == 1 && image[62][Lpoint + 1] == 0) && Lpoint < 92)
      Lpoint++;
    while (!(image[62][Rpoint] == 1 && image[62][Rpoint - 1] == 0) && Rpoint > 1)
      Rpoint--;
    if (Lpoint <= Rpoint)
    {
      for (uint8 i = Lpoint; i <= Rpoint; i++)
      {
        image[62][i] = 1;
        image[61][i] = 1;
        image[60][i] = 1;
      }
    }
  }
}
void state_40()
{
  if ((DI.Length - DI.tempLength > 100))
  {
    DI.ZebroNum++;
    state = 0;
    state_00();
    return;
  }
}
/********************************************************
 *@������:
 *@˵��: none
 *@��������: none
 *@Date: 2022-07-07 22:01:54
 ********************************************************/
//ʶ���󳵿�Ԫ�أ���ʶ�������
void state_41(void)
{
  CheKuL_Y = 64;
  for (uint8 i = DI.top_Y - 5; i > 10; i--)
  {
    if (DI.IEX[M_L][i] - DI.IEX[M_L][i - 1] >= 3)
    {
      CheKuL_Y = i;
      break;
    }
  }
  if (CheKuL_Y < 45)
  {
    state = 42;
    state_42();
  }
}
/********************************************************
 *@������:
 *@˵��: none
 *@��������: none
 *@Date: 2022-07-15 20:49:38
 ********************************************************/
//ʶ�𵽰����ߣ����������
void state_42(void)
{
  circleLx = 86;
  uint8 max = 5;

  for (uint8 i = 2; i < DI.top_Y - 5 && i < 54; i++) //��ˮƽ��������
  {
    if (DI.IEX[M_L][i] - DI.IEX[M_L][i - 1] > max)
    {
      max = DI.IEX[M_L][i] - DI.IEX[M_L][i - 1];
      circleLx = DI.IEX[M_L][i];
      circleLy = i;
      if (max > 8)
        break;
    }
  }
  circleLx = circleLx > 1 ? circleLx - 1 : 0;
  GarageInPatchLine(circleLx, circleLy, RingIn_50);
  if ((DI.top_Y < 25 && DI.top_Y > 5 && DI.Length - DI.tempLength > 100) || DI.Length - DI.tempLength > 120)
  {
    State = STOP;
    state = 43;
    return;
  }
}

//�������ɣ�����LCD��ʾ�����
void state_43(void)
{
}

/********************************************************
 *@������:
 *@˵��: none
 *@��������: none
 *@Date: 2022-07-04 11:05:50
 ********************************************************/
//ʶ���ҳ���Ԫ�أ���ʶ�������

void state_51(void)
{
  CheKuL_Y = 64;

  for (uint8 i = DI.top_Y - 5; i > 10; i--)
  {
    if (DI.IEX[M_R][i - 1] - DI.IEX[M_R][i] >= 3)
    {
      CheKuL_Y = i;
      break;
    }
  }
  if (CheKuL_Y <= 60)
  {
    beep_on();
    state = 52;
    state_52();
    DI.tempLength = DI.Length;
  }
}
/********************************************************
 *@������:
 *@˵��: none
 *@��������: none
 *@Date: 2022-07-04 11:07:03
 ********************************************************/
//ʶ�𵽰����ߣ��������ҿ�
void state_52(void)
{
  static last_x3;
  /*�ҵ�һ*/
  circleLx = 7;
  uint8 max = 2;
  Circle[M_R].A_y = 0;
  for (uint8 i = 2; i < DI.top_Y - 2; i++)
  {
    if (DI.IEX[M_R][i - 1] - DI.IEX[M_R][i] > max)
    {
      max = DI.IEX[M_R][i - 1] - DI.IEX[M_R][i];
      circleLx = DI.IEX[M_R][i];
      circleLy = i;
      if (max > 5)
        break;
    }
  }
  circleLx = circleLx < 93 ? circleLx + 1 : 93;

  for (uint8 i = 0; i < 93; i++)
  {
    if ((DI.Top_edge_Y[i]) > 2)
    {
      Z_point[M_R][1] = i;
      break;
    }
  }
  for (uint8 ui8_X = 93; ui8_X > 0; ui8_X--)
  {
    if ((DI.Top_edge_Y[ui8_X]) > 20) //�߽�ݼ�
    {
      Z_point[M_R][0] = ui8_X;
      // Z_point[M_R][1]=DI.IEX[M_R][ui8_X];
      break;
    }
  }

  /*�ҵ��*/
  // GarageInPatchLine(93, 40, RingIn_50);
  // Fill_line_image(0,0,93,40);

  // Fill_line_image(0,0,90,43);

  //   GarageInPatchLine(90, 43, cheku_line);
  // Fill_line_image(10,0,89, DI.Top_max_Y[89]);
  // GarageInPatchLine(circleLx, circleLy, RingIn_50);
  Fill_line_image(10, 0, Z_point[M_R][0], DI.Top_edge_Y[Z_point[M_R][0]]);

  if ((DI.top_Y < 35 && DI.top_Y > 5 && (DI.Length - DI.tempLength) > 70) || (DI.Length - DI.tempLength) > 80)
  {
    beep_off();
    State = STOP;
    state = 99;
    return;
  }
}
/********************************************************
 *@������:
 *@˵��: none
 *@��������: none
 *@Date: 2022-07-04 11:07:08
 ********************************************************/
//�������ɣ�����LCD��ʾ�����
void state_53(void)
{
}
/********************************************************
 *@������: �ж��Ƿ�Ϊ����
 *@˵��: none
 *@��������: �ж��Ƿ�Ϊ����
 *@Date: 2022-07-04 11:07:25
 ********************************************************/

uint8 Is_OutGarage()
{
  float RSlope, LSlope;
  LSlope = Is_straight_abs(1, 10, DI.IEX[M_L]);
  RSlope = Is_straight_abs(1, 10, DI.IEX[M_R]);
  if (DI.top_Y < 57 && LSlope < 0.38 && RSlope < 0.38 /*&&LSlope!=0&&RSlope!=0*/)
    return 1;
  else
    return 0;
}
// /********************************************************
//  *@������:
//  *@˵��: none
//  *@��������: none
//  *@Date: 2022-07-04 10:56:52
//  ********************************************************/
// //ֱ����ǰ��һ�ξ���
// void state_61()
// {
//   // if(DI.top_Y<45)
//   if (DI.top_Y <= 45)
//   {
//     state = 62;
//     state_62();
//     return;
//   }
// }
// /********************************************************
//  *@������:
//  *@˵��: none
//  *@��������: none
//  *@Date: 2022-07-04 10:57:06
//  ********************************************************/
// //���������
// void state_62()
// {
//   for (uint8 i = 5; i < L_Move.AllMaxY - 3; i++)
//   {
//     if (DI.IEX[M_R][i] < DI.IEX[M_R][i + 1] && DI.Ladder_RBorder[i] == DI.Ladder_RBorder[i + 3])
//     {                                                       //�ұ߽߱����ҹ�
//       while (DI.IEX[M_R][i] == DI.IEX[M_R][i - 1] && i > 7) //����͵�
//         i--;
//       circleLx = DI.IEX[M_R][i];
//       circleLy = i;
//       if (circleLx_temp > circleLx && circleLx > 57)
//         circleLx_temp = circleLx;
//       break;
//     }
//   }
//   // if(DI.Ladder_RBorder[0]>=47&&DI.top_Y>=58)
//   if (
//       (
//           DI.Ladder_RBorder[0] >= 47 && DI.top_Y >= 58) ||
//       DI.Length > 120)

//   {
//     state = 0;
//     is_ChuKu = 0;
//     return;
//   }
//   //  GarageOutPatchLine(circleLx,circleLy,RingIn_80);//����
//   GarageInPatchLine(7, DI.Top_max_Y[7], cheku_line); //����
// }
/********************************************************
 *@������:
 *@˵��: none
 *@��������: none
 *@Date: 2022-07-07 11:01:42
 ********************************************************/
/*�Ӿ��ŷ�   �ҳ���*/
uint8 chuku_p, chuku_p2;
void state_61()
{
  uint8 flag = 0;
  for (uint8 i = 0; i < 93; i++)
  {
    if (flag == 1 && (Top_edge_Y[i + 1] - Top_edge_Y[i] >= 2))
    {
      flag++;
      chuku_p2 = i;
      break;
    }

    if ((Top_edge_Y[i + 1] - Top_edge_Y[i] > 5) && flag == 0)
    {
      flag++;
      chuku_p = i;
    }
    if (DI.IEX[M_L][2] < 2 && flag == 0)
    {
      flag++;
      chuku_p = 0;
    }
  }
  // for(uint8 j=chuku_p+1;j<93;j++)
  // {
  //   if((Top_edge_Y[chuku_p] - (j - chuku_p))<=0)break;
  //   if(image[63 - Top_edge_Y[chuku_p] - (j - chuku_p)][j] ==0)break;
  //   image[63 - Top_edge_Y[chuku_p] - (j - chuku_p)][j] = 0;
  // }
  if (chuku_p == 0)
  {
    Fill_line_image(0, 0, chuku_p2, Top_edge_Y[chuku_p2]);
  }
  else
    Fill_line_image(chuku_p, Top_edge_Y[chuku_p], chuku_p2, Top_edge_Y[chuku_p2]);
  if (DI.Length - DI.LengthCheku > 100)
  {
    state = 0;
    is_ChuKu = 0;
    state_00();
    return;
  }
}
/********************************************************
 *@������:
 *@˵��: none
 *@��������: none
 *@Date: 2022-07-07 11:01:31
 ********************************************************/
void state_62()
{
}
/********************************************************
 *@������:
 *@˵��: none
 *@��������: none
 *@Date: 2022-07-07 11:01:35
 ********************************************************/
void state_63()
{
}

/********************************************************
 *@������:
 *@˵��: none
 *@��������: none
 *@Date: 2022-07-06 17:41:43
 ********************************************************/
/*�Ӿ��ŷ�   ��ʱֻд���ҳ���*/

void state_71()
{
}
/********************************************************
 *@������:
 *@˵��: none
 *@��������: none
 *@Date: 2022-07-06 17:41:48
 ********************************************************/
void state_72()
{
}

void state_73()
{
}

/********************************************************
�������ܣ���ⲹ��
********************************************************/
void GarageInPatchLine(uint8 x, uint8 y, int8 Str[94])
{
  int8 Dif = 0;
  int8 FinalY = y;
  if (state == 42 || state == 62) //����� ���������»�����
  {
    Dif = y - Str[x]; //����ڣ�x��y�����������ı仯
    for (uint8 i = x; i < 93; i++)
    {
      int8 temp_y = FinalY;  //��¼��һ��Y
      FinalY = Str[i] + Dif; //������С
      temp_y = temp_y - FinalY + 1;
      if (FinalY >= 0)
      {
        while (temp_y--)
          image[62 - FinalY - temp_y][i] = 0; //��ɫ
      }
      else
        break;
    }
  }
  else //�����
  {
    Dif = y - Str[93 - x];
    for (int8 i = x; i > 0; i--)
    {
      int8 temp_y = FinalY;       //��¼��һ��Y
      FinalY = Str[93 - i] + Dif; //������С
      temp_y = temp_y - FinalY + 1;
      if (FinalY >= 0 && FinalY <= 62)
      {
        while (temp_y--)
          image[62 - FinalY - temp_y][i] = 0;
      }
      else
        break;
    }
  }
}

//
///********************************************************
//�������ܣ�δʶ������Ԫ�أ���ʶ�𵽰����߽����жϳ��ⷽ��
//********************************************************/
// uint8 GarageDirection(void)
//{
//  float Slope = 0;
//
//  if(DI.MaxY[10]>=10&&(DI.MaxY[10]+1)<50){
//    Slope = Is_straight_abs(DI.MaxY[10]+1,50,DI.IEX[M_R]); //�ұ�Ϊֱ��
//  }
//  else{
//    Slope = Is_straight_abs(10,50,DI.IEX[M_R]); //�ұ�Ϊֱ��
//  }
//
//  if(Slope < 0.5&&Slope!=0)
//  {
//    return 1;
//  }
//  return 0;
//}
