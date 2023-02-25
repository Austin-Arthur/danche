/*
 * Deal.c
 *
 *  Created on: 2021年12月30日
 *      Author: 11609
 */
/*
 * Deal.c
 *
 *  Created on: 2021年12月30日
 *      Author: 11609
 */
#include "Deal.h"
/************************************************************************
函数功能：提取中线
返回值：中线值 (1-92)
************************************************************************/
DataI DI;
TwoDot L_Move;
int temp[5] = {0};
char *state_name = {"norma"};
uint8 is_checkRing = 0, is_checkPoDao = 0, is_checkZebro = 0, is_useDianCi = 0, is_ChuKu = 0;
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-25 00:13:17
 ********************************************************/
float Get_midline()
{
  /*图像处理*/
  ImageInit();           //初始化图??
  Deal_zebro();          //处理斑马线对车库图形识别的影响
  Deal_firstline();      //处理第一行，获取左右爬梯起点
  Ladder();              //爬梯
  Get_eight_neighbour(); // 8近邻找边??
  // Fork_Image();          //图像最低点
  Fit_Top_edge_Y();
  Vertical_scanning(); //获取十条竖线最远距??
  /*状态控??*/

  // if(Is_fork3())beep_on();
  // else beep_off();
  switch (state) //
  {
  //正常情况-做判断
  case 00:
    state_00();
    state_name = "norma";
    break;
  //直道
  case 01:
    state_01();
    state_name = "zhi_d";
    break;
  //入弯前的直道
  case 02:
    state_02();
    state_name = "w2z_d";
    break;
  //入弯
  case 03:
    state_03();
    state_name = "in_wa";
    break;

  case 06:
    state_06();
    state_name = "shi_z";
    break;
  //左边圆环
  case 11:
    state_11();
    state_name = "sta11";
    break;
  case 12:
    state_12();
    state_name = "sta12";
    break;
  case 13:
    state_13();
    state_name = "sta13";
    break;
  case 14:
    state_14();
    state_name = "sta14";
    break;
  case 15:
    state_15();
    state_name = "sta15";
    break;
  case 16:
    state_16();
    state_name = "sta16";
    break;
  case 17:
    state_17();
    state_name = "sta17";
    break;
  //右边圆环
  case 21:
    state_21();
    state_name = "sta21";
    break;
  case 22:
    state_22();
    state_name = "sta22";
    break;
  case 23:
    state_23();
    state_name = "sta23";
    break;
  case 24:
    state_24();
    state_name = "sta24";
    break;
  case 25:
    state_25();
    state_name = "sta25";
    break;
  //坡道
  case 31:
    state_31();
    state_name = "ramp1";
    break;
  case 32:
    state_32();
    state_name = "ramp2";
    break;
  case 33:
    state_33();
    state_name = "ramp3";
    break;
  case 34:
    state_34();
    state_name = "ramp4";
    break;
  case 35:
    state_35();
    state_name = "ramp5";
    break;

  //斑马线入左库
  case 40:
    state_40();
    state_name = "CeK40";
    break;
  case 41:
    state_41();
    state_name = "CeK41";
    break;
  case 42:
    state_42();
    state_name = "CeK42";
    break;
  case 43:
    state_43();
    state_name = "CeK43";
    break;
  //斑马线入右库
  case 51:
    state_51();
    state_name = "CeK51";
    break;
  case 52:
    state_52();
    state_name = "CeK52";
    break;
  case 53:
    state_53();
    state_name = "CeK53";
    break;
  //左出车库
  case 61:
    state_61();
    state_name = "CeK61";
    break;
  case 62:
    state_62();
    state_name = "CeK62";
    break;
  case 63:
    state_63();
    state_name = "CeK63";
    break;
  //右出车库
  case 71:
    state_71();
    state_name = "CeK71";
    break;
  case 72:
    state_72();
    state_name = "CeK72";
    break;
  case 73:
    state_73();
    state_name = "CeK73";
    break;
  case 80:
    state_80();
    state_name = "fork0";
    break;
  case 81:
    state_81();
    state_name = "fork1";
    break;
  case 82:
    state_82();
    state_name = "fork2";
    break;
  case 83:
    state_83();
    state_name = "fork3";
    break;
  case 84:
    state_84();
    state_name = "fork4";
    break;
  case 85:
    state_85();
    state_name = "fork5";
    break;
  case 86:
    state_86();
    state_name = "fork6";
    break;
  case 87:
    state_87();
    state_name = "fork7";
    break;
  //错误
  case 99:
    state_99();
    state_name = "Error";
    break;
  default:
    break;
  }
  if ((state < 10 && is_ChuKu == 0)
      // ||(state==80)
  )
  {
    FitRoad(); //十字处理
  }
  Deal_firstline(); //处理第一行

  // Judge_Cross();    //十字处理

  Ladder(); //爬梯
  smooth(); //赛道平滑处理

  for (uint8 i = 1; i < L_Move.AllMaxY; i++) //计算每一行的中??
  {
    DI.Ladder_MidPoint[i] = (DI.Ladder_LBorder[i] + DI.Ladder_RBorder[i]) / 2;
  }
  DI.SightDistance = (L_Move.AllMaxY + Get_VerticalHeight((uint8)DI.MidLine, 0)) / 2;

  float mid = getMid();

  if (mid > 92)
    return 92;
  else if (mid < 1)
    return 1;
  else
    return mid;
}

/********************************************************
 *@函数??: 十字补线
 *@说明: 版本1
 *@函数功能: none
 *@Date: 2022-06-02 01:25:40
 ********************************************************/
uint8 G_point[2][4];

// void FitRoad(void)
// {
//   /*横向边界************************************************************/

//   int8 i8_UpLpX = -1; //左侧两拐点坐??
//   uint8 ui8_UpLpY;
//   int8 i8_EndLpX = -1;
//   uint8 ui8_EndLpY;

//   float k_l, k_r;

//   int8 i8_UpRpX = -1; //右侧两拐点坐??
//   uint8 ui8_UpRpY;
//   int8 i8_EndRpX = -1;
//   uint8 ui8_EndRpY;

//   uint8 flag_l, flag_r;
//   /**************************************十字补线**************************************************/
//   //左补
//   for (uint8 ui8_Y = 3; ui8_Y <= L_Move.AllMaxY; ui8_Y++)
//   {
//     if (
//         i8_UpLpX == -1 //
//         && GetSlope2(DI.IEX[M_L][ui8_Y], ui8_Y, DI.IEX[M_L][ui8_Y - 3], ui8_Y - 3) * GetSlope2(DI.IEX[M_L][ui8_Y], ui8_Y, DI.IEX[M_L][ui8_Y + 3], ui8_Y + 3) < 0 //拐点
//         && (DI.IEX[M_L][ui8_Y] - DI.IEX[M_L][ui8_Y - 1]) >= 0                                                                        //
//         && (DI.IEX[M_L][ui8_Y] - DI.IEX[M_L][ui8_Y - 1]) <= 5                                                                        //
//         // && (DI.IEX[M_L][ui8_Y] - DI.IEX[M_L][ui8_Y + 1]) > 10 //
//         // && DI.IEX[M_L][ui8_Y + 3] < 5                                                                             //
//         // && DI.IEX[M_L][ui8_Y + 5] < 5                                                                             //
//         && ui8_Y <= 55 //
//     )
//     {
//       ui8_UpLpY = ui8_Y; //找到第一个拐点
//       i8_UpLpX = DI.IEX[M_L][ui8_UpLpY];
//       G_point[M_L][0] = i8_UpLpX;
//       G_point[M_L][1] = ui8_UpLpY;
//       k_l = GetSlope(DI.IEX[M_L][ui8_Y], ui8_Y, DI.IEX[M_L][ui8_Y - 3], ui8_Y - 3); //斜率
//       // k_l = GetSlope(DI.IEX[M_L][ui8_Y], ui8_Y, DI.IEX[M_L][1],1); //斜率

