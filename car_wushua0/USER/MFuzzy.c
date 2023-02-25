
#include "MFuzzy.h"
int  pe = 0, pec = 0, U1Rule[4] = { 0, 0, 0, 0 };//ƫ��  ƫ��ı仯��  ���õ���������
/**********************************************************************
* �������ƣ�FuzzyCtrl
* �������ܣ�ģ���� ȥģ��
* ��ڲ�����FuzzyStruct* Fuzzy
* ���ڲ�����Fuzzy Value
**********************************************************************/
int hang,lei;
float FuzzyCtrl(FuzzyStruct* Fuzzy)
{
  float  err[2] = { 0.0, 0.0 };//ƫ��
  float  errc[2] = { 0.0, 0.0 };//ƫ��΢��
  float  QRule[4] = { 0.0, 0.0, 0.0, 0.0 }; //URule[]���ֵ
  float  U1Fuzzy[4] = { 0.0, 0.0, 0.0, 0.0 }; //���ֵ��������
  float U = 0;//���ֵ�ľ�ȷ��
  float   temp1, temp2;//���ķ��м����
  /*-----���������������-----*/
  if (Fuzzy->err <= Fuzzy->eRule[0])                // |x_x_x_x_x_x_x_
  {
    err[0] = 1.0;
    pe = -2;
  }
  else if (Fuzzy->err <= Fuzzy->eRule[1])           // _x|x_x_x_x_x_x_
  {
    err[0] = (Fuzzy->eRule[1] - Fuzzy->err) / (Fuzzy->eRule[1] - Fuzzy->eRule[0]);//�ƽ��̶����� ��һ������
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
  /*-----���仯��������������-----*/
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
  errc[1] = 1 - errc[0]; //�������������
  /*��ѯģ������� rule[][]*/
  /*����ֵ��URule[]���*/
  /*һ�㶼���ĸ�������Ч*/
  U1Rule[0] = Fuzzy->rule[pe - 1 + 3][pec - 1 + 3];
  U1Rule[1] = Fuzzy->rule[pe + 3][pec - 1 + 3];
  U1Rule[2] = Fuzzy->rule[pe - 1 + 3][pec + 3];
  U1Rule[3] = Fuzzy->rule[pe + 3][pec + 3];
  hang = pe - 1 + 3;
  lei = pec - 1 + 3;
  //���������
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
  /*ͬ���������������ֵ���*/
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
  /*���ķ���ģ��*/
  /*U1Rule[]ԭֵΪ�������������ţ�ת��ΪURule[]��������ֵ*/
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
* �������ƣ�Fuzzy_Update
* �������ܣ�ģ�����Ƹ���
* ��ڲ�����FuzzyStruct* F_S
ek
ekc
* ���ڲ�����Fuzzy Value
**********************************************************************/
float Fuzzy_Update(FuzzyStruct* F_S, float ek, float ekc)
{
  float value = 0;
  F_S->err = ek;
  F_S->errc = ekc;
  value = FuzzyCtrl(F_S);
  return value;
}





