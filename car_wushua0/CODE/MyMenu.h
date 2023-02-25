/*
 * MyMenu.h
 *
 *  Created on: 2022年1月2日
 *      Author: 11609
 */
#include "headfile.h"
#ifndef CODE_MYMENU_H_
#define CODE_MYMENU_H_





//页面总数
#define Sum_Page        8                       //页面总数量
#define Max_Page        8                       //页面最大序号
#define Min_Page        1                       //页面最小序号
/*
//有刷单车
//上下中左右
#define KEY1    P20_2//左
#define KEY2    P21_6//上
#define KEY3    P20_0//中
#define KEY4    P21_7//下
#define KEY5    P21_5//右
*/

//无刷单车
//上下中左右
#define KEY1    P14_1//左
#define KEY2    P14_4//上
#define KEY3    P14_2//中

#define KEY4    P14_3//下

#define KEY5    P13_0//右

/*
#define KEY1    P22_0
#define KEY2    P22_1
#define KEY3    P23_1
#define KEY4    P22_2
#define KEY5    P22_3
*/

/*
//开发板
#define KEY1    P22_0
#define KEY2    P22_1
#define KEY3    P22_2
#define KEY4    P22_3
#define KEY5    P20_2
*/

//按键延时（ms）
#define DELAY_KEY               1500
#define DELAY_KEY_FAST          250

/*We fall in love********************************************************************/
#define IC_VERSION              "V1.0"//       版本日期
#define PageChange              "P+"//改变页数
#define ValueChange             "V+"//改变数值
/*We fall in love********************************************************************/


//  @param      Order      需要写入的扇区编号
//  @param      Addr        需要读取的页
//总共96K 一共有12个扇区
//每个扇区有1024页 一页大小8bit
#define i32_FlashReadInt32(Order,Addr)  ReadFlash(Order, Addr)



/*DebugBeg*************************************************************************/
#define Debug_Title                      "Debug"
#define Debug_Order                      Page_Order(1)
#define Debug_Num_Item                   6

//显示开启
#define Debug_Run_Title                 "run:"
#define Debug_Run_Order                  Item_Order(1)
#define Debug_Run_Value                  0
#define Debug_Run_MaxValue               1
#define Debug_Run_MinValue               0
#define Debug_Run_Rate                   1
#define Debug_Run_Addr                   FLASH_ADDR(0)

//显示二值化图像，爬梯图像，八近邻图像
#define Debug_DrawData_Title             "IMAG:"
#define Debug_DrawData_Order             Item_Order(2)
#define Debug_DrawData_Value             0
#define Debug_DrawData_MaxValue          5
#define Debug_DrawData_MinValue          0
#define Debug_DrawData_Rate              1
#define Debug_DrawData_Addr              FLASH_ADDR(1)

//阈值  第2页第3行
#define Debug_Threshold_Title            "Threshold:"
#define Debug_Threshold_Order            Item_Order(3)
#define Debug_Threshold_Value            i32_FlashReadInt32(Debug_Order,Debug_Threshold_Addr)
#define Debug_Threshold_MaxValue         200
#define Debug_Threshold_MinValue         0
#define Debug_Threshold_Rate             1
#define Debug_Threshold_Addr             FLASH_ADDR(2)

//设置速度
#define Debug_Speed_Title                "Speed:"
#define Debug_Speed_Order                Item_Order(4)
#define Debug_Speed_Value                i32_FlashReadInt32(Debug_Order,Debug_Speed_Addr)
#define Debug_Speed_MaxValue             300
#define Debug_Speed_MinValue             0
#define Debug_Speed_Rate                 1
#define Debug_Speed_Addr                 FLASH_ADDR(3)

//变量
#define Debug_Test_Title                "test:"
#define Debug_Test_Order                Item_Order(5)
#define Debug_Test_Value                i32_FlashReadInt32(Debug_Order,Debug_Test_Addr)
#define Debug_Test_MaxValue             100
#define Debug_Test_MinValue             0
#define Debug_Test_Rate                 1
#define Debug_Test_Addr                 FLASH_ADDR(4)

//变量
#define Debug_AD_Cam_Title                "2_Cam:"
#define Debug_AD_Cam_Order                Item_Order(6)
#define Debug_AD_Cam_Value                i32_FlashReadInt32(Debug_Order,Debug_AD_Cam_Addr)
#define Debug_AD_Cam_MaxValue             1
#define Debug_AD_Cam_MinValue             0
#define Debug_AD_Cam_Rate                 1
#define Debug_AD_Cam_Addr                 FLASH_ADDR(5)
/*DebugEnd*************************************************************************/
void DebugMenuInit (void);



