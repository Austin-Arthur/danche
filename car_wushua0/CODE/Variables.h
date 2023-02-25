/*
 * Variables.h
 *
 *  Created on: 2021年12月30日
 *      Author: 11609
 */

#ifndef CODE_VARIABLES_H_
#define CODE_VARIABLES_H_
#include "headfile.h"
typedef struct Point//点结构体
{
  int16 X;
  int16 Y;
}Point;
typedef struct Cnst//阈值结构体
{
  uint8 cnst;      //阈值
  uint8 setMaxCnst;  //设定阈值
  uint8 offsetCnst;//动态阈值偏移量
  int Bright_cnt;//亮点
  uint16 exp_time;//曝光时间
  uint8 cnst0;
  uint8 cnst1;
  uint8 num;
}Cnst;
typedef struct Ring//圆环结构体
{
  float variance;//直线方差
  uint8 A_y;
  uint8 B_y;
  uint8 C_y;//判断圆环的三个点
  uint8 D_x;
  uint8 D_y;//弧线跳变点
}Ring;
typedef struct//8近邻结构体
{
  uint16 time[2];
  uint16 Time[2][64];
  int8 now_Dir[2];//方向
  Point borderPoint[2];
  uint8 maxValue[2];
} _8feature;
typedef struct  TwoDot//爬梯两点结构体
{
  uint8 AllMaxY; //全图最远点 爬梯终点（交汇点）
  uint8 ui8_StartL;//爬梯起点 左
  uint8 ui8_StartR;//爬梯起点 右
}TwoDot;

typedef struct  DataI//图像数据结构体
{
  uint8 Ladder_LBorder[64];//爬梯左边界
  uint8 Ladder_RBorder[64]; //爬梯右边界
  uint8 Ladder_MidPoint[64];//爬梯中点
  uint16 AD_L;//左边电感值
  uint16 AD_R;//右边电感值
  uint16 AD_M;//右边电感值
  uint16 AD_VL;//右边电感值
  uint16 AD_VR;//右边电感值
  uint8 ad_p; //电磁PID
  uint8 ad_d;
  float AD_err;//电感当前误差
  float error;
  uint8 Inflection_x[2];//记录拐点
  uint8 Inflection_y[2];//记录拐点
  uint8 IEX[2][64];//内边界
  uint8 CUR[2][64];//定位数组
  int8  Dir[2][300];//定义方向数组
  Point DOT[2][300];//八近邻边界数组
  uint8 MEX[2][64][94]; //其余边界
  uint8 OEX[2][64];//外边界
  uint8 Top_edge_Y[94];//最小边沿距离  最近Y
  uint8 Top_max_Y[94]; //最大可视距离
  uint8 Line_Selected_Y[7];//等距离的七条线
  uint8 RingSumCnt;//圆环总个数
  uint8 DuanLu_cnt;//记录经过断路横断的个数
  uint8 HD_DLSumCnt;//横断断路总个数
  uint8 HD_DL[15];
  uint8 top_Y;//八近邻最远距离
  uint8 flag;//补线标志
  uint8 set;//设置起点标志
  long LengthCnt;//编码器总脉冲数
  long Length;//小车运行距离 单位cm
  int Length_angle;//小车运行距离 单位cm
  int tempLength; //临时记录小车距离
  int LengthBend;//记录入弯距离
  int LengthRing;//环沿距
  int LengthRamp;//坡道延距
  int LengthCheku;//出库补线
  int Lengthfork;//小车运行距离 单位cm
  uint8 ramp_flag;//坡道标志
  uint8 MaxY[11];//图像单边最远点
  float Data[60];//临时显示数据
  float MidLine; //中线
  float chaSu;//差速系数
  int rampCnt;//坡道计数
  uint8 rampV;//坡道速度
  uint8 hengDuanV;//横断速度
  uint8 elecV;//电磁速度
  uint16 setLength;  //设定距离
  uint8 SightDistance;//可视距离
  uint8 ring2DL;//环中断路
  uint8 yyy;
  uint8 speed_flag;
  float ZhiDao_radio;
  uint8 isSloop;
  uint8 maxCnt;
  uint8 isVdown;
  uint16 DLZDlength;
  uint8 ForkCnt;
  int ForkLength;//三岔路延距
  float Angle_error;
  float Angle_target;
  //扫描行左边界(补线)
  uint8 ui8_ScanLineL[10];
  //扫描行右边界(补线)
  uint8 ui8_ScanLineR[10];

  uint8 Two_Cam;
  uint8 ZebroNum;
}DataI;
typedef enum
{
  INITING ,     //初始化状态
  DEBUG,        //调试状态
  RUN,          //运行状态
  STOP,         //停车状态
}STATE;
extern STATE State;
extern DataI DI;
extern Ring Circle[2];
extern Cnst CI;
extern TwoDot L_Move;
extern TwoDot R_Move;
extern Point Stop;
extern int variable[10];
extern int state;
extern int image_temp[64];
extern float angle_klm_pitch;
extern float angle_klm_roll;
extern float angle_klm_yaw;
extern float xztt[10] ;//测试变量
extern int test_y[10] ;
#endif /* CODE_VARIABLES_H_ */
