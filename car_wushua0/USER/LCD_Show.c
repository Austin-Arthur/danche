/*
 * LCD_Show.c
 *
 *  Created on: 2021年12月31日
 *      Author: 11609
 */
#include"LCD_Show.h"
void ShowPath()//显示规划路径图像
{
  for(uint8 i=0;i<64;i++)
    for(uint8 j=0;j<94;j++)
      Show_Data[i][j] = 0;
  for(uint8 i=0;i<L_Move.AllMaxY;i++)
  {
    Show_Data[63-i][DI.Ladder_LBorder[i]] = 1 ;
    Show_Data[63-i][DI.Ladder_RBorder[i]] = 1 ;
    Show_Data[63-i][DI.Ladder_MidPoint[i]] = 1 ;
  }
  LCD_MT9V032(Show_Data);
}
void ShowPathOnLine()//显示规划路径图像
{
  for(uint8 i=0;i<64;i++)
    for(uint8 j=0;j<94;j++)
      Show_Data[i][j] = 0;

  for(uint8 i=0;i<L_Move.AllMaxY;i++)
  {
    Show_Data[63-i][DI.Ladder_LBorder[i]] = 1 ;
    Show_Data[63-i][DI.Ladder_RBorder[i]] = 1 ;
    Show_Data[63-i][DI.Ladder_MidPoint[i]] = 1 ;
  }

  ZW_Send_Image(Show_Data);
}

void Show8Path()//显示8近邻图像
{
  for(uint8 i=0;i<64;i++)
    for(uint8 j=0;j<94;j++)
      Show_Data[i][j] = 0;
  for(uint8 i=0;i<DI.top_Y;i++)
  {
    Show_Data[63-i][DI.IEX[M_L][i]] = 1 ;
    Show_Data[63-i][DI.IEX[M_R][i]] = 1 ; //内边界
    if(DI.OEX[M_L][i]<93)
      Show_Data[63-i][DI.OEX[M_L][i]] = 1 ; //外边界
    if(DI.OEX[M_R][i]>0)
      Show_Data[63-i][DI.OEX[M_R][i]] = 1 ;
    for(uint8 j=0;j<94;j++)
    {
      if(DI.MEX[M_L][i][j]<93)
        Show_Data[63-i][DI.MEX[M_L][i][j]] = 1 ;//其余边界
      if(DI.MEX[M_R][i][j]>0)
        Show_Data[63-i][DI.MEX[M_R][i][j]] = 1 ;
    }
  }
  LCD_MT9V032(Show_Data);
}

void Show8Path0()//显示内边界
{
  for(uint8 i=0;i<64;i++)
    for(uint8 j=0;j<94;j++)
      Show_Data[i][j] = 0;
  for(uint8 i=0;i<DI.top_Y;i++)
  {
    Show_Data[63-i][DI.IEX[M_L][i]] = 1 ;
    Show_Data[63-i][DI.IEX[M_R][i]] = 1 ; //内边界
  }

//  for(uint8 i=0;i<94;i++)
//  {
//      Show_Data[63-G_point[M_L][1]][i] = 1 ;
//      Show_Data[63-G_point[M_L][3]][i] = 1 ;
//      Show_Data[63-G_point[M_R][1]][i] = 1 ;
//      Show_Data[63-G_point[M_R][3]][i] = 1 ;
//  }
  for(uint8 j=0;j<64;j++)
  {
//      Show_Data[63-j][fork_L_x]=1;
//      Show_Data[63-j][fork_R_x]=1;
//      Show_Data[63-j][bottom_pointX]=1;
//      Show_Data[63-j][corner_Lx]=1;
//      Show_Data[63-j][corner_Rx]=1;
//      Show_Data[63-j][70]=1;
//      Show_Data[63-j][DI.Ladder_RBorder[0]]=1;
  }
  LCD_MT9V032(Show_Data);
}
void Show8Path1()//显示外边界
{
  for(uint8 i=0;i<64;i++)
    for(uint8 j=0;j<94;j++)
      Show_Data[i][j] = 0;
  for(uint8 i=0;i<94;i++)
  {
//    if(DI.OEX[M_L][i]<93)
//      Show_Data[63-i][DI.OEX[M_L][i]] = 1 ; //外边界
//    if(DI.OEX[M_R][i]>0)
//      Show_Data[63-i][DI.OEX[M_R][i]] = 1 ;


      Show_Data[63-Top_edge_Y[i]][i]=1;
//      Show_Data[63-DI.Top_edge_Y[i]][i]=1;
//      Show_Data[63-DI.Top_max_Y[i]][i]=1;
//      Show_Data[63-Dif_85][i]=1;

//      Show_Data[63-10][i]=1;


  }

  for(uint8 i=0;i<64;i++)
  {
//      Show_Data[63-i][G_point[M_L][0]] = 1 ;
//      Show_Data[63-i][G_point[M_L][2]] = 1 ;
//      Show_Data[63-i][G_point[M_R][0]] = 1 ;
//      Show_Data[63-i][G_point[M_R][2]] = 1 ;

//      Show_Data[63-i][Z_point[M_R][0]] = 1 ;

  }


  for(uint8 j=0;j<64;j++)
  {
//      Show_Data[63-j][fork_L_x]=1;
//      Show_Data[63-j][fork_R_x]=1;
//      Show_Data[63-j][bottom_pointX]=1;
//      Show_Data[63-j][corner_Lx]=1;
//      Show_Data[63-j][corner_Rx]=1;
//      Show_Data[63-j][x_82]=1;
//          Show_Data[63-j][btnF1]=1;
//          Show_Data[63-j][btnF2]=1;
//          Show_Data[63-j][BTN]=1;
//                Show_Data[63-j][x_82]=1;
//                Show_Data[63-j][btn_82]=1;
      Show_Data[63-j][break_p1]=1;
      Show_Data[63-j][break_p2]=1;
      Show_Data[63-j][break_p3]=1;
//      Show_Data[63-j][DI.Ladder_RBorder[0]]=1;
  }



  LCD_MT9V032(Show_Data);
}