/*StartBegin************************************************************************/
#define Start_Title                      "Angel"
#define Start_Order                      Page_Order(2)
#define Start_Num_Item                   6

#define Angle_zreo_Title                   "Angle_zreo:"
#define Angle_zreo_Order                   Item_Order(1)
#define Angle_zreo_Value                   i32_FlashReadInt32(Start_Order,Angle_zreo_Addr)
#define Angle_zreo_MaxValue                80
#define Angle_zreo_MinValue                -80
#define Angle_zreo_Rate                    1
#define Angle_zreo_Addr                    FLASH_ADDR(0)

//动量轮参数
#define Ang_vel_P_Title                   "Ang_vel_P:"
#define Ang_vel_P_Order                   Item_Order(2)
#define Ang_vel_P_Value                   i32_FlashReadInt32(Start_Order,Ang_vel_P_Addr)
#define Ang_vel_P_MaxValue                1000
#define Ang_vel_P_MinValue                0
#define Ang_vel_P_Rate                    1
#define Ang_vel_P_Addr                    FLASH_ADDR(1)


#define yingshe86_Title                   "YS_86:"
#define yingshe86_Order                   Item_Order(3)
#define yingshe86_Value                   i32_FlashReadInt32(Start_Order,yingshe86_Addr)
#define yingshe86_MaxValue                500
#define yingshe86_MinValue                0
#define yingshe86_Rate                    1
#define yingshe86_Addr                    FLASH_ADDR(2)

#define ramp_FK_Title                   "ramp_FK:"
#define ramp_FK_Order                   Item_Order(4)
#define ramp_FK_Value                   i32_FlashReadInt32(Start_Order,ramp_FK_Addr)
#define ramp_FK_MaxValue                500
#define ramp_FK_MinValue                0
#define ramp_FK_Rate                    1
#define ramp_FK_Addr                    FLASH_ADDR(3)

#define yingshe83_Title                   "YS_83:"
#define yingshe83_Order                   Item_Order(5)
#define yingshe83_Value                   i32_FlashReadInt32(Start_Order,yingshe83_Addr)
#define yingshe83_MaxValue                500
#define yingshe83_MinValue                0
#define yingshe83_Rate                    1
#define yingshe83_Addr                    FLASH_ADDR(4)

#define yingshe84_Title                   "YS_84:"
#define yingshe84_Order                   Item_Order(6)
#define yingshe84_Value                   i32_FlashReadInt32(Start_Order,yingshe84_Addr)
#define yingshe84_MaxValue                500
#define yingshe84_MinValue                0
#define yingshe84_Rate                    1
#define yingshe84_Addr                    FLASH_ADDR(5)
/*StartEnd************************************************************************/
void StartMenuInit (void);



/*pidBegin************************************************************************/
#define pid_Title                      "PID"
#define pid_Order                      Page_Order(3)
#define pid_Num_Item                   6



#define Ang_P_Title                   "Ang_P/10:"
#define Ang_P_Order                   Item_Order(1)
#define Ang_P_Value                   i32_FlashReadInt32(pid_Order,Ang_P_Addr)
#define Ang_P_MaxValue                500
#define Ang_P_MinValue                0
#define Ang_P_Rate                    1
#define Ang_P_Addr                    FLASH_ADDR(0)

#define yingshe87_2_Title                   "YS_87_2:"
#define yingshe87_2_Order                   Item_Order(2)
#define yingshe87_2_Value                   i32_FlashReadInt32(pid_Order,yingshe87_2_Addr)
#define yingshe87_2_MaxValue                500
#define yingshe87_2_MinValue                0
#define yingshe87_2_Rate                    1
#define yingshe87_2_Addr                    FLASH_ADDR(1)

#define speed_P_Title                   "speed_P/10:"
#define speed_P_Order                   Item_Order(3)
#define speed_P_Value                   i32_FlashReadInt32(pid_Order,speed_P_Addr)
#define speed_P_MaxValue                500
#define speed_P_MinValue                0
#define speed_P_Rate                    1
#define speed_P_Addr                    FLASH_ADDR(2)