//     }                                                                               //找到爬梯交点为止
//     /*找第二个点*/
//     if (i8_UpLpX != -1 && i8_EndLpX == -1)
//     {
//       if ((DI.IEX[M_L][ui8_Y] > 10                                                                  //                                                                                                                                        //
//            && abs(DI.IEX[M_L][ui8_Y] - DI.IEX[M_L][ui8_Y + 1]) < 5                                  //                                                                                                           //
//            && abs(DI.IEX[M_L][ui8_Y] - DI.IEX[M_L][ui8_Y - 1]) > 5                                  //                                                                                                           //
//            && DI.IEX[M_L][ui8_Y - 3] < 5                                                            //                                                                                                                                   //
//                                                                                                     //  && DI.IEX[M_L][ui8_Y - 5] < 5   //                                                                                                                                   //
//            && DI.IEX[M_L][ui8_Y] <= (DI.IEX[M_L][ui8_Y + 1])                                        //                                                                                                    //
//            && DI.IEX[M_L][ui8_Y] <= (DI.IEX[M_L][ui8_Y + 2])                                        //                                                                                                    //
//            && abs(k_l - GetSlope(DI.IEX[M_L][ui8_Y + 2], ui8_Y + 2, DI.IEX[M_L][ui8_Y], ui8_Y)) < 3 //
//            && ui8_Y <= 55                                                                           //                                                                                                     // && Is_straight_abs(ui8_Y, ui8_Y + 3, DI.Ladder_LBorder) < 0.38 //是直??
//                                                                                                     // 38
//            ))                                                                                       //垂直上升长度过短省去

//       {
//         ui8_EndLpY = ui8_Y; //找到??2个拐??
//         i8_EndLpX = DI.IEX[M_L][ui8_EndLpY];
//         G_point[M_L][2] = i8_EndLpX;
//         G_point[M_L][3] = ui8_EndLpY;
//       }
//     }

//     if (i8_UpLpX != -1 && i8_EndLpX != -1 && G_point[M_L][1]!=0 && G_point[M_L][3]!=0)
//     {
//       Fill_line_image(G_point[M_L][0], G_point[M_L][1], G_point[M_L][2], G_point[M_L][3]); //连线
//       beep_on();
//       i8_UpLpX = -1;
//       i8_EndLpX = -1;
//       flag_l = 1;
//       break;
//     }
//     else
//     beep_off();
//     if (i8_UpLpX == -1)
//     {
//       G_point[M_L][0] = 0;
//       G_point[M_L][1] = 0;
//     }
//     if (i8_EndLpX == -1)
//     {
//       G_point[M_L][2] = 0;
//       G_point[M_L][3] = 0;
//     }
//   }
//   //右补
//   for (uint8 ui8_Y = 3; ui8_Y <= L_Move.AllMaxY; ui8_Y++)
//   {
//     ////////////////////////////////////////
//     if (
//         i8_UpRpX == -1                                                                                                                                           //
//         && GetSlope2(DI.IEX[M_R][ui8_Y], ui8_Y, DI.IEX[M_R][ui8_Y - 3], ui8_Y - 3) * GetSlope2(DI.IEX[M_R][ui8_Y], ui8_Y, DI.IEX[M_R][ui8_Y + 3], ui8_Y + 3) < 0 //拐点                                                                                   //
//         && (DI.IEX[M_R][ui8_Y - 1] - DI.IEX[M_R][ui8_Y]) >= 0                                                                                                    //                                                    //
//         && (DI.IEX[M_R][ui8_Y - 1] - DI.IEX[M_R][ui8_Y]) <= 5                                                                                                    //
//         // && (DI.IEX[M_R][ui8_Y+1] - DI.IEX[M_R][ui8_Y]) > 5 //
//         // && DI.IEX[M_R][ui8_Y + 3] > 85                                                                             //
//         // && DI.IEX[M_R][ui8_Y + 5] > 85                                                                             //
//         && ui8_Y <= 55 //
//         )              //第一个拐点不应太靠后
//     {
//       ui8_UpRpY = ui8_Y; //找到第一个拐??
//       i8_UpRpX = DI.IEX[M_R][ui8_UpRpY];
//       G_point[M_R][0] = i8_UpRpX;
//       G_point[M_R][1] = ui8_UpRpY;
//       k_r = GetSlope2(DI.IEX[M_R][ui8_Y], ui8_Y, DI.IEX[M_R][ui8_Y - 3], ui8_Y - 3); //斜率
//       // k_r = GetSlope2(DI.IEX[M_R][ui8_Y], ui8_Y, DI.IEX[M_R][1], 1); //斜率

//     }
//     if (i8_UpRpX != -1 && i8_EndRpX == -1)
//     {
//       if ((DI.IEX[M_R][ui8_Y] < 85                                                                   //   范围                                                                                                                                       //
//            && abs(DI.IEX[M_R][ui8_Y] - DI.IEX[M_R][ui8_Y + 1]) < 5                                   //                                                                                                          //
//            && abs(DI.IEX[M_R][ui8_Y] - DI.IEX[M_R][ui8_Y - 1]) > 5                                   //   跳变??                                                                                                       //
//            && DI.IEX[M_R][ui8_Y - 3] > 85                                                            //                                                                                                                                    //                                                                                                                                     //                                       //
//            && DI.IEX[M_R][ui8_Y] >= (DI.IEX[M_R][ui8_Y + 2])                                         //
//            && abs(k_r - GetSlope2(DI.IEX[M_R][ui8_Y + 3], ui8_Y + 3, DI.IEX[M_R][ui8_Y], ui8_Y)) < 3 //
//            && ui8_Y <= 55                                                                            //                                                                                                     //  && Is_straight_abs(ui8_Y, ui8_Y + 3, DI.Ladder_RBorder) < 0.38 //是直??
//                                                                                                      // 38
//            ))                                                                                        //垂直上升长度过短省去

//       {
//         ui8_EndRpY = ui8_Y + 2; //找到??2个拐??
//         i8_EndRpX = DI.IEX[M_R][ui8_EndRpY];
//         G_point[M_R][2] = i8_EndRpX;
//         G_point[M_R][3] = ui8_EndRpY;
//       }
//     }
//     if (i8_UpRpX != -1 && i8_EndRpX != -1 && G_point[M_R][1]!=0 && G_point[M_R][3]!=0)
//     {
//       Fill_line_image(G_point[M_R][0], G_point[M_R][1], G_point[M_R][2], G_point[M_R][3]); //连线
//       beep_on();
//       i8_UpRpX = -1;
//       i8_EndRpX = -1;
//       flag_r = 1;
//       break;
//     }
//     else
//     beep_off();
//     if (i8_UpRpX == -1)
//     {
//       G_point[M_R][0] = 0;
//       G_point[M_R][1] = 0;
//     }
//     if (i8_EndRpX == -1)
//     {
//       G_point[M_R][2] = 0;
//       G_point[M_R][3] = 0;
//     }
//   }

//   /************************入环前补??************************************/
//   // if (flag_l && flag_r)
//   // {
//   //   Fill_line_image(G_point[M_L][0], G_point[M_L][1], G_point[M_L][2], G_point[M_L][3]); //连线
//   //   Fill_line_image(G_point[M_R][0], G_point[M_R][1], G_point[M_R][2], G_point[M_R][3]); //连线
//   // }
// }
/********************************************************
 *@函数名: 十字补线
 *@说明: V2
 *@函数功能: none
 *@Date: 2022-06-27 10:25:57
 ********************************************************/
