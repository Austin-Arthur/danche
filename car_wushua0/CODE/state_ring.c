/*
 * state_ring.c
 *
 *  Created on: 2022年3月8日
 *      Author: 11609
 */
#include "state_ring.h"
extern float Angle_Zero;
void RingInPatchLine(uint8 x,uint8 y,int8 Str[80]);
void RingOutPatchLine(uint8 x,uint8 y,int8 Str[80]);
void RingInPatchLine1(uint8 x,uint8 y,int8 Str[94]);

void RingIn(uint8 x,uint8 y,float dy);
uint8 GetR(uint8 x,uint8 y);
boolean isCircleOut();
uint8 Basic_is_Line_Saltus(uint8* arr,uint8 length,uint8 Max_error);
uint8 Manhattan(uint8 x,uint8 y,uint8 Dir);
boolean RingOutStageJudge();
uint8 ringSize[6];//环的大小，2为大环，1为中环，0为小环
uint8 ringCnt=0;
uint8 circleLx,circleLy,circleLx_temp;
uint8 circleLx1,circleLy1;
uint8 flag_cir;
int8 RingIn_50[94]=
// {
//  //0 1  2  3  4  5  6  7  8  9
//   42,42,42,42,42,42,42,42,42,42,//0
//   42,42,42,42,42,42,41,41,41,41,//1
//   41,41,40,40,40,40,40,39,39,39,//2
//   39,38,38,37,37,36,36,36,35,35,//3
//   34,34,33,33,32,32,31,30,29,29,//4
//   28,28,27,27,26,25,24,23,22,21,//5
//   20,19,19,18,17,16,15,14,13,12,//6
//   11,10,9,8,7,6,5,4,3,2,        //7
//   1,0,-1,-2,-3,-4,-5,-6,-7,-8,  //8
//   -9,-10,-11,-12                //9
// };
  {
   //0 1  2  3  4  5  6  7  8  9
    42,42,42,42,42,42,42,42,42,42,//0
    42,42,42,42,42,42,41,41,41,41,//1
    41,41,40,40,40,40,40,40,39,39,//2
    39,39,38,38,37,37,36,36,35,35,//3
    34,34,33,33,32,32,31,30,29,29,//4
    28,28,27,27,26,25,24,23,22,21,//5
    20,19,19,18,17,16,15,14,13,12,//6
    11,10,9,8,7,6,5,4,3,2,        //7
    1,0,-1,-2,-3,-4,-5,-6,-7,-8,  //8
    -9,-10,-11,-12                //9
  };
int8 RingIn_60[94]={
  //0 1  2  3  4  5  6  7  8  9
    47,47,47,47,47,47,47,47,46,46,//0
    46,46,46,46,46,46,45,45,45,45,//1
    45,45,44,44,44,43,43,43,43,42,//2
    42,42,41,41,40,40,40,40,39,39,//3
    38,37,37,37,36,35,35,34,34,33,//4
    32,32,31,30,30,29,29,28,27,26,//5
    26,25,24,23,22,21,20,20,19,18,//6
    17,16,15,14,13,12,11,10,9,8,//7
    7,6,5,4,3,2,1,0,-1,-2,//8
    -3,-4,-5,-6
};
int8 RingIn_80[94]={
  //0  1  2  3  4  5  6  7  8  9
  50,50,50,50,50,50,49,49,49,49,//0
  49,49,48,48,48,48,48,47,47,47,//1
  46,46,46,45,45,45,44,44,43,43,//2
  42,41,41,41,40,39,39,38,38,37,//3
  36,36,35,34,34,33,32,31,31,30,//4
  30,29,29,28,27,26,25,24,23,22,//5
  21,20,19,18,17,16,15,14,13,12,//6
  11,10,9,8,7,6,5,4,3,2,//7
  1,0,-1,-2,-3,-4,-5,-6,-7,-8,
  -9,-10,-11,-12
};

//左边圆环
void state_11()
{
  circleLx = 100;
  uint8 max=5;
//  if((DI.Top_max_Y[0]!=63&&DI.Top_max_Y[4]!=63)||(DI.Top_max_Y[4]!=63&&DI.Top_max_Y[8]!=63))
//  {
      for(uint8 i = 2;i<DI.top_Y-2;i++)//找水平跳变最大点
      {
          if(DI.IEX[M_L][i]-DI.IEX[M_L][i-1]>max)
          {
              max = DI.IEX[M_L][i]-DI.IEX[M_L][i-1];
              circleLx = DI.IEX[M_L][i];
              circleLy = i;
              if(max>8) break;
          }
      }
      flag_cir = 1;
//  }
  //if(Angle<-1&&(((DI.Top_max_Y[0]==63&&DI.Top_max_Y[4]==63)||(DI.Top_max_Y[4]==63&&DI.Top_max_Y[8]==63))||circleLx==86))//左倾
  if(Angle<-1&&circleLx==100)//左倾
   {
       for(uint8 i = 2;i<DI.top_Y-2;i++)
       {
           if(DI.IEX[M_R][i-1]-DI.IEX[M_R][i]>max)
           {
              max = DI.IEX[M_R][i-1]-DI.IEX[M_R][i];
              circleLx = DI.IEX[M_R][i];
              circleLy = i;
              if(max>8) break;
           }
       }
       flag_cir = 2;
   }
  circleLx = circleLx>1? circleLx-1:0;
  if(ringSize[ringCnt%DI.RingSumCnt]==0)//小圆
   RingInPatchLine(circleLx,circleLy,RingIn_50);//补线
  else if(ringSize[ringCnt%DI.RingSumCnt]==1)//中圆
    RingInPatchLine(circleLx,circleLy,RingIn_60);//补线
  else//大环
    RingInPatchLine(circleLx,circleLy,RingIn_80);//补线

  if(DI.Ladder_LBorder[L_Move.AllMaxY]<30&&DI.Ladder_RBorder[L_Move.AllMaxY]<45
     &&DI.Ladder_RBorder[L_Move.AllMaxY]-DI.Ladder_LBorder[L_Move.AllMaxY]<=30
        &&DI.IEX[M_L][L_Move.AllMaxY-1]<30&& DI.IEX[M_R][L_Move.AllMaxY-1]<=45
          &&L_Move.AllMaxY>10
            &&DI.Ladder_RBorder[0]<90
            &&circleLx==99)

  {//左边检测
    state = 12;//环内
    DI.LengthRing  = DI.tempLength = DI.Length;
    state_12();
    return ;
  }
}
//环内
void state_12()
{
  if(isCircleOut()==TRUE&&DI.Length-DI.LengthRing>140)//50
  {
    DI.LengthRing  = DI.tempLength = DI.Length;
    state = 13;
    circleLx_temp = 80;
    state_13();
    return ;
  }
}

