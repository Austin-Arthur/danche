/*
 * fuzzy.h
 *
 *  Created on: 2022年7月3日
 *      Author: 11609
 */
#include "headfile.h"
#ifndef USER_FUZZY_H_
#define USER_FUZZY_H_




typedef struct
{
  float err;  // e(k)
  float eRule[13];   //误差隶属度函数中心值
  float URule[13];  //输出隶属函数中心值
  int   rule[13]; //规则表
}FuzzyStruct_angle;  // 模糊结构体



/************舵机模糊表**********/
extern  FuzzyStruct_angle      table;


float Fuzzy_Update_angle(FuzzyStruct_angle* F_S,float ek);
float FuzzyCtrl_angle(FuzzyStruct_angle* Fuzzy_S);

#endif