uint8 flag_xxx;
uint8 test_G[2][4];
uint8 Top_edge_Y[94];
// void FitRoad(void)
// {
//   /*横向边界************************************************************/
//   static uint8 last_G[2][4];

//   int8 i8_UpLpX = -1; //左侧两拐点坐标
//   uint8 ui8_UpLpY;
//   int8 i8_EndLpX = -1;
//   uint8 ui8_EndLpY;

//   float k_l, k_r;
//   uint8 flag_l, flag_r;
//   int8 i8_UpRpX = -1; //右侧两拐点坐标
//   uint8 ui8_UpRpY;
//   int8 i8_EndRpX = -1;
//   uint8 ui8_EndRpY;
//   flag_xxx = 1;

  
//   /**************************************十字补线**************************************************/
//   //左补 DI.Top_edge_Y[i]

//   if (DI.IEX[M_R][11] > 92 && DI.IEX[M_R][12] > 92 && DI.IEX[M_R][13] > 92 && DI.IEX[M_R][14] > 92)
//   {
//     flag_l = 1;
//     flag_xxx = 1;
//   }
//   else
//   {
//     flag_l = 0;
//     flag_xxx = 0;
//   }
//   for (uint8 ui8_X = 1; ui8_X < 92; ui8_X++)
//   {
//     if (
//         i8_UpLpX == -1 //
//         && Top_edge_Y[ui8_X] > 2
//         // && GetSlope2(ui8_X, DI.Top_edge_Y[ui8_X],ui8_X-3 , DI.Top_edge_Y[ui8_X-3]) * GetSlope2(ui8_X+1, DI.Top_edge_Y[ui8_X+1], ui8_X+4, DI.Top_edge_Y[ui8_X+4]) < 0 //拐点
//         && (abs(Top_edge_Y[ui8_X + 1] - Top_edge_Y[ui8_X]) > 10) //大跳变
//         && (Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X - 1]) >= 0      //连线                                                                      //
//         && (Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X - 1]) <= 5      //
//         && Top_edge_Y[ui8_X] <= 45                                  //不远
//     )
//     {
//       ui8_UpLpY = Top_edge_Y[ui8_X]; //找到第一个拐点
//       i8_UpLpX = ui8_X;
//       G_point[M_L][0] = i8_UpLpX;
//       G_point[M_L][1] = ui8_UpLpY;
//       // k_l = GetSlope(i8_UpLpX, DI.Top_edge_Y[ui8_X], i8_UpLpX-3, DI.Top_edge_Y[ui8_X-3]); //斜率
//       // k_l = GetSlope(DI.IEX[M_L][ui8_Y], ui8_Y, DI.IEX[M_L][1],1); //斜率

//     } //找到爬梯交点为止
//     /*找第二个点*/
//     if ((i8_UpLpX != -1 && i8_EndLpX == -1) || (flag_l))
//     {
//       if ((Top_edge_Y[ui8_X] > 5 && Top_edge_Y[ui8_X] <= 60                                                                                                                //
//            && abs(Top_edge_Y[ui8_X + 1] - Top_edge_Y[ui8_X]) < 5                                                                                                           // 连续                                                                                                          //
//            && abs(Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X - 1]) < 5                                                                                                           // 跳变
//            && Top_edge_Y[ui8_X] <= Top_edge_Y[ui8_X + 2]                                                                                                                   // 递加                                                                                                   //
//            && Top_edge_Y[ui8_X] <= Top_edge_Y[ui8_X + 3]                                                                                                                   //                                                                                                    //
//            && (GetSlope2(ui8_X, Top_edge_Y[ui8_X], ui8_X - 3, Top_edge_Y[ui8_X - 3]) + GetSlope2(ui8_X + 3, Top_edge_Y[ui8_X + 3], ui8_X, Top_edge_Y[ui8_X])) >= 1.5 //拐点                                                                                   //
//            && (GetSlope2(ui8_X, Top_edge_Y[ui8_X], ui8_X - 3, Top_edge_Y[ui8_X - 3]) + GetSlope2(ui8_X + 3, Top_edge_Y[ui8_X + 3], ui8_X, Top_edge_Y[ui8_X])) <= 5.0 //拐点
//            ))                                                                                                                                                                    //垂直上升长度过短省去

//       {
//         ui8_EndLpY = Top_edge_Y[ui8_X]; //找到第二个拐点
//         i8_EndLpX = ui8_X;
//         G_point[M_L][2] = i8_EndLpX;
//         G_point[M_L][3] = ui8_EndLpY;
//       }

//       if (flag_l == 0 && abs(ui8_X - G_point[M_L][0]) > 25)
//         break; //相距太远
//     }
//     if (i8_EndLpX != -1 && flag_l && G_point[M_L][2] > 5 && G_point[M_L][2] < 90 && G_point[M_L][3] != 0 && G_point[M_L][0] == 0) //第二点反找第一点
//     {
//       i8_UpLpX = ((0 - G_point[M_L][3]) * GetSlope(G_point[M_L][2] + 5, Top_edge_Y[G_point[M_L][2] + 5], G_point[M_L][2], G_point[M_L][3]) + G_point[M_L][2]);
//       ui8_UpLpY = 0;
//       G_point[M_L][0] = i8_UpLpX;
//       G_point[M_L][1] = ui8_UpLpY;
//     }
//     if (i8_UpLpX != -1 && i8_EndLpX != -1
//         // && G_point[M_L][0] != 0 // x!=0
//         //     && G_point[M_L][3] > 20                                   // Y>20
//         //     && abs(G_point[M_L][0] - G_point[M_L][2]) < 30            //距离不能太远
//     )
//     {
//       if (G_point[M_L][0] != 0                           // x!=0
//           && (G_point[M_L][0]<=G_point[M_L][2])
//           && G_point[M_L][3] > 20                        // Y>20
//           && abs(G_point[M_L][0] - G_point[M_L][2]) < 30 //距离不能太远
//       )
//       {
//         test_G[M_L][0] = G_point[M_L][0];
//         test_G[M_L][1] = G_point[M_L][1];
//         test_G[M_L][2] = G_point[M_L][2];
//         test_G[M_L][3] = G_point[M_L][3];
//         Fill_line_image(G_point[M_L][0], G_point[M_L][1], G_point[M_L][2], G_point[M_L][3]); //连线

//         i8_UpLpX = -1;
//         i8_EndLpX = -1;
//         break;
//       }
//       else
//       {
//         Fill_line_image(test_G[M_L][0], test_G[M_L][1], test_G[M_L][2], Top_edge_Y[test_G[M_L][2]]); //连线
//         i8_UpLpX = -1;
//         i8_EndLpX = -1;
//         // break;
//       }
//     }

//     if (i8_UpLpX == -1)
//     {
//       G_point[M_L][0] = 0;
//       G_point[M_L][1] = 0;
//     }
//     if (i8_EndLpX == -1)
//     {
//       G_point[M_L][2] = 0;
//       G_point[M_L][3] = 0;
//     }
//   }
//   //右补

