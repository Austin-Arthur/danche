/*
 * Fun_8.c
 *
 *  Created on: 2021��12��30��
 *      Author: 11609
 */
#include "Fun_8.h"
_8feature _8;
Point Heading_Dir[2][8];
Point Stop;

void Init_8Neighbour();
void Get_eight_neighbour();
void Init_ThisIImg();
void Set_8(uint8 First_LPoint, uint8 First_RPoint);
uint8 exitflag = 1;

Point setPointValue(int x, int y)//���ص�
{
  Point tmp;
  tmp.X = x;
  tmp.Y = y;
  return tmp;
}

Point Point_add(Point a, Point b)//���������
{
  Point tmp;
  tmp.X = a.X + b.X;
  tmp.Y = a.Y + b.Y;
  return tmp;
}

Point getPoint(Point a)//��ȡ��
{
  return a;
}

void _8_Init_Heading_Dir()
{
  //��ߴ��ҵ���ʱ����
  Heading_Dir[M_L][0] = setPointValue(1, 0);
  Heading_Dir[M_L][1] = setPointValue(1, 1);
  Heading_Dir[M_L][2] = setPointValue(0, 1);
  Heading_Dir[M_L][3] = setPointValue(-1, 1);
  Heading_Dir[M_L][4] = setPointValue(-1, 0);
  Heading_Dir[M_L][5] = setPointValue(-1, -1);
  Heading_Dir[M_L][6] = setPointValue(0, -1);
  Heading_Dir[M_L][7] = setPointValue(1, -1);
  //�ұߴ����˳ʱ����
  Heading_Dir[M_R][0] = setPointValue(-1, 0);
  Heading_Dir[M_R][1] = setPointValue(-1, 1);
  Heading_Dir[M_R][2] = setPointValue(0, 1);
  Heading_Dir[M_R][3] = setPointValue(1, 1);
  Heading_Dir[M_R][4] = setPointValue(1, 0);
  Heading_Dir[M_R][5] = setPointValue(1, -1);
  Heading_Dir[M_R][6] = setPointValue(0, -1);
  Heading_Dir[M_R][7] = setPointValue(-1, -1);
}
void Init_8Neighbour()
{
  memset(DI.Top_edge_Y,0,sizeof(DI.Top_edge_Y));
  memset(DI.Top_max_Y,0,sizeof(DI.Top_max_Y));
  for(uint8 i=0;i<64;i++)
  {
    image[i][0]=0;//��
    image[i][93]=0;//��
    DI.IEX[M_L][i]=0;
    DI.IEX[M_R][i]=93;
    DI.OEX[M_L][i]=93;
    DI.OEX[M_R][i]=0;
    for(uint8 j=0;j<94;j++)
    {
      DI.MEX[M_L][i][j]=93;
      DI.MEX[M_R][i][j]=0;
    }
  }  //�γ�һ����շ�Χ
  for(uint8 i=0;i<2;i++)
  {
    _8.time[i] = 0;
    for(uint8 j=0;j<64;j++)
      _8.Time[i][j]=0;
  }
}
void Set_8(uint8 First_LPoint, uint8 First_RPoint)
{//������ʼ��
  if(First_LPoint!=First_RPoint)
  {
    First_LPoint--;
    First_RPoint++;
  }
  _8.borderPoint[M_L].X = First_LPoint;
  _8.borderPoint[M_L].Y = 1;
  _8.borderPoint[M_R].X = First_RPoint;
  _8.borderPoint[M_R].Y = 1;
  _8.maxValue[M_L] = First_LPoint;
  _8.maxValue[M_R] = First_RPoint;
  DI.OEX[M_L][1] = DI.IEX[M_L][1] = DI.OEX[M_L][0] = DI.IEX[M_L][0]  = First_LPoint;
  DI.OEX[M_R][1] = DI.IEX[M_R][1] = DI.OEX[M_R][0] = DI.IEX[M_R][0] = First_RPoint;
}