#define yingshe32_Title                   "YS_32:"
#define yingshe32_Order                   Item_Order(4)
#define yingshe32_Value                   i32_FlashReadInt32(pid_Order,yingshe32_Addr)
#define yingshe32_MaxValue                500
#define yingshe32_MinValue                0
#define yingshe32_Rate                    1
#define yingshe32_Addr                    FLASH_ADDR(3)

#define P84_Title                   "84_P:"
#define P84_Order                   Item_Order(5)
#define P84_Value                   i32_FlashReadInt32(pid_Order,P84_Addr)
#define P84_MaxValue                500
#define P84_MinValue                0
#define P84_Rate                    1
#define P84_Addr                    FLASH_ADDR(4)

#define I84_Title                   "84_I:"
#define I84_Order                   Item_Order(6)
#define I84_Value                   i32_FlashReadInt32(pid_Order,I84_Addr)
#define I84_MaxValue                500
#define I84_MinValue                0
#define I84_Rate                    1
#define I84_Addr                    FLASH_ADDR(5)
/*pidEnd************************************************************************/
void pidMenuInit (void);



/*RingBegin************************************************************************/
#define Ring_Title                      "Ring"
#define Ring_Order                      Page_Order(4)
#define Ring_Num_Item                   6


#define Ring_RingNum_Title                   "RingNum:"
#define Ring_RingNum_Order                   Item_Order(1)
#define Ring_RingNum_Value                   i32_FlashReadInt32(Ring_Order,Ring_RingNum_Addr)
#define Ring_RingNum_MaxValue                4
#define Ring_RingNum_MinValue                0
#define Ring_RingNum_Rate                    1
#define Ring_RingNum_Addr                    FLASH_ADDR(0)


#define Ring_Ring1_Title                   "Ring1:"
#define Ring_Ring1_Order                   Item_Order(2)
#define Ring_Ring1_Value                   i32_FlashReadInt32(Ring_Order,Ring_Ring1_Addr)
#define Ring_Ring1_MaxValue                2
#define Ring_Ring1_MinValue                0
#define Ring_Ring1_Rate                    1
#define Ring_Ring1_Addr                    FLASH_ADDR(1)

#define yingshe35_Title                   "YS_34:"
#define yingshe35_Order                   Item_Order(3)
#define yingshe35_Value                   i32_FlashReadInt32(Ring_Order,yingshe35_Addr)
#define yingshe35_MaxValue                500
#define yingshe35_MinValue                0
#define yingshe35_Rate                    1
#define yingshe35_Addr                    FLASH_ADDR(2)

#define yingshe87_Title                   "YS_87:"
#define yingshe87_Order                   Item_Order(4)
#define yingshe87_Value                   i32_FlashReadInt32(Ring_Order,yingshe87_Addr)
#define yingshe87_MaxValue                500
#define yingshe87_MinValue                0
#define yingshe87_Rate                    1
#define yingshe87_Addr                    FLASH_ADDR(3)

#define yingshe81_Title                   "YS_81:"
#define yingshe81_Order                   Item_Order(5)
#define yingshe81_Value                   i32_FlashReadInt32(Ring_Order,yingshe81_Addr)
#define yingshe81_MaxValue                500
#define yingshe81_MinValue                0
#define yingshe81_Rate                    1
#define yingshe81_Addr                    FLASH_ADDR(4)

#define yingshe52_Title                   "YS_52:"
#define yingshe52_Order                   Item_Order(6)
#define yingshe52_Value                   i32_FlashReadInt32(Ring_Order,yingshe52_Addr)
#define yingshe52_MaxValue                500
#define yingshe52_MinValue                0
#define yingshe52_Rate                    1
#define yingshe52_Addr                    FLASH_ADDR(5)

/*RingEnd************************************************************************/
void RingMenuInit (void);

/*chooseBegin************************************************************************/
#define Choose_Title                      "Choose"
#define Choose_Order                      Page_Order(5)
#define Choose_Num_Item                   6


#define is_checkZebro_Title                   "is_RukuZebro:"
#define is_checkZebro_Order                   Item_Order(1)
#define is_checkZebro_Value                   i32_FlashReadInt32(Choose_Order,is_checkZebro_Addr)
#define is_checkZebro_MaxValue                2
#define is_checkZebro_MinValue                0
#define is_checkZebro_Rate                    1
#define is_checkZebro_Addr                    FLASH_ADDR(0)