//   if (DI.IEX[M_L][11] < 2 && DI.IEX[M_L][12] < 2 && DI.IEX[M_L][13] < 2 && DI.IEX[M_L][14] < 2)
//   {
//     flag_r = 1;
//     // flag_xxx=1;
//   }
//   else
//   {
//     flag_r = 0;
//     // flag_xxx=0;
//   }
//   for (uint8 ui8_X = 92; ui8_X > 0; ui8_X--) //从右往左
//   {
//     ////////////////////////////////////////
//     /**/
//     if (
//         i8_UpRpX == -1 //
//         && Top_edge_Y[ui8_X] > 2
//         // && GetSlope2(ui8_X, DI.Top_edge_Y[ui8_X], ui8_X, ui8_Y - 3) * GetSlope2(DI.IEX[M_R][ui8_Y], ui8_Y, DI.IEX[M_R][ui8_Y + 3], ui8_Y + 3) < 0 //拐点                                                                                   //
//         && (abs(Top_edge_Y[ui8_X - 1] - Top_edge_Y[ui8_X]) > 10) //大跳变
//         && (Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X + 1]) >= 0      //连线                                                                      //
//         && (Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X + 1]) <= 5      //                                                                           //
//         && Top_edge_Y[ui8_X] <= 45                                  //不远
//         // && ui8_X>=70
//         ) //第一个拐点不应太靠后
//     {
//       ui8_UpRpY = Top_edge_Y[ui8_X]; //找到第一个拐点
//       i8_UpRpX = ui8_X;
//       G_point[M_R][0] = i8_UpRpX;
//       G_point[M_R][1] = ui8_UpRpY;
//       // k_r = GetSlope2(ui8_X, DI.Top_edge_Y[ui8_X], ui8_X+3, DI.Top_edge_Y[ui8_X+3]); //斜率
//     }
//     /**/

//     /**/
//     if ((i8_UpRpX != -1 && i8_EndRpX == -1) || (flag_r
//                                                 // && ui8_X <= 70
//                                                 )) //找第二个点
//     {
//       if ((Top_edge_Y[ui8_X] > 5 && Top_edge_Y[ui8_X] <= 60      //   范围                                                                                                                                       //
//            && abs(Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X - 1]) < 5 // 连续                                                                                                         //
//            && abs(Top_edge_Y[ui8_X + 1] - Top_edge_Y[ui8_X]) < 5 //   跳变??                                                                                                       //
//            && Top_edge_Y[ui8_X] <= Top_edge_Y[ui8_X - 2]         // 递加                                                                                                   //
//            && Top_edge_Y[ui8_X] <= Top_edge_Y[ui8_X - 3]         //'
//            //  && abs(k_r - GetSlope2(ui8_X-3, DI.Top_edge_Y[ui8_X-3], ui8_X, DI.Top_edge_Y[ui8_X])) < 1 //
//            // && abs(GetSlope2(ui8_X-3, DI.Top_edge_Y[ui8_X-3], ui8_X, DI.Top_edge_Y[ui8_X]))>1
//            && (GetSlope2(ui8_X, Top_edge_Y[ui8_X], ui8_X - 3, Top_edge_Y[ui8_X - 3]) + GetSlope2(ui8_X + 3, Top_edge_Y[ui8_X + 3], ui8_X, Top_edge_Y[ui8_X])) >= -5.0 //拐点                                                                                   //
//            && (GetSlope2(ui8_X, Top_edge_Y[ui8_X], ui8_X - 3, Top_edge_Y[ui8_X - 3]) + GetSlope2(ui8_X + 3, Top_edge_Y[ui8_X + 3], ui8_X, Top_edge_Y[ui8_X])) <= -1.5 //拐点                                                                                                                                                                         //  && ui8_Y <= 55                                                                            //
//            ))                                                                                                                                                                     //垂直上升长度过短省去
//       {
//         ui8_EndRpY = Top_edge_Y[ui8_X]; //找到第二个拐点
//         i8_EndRpX = ui8_X;
//         G_point[M_R][2] = i8_EndRpX;
//         G_point[M_R][3] = ui8_EndRpY;
//       }
//       if (flag_r == 0 && abs(G_point[M_R][0] - ui8_X) > 25)
//         break; //相距太远
//     }
//     if (i8_EndRpX != -1 && flag_r && G_point[M_R][2] > 5 //
//         && G_point[M_R][2] < 90                          //
//         && G_point[M_R][3] != 0 && G_point[M_R][0] == 0) //第二点反找第一点
//     {
//       i8_UpRpX = ((0 - G_point[M_R][3]) * GetSlope(G_point[M_R][2] - 5, Top_edge_Y[G_point[M_R][2] - 5], G_point[M_R][2], G_point[M_R][3]) + G_point[M_R][2]);
//       ui8_UpRpY = 0;
//       G_point[M_R][0] = i8_UpRpX;
//       G_point[M_R][1] = ui8_UpRpY;
//     }

//     if (i8_UpRpX != -1 && i8_EndRpX != -1
//         // && G_point[M_R][0] != 0 && G_point[M_R][3] > 20 && abs(G_point[M_R][0] - G_point[M_R][2]) < 30
//     )
//     {
//       if (G_point[M_R][0] != 0 && G_point[M_R][3] > 20 //
//       && (G_point[M_R][0]>=G_point[M_R][2])//
//       && abs(G_point[M_R][0] - G_point[M_R][2]) < 30)
//       {
//         test_G[M_R][0] = G_point[M_R][0];
//         test_G[M_R][1] = G_point[M_R][1];
//         test_G[M_R][2] = G_point[M_R][2];
//         test_G[M_R][3] = G_point[M_R][3];
//         Fill_line_image(G_point[M_R][0], G_point[M_R][1], G_point[M_R][2], G_point[M_R][3]); //连线
//         // Fill_line_image(G_point[M_R][2], G_point[M_R][3], G_point[M_R][0], G_point[M_R][1]); //连线
//         i8_UpRpX = -1;
//         i8_EndRpX = -1;
//         break;
//       }
//       else{
//         Fill_line_image(test_G[M_R][0], test_G[M_R][1], test_G[M_R][2], Top_edge_Y[test_G[M_R][2]]); //连线
//         i8_UpRpX = -1;
//         i8_EndRpX = -1;
//         // break;
//       }
//     }

