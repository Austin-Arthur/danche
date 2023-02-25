/*
 * Variables.h
 *
 *  Created on: 2021��12��30��
 *      Author: 11609
 */

#ifndef CODE_VARIABLES_H_
#define CODE_VARIABLES_H_
#include "headfile.h"
typedef struct Point//��ṹ��
{
  int16 X;
  int16 Y;
}Point;
typedef struct Cnst//��ֵ�ṹ��
{
  uint8 cnst;      //��ֵ
  uint8 setMaxCnst;  //�趨��ֵ
  uint8 offsetCnst;//��̬��ֵƫ����
  int Bright_cnt;//����
  uint16 exp_time;//�ع�ʱ��
  uint8 cnst0;
  uint8 cnst1;
  uint8 num;
}Cnst;
typedef struct Ring//Բ���ṹ��
{
  float variance;//ֱ�߷���
  uint8 A_y;
  uint8 B_y;
  uint8 C_y;//�ж�Բ����������
  uint8 D_x;
  uint8 D_y;//���������
}Ring;
typedef struct//8���ڽṹ��
{
  uint16 time[2];
  uint16 Time[2][64];
  int8 now_Dir[2];//����
  Point borderPoint[2];
  uint8 maxValue[2];
} _8feature;
typedef struct  TwoDot//��������ṹ��
{
  uint8 AllMaxY; //ȫͼ��Զ�� �����յ㣨����㣩
  uint8 ui8_StartL;//������� ��
  uint8 ui8_StartR;//������� ��
}TwoDot;

typedef struct  DataI//ͼ�����ݽṹ��
{
  uint8 Ladder_LBorder[64];//������߽�
  uint8 Ladder_RBorder[64]; //�����ұ߽�
  uint8 Ladder_MidPoint[64];//�����е�
  uint16 AD_L;//��ߵ��ֵ
  uint16 AD_R;//�ұߵ��ֵ
  uint16 AD_M;//�ұߵ��ֵ
  uint16 AD_VL;//�ұߵ��ֵ
  uint16 AD_VR;//�ұߵ��ֵ
  uint8 ad_p; //���PID
  uint8 ad_d;
  float AD_err;//��е�ǰ���
  float error;
  uint8 Inflection_x[2];//��¼�յ�
  uint8 Inflection_y[2];//��¼�յ�
  uint8 IEX[2][64];//�ڱ߽�
  uint8 CUR[2][64];//��λ����
  int8  Dir[2][300];//���巽������
  Point DOT[2][300];//�˽��ڱ߽�����
  uint8 MEX[2][64][94]; //����߽�
  uint8 OEX[2][64];//��߽�
  uint8 Top_edge_Y[94];//��С���ؾ���  ���Y
  uint8 Top_max_Y[94]; //�����Ӿ���
  uint8 Line_Selected_Y[7];//�Ⱦ����������
  uint8 RingSumCnt;//Բ���ܸ���
  uint8 DuanLu_cnt;//��¼������·��ϵĸ���
  uint8 HD_DLSumCnt;//��϶�·�ܸ���
  uint8 HD_DL[15];
  uint8 top_Y;//�˽�����Զ����
  uint8 flag;//���߱�־
  uint8 set;//��������־
  long LengthCnt;//��������������
  long Length;//С�����о��� ��λcm
  int Length_angle;//С�����о��� ��λcm
  int tempLength; //��ʱ��¼С������
  int LengthBend;//��¼�������
  int LengthRing;//���ؾ�
  int LengthRamp;//�µ��Ӿ�
  int LengthCheku;//���ⲹ��
  int Lengthfork;//С�����о��� ��λcm
  uint8 ramp_flag;//�µ���־
  uint8 MaxY[11];//ͼ�񵥱���Զ��
  float Data[60];//��ʱ��ʾ����
  float MidLine; //����
  float chaSu;//����ϵ��
  int rampCnt;//�µ�����
  uint8 rampV;//�µ��ٶ�
  uint8 hengDuanV;//����ٶ�
  uint8 elecV;//����ٶ�
  uint16 setLength;  //�趨����
  uint8 SightDistance;//���Ӿ���
  uint8 ring2DL;//���ж�·
  uint8 yyy;
  uint8 speed_flag;
  float ZhiDao_radio;
  uint8 isSloop;
  uint8 maxCnt;
  uint8 isVdown;
  uint16 DLZDlength;
  uint8 ForkCnt;
  int ForkLength;//����·�Ӿ�
  float Angle_error;
  float Angle_target;
  //ɨ������߽�(����)
  uint8 ui8_ScanLineL[10];
  //ɨ�����ұ߽�(����)
  uint8 ui8_ScanLineR[10];

  uint8 Two_Cam;
  uint8 ZebroNum;
}DataI;
typedef enum
{
  INITING ,     //��ʼ��״̬
  DEBUG,        //����״̬
  RUN,          //����״̬
  STOP,         //ͣ��״̬
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
extern float xztt[10] ;//���Ա���
extern int test_y[10] ;
#endif /* CODE_VARIABLES_H_ */
