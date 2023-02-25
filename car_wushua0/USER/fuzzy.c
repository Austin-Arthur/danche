
#include "fuzzy.h"
int  pe0 = 0, U0Rule[2] = { 0, 0};//偏差  偏差的变化率  采用的四条规则
/**********************************************************************
* 函数名称：FuzzyCtrl
* 函数功能：模糊化 去模糊
* 入口参数：FuzzyStruct* Fuzzy
* 出口参数：Fuzzy Value
**********************************************************************/
float FuzzyCtrl_angle(FuzzyStruct_angle* Fuzzy)
{
  float U = 0;//输出值的精确量
  /*-----误差隶属函数描述-----*/
  if (Fuzzy->err <= Fuzzy->eRule[0])                // |x_x_x_x_x_x_x_
    {
      pe0 = -6;
    }
  else if (Fuzzy->err <= Fuzzy->eRule[1])                // |x_x_x_x_x_x_x_
    {
      pe0 = -5;
    }
  else if (Fuzzy->err <= Fuzzy->eRule[2])                // |x_x_x_x_x_x_x_
    {
      pe0 = -4;
    }

  else if (Fuzzy->err <= Fuzzy->eRule[3])                // |x_x_x_x_x_x_x_
  {
    pe0 = -3;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[4])           // _x|x_x_x_x_x_x_
  {
    pe0 = -2;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[5])           // _x_x|x_x_x_x_x_
  {
    pe0 = -1;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[6])           // _x_x_x|x_x_x_x_
  {
    pe0 = 0;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[7])               // _x_x_x_x|x_x_x_
  {
    pe0 = 1;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[8])               // _x_x_x_x_x|x_x_
  {
    pe0 = 2;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[9])               // _x_x_x_x_x_x|x_
  {
    pe0 = 3;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[10])             // _x_x_x_x_x_x_x|
  {
    pe0 = 4;
  }

  else if (Fuzzy->err <= Fuzzy->eRule[11])             // _x_x_x_x_x_x_x|
    {
      pe0 = 5;
    }
  else if (Fuzzy->err <= Fuzzy->eRule[12])             // _x_x_x_x_x_x_x|
    {
      pe0 = 6;
    }
  else if (Fuzzy->err >= Fuzzy->eRule[12])             // _x_x_x_x_x_x_x|
    {
      pe0 = 7;
    }

  /*查询模糊规则表 rule[][]*/

  if(pe0>=-5&&pe0<=6)
  {
      U0Rule[0] = Fuzzy->rule[pe0 - 1 + 6];//取出当前位置的输出隶属度
      U0Rule[1] = Fuzzy->rule[pe0 + 6];
      /*
      U = ((Fuzzy->err - Fuzzy->eRule[U0Rule[0]])*Fuzzy->URule[U0Rule[0]]
            +(Fuzzy->eRule[U0Rule[1]]-Fuzzy->err)*Fuzzy->URule[U0Rule[1]])
                    /(Fuzzy->eRule[U0Rule[1]]-Fuzzy->eRule[U0Rule[0]]);
      */
      U = ((Fuzzy->eRule[pe0 + 6]- Fuzzy->err)*Fuzzy->URule[U0Rule[0]]
                  +(Fuzzy->err - Fuzzy->eRule[pe0 - 1 + 6])*Fuzzy->URule[U0Rule[1]])
                          /(Fuzzy->eRule[pe0 + 6]-Fuzzy->eRule[pe0 - 1 + 6]);
  }
  else if(pe0==-6)
  {
      U = Fuzzy->URule[Fuzzy->rule[pe0 + 6]];
  }
  else if(pe0==7)
  {
      U = Fuzzy->URule[Fuzzy->rule[pe0 - 1 + 6]];
  }

  return U;
}



/**********************************************************************
* 函数名称：Fuzzy_Update
* 函数功能：模糊控制更新
* 入口参数：FuzzyStruct* F_S
ek
ekc
* 出口参数：Fuzzy Value
**********************************************************************/
float Fuzzy_Update_angle(FuzzyStruct_angle* F_S, float ek)
{
  float value = 0;
  F_S->err = ek;
  value = FuzzyCtrl_angle(F_S);
  return value;
}