//     if (i8_UpRpX == -1)
//     {
//       G_point[M_R][0] = 0;
//       G_point[M_R][1] = 0;
//     }
//     if (i8_EndRpX == -1)
//     {
//       G_point[M_R][2] = 0;
//       G_point[M_R][3] = 0;
//     }
//   }
// }
void FitRoad(void)
{
  /*横向边界************************************************************/
  static uint8 last_G[2][4];

  int8 i8_UpLpX = -1; //左侧两拐点坐标
  uint8 ui8_UpLpY;
  int8 i8_EndLpX = -1;
  uint8 ui8_EndLpY;

  float k_l, k_r;
  uint8 flag_l, flag_r;
  int8 i8_UpRpX = -1; //右侧两拐点坐标
  uint8 ui8_UpRpY;
  int8 i8_EndRpX = -1;
  uint8 ui8_EndRpY;
  flag_xxx = 1;

  /**************************************十字补线**************************************************/
  //左补 DI.Top_edge_Y[i]

  if (DI.IEX[M_R][11] > 92 && DI.IEX[M_R][12] > 92 && DI.IEX[M_R][13] > 92 && DI.IEX[M_R][14] > 92)
  {
    flag_l = 1;
    flag_xxx = 1;
  }
  else
  {
    flag_l = 0;
    flag_xxx = 0;
  }
  for (uint8 ui8_X = 1; ui8_X < 92; ui8_X++)
  {
    if (
        i8_UpLpX == -1 //
        && Top_edge_Y[ui8_X] > 2
        // && GetSlope2(ui8_X, DI.Top_edge_Y[ui8_X],ui8_X-3 , DI.Top_edge_Y[ui8_X-3]) * GetSlope2(ui8_X+1, DI.Top_edge_Y[ui8_X+1], ui8_X+4, DI.Top_edge_Y[ui8_X+4]) < 0 //拐点
        && (abs(Top_edge_Y[ui8_X + 1] - Top_edge_Y[ui8_X]) > 10) //大跳变
        && (Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X - 1]) >= 0      //连线                                                                      //
        && (Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X - 1]) <= 5      //
        && Top_edge_Y[ui8_X] <= 45                               //不远
    )
    {
      ui8_UpLpY = Top_edge_Y[ui8_X]; //找到第一个拐点
      i8_UpLpX = ui8_X;
      G_point[M_L][0] = i8_UpLpX;
      G_point[M_L][1] = ui8_UpLpY;
      // k_l = GetSlope(i8_UpLpX, DI.Top_edge_Y[ui8_X], i8_UpLpX-3, DI.Top_edge_Y[ui8_X-3]); //斜率
      // k_l = GetSlope(DI.IEX[M_L][ui8_Y], ui8_Y, DI.IEX[M_L][1],1); //斜率

    } //找到爬梯交点为止
    /*找第二个点*/
    if ((i8_UpLpX != -1 && i8_EndLpX == -1) || (flag_l))
    {
      if ((Top_edge_Y[ui8_X] > 5 && Top_edge_Y[ui8_X] <= 55                                                                                                          //
           && abs(Top_edge_Y[ui8_X + 1] - Top_edge_Y[ui8_X]) < 5                                                                                                     // 连续                                                                                                          //
           && abs(Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X - 1]) < 5                                                                                                     // 跳变
           && Top_edge_Y[ui8_X] <= Top_edge_Y[ui8_X + 2]                                                                                                             // 递加                                                                                                   //
           && Top_edge_Y[ui8_X] <= Top_edge_Y[ui8_X + 3]                                                                                                             //                                                                                                    //
           && (GetSlope2(ui8_X, Top_edge_Y[ui8_X], ui8_X - 3, Top_edge_Y[ui8_X - 3]) + GetSlope2(ui8_X + 3, Top_edge_Y[ui8_X + 3], ui8_X, Top_edge_Y[ui8_X])) >= 1.5 //拐点                                                                                   //
           && (GetSlope2(ui8_X, Top_edge_Y[ui8_X], ui8_X - 3, Top_edge_Y[ui8_X - 3]) + GetSlope2(ui8_X + 3, Top_edge_Y[ui8_X + 3], ui8_X, Top_edge_Y[ui8_X])) <= 5.0 //拐点
           ))                                                                                                                                                        //垂直上升长度过短省去

      {
        ui8_EndLpY = Top_edge_Y[ui8_X]; //找到第二个拐点
        i8_EndLpX = ui8_X;
        G_point[M_L][2] = i8_EndLpX;
        G_point[M_L][3] = ui8_EndLpY;
      }

      if (flag_l == 0 && abs(ui8_X - G_point[M_L][0]) > 25)
        break; //相距太远
    }
    if (i8_EndLpX != -1 && flag_l && G_point[M_L][2] > 5 && G_point[M_L][2] < 90 && G_point[M_L][3] != 0 && G_point[M_L][0] == 0) //第二点反找第一点
    {
      i8_UpLpX = ((0 - G_point[M_L][3]) * GetSlope(G_point[M_L][2] + 5, Top_edge_Y[G_point[M_L][2] + 5], G_point[M_L][2], G_point[M_L][3]) + G_point[M_L][2]);
      ui8_UpLpY = 0;
      G_point[M_L][0] = i8_UpLpX;
      G_point[M_L][1] = ui8_UpLpY;
    }
    if (i8_UpLpX != -1 && i8_EndLpX != -1
        // && G_point[M_L][0] != 0 // x!=0
        //     && G_point[M_L][3] > 20                                   // Y>20
        //     && abs(G_point[M_L][0] - G_point[M_L][2]) < 30            //距离不能太远
    )
    {
      if (G_point[M_L][0] != 0                                            // x!=0
          && (G_point[M_L][0] <= G_point[M_L][2]) && G_point[M_L][3] > 20 // Y>20
          && abs(G_point[M_L][0] - G_point[M_L][2]) < 30                  //距离不能太远

          && (G_point[M_L][0] <= G_point[M_R][0]) && (G_point[M_L][2] <= G_point[M_R][2]))
      {
        test_G[M_L][0] = G_point[M_L][0];
        test_G[M_L][1] = G_point[M_L][1];
        test_G[M_L][2] = G_point[M_L][2];
        test_G[M_L][3] = G_point[M_L][3];
        if (G_point[M_L][3] < 55&&abs(error_xunxian)<40)
          Fill_line_image(G_point[M_L][0], G_point[M_L][1], G_point[M_L][2], G_point[M_L][3]); //连线

        i8_UpLpX = -1;
        i8_EndLpX = -1;
        break;
      }
      else
      {
        if (Top_edge_Y[test_G[M_L][2]] < 55&&abs(error_xunxian)<40)
          Fill_line_image(test_G[M_L][0], test_G[M_L][1], test_G[M_L][2], Top_edge_Y[test_G[M_L][2]]); //连线
        i8_UpLpX = -1;
        i8_EndLpX = -1;
        // break;
      }
    }

    if (i8_UpLpX == -1)
    {
      G_point[M_L][0] = 0;
      G_point[M_L][1] = 0;
    }
    if (i8_EndLpX == -1)
    {
      G_point[M_L][2] = 0;
      G_point[M_L][3] = 0;
    }
  }
  //右补

  if (DI.IEX[M_L][11] < 2 && DI.IEX[M_L][12] < 2 && DI.IEX[M_L][13] < 2 && DI.IEX[M_L][14] < 2)
  {
    flag_r = 1;
    // flag_xxx=1;
  }
  else
  {
    flag_r = 0;
    // flag_xxx=0;
  }
  for (uint8 ui8_X = 92; ui8_X > 0; ui8_X--) //从右往左
  {
    ////////////////////////////////////////
    /*第一个点*/
    if (
        i8_UpRpX == -1 //
        && Top_edge_Y[ui8_X] > 2
        // && GetSlope2(ui8_X, DI.Top_edge_Y[ui8_X], ui8_X, ui8_Y - 3) * GetSlope2(DI.IEX[M_R][ui8_Y], ui8_Y, DI.IEX[M_R][ui8_Y + 3], ui8_Y + 3) < 0 //拐点                                                                                   //
        && (abs(Top_edge_Y[ui8_X - 1] - Top_edge_Y[ui8_X]) > 10) //大跳变
        && (Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X + 1]) >= 0      //连线                                                                      //
        && (Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X + 1]) <= 5      //                                                                           //
        && Top_edge_Y[ui8_X] <= 45                               //不远
        // && ui8_X>=70
        ) //第一个拐点不应太靠后
    {
      ui8_UpRpY = Top_edge_Y[ui8_X]; //找到第一个拐点
      i8_UpRpX = ui8_X;
      G_point[M_R][0] = i8_UpRpX;
      G_point[M_R][1] = ui8_UpRpY;
      // k_r = GetSlope2(ui8_X, DI.Top_edge_Y[ui8_X], ui8_X+3, DI.Top_edge_Y[ui8_X+3]); //斜率
    }
    /**/

    /*第二个点*/
    if ((i8_UpRpX != -1 && i8_EndRpX == -1) || (flag_r)) //找第二个远点
    {
      if ((Top_edge_Y[ui8_X] > 5 && Top_edge_Y[ui8_X] <= 55      //   范围  
           && ui8_X<75                                                                                                                                 //
           && abs(Top_edge_Y[ui8_X] - Top_edge_Y[ui8_X - 1]) < 5 // 连续                                                                                                         //
           && abs(Top_edge_Y[ui8_X + 1] - Top_edge_Y[ui8_X]) < 5 //                                                                                                         //
           && Top_edge_Y[ui8_X] <= Top_edge_Y[ui8_X - 2]         // 递加                                                                                                   //
           && Top_edge_Y[ui8_X] <= Top_edge_Y[ui8_X - 3]         //

          &&(Top_edge_Y[ui8_X - 3]-Top_edge_Y[ui8_X])<10
           &&(GetSlope2(G_point[M_R][2], Top_edge_Y[G_point[M_R][2]], G_point[M_R][2] - 3, Top_edge_Y[G_point[M_R][2] - 3]) - GetSlope2(G_point[M_R][2] + 3, Top_edge_Y[G_point[M_R][2] + 3], G_point[M_R][2], Top_edge_Y[G_point[M_R][2]]))<=-0.5
           //  && abs(k_r - GetSlope2(ui8_X-3, DI.Top_edge_Y[ui8_X-3], ui8_X, DI.Top_edge_Y[ui8_X])) < 1 //
           // && abs(GetSlope2(ui8_X-3, DI.Top_edge_Y[ui8_X-3], ui8_X, DI.Top_edge_Y[ui8_X]))>1
           && (GetSlope2(ui8_X, Top_edge_Y[ui8_X], ui8_X - 3, Top_edge_Y[ui8_X - 3]) + GetSlope2(ui8_X + 3, Top_edge_Y[ui8_X + 3], ui8_X, Top_edge_Y[ui8_X])) >= -5.0 //拐点                                                                                   //
           && (GetSlope2(ui8_X, Top_edge_Y[ui8_X], ui8_X - 3, Top_edge_Y[ui8_X - 3]) + GetSlope2(ui8_X + 3, Top_edge_Y[ui8_X + 3], ui8_X, Top_edge_Y[ui8_X])) <= -1.5 //拐点                                                                                                                                                                         //  && ui8_Y <= 55                                                                            //
           ))                                                                                                                                                         //垂直上升长度过短省去
      {
        ui8_EndRpY = Top_edge_Y[ui8_X]; //找到第二个拐点
        i8_EndRpX = ui8_X;
        G_point[M_R][2] = i8_EndRpX;
        G_point[M_R][3] = ui8_EndRpY;
      }
      if (flag_r == 0 && abs(G_point[M_R][0] - ui8_X) > 25)
        break; //相距太远
    }
    if (i8_EndRpX != -1 && flag_r && G_point[M_R][2] > 5 //
        && G_point[M_R][2] < 90                          //
        && G_point[M_R][3] != 0 && G_point[M_R][0] == 0) //第二点反找第一点
    {
      i8_UpRpX = ((0 - G_point[M_R][3]) * GetSlope(G_point[M_R][2] - 5, Top_edge_Y[G_point[M_R][2] - 5], G_point[M_R][2], G_point[M_R][3]) + G_point[M_R][2]);
      ui8_UpRpY = 0;
      G_point[M_R][0] = i8_UpRpX;
      G_point[M_R][1] = ui8_UpRpY;
    }
    /**/
    if (i8_UpRpX != -1 && i8_EndRpX != -1
        // && G_point[M_R][0] != 0 && G_point[M_R][3] > 20 && abs(G_point[M_R][0] - G_point[M_R][2]) < 30
    )
    {
      if (G_point[M_R][0] != 0 && G_point[M_R][3] > 20 //
          && (G_point[M_R][0] >= G_point[M_R][2])      //
          && abs(G_point[M_R][0] - G_point[M_R][2]) < 30

          && (G_point[M_L][0] <= G_point[M_R][0]) && (G_point[M_L][2] <= G_point[M_R][2]))
      {
        test_G[M_R][0] = G_point[M_R][0];
        test_G[M_R][1] = G_point[M_R][1];
        test_G[M_R][2] = G_point[M_R][2];
        test_G[M_R][3] = G_point[M_R][3];
        if (
          // G_point[M_R][3] < 55&&G_point[M_R][2] < 80&&
          abs(error_xunxian)<40)
          Fill_line_image(G_point[M_R][0], G_point[M_R][1], G_point[M_R][2], G_point[M_R][3]); //连线
        // Fill_line_image(G_point[M_R][2], G_point[M_R][3], G_point[M_R][0], G_point[M_R][1]); //连线
        i8_UpRpX = -1;
        i8_EndRpX = -1;
        break;
      }
      else
      {
        if (
          // test_G[M_R][3] < 55&&test_G[M_R][2] < 80&&
        abs(error_xunxian)<40)
          Fill_line_image(test_G[M_R][0], test_G[M_R][1], test_G[M_R][2], Top_edge_Y[test_G[M_R][2]]); //连线
        i8_UpRpX = -1;
        i8_EndRpX = -1;
        // break;
      }
    }

    if (i8_UpRpX == -1)
    {
      G_point[M_R][0] = 0;
      G_point[M_R][1] = 0;
    }
    if (i8_EndRpX == -1)
    {
      G_point[M_R][2] = 0;
      G_point[M_R][3] = 0;
    }
  }
  if (DI.Length - DI.LengthCheku < 100)
  {
    
  }
}
/********************************************************
 *@函数名: 获取电磁偏差
 *@入口参数:电磁初始值
 *@函数功能: none
 *@Date: 2022-06-25 00:13:31
 ********************************************************/