//出环第一阶段
void state_13()
{
  circleLx=0;
  for(uint8 i = 5;i<L_Move.AllMaxY-3;i++)
  {
    if(DI.IEX[M_R][i]<DI.IEX[M_R][i+1]&&DI.Ladder_RBorder[i]==DI.Ladder_RBorder[i+3])
    {//右边边界向右拐
      while(DI.IEX[M_R][i]==DI.IEX[M_R][i-1]&&i>7)//找最低点
        i--;
      circleLx = DI.IEX[M_R][i];
      circleLy = i;
      if(circleLx_temp>circleLx&&circleLx>57) circleLx_temp = circleLx;
      if((i<10||DI.IEX[M_R][i]>80||DI.MaxY[10]>20))//拐点将从两边消失
//      if(circleLx==0)//拐点将从两边消失
      {
        state = 14;
        state_14();
        return ;
      }
      break;
    }
  }
/*
  if(ringSize[ringCnt%DI.RingSumCnt]==0)//小圆
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_50);//补线
    RingInPatchLine(7,DI.Top_max_Y[7],RingIn_50);//补线
  }
  else if(ringSize[ringCnt%DI.RingSumCnt]==1)//中圆
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_60);//补线
    RingInPatchLine(7,DI.Top_max_Y[7],RingIn_60);//补线
  }
  else//大圆
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_80);//补线
    RingInPatchLine(7,DI.Top_max_Y[7],RingIn_80);//补线
  }
*/
//  if(DI.IEX[M_L][62]>10)
//  {
//      Fill_line_image(DI.IEX[M_L][62],DI.Top_max_Y[DI.IEX[M_L][62]],circleLx,circleLy);
//  }
//  else
//  {
//      Fill_line_image(DI.IEX[M_R][62],DI.Top_max_Y[DI.IEX[M_R][62]],circleLx,circleLy);
//  }


  for (uint8 x = 1; x < 90; x++) //递增点
  {
    if (DI.Top_edge_Y[x]<=62 ) //递增点
    {
        circleLx1 = (int)(x/2);
        circleLy1 = DI.Top_edge_Y[x];
        break;
    }
  }
    Fill_line_image(circleLx1,circleLy1,circleLx,circleLy);

//  Fill_line_image(1,DI.Top_max_Y[1],circleLx,circleLy);
//  if(DI.IEX[M_R][62]>60)
//  {
//      Fill_line_image(1,DI.Top_max_Y[1],circleLx,circleLy);
//  }
//  else
//  {
//      Fill_line_image(DI.IEX[M_R][62],DI.Top_max_Y[DI.IEX[M_R][62]],circleLx,circleLy);
//  }

}
//出环第二阶段

void state_14()
{
//  if(DI.Top_edge_Y[92]>20&&DI.Top_edge_Y[91]>20&&DI.Top_edge_Y[90]>20&&DI.Top_edge_Y[89]>20||DI.AD_L+DI.AD_R>360)
  if(DI.Ladder_RBorder[0]>80)
  {
    DI.LengthRing = DI.Length;
    state = 15;
    state_15();
    return ;
  }
/*
  if(ringSize[ringCnt%DI.RingSumCnt]==0)//小圆
  {
     RingOutPatchLine(circleLx,circleLy,RingIn_50);//补线
     RingInPatchLine(circleLx,circleLy,RingIn_50);//补线
     RingInPatchLine(7,DI.Top_max_Y[7],RingIn_50);//补线
  }
  else if(ringSize[ringCnt%DI.RingSumCnt]==1)//中环
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_60);//补线
    RingInPatchLine(circleLx,circleLy,RingIn_60);//补线
    RingInPatchLine(7,DI.Top_max_Y[7],RingIn_60);//补线
  }
  else//大圆
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_80);//补线
    RingInPatchLine(circleLx,circleLy,RingIn_80);//补线
    RingInPatchLine(7,DI.Top_max_Y[7],RingIn_80);//补线
  }
*/
//  if(DI.IEX[M_L][62]>10)
//  {
//      Fill_line_image(DI.IEX[M_L][62],DI.Top_max_Y[DI.IEX[M_L][62]],circleLx+circleLy,0);
//  }
//  else
//  {
//      Fill_line_image(DI.IEX[M_R][62],DI.Top_max_Y[DI.IEX[M_R][62]],circleLx+circleLy,0);
//  }


  for (uint8 x = 1; x < 90; x++) //递增点
  {
    if (DI.Top_edge_Y[x]<=62 ) //递增点
    {
        circleLx1 = (int)(x/2);
        circleLy1 = DI.Top_edge_Y[x];
        break;
    }
  }

  Fill_line_image(circleLx1,circleLy1,circleLx+circleLy,0);

//  Fill_line_image(1,DI.Top_max_Y[1],circleLx+circleLy,0);
//  if(DI.IEX[M_R][62]>60)
//  {
//      Fill_line_image(1,DI.Top_max_Y[1],circleLx+circleLy,0);
//  }
//  else
//  {
//      Fill_line_image(DI.IEX[M_R][62],DI.Top_max_Y[DI.IEX[M_R][62]],circleLx+circleLy,0);
//  }
}

