/*
 * Fun_L.c
 *
 *  Created on: 2021��12��30��
 *      Author: 11609
 */
#include "Fun_L.h"
void Deal_firstline();
/************************************************************************
���������������������㷨
���ܣ���¼���ݱ߽�
************************************************************************/
void Ladder()
{
  for(uint8 i=1;;i++)
  {
    DI.Ladder_LBorder[i] = DI.Ladder_LBorder[i-1];
    DI.Ladder_RBorder[i] = DI.Ladder_RBorder[i-1];//���ظ���
    while(!image[63-i][DI.Ladder_LBorder[i]]&&DI.Ladder_LBorder[i]<92)//��ǰΪ�� �����ҵ���Ϊֹ
      DI.Ladder_LBorder[i]++;
    while(!image[63-i][DI.Ladder_RBorder[i]]&&DI.Ladder_RBorder[i]>1)//��ǰΪ�� �����ҵ���Ϊֹ
      DI.Ladder_RBorder[i]--;
    if(DI.Ladder_RBorder[i]<= DI.Ladder_LBorder[i]||i==61)//���������ҵ���
    {
      DI.Ladder_LBorder[i] = DI.Ladder_LBorder[i-1];
      DI.Ladder_RBorder[i] = DI.Ladder_RBorder[i-1];
      L_Move.AllMaxY = i ;
      break;
    }
  }
}
/********************************************************
�������ܣ������һ��ͼ��
˵��������һ�ε�һ�е���ֵ�������������
�������ܣ���ȡ����������㣨1-92��
********************************************************/
void Deal_firstline()
{
   if(state==31||state==32||state==33||state==34||state==13||state==14||state==15||state==23||state==24||state==25)
     {
       uint8 max = 0,count=0;
       for(uint8 i=1;i<94;i++)//Ѱ����������׿��������ұ߽磬������ֵ
       {
         if(image[62][i]==1&&i!=93)//Ϊ��
           count++;
         else//Ϊ��
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
  {//�����Ұױ�ڵĵ�
    DI.Ladder_LBorder[0]--;
  }
  while(image[62][DI.Ladder_RBorder[0]+1]&&image[62][DI.Ladder_RBorder[0]])
  {//�����Ұױ�ڵĵ�
    DI.Ladder_RBorder[0]++;
  }
  DI.Ladder_MidPoint[0]=(DI.Ladder_LBorder[0] + DI.Ladder_RBorder[0])/2;
}