uint16 Before_Get[5][3] = {0}; //之前三次的电感

void Get_Elec_err()
{

  for (int i = 0; i < 2; i++)
  {
    Before_Get[0][i] = Before_Get[0][i + 1];
    Before_Get[1][i] = Before_Get[1][i + 1];
    Before_Get[2][i] = Before_Get[2][i + 1];
    Before_Get[3][i] = Before_Get[3][i + 1];
    Before_Get[4][i] = Before_Get[4][i + 1];
  }

  Before_Get[0][2] = GET_LEFT();
  Before_Get[1][2] = GET_MID();
  Before_Get[2][2] = GET_RIGHT();
  Before_Get[3][2] = GET_V_LEFT();
  Before_Get[4][2] = GET_V_RIGHT();

  DI.AD_L = (uint16)(Before_Get[0][0] * 0.2 + Before_Get[0][1] * 0.3 + Before_Get[0][2] * 0.5);
  DI.AD_M = (uint16)(Before_Get[1][0] * 0.2 + Before_Get[1][1] * 0.3 + Before_Get[1][2] * 0.5);
  DI.AD_R = (uint16)(Before_Get[2][0] * 0.2 + Before_Get[2][1] * 0.3 + Before_Get[2][2] * 0.5);
  DI.AD_VL = (uint16)(Before_Get[3][0] * 0.2 + Before_Get[3][1] * 0.3 + Before_Get[3][2] * 0.5);
  DI.AD_VR = (uint16)(Before_Get[4][0] * 0.2 + Before_Get[4][1] * 0.3 + Before_Get[4][2] * 0.5);

  if (DI.AD_M < 100)
    DI.AD_err = 0;
  else
    DI.AD_err = ((DI.AD_R - DI.AD_L) * 1.0 / (DI.AD_R + DI.AD_L + DI.AD_M)) * 100; //差比和 归一化-60-60
}

