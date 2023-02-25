
#include "MFuzzy.h"
int  pe = 0, pec = 0, U1Rule[4] = { 0, 0, 0, 0 };//偏差  偏差的变化率  采用的四条规则
/**********************************************************************
* 函数名称：FuzzyCtrl
* 函数功能：模糊化 去模糊
* 入口参数：FuzzyStruct* Fuzzy
* 出口参数：Fuzzy Value
**********************************************************************/
int hang,lei;
float FuzzyCtrl(FuzzyStruct* Fuzzy)
{
  float  err[2] = { 0.0, 0.0 };//偏差
  float  errc[2] = { 0.0, 0.0 };//偏差微分
  float  QRule[4] = { 0.0, 0.0, 0.0, 0.0 }; //URule[]输出值
  float  U1Fuzzy[4] = { 0.0, 0.0, 0.0, 0.0 }; //输出值的隶属度
  float U = 0;//输出值的精确量
  float   temp1, temp2;//重心法中间变量
  /*-----误差隶属函数描述-----*/
  if (Fuzzy->err <= Fuzzy->eRule[0])                // |x_x_x_x_x_x_x_
  {
    err[0] = 1.0;
    pe = -2;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[1])           // _x|x_x_x_x_x_x_
  {
    err[0] = (Fuzzy->eRule[1] - Fuzzy->err) / (Fuzzy->eRule[1] - Fuzzy->eRule[0]);//逼近程度描述 归一化处理
    pe = -2;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[2])           // _x_x|x_x_x_x_x_
  {
    err[0] = (Fuzzy->eRule[2] - Fuzzy->err) / (Fuzzy->eRule[2] - Fuzzy->eRule[1]);
    pe = -1;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[3])           // _x_x_x|x_x_x_x_
  {
    err[0] = (Fuzzy->eRule[3] - Fuzzy->err) / (Fuzzy->eRule[3] - Fuzzy->eRule[2]);
    pe = 0;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[4])               // _x_x_x_x|x_x_x_
  {
    err[0] = (Fuzzy->eRule[4] - Fuzzy->err) / (Fuzzy->eRule[4] - Fuzzy->eRule[3]);
    pe = 1;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[5])               // _x_x_x_x_x|x_x_
  {
    err[0] = (Fuzzy->eRule[5] - Fuzzy->err) / (Fuzzy->eRule[5] - Fuzzy->eRule[4]);
    pe = 2;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[6])               // _x_x_x_x_x_x|x_
  {
    err[0] = (Fuzzy->eRule[6] - Fuzzy->err) / (Fuzzy->eRule[6] - Fuzzy->eRule[5]);
    pe = 3;
  }
  else if (Fuzzy->err >= Fuzzy->eRule[6])             // _x_x_x_x_x_x_x|
  {
    err[0] = 0;
    pe = 3;
  }
  err[1] = 1 - err[0];
  /*-----误差变化率隶属函数描述-----*/
  if (Fuzzy->errc <= Fuzzy->ecRule[0])
  {
    errc[0] = 1.0;
    pec = -2;
  }
  else if (Fuzzy->errc <= Fuzzy->ecRule[1])
  {
    errc[0] = (Fuzzy->ecRule[1] - Fuzzy->errc) / (Fuzzy->ecRule[1] - Fuzzy->ecRule[0]);
    pec = -2;
  }
  else if (Fuzzy->errc <= Fuzzy->ecRule[2])
  {
    errc[0] = (Fuzzy->ecRule[2] - Fuzzy->errc) / (Fuzzy->ecRule[2] - Fuzzy->ecRule[1]);
    pec = -1;
  }
  else if (Fuzzy->errc <= Fuzzy->ecRule[3])
  {
    errc[0] = (Fuzzy->ecRule[3] - Fuzzy->errc) / (Fuzzy->ecRule[3] - Fuzzy->ecRule[2]);
    pec = 0;
  }
  else if (Fuzzy->errc <= Fuzzy->ecRule[4])
  {
    errc[0] = (Fuzzy->ecRule[4] - Fuzzy->errc) / (Fuzzy->ecRule[4] - Fuzzy->ecRule[3]);
    pec = 1;
  }
  else if (Fuzzy->errc <= Fuzzy->ecRule[5])
  {
    errc[0] = (Fuzzy->ecRule[5] - Fuzzy->errc) / (Fuzzy->ecRule[5] - Fuzzy->ecRule[4]);
    pec = 2;
  }
  else if (Fuzzy->errc <= Fuzzy->ecRule[6])
  {
    errc[0] = (Fuzzy->ecRule[6] - Fuzzy->errc) / (Fuzzy->ecRule[6] - Fuzzy->ecRule[5]);
    pec = 3;
  }
  else
  {
    errc[0] = 0;
    pec = 3;
  }
  errc[1] = 1 - errc[0]; //隶属度描述完成
  /*查询模糊规则表 rule[][]*/
  /*中心值由URule[]输出*/
  /*一般都是四个规则有效*/
  U1Rule[0] = Fuzzy->rule[pe - 1 + 3][pec - 1 + 3];
  U1Rule[1] = Fuzzy->rule[pe + 3][pec - 1 + 3];
  U1Rule[2] = Fuzzy->rule[pe - 1 + 3][pec + 3];
  U1Rule[3] = Fuzzy->rule[pe + 3][pec + 3];
  hang = pe - 1 + 3;
  lei = pec - 1 + 3;
  //相近隶属度
  if (err[0] <= errc[0]) // 0-0
    U1Fuzzy[0] = err[0];
  else
    U1Fuzzy[0] = errc[0];

  if (err[1] <= errc[0]) // 1-0
    U1Fuzzy[1] = err[1];
  else
    U1Fuzzy[1] = errc[0];

  if (err[0] <= errc[1]) // 0-1
    U1Fuzzy[2] = err[0];
  else
    U1Fuzzy[2] = errc[1];

  if (err[1] <= errc[1]) // 1-1
    U1Fuzzy[3] = err[1];
  else
    U1Fuzzy[3] = errc[1];
  /*同隶属函数输出语言值求大*/
  if (U1Rule[0] == U1Rule[1])
  {
    if (U1Fuzzy[0]>U1Fuzzy[1])
      U1Fuzzy[1] = 0;
    else
      U1Fuzzy[0] = 0;
  }
  if (U1Rule[0] == U1Rule[2])
  {
    if (U1Fuzzy[0]>U1Fuzzy[2])
      U1Fuzzy[2] = 0;
    else
      U1Fuzzy[0] = 0;
  }
  if (U1Rule[0] == U1Rule[3])
  {
    if (U1Fuzzy[0]>U1Fuzzy[3])
      U1Fuzzy[3] = 0;
    else
      U1Fuzzy[0] = 0;
  }
  if (U1Rule[1] == U1Rule[2])
  {
    if (U1Fuzzy[1]>U1Fuzzy[2])
      U1Fuzzy[2] = 0;
    else
      U1Fuzzy[1] = 0;
  }
  if (U1Rule[1] == U1Rule[3])
  {
    if (U1Fuzzy[1]>U1Fuzzy[3])
      U1Fuzzy[3] = 0;
    else
      U1Fuzzy[1] = 0;
  }
  if (U1Rule[2] == U1Rule[3])
  {
    if (U1Fuzzy[2]>U1Fuzzy[3])
      U1Fuzzy[3] = 0;
    else
      U1Fuzzy[2] = 0;
  }
  /*重心法反模糊*/
  /*U1Rule[]原值为输出隶属函数标号，转换为URule[]隶属函数值*/
  if (U1Rule[0] >= 0)
    QRule[0] = Fuzzy->URule[U1Rule[0]];
  else
    QRule[0] = -(Fuzzy->URule[-U1Rule[0]]);

  if (U1Rule[1] >= 0)
    QRule[1] = Fuzzy->URule[U1Rule[1]];
  else
    QRule[1] = -(Fuzzy->URule[-U1Rule[1]]);

  if (U1Rule[2] >= 0)
    QRule[2] = Fuzzy->URule[U1Rule[2]];
  else
    QRule[2] = -(Fuzzy->URule[-U1Rule[2]]);

  if (U1Rule[3] >= 0)
    QRule[3] = Fuzzy->URule[U1Rule[3]];
  else
    QRule[3] = -(Fuzzy->URule[-U1Rule[3]]);
  temp1 = U1Fuzzy[0] * QRule[0] + U1Fuzzy[1] * QRule[1] + U1Fuzzy[2] * QRule[2] + U1Fuzzy[3] * QRule[3];
  temp2 = U1Fuzzy[0] + U1Fuzzy[1] + U1Fuzzy[2] + U1Fuzzy[3];
  U = temp1 / temp2;
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
float Fuzzy_Update(FuzzyStruct* F_S, float ek, float ekc)
{
  float value = 0;
  F_S->err = ek;
  F_S->errc = ekc;
  value = FuzzyCtrl(F_S);
  return value;
}