#define is_ChuKu_Title                   "is_ChuKu:"
#define is_ChuKu_Order                   Item_Order(2)
#define is_ChuKu_Value                   i32_FlashReadInt32(Choose_Order,is_ChuKu_Addr)
#define is_ChuKu_MaxValue                2
#define is_ChuKu_MinValue                0
#define is_ChuKu_Rate                    1
#define is_ChuKu_Addr                    FLASH_ADDR(1)

#define speed34_Title                   "speed34:"
#define speed34_Order                   Item_Order(3)
#define speed34_Value                   i32_FlashReadInt32(Choose_Order,speed34_Addr)
#define speed34_MaxValue                100
#define speed34_MinValue                0
#define speed34_Rate                    1
#define speed34_Addr                    FLASH_ADDR(2)


#define speed84_Title                   "speed84_2:"
#define speed84_Order                   Item_Order(4)
#define speed84_Value                   i32_FlashReadInt32(Choose_Order,speed84_Addr)
#define speed84_MaxValue                100
#define speed84_MinValue                0
#define speed84_Rate                    1
#define speed84_Addr                    FLASH_ADDR(3)


#define r_f_p_Title                   "34_P:"
#define r_f_p_Order                   Item_Order(5)
#define r_f_p_Value                   i32_FlashReadInt32(Choose_Order,r_f_p_Addr)
#define r_f_p_MaxValue                500
#define r_f_p_MinValue                0
#define r_f_p_Rate                    1
#define r_f_p_Addr                    FLASH_ADDR(4)


#define r_f_I_Title                   "34_I:"
#define r_f_I_Order                   Item_Order(6)
#define r_f_I_Value                   i32_FlashReadInt32(Choose_Order,r_f_I_Addr)
#define r_f_I_MaxValue                500
#define r_f_I_MinValue                0
#define r_f_I_Rate                    1
#define r_f_I_Addr                    FLASH_ADDR(5)
/*chooseEnd************************************************************************/
void ChooseMenuInit (void);


/*yinghsheBegin************************************************************************/
#define yingshe_Title                      "Bend"
#define yingshe_Order                      Page_Order(6)
#define yingshe_Num_Item                   6


#define ringy_Title                   "YS_ring:"
#define ringy_Order                   Item_Order(1)
#define ringy_Value                   i32_FlashReadInt32(yingshe_Order,ringy_Addr)
#define ringy_MaxValue                500
#define ringy_MinValue                0
#define ringy_Rate                    1
#define ringy_Addr                    FLASH_ADDR(0)


#define rampy_Title                   "YS_31:"
#define rampy_Order                   Item_Order(2)
#define rampy_Value                   i32_FlashReadInt32(yingshe_Order,rampy_Addr)
#define rampy_MaxValue                500
#define rampy_MinValue                0
#define rampy_Rate                    1
#define rampy_Addr                    FLASH_ADDR(1)

#define ChuKuy_Title                   "YS_chuku:"
#define ChuKuy_Order                   Item_Order(3)
#define ChuKuy_Value                   i32_FlashReadInt32(yingshe_Order,ChuKuy_Addr)
#define ChuKuy_MaxValue                500
#define ChuKuy_MinValue                0
#define ChuKuy_Rate                    1
#define ChuKuy_Addr                    FLASH_ADDR(2)


#define yingsheS_Title                   "YS_yingshe:"
#define yingsheS_Order                   Item_Order(4)
#define yingsheS_Value                   i32_FlashReadInt32(yingshe_Order,yingsheS_Addr)
#define yingsheS_MaxValue                500
#define yingsheS_MinValue                0
#define yingsheS_Rate                    1
#define yingsheS_Addr                    FLASH_ADDR(3)

#define fork0_Title                   "YS_fork0:"
#define fork0_Order                   Item_Order(5)
#define fork0_Value                   i32_FlashReadInt32(yingshe_Order,fork0_Addr)
#define fork0_MaxValue                500
#define fork0_MinValue                0
#define fork0_Rate                    1
#define fork0_Addr                    FLASH_ADDR(4)

#define ring16_Title                   "YS_ring16:"
#define ring16_Order                   Item_Order(6)
#define ring16_Value                   i32_FlashReadInt32(yingshe_Order,ring16_Addr)
#define ring16_MaxValue                500
#define ring16_MinValue                0
#define ring16_Rate                    1
#define ring16_Addr                    FLASH_ADDR(5)
/*yingsheEnd************************************************************************/
void yingsheMenuInit (void);

/*tarspeedBegin************************************************************************/
#define tarspeed_Title                      "Tar_Sp"
#define tarspeed_Order                      Page_Order(7)
#define tarspeed_Num_Item                   6