void Init_ThisIImg()
{
  _8.now_Dir[M_L] = 0;
  _8.now_Dir[M_R] = 0;
}
int8 dL[8] = {-2,-1,0,1,2,3,-4,-3};
int8 dR[8] = {2,1,0,-1,-2,-3,4,3};
void rotate(int R_or_L)
{
  Point tmp;
  for(uint8 i=0;i<8;i++)//�����������ұ߽�
  {
    tmp = Point_add(_8.borderPoint[R_or_L], Heading_Dir[R_or_L][(_8.now_Dir[R_or_L] + i) % 8]);
    if (image[63-tmp.Y][tmp.X]==0)//������ɫ
    {
      if (R_or_L == M_L)//���
      {
        DI.Dir[M_L][_8.time[M_L]] = dL[(_8.now_Dir[R_or_L] + 8 + i)%8];//��¼��ǰ����
        DI.MEX[M_L][tmp.Y][_8.Time[M_L][tmp.Y]] = tmp.X; //�м��
        DI.IEX[M_L][tmp.Y] = tmp.X>DI.IEX[M_L][tmp.Y] ? tmp.X : DI.IEX[M_L][tmp.Y];//�����ȡ��
        DI.OEX[M_L][tmp.Y] = tmp.X<DI.OEX[M_L][tmp.Y] ? tmp.X : DI.OEX[M_L][tmp.Y];//�����ȡС
        _8.maxValue[M_L] = tmp.X;
        _8.Time[M_L][tmp.Y]++;
        _8.time[M_L]++;
      }
      else
      {
        DI.Dir[M_R][_8.time[M_R]] = dR[(_8.now_Dir[R_or_L] + 8 + i)%8];//��¼��ǰ����
        DI.MEX[M_R][tmp.Y][_8.Time[M_R][tmp.Y]] = tmp.X; //��¼�м��
        DI.IEX[M_R][tmp.Y] = tmp.X<DI.IEX[M_R][tmp.Y] ? tmp.X : DI.IEX[M_R][tmp.Y];//�����ȡС
        DI.OEX[M_R][tmp.Y] = tmp.X>DI.OEX[M_R][tmp.Y] ? tmp.X : DI.OEX[M_R][tmp.Y];//�����ȡ��
        _8.maxValue[M_R] = tmp.X;
        _8.Time[M_R][tmp.Y]++;
        _8.time[M_R]++;
      }
      if (tmp.Y<DI.Top_edge_Y[tmp.X] || DI.Top_edge_Y[tmp.X] == 0
          &&tmp.X>DI.OEX[M_L][0]&&tmp.X<DI.OEX[M_R][0])
      {
        DI.Top_edge_Y[tmp.X] = tmp.Y;//ȡС
      }
      if (tmp.Y>DI.Top_max_Y[tmp.X] || DI.Top_max_Y[tmp.X] == 0)
      {
        DI.Top_max_Y[tmp.X] = tmp.Y;//ȡ��
      }
      _8.borderPoint[R_or_L] = Point_add(Heading_Dir[R_or_L][(_8.now_Dir[R_or_L] + i) % 8], _8.borderPoint[R_or_L]);
      _8.now_Dir[R_or_L] = (_8.now_Dir[R_or_L] + i + 8 - 2) % 8;
      break;
    }
  }
}
void Get_eight_neighbour()//�˽����ұ߽�
{//��ȡ8��������߽�
  Set_8(DI.Ladder_LBorder[0],DI.Ladder_RBorder[0]);//����8�������
  uint8 goal = 1;
  exitflag = 1;
  Init_ThisIImg();//��ʼ��
  while(exitflag)//һֱ�ҵ���������
  {
    goal++;
    while(_8.borderPoint[M_L].Y < goal&&exitflag)
    {
      rotate(M_L);
      if ((_8.maxValue[M_R] <= _8.maxValue[M_L]
           &&_8.borderPoint[M_L].Y==_8.borderPoint[M_R].Y)
          ||_8.time[M_L]>300)//��������
      {
        DI.top_Y = goal;
        exitflag = 0;
      }
    }
    while(_8.borderPoint[M_R].Y < goal&&exitflag)
    {
      rotate(M_R);
      if ((_8.maxValue[M_R] <= _8.maxValue[M_L]
          &&_8.borderPoint[M_L].Y==_8.borderPoint[M_R].Y)
          ||_8.time[M_R]>300)//��������
      {
        DI.top_Y = goal;
        exitflag = 0;
      }
    }
  }
////���Ͱ˽��ڱ߽�
//  if(GetItemValue(Debug_Order,Debug_DrawData_Order)==4)
//  {
//    LPLD_UART_PutChar(UART3,DI.IEX[M_L][0]);
//    for(int i=0;i<_8.time[M_L];i++)
//    {
//      LPLD_UART_PutChar(UART3,DI.Dir[M_L][i]);
//    }
//    LPLD_UART_PutChar(UART3,0xAA);
//    LPLD_UART_PutChar(UART3,DI.IEX[M_R][0]);
//    for(int i=0;i<_8.time[M_R];i++)
//    {
//      LPLD_UART_PutChar(UART3,DI.Dir[M_R][i]);
//    }
//    LPLD_UART_PutChar(UART3,0xAA);
//    SetItemValue(Debug_Order,Debug_DrawData_Order,1);
//  }
//����Բ������
//  if(GetItemValue(Debug_Order,Debug_DrawData_Order)==4)
//  {
//    for(int i=0;i<94;i++)
//    {
//      LPLD_UART_PutChar(UART3,DI.Top_max_Y[i]);
//    }
//    SetItemValue(Debug_Order,Debug_DrawData_Order,1);
//  }
//  ////���������������
//  if(GetItemValue(Debug_Order,Debug_DrawData_Order)==4)
//  {
//    for(int i=0;i<62;i++)
//    {
//      LPLD_UART_PutChar(UART3,DI.Ladder_RBorder[i]-DI.Ladder_LBorder[i]);
//    }
//    SetItemValue(Debug_Order,Debug_DrawData_Order,1);
//  }


  Stop.Y = goal;
  Stop.X = _8.maxValue[M_L];

}