/********************************************************
函数名：赛道补线函数(对图像操作）
入口参数:L_x 0-63 L_y 0-93
********************************************************/
void Fill_line_image(int8 L_x, int8 L_y, uint8 R_x, uint8 R_y)
{
  float dx = 0; //增长因子
  uint8 count = 0;
  uint8 j_before = 0;
  uint8 j_before1 = 0;
  if (L_x > 93)
    L_x = 93;
  if (R_x > 93)
    R_x = 93;
  if (L_y > 63)
    L_y = 63;
  if (R_y > 63)
    R_y = 63;
  if (L_x < 0)
    L_x = 0;
  if (R_x < 0)
    R_x = 0;
  if (L_y < 0)
    L_y = 0;
  if (R_y < 0)
    R_y = 0;

  if (L_y > R_y) //左边远,则补右边线
  {
    image[63 - R_y][R_x] = 0;
    dx = (R_x - L_x) * 1.0 / (L_y - R_y);
    for (uint8 i = R_y; i <= L_y; i++)
    {
      uint8 j = (int)(R_x - count * dx);
      image[63 - i][j] = 0;
      if (j_before1 != 0)
      {
        for (uint8 k = j + 1; k <= j_before1; k++)
        {
          image[63 - i][k] = 0;
        }
      }
      count++;
      j_before1 = j;
    }
  }
  else if (L_y < R_y) //右边远,则补左边线
  {
    image[63 - L_y][L_x] = 0;
    dx = (R_x - L_x) * 1.0 / (R_y - L_y);
    for (uint8 i = L_y; i <= R_y; i++)
    {
      uint8 j = (int)(L_x + count * dx);
      image[63 - i][j] = 0;
      if (j_before != 0)
      {
        for (uint8 k = j_before + 1; k <= j; k++)
        {
          image[63 - i][k] = 0;
        }
      }
      count++;
      j_before = j;
    }
  }
}

/********************************************************
函数名：赛道补线函数(对爬梯数组操作）
入口参数:两点坐标
********************************************************/
void Fill_line(int8 L_x, int8 L_y, uint8 R_x, uint8 R_y)
{
  float dx = 0; //增长因子
  uint8 count = 0;
  if (L_y > R_y) //左边远,则补右边线
  {
    DI.Ladder_RBorder[R_y] = R_x;
    dx = (R_x - L_x) * 1.0 / (L_y - R_y);
    for (uint8 i = R_y; i <= L_y; i++)
    {
      uint8 j = (int)(DI.Ladder_RBorder[R_y] - count * dx);
      DI.Ladder_RBorder[i] = j;
      count++;
    }
  }
  else if (L_y < R_y) //右边远,则补左边线
  {
    DI.Ladder_LBorder[L_y] = L_x;
    dx = (R_x - L_x) * 1.0 / (R_y - L_y);
    for (uint8 i = L_y; i <= R_y; i++)
    {
      uint8 j = (int)(DI.Ladder_LBorder[L_y] + count * dx);
      DI.Ladder_LBorder[i] = j;
      count++;
    }
  }
}
void Fill_line_set(int8 L_x, int8 L_y, uint8 R_x, uint8 R_y, uint8 set_y)
{
  float k;
  int x;
  k = GetSlope(L_x, L_y, R_x, R_y);
  x = (int)((set_y - R_y) * k + R_x);
  if (L_x > 0 && R_x > 0 && L_x < 93 && R_x < 93)
    Fill_line(R_x, R_y, x, set_y);
}
//最小二乘法
float Basic_Least_Square(uint8 *a, uint8 length)
{
  uint8 b = a[0];
  float k = 1.0 * (a[length] - a[0]) / length;
  float sum = 0;
  for (uint8 i = 1; i < length; i++)
  {
    sum += 1.0 * (a[i] - k * i - b) * (a[i] - k * i - b);
    if (sum > 500)
      return 500;
  }
  return sum;
}
/********************************************************
函数功能：获取两点的斜率
********************************************************/
float GetSlope(uint8 x1, uint8 y1, uint8 x2, uint8 y2)
{
  if (x1 == x2)
    return 0;
  else
    return (1.0 * x2 - x1) / (float)(y2 - y1);
}

float GetSlope2(uint8 x1, uint8 y1, uint8 x2, uint8 y2)
{
  if (y1 == y2)
    return 0;
  else
    return (1.0 * y2 - y1) / (float)(x2 - x1);
}

/************************************************************************
函数名：十一线竖直扫描
说明：获取每条竖线的最远扫描距离
********************************************************/
void Vertical_scanning()
{
  DI.MaxY[0] = Get_VerticalHeight(1, 0);
  DI.MaxY[1] = Get_VerticalHeight(9, 0);
  DI.MaxY[2] = Get_VerticalHeight(17, 0);
  DI.MaxY[3] = Get_VerticalHeight(27, 0);
  DI.MaxY[4] = Get_VerticalHeight(37, 0);
  DI.MaxY[5] = Get_VerticalHeight(47, 0);
  DI.MaxY[6] = Get_VerticalHeight(57, 0);
  DI.MaxY[7] = Get_VerticalHeight(67, 0);
  DI.MaxY[8] = Get_VerticalHeight(76, 0);
  DI.MaxY[9] = Get_VerticalHeight(84, 0);
  DI.MaxY[10] = Get_VerticalHeight(92, 0);
}

/********************************************************
函数名：获取(黑点)竖直高度
函数功能：竖直扫描获得第一个黑点的纵坐标
说明：从(x0,y0)向上扫描,返回第一个黑点的纵坐标
********************************************************/
uint8 Get_VerticalHeight(uint8 x0, uint8 y0)
{
  uint8 temp_y = 62;
  for (uint8 j = y0; j < 58; j++)
  {
    if (image[62 - j][x0] == 0)
    {
      temp_y = j;
      break;
    }
  }
  return temp_y;
}

/********************************************************
函数名：获取赛道宽度
函数功能： 从一个点向两边扫描获取赛道宽度
说明：
********************************************************/
uint8 Get_LevelWidth(uint8 x0, uint8 y0)
{
  uint8 width = 0;
  int x = x0;
  while (image[62 - y0][x++])
  {
    width++;
  }
  x = x0;
  while (image[62 - y0][x--])
  {
    width++;
  }
  return width;
}
//赛道边界平滑函数
void smooth()
{
  if (DI.isSloop == 0)
    return;
  if (state > 10 && state != 11 && state != 21)
    return;
  DI.flag = DI.set = 0;
  for (uint8 i = 2; i < L_Move.AllMaxY && i < 57; i++)
  {
    if (DI.set == 0) //若未记录起点
    {
      DI.Inflection_x[0] = DI.Ladder_LBorder[i];
      DI.Inflection_y[0] = i;
      DI.set = 1; //起点已经记录
    }
    if (DI.Ladder_LBorder[i] != DI.Ladder_LBorder[i - 2]) //有跳变
    {
      DI.flag++;
    }
    if (DI.flag == 5)
    {
      //      if(Get_LevelWidth(DI.Ladder_LBorder[i]+1,i)>20)
      Fill_line(DI.Inflection_x[0], DI.Inflection_y[0], DI.Ladder_LBorder[i], i); //补拐点线
      DI.flag = 0;
      DI.set = 0;
    }
  }
  DI.flag = DI.set = 0;
  for (uint8 i = 2; i < L_Move.AllMaxY && i < 57; i++)
  {
    if (DI.set == 0) //若未记录起点
    {
      DI.Inflection_x[0] = DI.Ladder_RBorder[i];
      DI.Inflection_y[0] = i;
      DI.set = 1; //起点已经记录
    }
    if (DI.Ladder_RBorder[i] != DI.Ladder_RBorder[i - 2]) //有跳变
    {
      DI.flag++;
    }
    if (DI.flag == 5)
    {
      //      if(Get_LevelWidth(DI.Ladder_RBorder[i]-1,i)>20)
      Fill_line(DI.Ladder_RBorder[i], i, DI.Inflection_x[0], DI.Inflection_y[0]); //补拐点线
      DI.flag = 0;
      DI.set = 0;
    }
  }
}

