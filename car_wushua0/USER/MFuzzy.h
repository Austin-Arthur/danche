/*
 * MFuzzy.h
 *
 *  Created on: 2021��12��30��
 *      Author: 11609
 */
#include "headfile.h"

#ifndef USER_MFUZZY_H_
#define USER_MFUZZY_H_

#ifndef _MFUZZY_H_
#define _MFUZZY_H_


typedef struct
{
  float err;  // e(k)
  float errc; // e(k)'
  float eRule[7];   //��������Ⱥ�������ֵ
  float ecRule[7];  //���仯�����Ⱥ�������ֵ
  float URule[7];  //���������������ֵ
  int   rule[7][7]; //�����
}FuzzyStruct;  // ģ���ṹ��



/************���ģ����**********/
extern  FuzzyStruct      Agnle_P_TableOne;
extern  FuzzyStruct      Agnle_D_TableOne;


/************�����ģ����**********/

extern  FuzzyStruct      Motor_P_Table;
extern  FuzzyStruct      Motor_I_Table;

extern int hang,lei;
extern FuzzyStruct       Speed_TableOne;

float Fuzzy_Update(FuzzyStruct* F_S,float ek,float ekc);
float FuzzyCtrl(FuzzyStruct* Fuzzy_S);

#endif



#endif /* USER_MFUZZY_H_ */