//出环第三阶段
int state_15_temp;
void state_15()
{
    /*
  if(circleLx<59)
    circleLx = 59;
  if(ringSize[ringCnt%DI.RingSumCnt]==0)//小圆
  {
     //RingOutPatchLine(circleLx,circleLy,RingIn_50);//补线
     //RingInPatchLine(circleLx,circleLy,RingIn_50);//补线

     RingInPatchLine(1,DI.Top_max_Y[1],RingIn_50);//补线
     RingInPatchLine_angle(1,DI.Top_max_Y[1],RingIn_50,((Angle-Angle_Zero)*-0.05+1));

  }
  else if(ringSize[ringCnt%DI.RingSumCnt]==1)//中环
  {
    //RingOutPatchLine(circleLx,circleLy,RingIn_60);//补线
    //RingInPatchLine(circleLx,circleLy,RingIn_60);//补线
    RingInPatchLine(1,DI.Top_max_Y[1],RingIn_60);//补线
  }
  else//大圆
  {
    //RingOutPatchLine(circleLx,circleLy,RingIn_80);//补线
    //RingInPatchLine(circleLx,circleLy,RingIn_80);//补线
    RingInPatchLine(1,DI.Top_max_Y[1],RingIn_80);//补线 7
  }

  /*
  if((DI.Top_max_Y[92]+28<DI.Top_max_Y[1]&&DI.Top_max_Y[92]>1)
    ||(DI.Top_max_Y[84]+22<DI.Top_max_Y[10]&&DI.Top_max_Y[84]>1)
      ||(DI.Top_max_Y[74]+16<DI.Top_max_Y[20]&&DI.Top_max_Y[74]>1)
        ||(DI.Top_max_Y[64]+10<DI.Top_max_Y[30]&&DI.Top_max_Y[64]>1)
          ||DI.AD_L+DI.AD_R>360)
          */

    for (uint8 x = 1; x < 90; x++) //递增点
    {
      if (DI.Top_edge_Y[x]<=62 ) //递增点
      {
          circleLx1 = (int)(x/2);
          circleLy1 = DI.Top_edge_Y[x];
          break;
      }
    }

  if(((circleLx+circleLy+(DI.Length-DI.LengthRing)*0.05)<DI.Ladder_RBorder[0]))
  {
//      if(DI.IEX[M_L][62]>10)
//      {
//          Fill_line_image(DI.IEX[M_L][62],DI.Top_max_Y[DI.IEX[M_L][62]],((circleLx+circleLy+(DI.Length-DI.LengthRing))),0);
//      }
//      else
//      {
//          Fill_line_image(DI.IEX[M_R][62],DI.Top_max_Y[DI.IEX[M_R][62]],((circleLx+circleLy+(DI.Length-DI.LengthRing))),0);//92
//      }


//      if(DI.IEX[M_R][62]>60)
//      {
//          Fill_line_image(1,DI.Top_max_Y[1],((circleLx+circleLy+(DI.Length-DI.LengthRing))),0);
//      }
//      else
//      {
//          Fill_line_image(DI.IEX[M_R][62],DI.Top_max_Y[DI.IEX[M_R][62]],((circleLx+circleLy+(DI.Length-DI.LengthRing))),0);
//      }

      Fill_line_image(circleLx1,circleLy1,((circleLx+circleLy+(DI.Length-DI.LengthRing)*0.05)),0);
//      Fill_line_image(1,DI.Top_max_Y[1],((circleLx+circleLy+(DI.Length-DI.LengthRing))),0);
      state_15_temp = DI.Length;
  }
  else
  {
      DI.LengthRing  = DI.tempLength = DI.Length;
      state = 16;
      ringCnt++;
      DI.Lengthfork = DI.Length;
      return ;
  }
      /*
      Fill_line_image(1,DI.Top_max_Y[1],DI.Ladder_RBorder[0],(DI.Length-state_15_temp));

  if(DI.Top_max_Y[92]<=(DI.Length-state_15_temp))
  {
      DI.LengthRing  = DI.tempLength = DI.Length;
      state = 0;
      ringCnt++;
      return ;
  }

*/
/*
  if(DI.Top_max_Y[92]<3||abs(DI.Top_max_Y[10]-DI.Top_max_Y[80]-45)<5)
  {
    if(Basic_is_Line_Saltus(DI.Top_edge_Y+64,20,5)==0)//边缘跳变太大
      return;
    DI.LengthRing  = DI.tempLength = DI.Length;
    state = 0;
    ringCnt++;
    return ;
  }
 */
}
void state_16()
{
    if(DI.Length-DI.LengthRing>20)
    {
        DI.LengthRing  = DI.tempLength = DI.Length;
        state = 17;
        return;
    }
}
/********************************************************
 *@函数名: 
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-08 14:16:07
********************************************************/
//防止再次入环，调整姿态
void state_17()
{
    circleLx = 100;
    uint8 max=5;
  //  if((DI.Top_max_Y[0]!=63&&DI.Top_max_Y[4]!=63)||(DI.Top_max_Y[4]!=63&&DI.Top_max_Y[8]!=63))
  //  {
        for(uint8 i = 2;i<DI.top_Y-2;i++)//找水平跳变最大点
        {
            if(DI.IEX[M_L][i]-DI.IEX[M_L][i-1]>max)
            {
                max = DI.IEX[M_L][i]-DI.IEX[M_L][i-1];
                circleLx = DI.IEX[M_L][i];
                circleLy = i;
                if(max>8) break;
            }
        }
  //  }
    //if(Angle<-1&&(((DI.Top_max_Y[0]==63&&DI.Top_max_Y[4]==63)||(DI.Top_max_Y[4]==63&&DI.Top_max_Y[8]==63))||circleLx==86))//左倾
    if(Angle<-1&&circleLx==100)//左倾
     {
         for(uint8 i = 2;i<DI.top_Y-2;i++)
         {
             if(DI.IEX[M_R][i-1]-DI.IEX[M_R][i]>max)
             {
                max = DI.IEX[M_R][i-1]-DI.IEX[M_R][i];
                circleLx = DI.IEX[M_R][i];
                circleLy = i;
                if(max>8) break;
             }
         }
     }

    if(circleLx<50&&circleLy<55)
    {
       Fill_line_image(circleLx,circleLy,0,0);
       Fill_line_image(circleLx+1,circleLy,0+1,0);
    }

//    if(DI.Ladder_LBorder[L_Move.AllMaxY]<10&&DI.Ladder_RBorder[L_Move.AllMaxY]<20
//       &&DI.Ladder_RBorder[L_Move.AllMaxY]-DI.Ladder_LBorder[L_Move.AllMaxY]<=10
//          &&DI.IEX[M_L][L_Move.AllMaxY-1]<10&& DI.IEX[M_R][L_Move.AllMaxY-1]<=20
//            &&L_Move.AllMaxY>10
//              &&DI.Ladder_RBorder[0]<90
//              &&circleLx==99)
    if(((circleLx>50&&DI.Length-DI.LengthRing>=50&&circleLy<50)||DI.Length-DI.LengthRing>=100)&&abs(Servo_PWM2)<10)
    {//左边检测
      state = 80;//环内
      DI.LengthRing  = DI.tempLength = DI.Length;
      return ;
    }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-08-12 11:34:44
********************************************************/
//右边圆环
void state_21()
{
  circleLx = 0;
  uint8 max = 5;
//  if((DI.Top_max_Y[92]!=63&&DI.Top_max_Y[88]!=63)||(DI.Top_max_Y[88]!=63&&DI.Top_max_Y[84]!=63))
//  {
      for(uint8 i = 2;i<DI.top_Y-2;i++)
      {
          if(DI.IEX[M_R][i-1]-DI.IEX[M_R][i]>max)
              {
                  max = DI.IEX[M_R][i-1]-DI.IEX[M_R][i];
                  circleLx = DI.IEX[M_R][i];
                  circleLy = i;
                  if(max>8) break;
              }
      }
      flag_cir = 1;
// }
// if(Angle>1&&(((DI.Top_max_Y[92]==63&&DI.Top_max_Y[88]==63)||(DI.Top_max_Y[88]==63&&DI.Top_max_Y[84]==63))||circleLx==7))//右倾
if(Angle>1&&circleLx==0)//右倾
  {
      for(uint8 i = 2;i<DI.top_Y-2;i++)
            {
                if(DI.IEX[M_L][i]-DI.IEX[M_L][i-1]>max)
                    {
                        max = DI.IEX[M_L][i]-DI.IEX[M_L][i-1];
                        circleLx = DI.IEX[M_L][i];
                        circleLy = i;
                        if(max>8) break;
                    }
            }
      flag_cir = 2;
  }
/*
  if(Angle<-1&&circleLx==7)//左倾     误判 删去
  {
      for(uint8 i = 48;i<92;i++)
            {
                if(DI.Top_edge_Y[i]-DI.Top_edge_Y[i+1]>max)
                    {
                        max = DI.Top_edge_Y[i]-DI.Top_edge_Y[i+1];
                        circleLx = i;
                        circleLy = DI.Top_edge_Y[i];
                        if(max>8) break;
                    }
            }
      flag_cir = 3;
  }
*/
  circleLx = circleLx<93? circleLx+1:93;//如果小于93 就+1
  Circle[M_R].D_y = circleLy;//1
  Circle[M_R].D_x = circleLx;//0

  if(ringSize[ringCnt%DI.RingSumCnt]==0)//小圆
   RingInPatchLine(circleLx,circleLy,RingIn_50);//补线
  else if(ringSize[ringCnt%DI.RingSumCnt]==1)//中圆
    RingInPatchLine(circleLx,circleLy,RingIn_60);//补线
  else//大环
    RingInPatchLine(circleLx,circleLy,RingIn_80);//补线

  if(DI.Ladder_LBorder[L_Move.AllMaxY]>64&&DI.Ladder_RBorder[L_Move.AllMaxY]>80
     &&DI.Ladder_RBorder[L_Move.AllMaxY]-DI.Ladder_LBorder[L_Move.AllMaxY]<=30
         &&DI.IEX[M_R][L_Move.AllMaxY-1]>64&& DI.IEX[M_L][L_Move.AllMaxY-1]>80
         &&L_Move.AllMaxY>10
         &&DI.Ladder_LBorder[0]>5
         &&circleLx==1)
  {
    state=22;//环内
    DI.LengthRing  = DI.tempLength = DI.Length;
    state_22();
    return ;
  }
}
void state_22()
{
  if(isCircleOut()==TRUE&&DI.Length-DI.LengthRing>140)
  {
    DI.LengthRing  = DI.tempLength = DI.Length;
    state = 23;
    circleLx_temp = 10;
    state_23();
    return ;
  }
}
void state_23()
{
  for(uint8 i = 5;i<L_Move.AllMaxY-3;i++)
  {
    if(DI.IEX[M_L][i]>DI.IEX[M_L][i+1]&&DI.Ladder_LBorder[i]==DI.Ladder_LBorder[i+3])//向左拐
    {
      while(DI.IEX[M_L][i]==DI.IEX[M_L][i-1]&&i>7)
        i--;
      circleLx = DI.IEX[M_L][i];
      circleLy = i;
      if(circleLx_temp<circleLx&&circleLx<37) circleLx_temp = circleLx;
      if(i<10||DI.IEX[M_L][i]<14||DI.MaxY[0]>20)
      {
        state = 24;
        state_24();
        return ;
      }
      break;
    }
  }
  /*
  if(ringSize[ringCnt%DI.RingSumCnt]==0)//小圆
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_50);//补线
    RingInPatchLine(86,DI.Top_max_Y[86],RingIn_50);//补线
  }
  else if(ringSize[ringCnt%DI.RingSumCnt]==1)//中圆
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_60);//补线
    RingInPatchLine(86,DI.Top_max_Y[86],RingIn_60);//补线
  }
  else//大圆
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_80);//补线
    RingInPatchLine(86,DI.Top_max_Y[86],RingIn_80);//补线
  }
  */
  for (uint8 x = 92; x > 10; x--) //递增点
    {
      if (DI.Top_edge_Y[x]<=62 ) //递增点
      {
          circleLx1 = (int)((92+x)/2);
          circleLy1 = DI.Top_edge_Y[(92+x)/2];
          break;
      }
    }

  Fill_line_image(circleLx,circleLy,circleLx1,circleLy1);

//  Fill_line_image(circleLx,circleLy,92,DI.Top_max_Y[92]);
}
void state_24()
{
  //if(DI.Top_edge_Y[1]>20&&DI.Top_edge_Y[2]>20&&DI.Top_edge_Y[3]>20&&DI.Top_edge_Y[4]>20||DI.AD_L+DI.AD_R>360)
  if(DI.Ladder_LBorder[0]<10)//DI.Top_edge_Y 图像第几列的长度
  {
    DI.LengthRing = DI.Length;
    state = 25;
    state_25();
    return ;
  }
  /*
  if(ringSize[ringCnt%DI.RingSumCnt]==0)//小圆
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_50);//补线
    RingInPatchLine(circleLx,circleLy,RingIn_50);//补线
    RingInPatchLine(86,DI.Top_max_Y[86],RingIn_50);//补线
  }
  else if(ringSize[ringCnt%DI.RingSumCnt]==1)//中环
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_60);//补线
    RingInPatchLine(circleLx,circleLy,RingIn_60);//补线
    RingInPatchLine(86,DI.Top_max_Y[86],RingIn_60);//补线
  }
  else//大圆
  {
    RingOutPatchLine(circleLx,circleLy,RingIn_80);//补线
    RingInPatchLine(circleLx,circleLy,RingIn_80);//补线
    RingInPatchLine(86,DI.Top_max_Y[86],RingIn_80);//补线
  }
  */
//  Fill_line_image(circleLx-circleLy,0,92,DI.Top_max_Y[92]);

  for (uint8 x = 92; x > 10; x--) //递增点
    {
      if (DI.Top_edge_Y[x]<=62 ) //递增点
      {
          circleLx1 = (int)((92+x)/2);
          circleLy1 = DI.Top_edge_Y[(92+x)/2];
          break;
      }
    }

   Fill_line_image(circleLx-circleLy,0,circleLx1,circleLy1);

}
/********************************************************
 *@函数名: 
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-09 13:34:48
********************************************************/
int state_25_temp;
void state_25()
{
    /*
  if(circleLx>35)
    circleLx = 35;
  if(ringSize[ringCnt%DI.RingSumCnt]==0)//小圆
  {
    //RingOutPatchLine(circleLx,circleLy,RingIn_50);//补线
    //RingInPatchLine(circleLx,circleLy,RingIn_50);//补线
    RingInPatchLine(92,DI.Top_max_Y[92],RingIn_50);//补线
  }

  else if(ringSize[ringCnt%DI.RingSumCnt]==1)//中环
  {
    //RingOutPatchLine(circleLx,circleLy,RingIn_60);//补线
    //RingInPatchLine(circleLx,circleLy,RingIn_60);//补线
    RingInPatchLine(92,DI.Top_max_Y[92],RingIn_60);//补线
  }
  else//大圆
  {
    //RingOutPatchLine(circleLx,circleLy,RingIn_80);//补线
    //RingInPatchLine(circleLx,circleLy,RingIn_80);//补线
    RingInPatchLine(92,DI.Top_max_Y[92],RingIn_80);//补线
  }
  */
    for (uint8 x = 92; x > 10; x--) //递增点
      {
        if (DI.Top_edge_Y[x]<=62 ) //递增点
        {
            circleLx1 = (int)((92+x)/2);
            circleLy1 = DI.Top_edge_Y[(92+x)/2];
            break;
        }
      }
  /*
  if((DI.Top_max_Y[1]+28<DI.Top_max_Y[92]&&DI.Top_max_Y[1]>1)
    ||(DI.Top_max_Y[10]+22<DI.Top_max_Y[84]&&DI.Top_max_Y[10]>1)
      ||(DI.Top_max_Y[20]+16<DI.Top_max_Y[64]&&DI.Top_max_Y[20]>1)
        ||(DI.Top_max_Y[30]+10<DI.Top_max_Y[54]&&DI.Top_max_Y[30]>1)
          ||DI.AD_L+DI.AD_R>360)
          */
   if(((circleLx-circleLy)-(DI.Length-DI.LengthRing)*0.3)>DI.Ladder_LBorder[0])
   {
       Fill_line_image((circleLx-circleLy-(DI.Length-DI.LengthRing)*0.3),0,circleLx1,circleLy1);


       state_25_temp = DI.Length;
   }
   else
   {
       DI.LengthRing  = DI.tempLength = DI.Length;
       state = 26;
       ringCnt++;
      //  state_26();
       return ;
   }

       /*
       Fill_line_image(0,(DI.Length-state_25_temp),92,DI.Top_max_Y[92]);

   if(DI.Top_max_Y[1]<=(DI.Length-state_25_temp))
   {
     DI.LengthRing  = DI.tempLength = DI.Length;
     state = 0;
     ringCnt++;
     return ;
   }
   */
/*
  if(DI.Top_max_Y[1]<3||abs(DI.Top_max_Y[80]-DI.Top_max_Y[10]-46)<5)
  {
    if(Basic_is_Line_Saltus(DI.Top_edge_Y+10,20,5)==0)//边缘跳变太大或者最远距离太小
      return;//仍处于补线状态
    DI.LengthRing  = DI.tempLength = DI.Length;
    state = 0;
    ringCnt++;
    return ;
  }
  */
}

void state_26()
{
    if(DI.Length-DI.LengthRing>50)
    {
        DI.LengthRing  = DI.tempLength = DI.Length;
        state = 27;
        // state_27();
        return;
    }
}
/********************************************************
 *@函数名:
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-08 14:16:07
********************************************************/
//防止再次入环，调整姿态
void state_27()
{
    circleLx = 0;
     uint8 max = 5;
   //  if((DI.Top_max_Y[92]!=63&&DI.Top_max_Y[88]!=63)||(DI.Top_max_Y[88]!=63&&DI.Top_max_Y[84]!=63))
   //  {
         for(uint8 i = 2;i<DI.top_Y-2;i++)
         {
             if(DI.IEX[M_R][i-1]-DI.IEX[M_R][i]>max)
                 {
                     max = DI.IEX[M_R][i-1]-DI.IEX[M_R][i];
                     circleLx = DI.IEX[M_R][i];
                     circleLy = i;
                     if(max>8) break;
                 }
         }
         flag_cir = 1;
   // }
   // if(Angle>1&&(((DI.Top_max_Y[92]==63&&DI.Top_max_Y[88]==63)||(DI.Top_max_Y[88]==63&&DI.Top_max_Y[84]==63))||circleLx==7))//右倾
   if(Angle>1&&circleLx==0)//右倾
     {
         for(uint8 i = 2;i<DI.top_Y-2;i++)
               {
                   if(DI.IEX[M_L][i]-DI.IEX[M_L][i-1]>max)
                       {
                           max = DI.IEX[M_L][i]-DI.IEX[M_L][i-1];
                           circleLx = DI.IEX[M_L][i];
                           circleLy = i;
                           if(max>8) break;
                       }
               }
         flag_cir = 2;
     }

    if(circleLx>60)
    {
       Fill_line_image(circleLx,circleLy,93,0);
       Fill_line_image(circleLx+1,circleLy,92,0);
    }

//    if(DI.Ladder_LBorder[L_Move.AllMaxY]<10&&DI.Ladder_RBorder[L_Move.AllMaxY]<20
//       &&DI.Ladder_RBorder[L_Move.AllMaxY]-DI.Ladder_LBorder[L_Move.AllMaxY]<=10
//          &&DI.IEX[M_L][L_Move.AllMaxY-1]<10&& DI.IEX[M_R][L_Move.AllMaxY-1]<=20
//            &&L_Move.AllMaxY>10
//              &&DI.Ladder_RBorder[0]<90
//              &&circleLx==99)
    if((circleLx<60&&DI.Length-DI.LengthRing>=50)||DI.Length-DI.LengthRing>=100)
    {//左边检测
      state = 0;//环内
      DI.LengthRing  = DI.tempLength = DI.Length;
      return ;
    }
}
/************************************************************************
函数名：扫线判断出环
************************************************************************/
boolean isCircleOut()
{
  if(state<20 )//左边环岛
  {
    for(uint8 i = 25;i<L_Move.AllMaxY-3;i++)//爬梯最远点
    {
      if(DI.IEX[M_R][i]<DI.IEX[M_R][i+1]&&DI.Ladder_RBorder[i]==DI.Ladder_RBorder[i+4])
      {//右边边界向右拐
        while(DI.IEX[M_R][i]==DI.IEX[M_R][i-1]&&i>7)//找最低点
          i--;
        if(Manhattan(DI.IEX[M_R][i]-1,i,M_R)>15)
        {
          return 1;
        }
        break;
      }
    }
  }
  else
  {
    for(uint8 i = 25;i<L_Move.AllMaxY-3;i++)
    {
      if(DI.IEX[M_L][i]>DI.IEX[M_L][i+1]&&DI.Ladder_LBorder[i]==DI.Ladder_LBorder[i+4])//向左拐
      {
        while(DI.IEX[M_L][i]==DI.IEX[M_L][i-1]&&i>7)
          i--;
        if(Manhattan(DI.IEX[M_L][i]+1,i,M_L)>15)
        {
          return 1;
        }
        break;
      }
    }
  }
  return 0;
}

/************************************************************************
*函数名：入环补线(从上面往下面画弧线)
*参数：拐点坐标
************************************************************************/
void RingInPatchLine1(uint8 x,uint8 y,int8 Str[94])
{
  int8 Dif = 0;
  int8 FinalY = y;
  if(state<20)//左入环  左上往右下画弧线
  {
    Dif=y-Str[x];//相对于（x，y）点的纵坐标的变化
    for(uint8 i=x;i<93;i++)
    {
      int8 temp_y = FinalY;//记录上一个Y
      FinalY=Str[i]+Dif;//慢慢变小
      temp_y = temp_y - FinalY + 1;
      if(FinalY>=0)
      {
        while(temp_y--)
         image[62-FinalY-temp_y][i] = 1;//黑色
      }
      else
        break;
    }
  }
  else //右入环
  {
    Dif=y-Str[93-x];
    for(int8 i=x;i>0;i--)
    {
      int8 temp_y = FinalY;//记录上一个Y
      FinalY=Str[93-i]+Dif;//慢慢变小
      temp_y = temp_y - FinalY+1;
      if(FinalY>=0&&FinalY<=62)
      {
        while(temp_y--)
          image[62-FinalY-temp_y][i]=1;
      }
      else
        break;
    }
  }
}

/************************************************************************
*函数名：入环补线(从上面往下面画弧线)
*参数：拐点坐标
************************************************************************/
void RingInPatchLine(uint8 x,uint8 y,int8 Str[94])
{
  int8 Dif = 0;
  int8 FinalY = y;
  if(state<20)//左入环  左上往右下画弧线
  {
    Dif=y-Str[x];//相对于（x，y）点的纵坐标的变化
    for(uint8 i=x;i<93;i++)
    {
      int8 temp_y = FinalY;//记录上一个Y
      FinalY=Str[i]+Dif;//慢慢变小
      temp_y = temp_y - FinalY + 1;
      if(FinalY>=0)
      {
        while(temp_y--)
         image[62-FinalY-temp_y][i] = 0;//黑色
      }
      else
        break;
    }
  }
  else //右入环
  {
    Dif=y-Str[93-x];
    for(int8 i=x;i>0;i--)
    {
      int8 temp_y = FinalY;//记录上一个Y
      FinalY=Str[93-i]+Dif;//慢慢变小
      temp_y = temp_y - FinalY+1;
      if(FinalY>=0&&FinalY<=62)
      {
        while(temp_y--)
          image[62-FinalY-temp_y][i]=0;
      }
      else
        break;
    }
  }
}
/************************************************************************
*函数名：入环补线(从上面往下面画弧线)  角度相关
*参数：拐点坐标
************************************************************************/
void RingInPatchLine_angle(uint8 x,uint8 y,int8 Str[94],float rato)
{
  int8 Dif = 0;
  int8 FinalY = y;
  if(state<20)//左入环  左上往右下画弧线
  {
    Dif=y-(int8)(Str[x]*rato);//相对于（x，y）点的纵坐标的变化
    for(uint8 i=x;i<93;i++)
    {
      int8 temp_y = FinalY;//记录上一个Y
      FinalY=(int8)(Str[i]*rato)+Dif;//慢慢变小
      temp_y = temp_y - FinalY + 1;
      if(FinalY>=0)
      {
        while(temp_y--)
         image[62-FinalY-temp_y][i] = 0;//黑色
      }
      else
        break;
    }
  }
  else //右入环
  {
    Dif=y-(int8)(Str[93-x]*rato);
    for(int8 i=x;i>0;i--)
    {
      int8 temp_y = FinalY;//记录上一个Y
      FinalY=(int8)(Str[93-i]*rato)+Dif;//慢慢变小
      temp_y = temp_y - FinalY+1;
      if(FinalY>=0&&FinalY<=62)
      {
        while(temp_y--)
          image[62-FinalY-temp_y][i]=0;
      }
      else
        break;
    }
  }
}

/************************************************************************
*函数名：出环补线  从下往上补弧线
*参数：拐点坐标
************************************************************************/
void RingOutPatchLine(uint8 X,uint8 Y,int8 Str[94])
{
  int8 Dif;
  int8 FinalY= Y;
  if(state<20)//左出环   从右下角往左上角补弧线
  {
    Dif=Y-Str[X];//相对坐标
    for(int8 i=X;i>0;i--)
    {   //补线
      int8 temp_y = FinalY;//记录上一个Y
      FinalY=Str[i]+Dif;//慢慢变缓 变大
      temp_y = FinalY - temp_y + 1;
      if(FinalY<=62)
      {
        while(temp_y--)
          image[62-FinalY + temp_y][i]=0;
      }
      else
        break;
    }
  }
  else
  {
    Dif=Y-Str[93-X];
    for(int8 i=X;i<93;i++)
    {   //补线
      int8 temp_y = FinalY;//记录上一个Y
      FinalY=Str[93-i]+Dif;
      temp_y = FinalY - temp_y + 1;
      if(FinalY>=0&&FinalY<=62)
      {
        while(temp_y--)
          image[62-FinalY+temp_y][i]=0;
      }
      else
        break;
    }
  }
}

uint8 Is_circleL_2()
{
  uint8 flag = 0;
  float xx = Is_straight_abs(15,42,DI.IEX[M_R]);
  //if(L_Move.AllMaxY>50&&(xx<0.75||(DI.AD_L>250&&DI.AD_R>150)||DI.AD_L+DI.AD_R>360))//右边界为直道
  if(L_Move.AllMaxY>50&&(xx<0.75))//右边界为直道
  {
    flag = 1;
    for(uint8 i=25;i<40;i+=5)//限制右边赛道范围
      if(DI.IEX[M_R][i]>DI.IEX[M_R][i-5]-2||DI.IEX[M_R][27]>92||DI.IEX[M_R][33]>87||DI.IEX[M_R][37]>80)
        return 1;
    for(uint8 i=40;i<55;i++)//限制右边赛道范围
    {
      if(DI.IEX[M_R][i]>83)
        return 1;
    }
    flag = 2;
    if(DI.Top_edge_Y[1]==0)//最左边上升为黑
    {
      flag = 2;
      uint8 temp_y = GetR(1,0);
      if(temp_y<53&&temp_y>10)//黑色上升一段距离
      {
        flag = 3;
        int8 cnt = 0;
        Point p;
        p.X = 0;
        for(uint8 i=1;i<temp_y;i++)//找最右边的点
        {
          if(DI.IEX[M_L][i]>p.X)
          {
            p.X = DI.IEX[M_L][i];
            p.Y = i;
          }
        }
        uint8 num = 0;
        for(uint8 i=p.Y+1;i<temp_y;i++)
        {
          if(DI.IEX[M_L][i]==p.X)
            num++;
          else
            break;
        }
        p.Y = p.Y + num/2;
        cnt = temp_y - p.Y;
        if(cnt>10&&cnt<35&&DI.Ladder_LBorder[p.Y]==DI.Ladder_LBorder[p.Y+4])
        {
          flag = 4;
          uint8 length = Get_VerticalHeight(1,temp_y) - temp_y;
          if(temp_y+length>57)
            return 4;
          flag = 5;
          if(length>3&&length<30)//有一段白色的
          {
            for(uint8 i=10;i<L_Move.AllMaxY-4;i++)
            {
              if(DI.IEX[M_L][i]-DI.IEX[M_L][i-1]>8)//有拐点
              {//找到拐点
                flag = 6;
                break;
              }
            }
          }
        }
      }
    }
  }
  return flag;
}

uint8 Is_circleR_2()
{
  uint8 flag = 0;
  float xx = Is_straight_abs(15,42,DI.IEX[M_L]);
  if(L_Move.AllMaxY>50&&(xx<0.75))//左边界为直道或者电感值达到一定要求
//  if(L_Move.AllMaxY>50&&(xx<0.75||(DI.AD_R>250&&DI.AD_L>150)||DI.AD_L+DI.AD_R>360))//左边界为直道或者电感值达到一定要求
  {
    flag = 1;
    for(uint8 i=25;i<40;i+=5)//限制左边赛道范围
      if(DI.IEX[M_L][i]<DI.IEX[M_L][i-5]+2||DI.IEX[M_L][27]<2||DI.IEX[M_L][33]<7||DI.IEX[M_L][37]<14)
        return 1;
    for(uint8 i=40;i<55;i++)//限制左边赛道范围
    {
      if(DI.IEX[M_L][i]<10)
        return 1;
    }
    flag = 2;
    if(DI.Top_edge_Y[92]==0)//最右边上升为黑
    {
      flag = 2;
      uint8 temp_y = GetR(92,0);
      if(temp_y<53&&temp_y>10)//黑色上升一段距离
      {
        flag = 3;
        int8 cnt = 0;
        Point p;
        p.X = 94;
        for(uint8 i=1;i<temp_y;i++)
        {
          if(DI.IEX[M_R][i]<p.X)//取最左边的点
          {
            p.X = DI.IEX[M_R][i];
            p.Y = i;
          }
        }
        uint8 num = 0;
        for(uint8 i=p.Y+1;i<temp_y;i++)
        {
          if(DI.IEX[M_R][i]==p.X)
            num++;
          else
            break;
        }
        p.Y = p.Y + num/2;
        DI.Data[13] = temp_y;
        DI.Data[14] = p.X;
        DI.Data[15] = p.Y;
        cnt = temp_y - p.Y;
        if(cnt>10&&cnt<35&&DI.Ladder_RBorder[p.Y]==DI.Ladder_RBorder[p.Y+4])
        {
          flag = 4;
          uint8 length = Get_VerticalHeight(92,temp_y) - temp_y;
          if(temp_y+length>57)
            return 4;
          flag = 5;
          if(length>3&&length<30)//有一段白色的
          {
            for(uint8 i=10;i<L_Move.AllMaxY-4;i++)
            {
              if(DI.IEX[M_R][i-1]-DI.IEX[M_R][i]>8)//右边有拐点
              {//找到拐点
                flag = 6;
                break;
              }
            }
          }

        }
      }
    }
  }
  return flag;
}

uint8 Is_circleL()
{
  if(DI.LengthRing!=0&&DI.Length>220&&(DI.Length-DI.tempLength<40||DI.Length-DI.LengthRing<180))
    return 0;
//  if(DI.AD_L+DI.AD_R<270||DI.AD_L<100) return 0;
  uint8 flag = 0;
  Circle[M_L].variance = Is_straight_abs(25,50,DI.IEX[M_R]); //右边为直线
  if(Circle[M_L].variance<0.38&&DI.IEX[M_R][20]<84&&DI.IEX[M_R][30]<79&&DI.IEX[M_R][40]<74&&DI.IEX[M_R][50]<69)//右边界为直道
  {
    flag = 1;
    Circle[M_L].A_y = DI.MaxY[0];
    if(Circle[M_L].A_y>2&&Circle[M_L].A_y<35&&L_Move.AllMaxY>52)//左边有段上升的直线
    {
      flag = 2;
      uint8 r = GetR(1,DI.MaxY[0]);
      Circle[M_L].C_y = r + DI.MaxY[0];
      if(r>10&&r<45)//半径符合要求
      {
        flag = 3;
        if(DI.MaxY[0]+2<DI.MaxY[1]&&DI.MaxY[1]+3<DI.MaxY[2]&&(DI.MaxY[2]+DI.MaxY[0])>=2*DI.MaxY[1])//左下半部分是圆弧
        {
          flag = 4;
          for(uint8 i=DI.MaxY[0];i<DI.MaxY[0]+r+3&&i<L_Move.AllMaxY;i++)
          {
            if(DI.Ladder_LBorder[i]==DI.Ladder_LBorder[i+4])//找到拐点
            {
              flag = 5;
              Circle[M_L].B_y = i;
              circleLx = DI.Ladder_LBorder[i];//拐点横坐标
              circleLy = i;//拐点纵坐标
              if(2*(Circle[M_L].C_y-Circle[M_L].B_y)>=Circle[M_L].B_y-Circle[M_L].A_y
                 &&Circle[M_L].C_y-Circle[M_L].B_y>5
                   &&Circle[M_L].B_y-Circle[M_L].A_y>Circle[M_L].C_y-Circle[M_L].B_y+4
                     &&Circle[M_L].B_y-Circle[M_L].A_y<Circle[M_L].C_y-Circle[M_L].B_y+15
                       &&circleLx>5) //上半弧长度小于下半弧
              {
                for(uint8 i = 3;i<DI.top_Y-4;i++)
                {
                  if(DI.IEX[M_L][i]-DI.IEX[M_L][i-1]>10)
                  {//找到拐点
                    Circle[M_L].D_x = DI.IEX[M_L][i];
                    Circle[M_L].D_y = i;
                    flag = 6;
                    break;
                  }
                }
              }
              break;
            }
          }
        }
      }
    }
  }
  else
    flag = 0;
  if(flag<6)
    flag = Is_circleL_2();
  return flag;
}
/********************************************************
 *@函数名: 
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-09 13:34:31
********************************************************/
uint8 Is_circleR()
{
  if(DI.LengthRing!=0&&DI.Length>220&&(DI.Length-DI.tempLength<40||DI.Length-DI.LengthRing<180))
    return 0;
 // if(DI.AD_L+DI.AD_R<270||DI.AD_R<100) return 0;//电感不符合要求
  uint8 flag = 0;
  Circle[M_R].variance = Is_straight_abs(25,50,DI.IEX[M_L]); //左边为直道
  if(Circle[M_R].variance<0.38&&DI.IEX[M_L][20]>10&&DI.IEX[M_L][30]>15&&DI.IEX[M_L][40]>20&&DI.IEX[M_L][50]>25)
  {
    flag = 1;
    Circle[M_R].A_y = DI.MaxY[10];
    if(DI.MaxY[10]>2&&DI.MaxY[10]<35&&L_Move.AllMaxY>52)//右边有段上升的直线
    {
      flag = 2;
      uint8 r = GetR(92,DI.MaxY[10]);
      Circle[M_R].C_y = r + DI.MaxY[10];
      if(r>10&&r<45)//半径符合要求
      {
        flag = 3;
        if(DI.MaxY[10]+2<DI.MaxY[9]&&DI.MaxY[9]+3<DI.MaxY[8]&&(DI.MaxY[8]+DI.MaxY[10])>=2*DI.MaxY[9])//左下半部分是圆弧
        {
          flag = 4;
          for(uint8 i=DI.MaxY[10];i<DI.MaxY[10]+r+3&&i<L_Move.AllMaxY;i++)
          {
            if(DI.Ladder_RBorder[i]==DI.Ladder_RBorder[i+4])//找到拐点
            {
              flag = 5;
              circleLx = DI.Ladder_RBorder[i];//拐点横坐标
              Circle[M_R].B_y = i;
              if(2*(Circle[M_R].C_y-Circle[M_R].B_y)>Circle[M_R].B_y-Circle[M_R].A_y
                 &&Circle[M_R].C_y-Circle[M_R].B_y>5
                   &&Circle[M_R].B_y-Circle[M_R].A_y>Circle[M_R].C_y-Circle[M_R].B_y+4
                   &&Circle[M_R].B_y-Circle[M_R].A_y<Circle[M_R].C_y-Circle[M_R].B_y+15
                     &&circleLx<89) //上半弧长度小于下半弧
              {
                for(uint8 i = Circle[M_R].B_y;i<DI.top_Y-4;i++)
                {
                  if(DI.IEX[M_R][i]-DI.IEX[M_R][i-1]<-8)
                  {//找到拐点
                    Circle[M_R].D_x = DI.IEX[M_R][i];
                    Circle[M_R].D_y = i;
                    flag = 6;
                    break;
                  }
                }
              }
              break;
            }
          }
        }
      }
    }
  }
  else
    flag = 0;
  if(flag<6)
    flag = Is_circleR_2();
  return flag;
}


/********************************************************
 *@函数名: 
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-09 13:33:53
********************************************************/

uint8 GetR(uint8 x,uint8 y)//获取圆环半径值
{
  uint8 r=60;
  for(int j=62-y;j>1;j--)//从下往上扫描
  {
    if(image[j][x]==1)//是白色
    {
      r=62-j-y; break;
    }
  }
  return r;
}

float getLine(uint8* A)
{
  if(L_Move.AllMaxY<45) return 0;
  float k,sum=0,kb,temp=0,ss=0;
  k=GetSlope(A[0],0,A[40],40);//斜率
  kb=A[0]; //截距
  for(uint8 i= 0;i<=40;i++)
  {
    temp = kb + i*k;
    sum+= (temp-A[i]);
  }
  ss = sum/40.0;
  if(ss<1.2&&ss>-1.2)
    return 1;
  return 0;
}

//曼哈顿方法  寻找有效的圆环出口
uint8 Manhattan(uint8 x,uint8 y,uint8 Dir)
{
  uint8 cnt=0;
  if(Dir==M_L)//往左找
  {
    while(y<60&&x>10&&cnt<7)
    {
      cnt++;
      while(image[63-(y+1)][x]&&y<60&&x>10)//上边是白就向上
      {
        y++;
      }
      while(image[63-y][x-1]&&y<60&&x>10)//左边是白就向左
      {
        x--;
      }
    }
  }
  else
  {
    while(y<60&&x<84&&cnt<7)
    {
      cnt++;
      while(image[63-(y+1)][x]&&y<60&&x<84)//上边是白就向上
      {
        y++;
      }
      while(image[63-y][x+1]&&y<60&&x<84)//右边是白就向右
      {
        x++;
      }
    }
  }
  return x;
}

//*-----------------------------------
//函数作用：判断一段数据是否有跳变
//没有跳变回复TRUE
//arr     数据数组
//length  数据长度
//Max_error 允许最大误差
//------------------------------------
uint8 Basic_is_Line_Saltus(uint8* arr,uint8 length,uint8 Max_error)
{
  if(length<5)
    return 0;
  for(uint8 i=0;i<length-1;i++)
  {
    if(arr[i]+Max_error<arr[i+1]||arr[i]>arr[i+1]+Max_error)
      return 0;
  }
  return 1;
}