//函数作用：初始化图像
void ImageInit()
{
  Init_8Neighbour(); // 8近邻初始化
}
//十字判断函数
void Judge_Cross()
{
  if (state > 10)
    return;
  /*
  DI.Ladder_LBorder[0] = DI.Ladder_LBorder[0]<5? 4:DI.Ladder_LBorder[0];
  DI.Ladder_RBorder[0] = DI.Ladder_RBorder[0]>88? 89:DI.Ladder_RBorder[0];
  */
  if (DI.Top_max_Y[1] > 35 && DI.Top_max_Y[92] > 35 && (DI.Ladder_LBorder[0] < 7 || DI.Ladder_RBorder[0] > 86))
  {
    DI.Ladder_LBorder[0] = 10; // 10
    DI.Ladder_RBorder[0] = 83; // 83
    DI.Ladder_MidPoint[0] = (DI.Ladder_LBorder[0] + DI.Ladder_RBorder[0]) / 2;
    state = 4;
  }

  else if ((Top_edge_Y[1] > 20 && Top_edge_Y[92] > 20))
  {
    DI.Ladder_LBorder[0] = 15;
    DI.Ladder_RBorder[0] = 79;
    DI.Ladder_MidPoint[0] = (DI.Ladder_LBorder[0] + DI.Ladder_RBorder[0]) / 2;
    state = 5;
  }
  else
  {
    state = 0;
  }
}
/********************************************************
 *@函数名: 最近距离图像
 *@说明: none
 *@函数功能: none
 *@Date: 2022-05-11 12:54:13
 ********************************************************/
void Fork_Image()
{

  uint8 bottom_flag = 0;
  uint8 max = 5;
  uint8 bottom_lx, bottom_rx, bottomx,bottomx2;
  uint8 bottom_ly, bottom_ry, bottomy,bottomy2;

  for (uint8 x = 0; x < 90; x++) //递增点
  {
    if ((DI.Top_edge_Y[x] < DI.Top_edge_Y[x + 1]) //
    && (DI.Top_edge_Y[x + 1] < DI.Top_edge_Y[x + 2])//
    && (DI.Top_edge_Y[x + 2] < DI.Top_edge_Y[x + 3]) //
    && DI.Top_edge_Y[x] < 10) //递增点
    {
      corner_Lx = x;
      break;
    }
    if (abs(DI.Top_edge_Y[x] - DI.Top_edge_Y[x - 1]) < max //
    && abs(DI.Top_edge_Y[x + 1] - DI.Top_edge_Y[x]) > max //
    && DI.Top_edge_Y[x] < 10)
    {
      corner_Lx = x;
      break;
    }
  }
  for (uint8 x = 90; x > 0; x--)
  {
    if ((DI.Top_edge_Y[x] < DI.Top_edge_Y[x - 1]) //
    && (DI.Top_edge_Y[x - 1] < DI.Top_edge_Y[x - 2])//
     && (DI.Top_edge_Y[x - 2] < DI.Top_edge_Y[x - 3]) //
     && DI.Top_edge_Y[x] < 10) //递增点
    {
      corner_Rx = x;
      break;
    }
    if (abs(DI.Top_edge_Y[x] - DI.Top_edge_Y[x + 1]) < max //
    && abs(DI.Top_edge_Y[x - 1] - DI.Top_edge_Y[x]) > max //
    && DI.Top_edge_Y[x] < 10)//
    {
      corner_Rx = x;
      break;
    }
  }

  for (uint8 i = 10; i < 94 - 10; i++)
  {
    if ((DI.Top_edge_Y[i - 3] >= DI.Top_edge_Y[i]) //递减
        && (DI.Top_edge_Y[i] >= DI.Top_edge_Y[i + 3]) //递减
        && ((DI.Top_edge_Y[i - 3] - DI.Top_edge_Y[i]) < max)//连续
         && ((DI.Top_edge_Y[i] - DI.Top_edge_Y[i + 3]) < max) //连续
         && DI.Top_edge_Y[i] > 10)//不太近
    {
      //找到第一个点
      bottom_lx = i;
      bottom_ly = DI.Top_edge_Y[i];
      bottom_flag = 1;
      break;
    }
  }

  if (bottom_flag == 1)
  {
    bottomy = bottom_ly;
    bottomy2 = bottom_ly;
    //找最低点
    for (uint8 i = bottom_lx; i < 94 - 10; i++)
    {
      if (!((abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i + 3]) < max) && (abs(DI.Top_edge_Y[i] - DI.Top_edge_Y[i - 3]) < max))) //左右存在不连续跳出
      {
        break;
      }
      if (DI.Top_edge_Y[i] < bottomy)//记录最近点
      // if (abs(GetSlope2(i-10, DI.Top_edge_Y[i-10], i-5, DI.Top_edge_Y[i-5])-GetSlope2(i-5, DI.Top_edge_Y[i-5], i, DI.Top_edge_Y[i]))>=1)
      {
        bottomx = i;
        bottomy = DI.Top_edge_Y[i];
      }
      if (DI.Top_edge_Y[i] <= bottomy2)//记录最近点
      // if (abs(GetSlope2(i-10, DI.Top_edge_Y[i-10], i-5, DI.Top_edge_Y[i-5])-GetSlope2(i-5, DI.Top_edge_Y[i-5], i, DI.Top_edge_Y[i]))>=1)
      {
        bottomx2 = i;
        bottomy2 = DI.Top_edge_Y[i];
      }
      bottom_rx = i;
      bottom_ry = DI.Top_edge_Y[i];
    }

    if (bottom_lx < bottomx && bottom_rx > bottomx)
    {
      bottomx = (uint8)(bottomx+bottomx2)/2;
      fork_L_x = bottom_lx;
      bottom_pointX = bottomx;
      fork_R_x = bottom_rx;
      fork_L_y = bottom_ly;
      bottom_pointY = bottomy;
      fork_R_y = bottom_ry;
      fork_L_k = GetSlope2(bottom_lx, bottomx, bottom_ly, bottomy);
      fork_R_k = GetSlope2(bottom_rx, bottomx, bottom_ry, bottomy);
    }
    else //无效点
    {
      fork_L_x = 94 / 2 - 1;
      bottom_pointX = 94 / 2 - 1;
      fork_R_x = 94 / 2 - 1;
      fork_L_y = DI.Top_edge_Y[94 / 2 - 1];
      bottom_pointY = DI.Top_edge_Y[94 / 2 - 1];
      fork_R_y = DI.Top_edge_Y[94 / 2 - 1];
      fork_L_k = 0;
      fork_R_k = 0;

      // fork_L_x = bottom_lx;
      // fork_R_x = bottom_rx;
      // fork_L_y = bottom_ly;
      // fork_R_y = bottom_ry;
      // bottom_pointX = (int)(fork_L_x+fork_R_x)/2;
      // bottom_pointY = DI.Top_edge_Y[bottom_pointX];

      // fork_L_k = GetSlope2(bottom_lx, bottomx, bottom_ly, bottomy);
      // fork_R_k = GetSlope2(bottom_rx, bottomx, bottom_ry, bottomy);
    }
  }
}
void Fit_Top_edge_Y()
{
  for(uint8 i=0;i<94;i++)
  {
    for(uint8 j=1;j<64;j++)
    {
      if(image[63-j][i]==0)
      {
        Top_edge_Y[i]=j;
        break;
      }
    }
  }
}