#define ringt_Title                   "sp_ring:"
#define ringt_Order                   Item_Order(1)
#define ringt_Value                   i32_FlashReadInt32(tarspeed_Order,ringt_Addr)
#define ringt_MaxValue                500
#define ringt_MinValue                0
#define ringt_Rate                    1
#define ringt_Addr                    FLASH_ADDR(0)


#define rampt_Title                   "sp1_81:"
#define rampt_Order                   Item_Order(2)
#define rampt_Value                   i32_FlashReadInt32(tarspeed_Order,rampt_Addr)
#define rampt_MaxValue                100
#define rampt_MinValue                0
#define rampt_Rate                    1
#define rampt_Addr                    FLASH_ADDR(1)

#define ChuKut_Title                   "sp_cheku:"
#define ChuKut_Order                   Item_Order(3)
#define ChuKut_Value                   i32_FlashReadInt32(tarspeed_Order,ChuKut_Addr)
#define ChuKut_MaxValue                100
#define ChuKut_MinValue                0
#define ChuKut_Rate                    1
#define ChuKut_Addr                    FLASH_ADDR(2)

#define Fork0_Title                   "sp_fork0:"
#define Fork0_Order                   Item_Order(4)
#define Fork0_Value                   i32_FlashReadInt32(tarspeed_Order,Fork0_Addr)
#define Fork0_MaxValue                100
#define Fork0_MinValue                0
#define Fork0_Rate                    1
#define Fork0_Addr                    FLASH_ADDR(3)

#define ring16_sp_Title                   "sp_r16:"
#define ring16_sp_Order                   Item_Order(5)
#define ring16_sp_Value                   i32_FlashReadInt32(tarspeed_Order,ring16_sp_Addr)
#define ring16_sp_MaxValue                100
#define ring16_sp_MinValue                0
#define ring16_sp_Rate                    1
#define ring16_sp_Addr                    FLASH_ADDR(4)

#define yingshe85_Title                   "YS_85:"
#define yingshe85_Order                   Item_Order(6)
#define yingshe85_Value                   i32_FlashReadInt32(tarspeed_Order,yingshe85_Addr)
#define yingshe85_MaxValue                500
#define yingshe85_MinValue                0
#define yingshe85_Rate                    1
#define yingshe85_Addr                    FLASH_ADDR(5)
/*tarspeedEnd************************************************************************/
void tarspeedMenuInit (void);


/*ForkOutBegin************************************************************************/
#define ForkOut_Title                      "FK_Out"
#define ForkOut_Order                      Page_Order(8)
#define ForkOut_Num_Item                   6


#define speed85_Title                   "speed85_2:"
#define speed85_Order                   Item_Order(1)
#define speed85_Value                   i32_FlashReadInt32(ForkOut_Order,speed85_Addr)
#define speed85_MaxValue                500
#define speed85_MinValue                0
#define speed85_Rate                    1
#define speed85_Addr                    FLASH_ADDR(0)


#define yingshe84_2_Title                   "YS_84_2:"
#define yingshe84_2_Order                   Item_Order(2)
#define yingshe84_2_Value                   i32_FlashReadInt32(ForkOut_Order,yingshe84_2_Addr)
#define yingshe84_2_MaxValue                500
#define yingshe84_2_MinValue                0
#define yingshe84_2_Rate                    1
#define yingshe84_2_Addr                    FLASH_ADDR(1)

#define yingshe85_2_Title                   "YS_85_2:"
#define yingshe85_2_Order                   Item_Order(3)
#define yingshe85_2_Value                   i32_FlashReadInt32(ForkOut_Order,yingshe85_2_Addr)
#define yingshe85_2_MaxValue                500
#define yingshe85_2_MinValue                0
#define yingshe85_2_Rate                    1
#define yingshe85_2_Addr                    FLASH_ADDR(2)

#define speed_86_87_Title             "SP1_86_87:"
#define speed_86_87_Order                   Item_Order(4)
#define speed_86_87_Value                   i32_FlashReadInt32(ForkOut_Order,speed_86_87_Addr)
#define speed_86_87_MaxValue                500
#define speed_86_87_MinValue                0
#define speed_86_87_Rate                    1
#define speed_86_87_Addr                    FLASH_ADDR(3)

