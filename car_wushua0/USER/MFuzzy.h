/*
 * MFuzzy.h
 *
 *  Created on: 2021年12月30日
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
  float eRule[7];   //误差隶属度函数中心值
  float ecRule[7];  //误差变化隶属度函数中心值
  float URule[7];  //输出隶属函数中心值
  int   rule[7][7]; //规则表
}FuzzyStruct;  // 模糊结构体



/************舵机模糊表**********/
extern  FuzzyStruct      Agnle_P_TableOne;
extern  FuzzyStruct      Agnle_D_TableOne;


/************电机机模糊表**********/

extern  FuzzyStruct      Motor_P_Table;
extern  FuzzyStruct      Motor_I_Table;

extern int hang,lei;
extern FuzzyStruct       Speed_TableOne;

float Fuzzy_Update(FuzzyStruct* F_S,float ek,float ekc);
float FuzzyCtrl(FuzzyStruct* Fuzzy_S);

#endif



#endif /* USER_MFUZZY_H_ */