#define yingshe86_2_Title                   "YS_86_2:"
#define yingshe86_2_Order                   Item_Order(5)
#define yingshe86_2_Value                   i32_FlashReadInt32(ForkOut_Order,yingshe86_2_Addr)
#define yingshe86_2_MaxValue                500
#define yingshe86_2_MinValue                0
#define yingshe86_2_Rate                    1
#define yingshe86_2_Addr                    FLASH_ADDR(4)

#define I_86_87_Title                   "I_86_87:"
#define I_86_87_Order                   Item_Order(6)
#define I_86_87_Value                   i32_FlashReadInt32(ForkOut_Order,I_86_87_Addr)
#define I_86_87_MaxValue                500
#define I_86_87_MinValue                0
#define I_86_87_Rate                    1
#define I_86_87_Addr                    FLASH_ADDR(5)
/*ForkOutEnd************************************************************************/
void ForkOutMenuInit (void);

//初始化菜单
void InitMenu (void);

//ADD按键附加功能
void ADD_ADT (void);

//SUB按键附加功能
void SUB_ADT (void);

//UP按键附加功能
void UP_ADT (void);

//DOWN按键附加功能
void DOWN_ADT (void);

//LEFT按键附加功能
void LEFT_ADT (void);

//RIGHT按键附加功能
void RIGHT_ADT (void);

/*引入需要更改*****************************************************************/

/*内部工作*********************************************************************/

//按键读取      22_0    22_1    22_2    22_3    23_1



//按键读取
#define KEY_UP     0
#define KEY_DOWN   1
#define KEY_ADD    2
#define KEY_SUB    3
#define KEY_LEFT   4
#define KEY_RIGHT  5


#define UP     !gpio_get(KEY1)
#define DOWN   !gpio_get(KEY2)
#define CENTER !gpio_get(KEY3)
#define LEFT   !gpio_get(KEY4)
#define RIGHT  !gpio_get(KEY5)



#define byte uint8


//页面序号 对应扇区
#define Page_Order(x)           (x-1)
//项目序号
#define Item_Order(x)           x
//项目选中标志
#define Item_Flag(x)            x

//写到固定一个扇区的X页
#define FLASH_ADDR(x)       x

/*页面管理结构体*/
typedef struct {
  //当前页面
  uint8  ui8_NowPage;
  //当前显示页面
  uint8 ui8_NowDisPage;
  //当前选择标志位置
  uint8 ui8_NowFlag;
  //改变值标志
  uint8 ui8_ChangeValueFlag;
  //最后响应按键
  uint8 ui8_LastKey;
} MenuControl_InitTypeDef;

/*项目结构体*/
typedef struct {
  //项目标题
  byte Item_Title[20];
  //项目次序
  uint8 Item_Order;
  //项目值
  int32 Item_Value;
  //项目最大值
  int16 Item_MaxValue;
  //项目最小值
  int16 Item_MinValue;
  //项目值倍率
  double Item_Rate;
  //项目值存储位置
  uint32 Addr;
} Option_InitTypeDef;

/*页面结构体*/
typedef struct {
  //页面标题
  byte Page_Title[20];
  //页面次序
  uint8 Page_Order;
  //页面项目数量
  uint8 Page_Num_Item;
  //项目结构体数组
  Option_InitTypeDef Option[20];
} Menu_InitTypeDef;

//键盘初始化
void KeyInit (void);

//键盘工作
void KeyWork (void);

//显示菜单
void DisplayMenu (Menu_InitTypeDef M);

//显示页面
void DisplayPage (uint8 ui8_Page);

//显示图标
void DisplayIcon (void);

//显示值
void DisplayItemValue(int16 i16_Value, uint8 ui8_Row);

//显示标志
void DisplayItemFlag(void);

//获取值
double GetItemValue (uint8 ui8_Page, uint8 ui8_Item);

//加值
void AddItemValue (uint8 ui8_Page, uint8 ui8_Item);

//减值
void SubItemValue (uint8 ui8_Page, uint8 ui8_Item);

//设置值
void SetItemValue (uint8 ui8_Page, uint8 ui8_Item, double d_Value);

//存储数据
void SaveData (uint8 ui8_Page, uint8 ui8_Item);

//改变标志
void ChangeMenuFlag (uint8 ui8_UpDown);

//改变页面
void ChangeMenuPage (uint8 ui8_LeftRight);

//按键GPIO初始化
void InitKeyGpio(void);

extern MenuControl_InitTypeDef MCtrl;
/*内部工作*********************************************************************/





#endif /* CODE_MYMENU_H_ */
