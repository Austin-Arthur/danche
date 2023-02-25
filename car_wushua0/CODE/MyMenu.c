/*
 * MyMenu.c
 *
 *  Created on: 2022年1月2日
 *      Author: 11609
 */
/*
 * Menu.c
 *
 *  Created on: 2021年12月31日
 *      Author: 11609
 */
#include "MyMenu.h"

uint8 Key_Change = 0;

/*变量初始化-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
MenuControl_InitTypeDef MCtrl =
    {
        Page_Order(1),
        Min_Page,
        Item_Flag(1),
        0,
        KEY_UP,
};

Menu_InitTypeDef Page[Sum_Page] =
    {
        /*添加/删除页面都要改变*/
        {
            Debug_Title,
            Debug_Order,
            Debug_Num_Item},
        /*添加/删除页面都要改变*/
        {
            Start_Title,
            Start_Order,
            Start_Num_Item},
        {pid_Title,
         pid_Order,
         pid_Num_Item},
        {Ring_Title,
         Ring_Order,
         Ring_Num_Item},
        {Choose_Title,
         Choose_Order,
         Choose_Num_Item},
        {yingshe_Title,
         yingshe_Order,
         yingshe_Num_Item},
        {tarspeed_Title,
         tarspeed_Order,
         tarspeed_Num_Item},
         {ForkOut_Title,
          ForkOut_Order,
          ForkOut_Num_Item},

};
/*变量初始化-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/************************************************************************
函数名：DelayMs
函数作用：延时
************************************************************************/
void DelayMs(int f_Ms)
{
  uint16 ui16_Ms = (uint16)f_Ms;
  uint16 ui16_Us = (uint16)((f_Ms - (int16)f_Ms) * 1000);
  for (uint16 ui16_I = 0; ui16_I < ui16_Ms; ui16_I++)
  {
    for (uint16 ui16_J = 0; ui16_J < 19177; ui16_J++)
      ;
  }
  for (uint16 ui16_I = 0; ui16_I < ui16_Us; ui16_I++)
  {
    for (uint16 ui16_J = 0; ui16_J < 19; ui16_J++)
      ;
  }
}

/************************************************************************
函数名：初始化菜单
功能：菜单初始化
每加一个页面，多一个页面初始化
************************************************************************/
void InitMenu(void)
{
  KeyInit();
  StartMenuInit(); // Start页面初始化
  DebugMenuInit(); // Init页面初始化
  RingMenuInit();
  pidMenuInit();
  ChooseMenuInit();
  yingsheMenuInit();
  tarspeedMenuInit();
  ForkOutMenuInit();
  DisplayPage(MCtrl.ui8_NowPage); //初始化完成显示首页
}

/************************************************************************
函数名：KeyInit
功能：按键初始化
************************************************************************/
void KeyInit(void)
{
  gpio_init(KEY1, GPI, 0, PULLUP);
  gpio_init(KEY2, GPI, 0, PULLUP);
  gpio_init(KEY3, GPI, 0, PULLUP);
  gpio_init(KEY4, GPI, 0, PULLUP);
  gpio_init(KEY5, GPI, 0, PULLUP);

  //  gpio_init(KE1,GPI,0,PULLUP);
  //  gpio_init(KE2,GPI,0,PULLUP);
  //  gpio_init(KE3,GPI,0,PULLUP);
  //  gpio_init(KE4,GPI,0,PULLUP);
  //  gpio_init(KE5,GPI,0,PULLUP);
}

/************************************************************************
函数名：KeyWork
功能：按键工作
************************************************************************/
void KeyWork(void)
{
  uint16 ui16_DK = DELAY_KEY;
  while (CENTER)
  {
    Key_Change++;
    Key_Change %= 2;
    if (ui16_DK > DELAY_KEY_FAST)
    {
      ui16_DK -= DELAY_KEY_FAST;
      DelayMs(ui16_DK);
    }
    else
    {
      DelayMs(DELAY_KEY_FAST);
    }
    DisplayIcon();
  }

  while (UP)
  {           //箭头上移
    UP_ADT(); //刷Flash
    ChangeMenuFlag(UP);
    if (ui16_DK > DELAY_KEY_FAST)
    {
      DelayMs(ui16_DK -= DELAY_KEY_FAST);
    }
    else
    {
      DelayMs(DELAY_KEY_FAST);
    }
  }

  while (DOWN)
  {             //箭头下移
    DOWN_ADT(); //刷Flash
    ChangeMenuFlag(!DOWN);
    if (ui16_DK > DELAY_KEY_FAST)
    {
      DelayMs(ui16_DK -= DELAY_KEY_FAST);
    }
    else
    {
      DelayMs(DELAY_KEY_FAST);
    }
  }
  //翻页
  if (Key_Change == 0) //翻页
  {
    while (LEFT)
    {
      LEFT_ADT();           //刷Flash
      ChangeMenuPage(LEFT); //翻页
      if (ui16_DK > DELAY_KEY_FAST)
      {
        DelayMs(ui16_DK -= DELAY_KEY_FAST);
      }
      else
      {
        DelayMs(DELAY_KEY_FAST);
      }
    }

    while (RIGHT)
    {
      RIGHT_ADT(); //刷FLASH
      ChangeMenuPage(!RIGHT);
      if (ui16_DK > DELAY_KEY_FAST)
      {
        DelayMs(ui16_DK -= DELAY_KEY_FAST);
      }
      else
      {
        DelayMs(DELAY_KEY_FAST);
      }
    }
  }
  //数据加减
  else if (Key_Change == 1) //改变数据
  {
    while (LEFT)
    {
      SUB_ADT(); //数据减 Flash未改变
      if (ui16_DK > DELAY_KEY_FAST)
      {
        DelayMs(ui16_DK -= DELAY_KEY_FAST);
      }
      else
      {
        DelayMs(DELAY_KEY_FAST);
      }
    }

    while (RIGHT)
    { //数据加
      ADD_ADT();
      if (ui16_DK > DELAY_KEY_FAST)
      {
        DelayMs(ui16_DK -= DELAY_KEY_FAST);
      }
      else
      {
        DelayMs(DELAY_KEY_FAST);
      }
    }
  }
}

/************************************************************************
函数名：ADD按键附加功能
************************************************************************/
void ADD_ADT(void)
{
  //系统加
  AddItemValue(MCtrl.ui8_NowPage, MCtrl.ui8_NowFlag);
  MCtrl.ui8_LastKey = KEY_SUB;
  MCtrl.ui8_ChangeValueFlag = 1;
}

/************************************************************************
函数名：SUB按键附加功能
************************************************************************/
void SUB_ADT(void)
{
  //系统减
  SubItemValue(MCtrl.ui8_NowPage, MCtrl.ui8_NowFlag);
  MCtrl.ui8_LastKey = KEY_SUB;
  MCtrl.ui8_ChangeValueFlag = 1;
}
/************************************************************************
函数名：UP按键附加功能
************************************************************************/
void UP_ADT(void)
{
  MCtrl.ui8_LastKey = KEY_UP;
  if (MCtrl.ui8_ChangeValueFlag) //是否改变
  {
    SaveData(MCtrl.ui8_NowPage, MCtrl.ui8_NowFlag); //存储FLASH
    MCtrl.ui8_ChangeValueFlag = 0;                  //改变标志清除
  }
}

/************************************************************************
函数名：DOWN按键附加功能
************************************************************************/
void DOWN_ADT(void)
{
  MCtrl.ui8_LastKey = KEY_DOWN;
  if (MCtrl.ui8_ChangeValueFlag) //是否改变
  {
    SaveData(MCtrl.ui8_NowPage, MCtrl.ui8_NowFlag); //存储FLASH
    MCtrl.ui8_ChangeValueFlag = 0;
  }
}

/************************************************************************
函数名：LEFT按键附加功能
************************************************************************/
void LEFT_ADT(void)
{
  MCtrl.ui8_LastKey = KEY_LEFT;
  if (MCtrl.ui8_ChangeValueFlag)
  {
    SaveData(MCtrl.ui8_NowPage, MCtrl.ui8_NowFlag);
    MCtrl.ui8_ChangeValueFlag = 0;
  }
}

/************************************************************************
函数名：RIGHT按键附加功能
************************************************************************/
void RIGHT_ADT(void)
{
  MCtrl.ui8_LastKey = KEY_RIGHT;
  if (MCtrl.ui8_ChangeValueFlag)
  {
    SaveData(MCtrl.ui8_NowPage, MCtrl.ui8_NowFlag);
    MCtrl.ui8_ChangeValueFlag = 0;
  }
}

/************************************************************************
函数名：获取值
功能：获取对应项目值
参数：ui8_Page---页面位置(例如：Start_Order)
      ui8_Item---项目位置(例如：Start_Delay_Order)
************************************************************************/
double GetItemValue(uint8 ui8_Page, uint8 ui8_Item)
{
  //读取倍率转换
  return Page[ui8_Page].Option[ui8_Item].Item_Value *
         Page[ui8_Page].Option[ui8_Item].Item_Rate;
}

/************************************************************************
函数名：设置值
功能：设置对应项目值
参数：ui8_Page---页面位置(例如：Start_Order)
      ui8_Item---项目位置(例如：Start_Delay_Order)
      d_Value----项目值
************************************************************************/
void SetItemValue(uint8 ui8_Page, uint8 ui8_Item, double d_Value)
{
  //写入倍率转换
  d_Value /= Page[ui8_Page].Option[ui8_Item].Item_Rate;
  //判定范围
  if (d_Value > Page[ui8_Page].Option[ui8_Item].Item_MaxValue)
  {
    Page[ui8_Page].Option[ui8_Item].Item_Value = Page[ui8_Page].Option[ui8_Item].Item_MaxValue;
  }
  else if (d_Value < Page[ui8_Page].Option[ui8_Item].Item_MinValue)
  {
    Page[ui8_Page].Option[ui8_Item].Item_Value = Page[ui8_Page].Option[ui8_Item].Item_MinValue;
  }
  else
  {
    Page[ui8_Page].Option[ui8_Item].Item_Value = (int)d_Value;
  }
  DisplayPage(MCtrl.ui8_NowPage);
}

/************************************************************************
函数名：改变标志
功能：选择改变标志
参数：ui8_UpDown---标志移动方向
************************************************************************/
void ChangeMenuFlag(uint8 ui8_UpDown)
{
  //记录当前选中项

  if (ui8_UpDown)
  {
    MCtrl.ui8_NowFlag = MCtrl.ui8_NowFlag > Item_Flag(1) ? (MCtrl.ui8_NowFlag - 1) : Item_Flag(Page[MCtrl.ui8_NowPage].Page_Num_Item);
  }
  else
  {
    MCtrl.ui8_NowFlag = MCtrl.ui8_NowFlag < Page[MCtrl.ui8_NowPage].Page_Num_Item
                            ? (MCtrl.ui8_NowFlag + 1)
                            : Item_Flag(1);
  }

  MCtrl.ui8_NowDisPage = MCtrl.ui8_NowFlag / 7 + 1;

  //刷新显示
  DisplayPage(MCtrl.ui8_NowPage);
}

/************************************************************************
函数名：改变页面
功能：改变页面参数
参数：ui8_LeftRight---切换页面方向
************************************************************************/
void ChangeMenuPage(uint8 ui8_LeftRight)
{
  //记录当前选中页
  if (ui8_LeftRight)
  {
    MCtrl.ui8_NowPage = MCtrl.ui8_NowPage > Page_Order(Min_Page)
                            ? (MCtrl.ui8_NowPage - 1)
                            : Page_Order(Max_Page);
  }
  else
  {
    MCtrl.ui8_NowPage = MCtrl.ui8_NowPage < Page_Order(Max_Page) ? (MCtrl.ui8_NowPage + 1) : Page_Order(Min_Page);
  }

  MCtrl.ui8_NowFlag = Item_Flag(1);
  MCtrl.ui8_NowDisPage = Page_Order(1 + 1);

  DisplayPage(MCtrl.ui8_NowPage);
}

/************************************************************************
函数名：显示页面
功能：显示当前页面
参数：ui8_Page---页面序号
************************************************************************/
void DisplayPage(uint8 ui8_Page)
{
  //调用显示时记录当前选中页
  MCtrl.ui8_NowPage = ui8_Page;
  DisplayMenu(Page[ui8_Page]);
}

/************************************************************************
函数名：加值
功能：根据当前标志，选择增加值的结构体
参数：ui8_Page---页面序号
     ui8_Item---条目序号
************************************************************************/
void AddItemValue(uint8 ui8_Page, uint8 ui8_Item)
{
  //范围内循环加
  int16 Value = Page[ui8_Page].Option[ui8_Item].Item_Value + 1;
  if (Value <= Page[ui8_Page].Option[ui8_Item].Item_MaxValue)
  {
    Page[ui8_Page].Option[ui8_Item].Item_Value = Value;
  }
  else
  {
    Page[ui8_Page].Option[ui8_Item].Item_Value =
        Page[ui8_Page].Option[ui8_Item].Item_MinValue;
  }
  if (Page[Debug_Order].Option[Debug_DrawData_Order].Item_Value == 0 || MCtrl.ui8_NowPage != Debug_Order)
    DisplayPage(MCtrl.ui8_NowPage);
  else
    oled_fill(0);
}

/************************************************************************
函数名：减值
功能：根据当前标志，选择减少值的结构体
参数：ui8_Page---页面序号
      ui8_Item---条目序号
************************************************************************/
void SubItemValue(uint8 ui8_Page, uint8 ui8_Item)
{ //范围内循环减
  int16 Value = Page[ui8_Page].Option[ui8_Item].Item_Value - 1;
  if (Value >= Page[ui8_Page].Option[ui8_Item].Item_MinValue)
  {
    Page[ui8_Page].Option[ui8_Item].Item_Value = Value;
  }
  else
  {
    Page[ui8_Page].Option[ui8_Item].Item_Value =
        Page[ui8_Page].Option[ui8_Item].Item_MaxValue;
  }
  if (Page[Debug_Order].Option[Debug_DrawData_Order].Item_Value == 0 || MCtrl.ui8_NowPage != Debug_Order)
    DisplayPage(MCtrl.ui8_NowPage);
  else
    oled_fill(0);
}

/************************************************************************
函数名：显示菜单
功能：显示对应菜单参数
参数：M---项目结构图
************************************************************************/
void DisplayMenu(Menu_InitTypeDef M)
{

  uint8 ui8_MaxItem = (MCtrl.ui8_NowDisPage * 6) > M.Page_Num_Item ? M.Page_Num_Item : (MCtrl.ui8_NowDisPage * 6);

  //清屏
  oled_fill(0);
  //显示页面标题和分割线
  oled_p8x16str(0, 0, M.Page_Title);
  // oled_p6x8str(40, 0, "|");

  for (uint8 ui8_I = (MCtrl.ui8_NowDisPage - 1) * 6 + 1; ui8_I <= ui8_MaxItem; ui8_I++)
  {
    //显示项目标题
    oled_p6x8str(12, M.Option[ui8_I].Item_Order + 1 - (MCtrl.ui8_NowDisPage - 1) * 6,
                 M.Option[ui8_I].Item_Title);
    //显示项目值
    DisplayItemValue(M.Option[ui8_I].Item_Value, M.Option[ui8_I].Item_Order + 1);
  }

  //显示选中标志
  DisplayItemFlag();
  //显示状态标志
  DisplayIcon();
}

/************************************************************************
函数名：显示图标
功能：显示状态
************************************************************************/
void DisplayIcon(void)
{

  //显示日期版本号
  oled_p6x8str(48, 1, IC_VERSION);
  //按钮切换
  if (Key_Change == 1)
  {
    oled_p6x8str(48, 0, ValueChange);
  }
  else
  {
    oled_p6x8str(48, 0, PageChange);
  }
  oled_p6x8str(60, 0, " ");
}

/************************************************************************
函数名：显示值
功能：显示对应数值
参数：i16_Value---值
      ui8_Row---行坐标
************************************************************************/
void DisplayItemValue(int16 i16_Value, uint8 ui8_Row)
{
  uint8 ui8_Fu = 0;

  //记录正负
  if (i16_Value < 0)
  {
    i16_Value = -i16_Value;
    ui8_Fu = 1;
  }
  if (ui8_Row >= 8)
    ui8_Row += 2;

  oled_p6x8str(79, ui8_Row, "        ");

  uint8 ui8_Num[2] = " ";
  uint8 ui8_Dis = 127;

  //从右到左显示
  do
  {
    *ui8_Num = i16_Value % 10 + 48;
    oled_p6x8str(ui8_Dis -= 6, ui8_Row, ui8_Num);
  } while (i16_Value /= 10);

  if (ui8_Fu)
  {
    oled_p6x8str(ui8_Dis -= 6, ui8_Row, "-");
  }
}

/************************************************************************
函数名：显示标志
功能：显示并清除标志
************************************************************************/
void DisplayItemFlag(void)
{
  oled_p6x8str(0, MCtrl.ui8_NowFlag % 7 + MCtrl.ui8_NowDisPage, "->");
}

/************************************************************************
函数名：Init页面初始化
功能：初始化初始化页面结构体
************************************************************************/
void DebugMenuInit(void)
{

  Option_InitTypeDef Option_Run = {
      Debug_Run_Title,
      Debug_Run_Order,
      Debug_Run_Value,
      Debug_Run_MaxValue,
      Debug_Run_MinValue,
      Debug_Run_Rate,
      Debug_Run_Addr};
  Page[Debug_Order].Option[Debug_Run_Order] = Option_Run;

  Option_InitTypeDef Option_DrawData = {
      Debug_DrawData_Title,
      Debug_DrawData_Order,
      Debug_DrawData_Value,
      Debug_DrawData_MaxValue,
      Debug_DrawData_MinValue,
      Debug_DrawData_Rate,
      Debug_DrawData_Addr};
  Page[Debug_Order].Option[Debug_DrawData_Order] = Option_DrawData;

  Option_InitTypeDef Debug_Option_Threshold = {
      Debug_Threshold_Title,
      Debug_Threshold_Order,
      Debug_Threshold_Value,
      Debug_Threshold_MaxValue,
      Debug_Threshold_MinValue,
      Debug_Threshold_Rate,
      Debug_Threshold_Addr};
  Page[Debug_Order].Option[Debug_Threshold_Order] = Debug_Option_Threshold;

  Option_InitTypeDef Debug_Option_Speed = {
      Debug_Speed_Title,
      Debug_Speed_Order,
      Debug_Speed_Value,
      Debug_Speed_MaxValue,
      Debug_Speed_MinValue,
      Debug_Speed_Rate,
      Debug_Speed_Addr};
  Page[Debug_Order].Option[Debug_Speed_Order] = Debug_Option_Speed;

  Option_InitTypeDef Debug_Option_Test = {
      Debug_Test_Title,
      Debug_Test_Order,
      Debug_Test_Value,
      Debug_Test_MaxValue,
      Debug_Test_MinValue,
      Debug_Test_Rate,
      Debug_Test_Addr};
  Page[Debug_Order].Option[Debug_Test_Order] = Debug_Option_Test;

  Option_InitTypeDef Debug_Option_AD_Cam = {
      Debug_AD_Cam_Title,
      Debug_AD_Cam_Order,
      Debug_AD_Cam_Value,
      Debug_AD_Cam_MaxValue,
      Debug_AD_Cam_MinValue,
      Debug_AD_Cam_Rate,
      Debug_AD_Cam_Addr};
  Page[Debug_Order].Option[Debug_AD_Cam_Order] = Debug_Option_AD_Cam;
}

/************************************************************************
函数名：Start页面初始化
功能：初始化开始页面结构体
************************************************************************/
void StartMenuInit(void)
{
  Option_InitTypeDef Option_Angle_zreo = {
      Angle_zreo_Title,
      Angle_zreo_Order,
      Angle_zreo_Value,
      Angle_zreo_MaxValue,
      Angle_zreo_MinValue,
      Angle_zreo_Rate,
      Angle_zreo_Addr};
  Page[Start_Order].Option[Angle_zreo_Order] = Option_Angle_zreo;

  Option_InitTypeDef Option_Ang_vel_P = {
      Ang_vel_P_Title,
      Ang_vel_P_Order,
      Ang_vel_P_Value,
      Ang_vel_P_MaxValue,
      Ang_vel_P_MinValue,
      Ang_vel_P_Rate,
      Ang_vel_P_Addr};
  Page[Start_Order].Option[Ang_vel_P_Order] = Option_Ang_vel_P;

  Option_InitTypeDef Option_yingshe86 = {
      yingshe86_Title,
      yingshe86_Order,
      yingshe86_Value,
      yingshe86_MaxValue,
      yingshe86_MinValue,
      yingshe86_Rate,
      yingshe86_Addr};
  Page[Start_Order].Option[yingshe86_Order] = Option_yingshe86;

  Option_InitTypeDef Option_ramp_FK = {
      ramp_FK_Title,
      ramp_FK_Order,
      ramp_FK_Value,
      ramp_FK_MaxValue,
      ramp_FK_MinValue,
      ramp_FK_Rate,
      ramp_FK_Addr};
  Page[Start_Order].Option[ramp_FK_Order] = Option_ramp_FK;

    Option_InitTypeDef Option_yingshe83 = {
      yingshe83_Title,
      yingshe83_Order,
      yingshe83_Value,
      yingshe83_MaxValue,
      yingshe83_MinValue,
      yingshe83_Rate,
      yingshe83_Addr};
  Page[Start_Order].Option[yingshe83_Order] = Option_yingshe83;

      Option_InitTypeDef Option_yingshe84 = {
      yingshe84_Title,
      yingshe84_Order,
      yingshe84_Value,
      yingshe84_MaxValue,
      yingshe84_MinValue,
      yingshe84_Rate,
      yingshe84_Addr};
  Page[Start_Order].Option[yingshe84_Order] = Option_yingshe84;
}

/************************************************************************
函数名：pid页面初始化
功能：初始化开始页面结构体
************************************************************************/
void pidMenuInit(void)
{

  Option_InitTypeDef Option_Ang_P = {
      Ang_P_Title,
      Ang_P_Order,
      Ang_P_Value,
      Ang_P_MaxValue,
      Ang_P_MinValue,
      Ang_P_Rate,
      Ang_P_Addr};
  Page[pid_Order].Option[Ang_P_Order] = Option_Ang_P;
  Option_InitTypeDef Option_yingshe87_2 = {
      yingshe87_2_Title,
      yingshe87_2_Order,
      yingshe87_2_Value,
      yingshe87_2_MaxValue,
      yingshe87_2_MinValue,
      yingshe87_2_Rate,
      yingshe87_2_Addr};
  Page[pid_Order].Option[yingshe87_2_Order] = Option_yingshe87_2;
  Option_InitTypeDef Option_speed_P = {
      speed_P_Title,
      speed_P_Order,
      speed_P_Value,
      speed_P_MaxValue,
      speed_P_MinValue,
      speed_P_Rate,
      speed_P_Addr};
  Page[pid_Order].Option[speed_P_Order] = Option_speed_P;
  Option_InitTypeDef Option_yingshe32 = {
      yingshe32_Title,
      yingshe32_Order,
      yingshe32_Value,
      yingshe32_MaxValue,
      yingshe32_MinValue,
      yingshe32_Rate,
      yingshe32_Addr};
  Page[pid_Order].Option[yingshe32_Order] = Option_yingshe32;
  Option_InitTypeDef Option_P84 = {
      P84_Title,
      P84_Order,
      P84_Value,
      P84_MaxValue,
      P84_MinValue,
      P84_Rate,
      P84_Addr};
  Page[pid_Order].Option[P84_Order] = Option_P84;

  Option_InitTypeDef Option_I84 = {
      I84_Title,
      I84_Order,
      I84_Value,
      I84_MaxValue,
      I84_MinValue,
      I84_Rate,
      I84_Addr};
  Page[pid_Order].Option[I84_Order] = Option_I84;
}

/************************************************************************
函数名：Ring页面初始化
功能：初始化开始页面结构体
************************************************************************/
void RingMenuInit(void)
{
  Option_InitTypeDef Option_Ring_RingNum = {
      Ring_RingNum_Title,
      Ring_RingNum_Order,
      Ring_RingNum_Value,
      Ring_RingNum_MaxValue,
      Ring_RingNum_MinValue,
      Ring_RingNum_Rate,
      Ring_RingNum_Addr};
  Page[Ring_Order].Option[Ring_RingNum_Order] = Option_Ring_RingNum;

  Option_InitTypeDef Option_Ring_Ring1 = {
      Ring_Ring1_Title,
      Ring_Ring1_Order,
      Ring_Ring1_Value,
      Ring_Ring1_MaxValue,
      Ring_Ring1_MinValue,
      Ring_Ring1_Rate,
      Ring_Ring1_Addr};
  Page[Ring_Order].Option[Ring_Ring1_Order] = Option_Ring_Ring1;

  Option_InitTypeDef Option_yingshe35 = {
      yingshe35_Title,
      yingshe35_Order,
      yingshe35_Value,
      yingshe35_MaxValue,
      yingshe35_MinValue,
      yingshe35_Rate,
      yingshe35_Addr};
  Page[Ring_Order].Option[yingshe35_Order] = Option_yingshe35;

  Option_InitTypeDef Option_yingshe87 = {
      yingshe87_Title,
      yingshe87_Order,
      yingshe87_Value,
      yingshe87_MaxValue,
      yingshe87_MinValue,
      yingshe87_Rate,
      yingshe87_Addr};
  Page[Ring_Order].Option[yingshe87_Order] = Option_yingshe87;

  Option_InitTypeDef Option_yingshe81 = {
      yingshe81_Title,
      yingshe81_Order,
      yingshe81_Value,
      yingshe81_MaxValue,
      yingshe81_MinValue,
      yingshe81_Rate,
      yingshe81_Addr};
  Page[Ring_Order].Option[yingshe81_Order] = Option_yingshe81;

  Option_InitTypeDef Option_yingshe52 = {
      yingshe52_Title,
      yingshe52_Order,
      yingshe52_Value,
      yingshe52_MaxValue,
      yingshe52_MinValue,
      yingshe52_Rate,
      yingshe52_Addr};
  Page[Ring_Order].Option[yingshe52_Order] = Option_yingshe52;
  
}

/************************************************************************
函数名：Choose页面初始化
功能：初始化开始页面结构体
************************************************************************/
void ChooseMenuInit(void)
{
  Option_InitTypeDef Option_is_checkZebro = {
      is_checkZebro_Title,
      is_checkZebro_Order,
      is_checkZebro_Value,
      is_checkZebro_MaxValue,
      is_checkZebro_MinValue,
      is_checkZebro_Rate,
      is_checkZebro_Addr};
  Page[Choose_Order].Option[is_checkZebro_Order] = Option_is_checkZebro;

  Option_InitTypeDef Option_is_ChuKu = {
      is_ChuKu_Title,
      is_ChuKu_Order,
      is_ChuKu_Value,
      is_ChuKu_MaxValue,
      is_ChuKu_MinValue,
      is_ChuKu_Rate,
      is_ChuKu_Addr};
  Page[Choose_Order].Option[is_ChuKu_Order] = Option_is_ChuKu;

  Option_InitTypeDef Option_speed34 = {
      speed34_Title,
      speed34_Order,
      speed34_Value,
      speed34_MaxValue,
      speed34_MinValue,
      speed34_Rate,
      speed34_Addr};
  Page[Choose_Order].Option[speed34_Order] = Option_speed34;

  Option_InitTypeDef Option_speed84 = {
      speed84_Title,
      speed84_Order,
      speed84_Value,
      speed84_MaxValue,
      speed84_MinValue,
      speed84_Rate,
      speed84_Addr};
  Page[Choose_Order].Option[speed84_Order] = Option_speed84;

  Option_InitTypeDef Option_r_f_p = {
          r_f_p_Title,
          r_f_p_Order,
          r_f_p_Value,
          r_f_p_MaxValue,
          r_f_p_MinValue,
          r_f_p_Rate,
          r_f_p_Addr};
    Page[Choose_Order].Option[r_f_p_Order] = Option_r_f_p;

    Option_InitTypeDef Option_r_f_I = {
            r_f_I_Title,
            r_f_I_Order,
            r_f_I_Value,
            r_f_I_MaxValue,
            r_f_I_MinValue,
            r_f_I_Rate,
            r_f_I_Addr};
      Page[Choose_Order].Option[r_f_I_Order] = Option_r_f_I;
}

/************************************************************************
函数名：yingshe页面初始化
功能：初始化开始页面结构体
************************************************************************/
void yingsheMenuInit(void)
{
  Option_InitTypeDef Option_ringy = {
      ringy_Title,
      ringy_Order,
      ringy_Value,
      ringy_MaxValue,
      ringy_MinValue,
      ringy_Rate,
      ringy_Addr};
  Page[yingshe_Order].Option[ringy_Order] = Option_ringy;

  Option_InitTypeDef Option_rampy = {
      rampy_Title,
      rampy_Order,
      rampy_Value,
      rampy_MaxValue,
      rampy_MinValue,
      rampy_Rate,
      rampy_Addr};
  Page[yingshe_Order].Option[rampy_Order] = Option_rampy;

  Option_InitTypeDef Option_ChuKuy = {
      ChuKuy_Title,
      ChuKuy_Order,
      ChuKuy_Value,
      ChuKuy_MaxValue,
      ChuKuy_MinValue,
      ChuKuy_Rate,
      ChuKuy_Addr};
  Page[yingshe_Order].Option[ChuKuy_Order] = Option_ChuKuy;

  Option_InitTypeDef Option_yingsheS = {
      yingsheS_Title,
      yingsheS_Order,
      yingsheS_Value,
      yingsheS_MaxValue,
      yingsheS_MinValue,
      yingsheS_Rate,
      yingsheS_Addr};
  Page[yingshe_Order].Option[yingsheS_Order] = Option_yingsheS;

  Option_InitTypeDef Option_fork0 = {
      fork0_Title,
      fork0_Order,
      fork0_Value,
      fork0_MaxValue,
      fork0_MinValue,
      fork0_Rate,
      fork0_Addr};
  Page[yingshe_Order].Option[fork0_Order] = Option_fork0;

  Option_InitTypeDef Option_ring16 = {
      ring16_Title,
      ring16_Order,
      ring16_Value,
      ring16_MaxValue,
      ring16_MinValue,
      ring16_Rate,
      ring16_Addr};
  Page[yingshe_Order].Option[ring16_Order] = Option_ring16;
}

/************************************************************************
函数名：tarspeedMenuInit页面初始化
功能：初始化开始页面结构体
************************************************************************/
void tarspeedMenuInit(void)
{
  Option_InitTypeDef Option_ringt = {
      ringt_Title,
      ringt_Order,
      ringt_Value,
      ringt_MaxValue,
      ringt_MinValue,
      ringt_Rate,
      ringt_Addr};
  Page[tarspeed_Order].Option[ringt_Order] = Option_ringt;

  Option_InitTypeDef Option_rampt = {
      rampt_Title,
      rampt_Order,
      rampt_Value,
      rampt_MaxValue,
      rampt_MinValue,
      rampt_Rate,
      rampt_Addr};
  Page[tarspeed_Order].Option[rampt_Order] = Option_rampt;

  Option_InitTypeDef Option_ChuKut = {
      ChuKut_Title,
      ChuKut_Order,
      ChuKut_Value,
      ChuKut_MaxValue,
      ChuKut_MinValue,
      ChuKut_Rate,
      ChuKut_Addr};
  Page[tarspeed_Order].Option[ChuKut_Order] = Option_ChuKut;

  Option_InitTypeDef Option_Fork0 = {
      Fork0_Title,
      Fork0_Order,
      Fork0_Value,
      Fork0_MaxValue,
      Fork0_MinValue,
      Fork0_Rate,
      Fork0_Addr};
  Page[tarspeed_Order].Option[Fork0_Order] = Option_Fork0;

  Option_InitTypeDef Option_ring16_sp = {
      ring16_sp_Title,
      ring16_sp_Order,
      ring16_sp_Value,
      ring16_sp_MaxValue,
      ring16_sp_MinValue,
      ring16_sp_Rate,
      ring16_sp_Addr};
  Page[tarspeed_Order].Option[ring16_sp_Order] = Option_ring16_sp;

    Option_InitTypeDef Option_yingshe85 = {
      yingshe85_Title,
      yingshe85_Order,
      yingshe85_Value,
      yingshe85_MaxValue,
      yingshe85_MinValue,
      yingshe85_Rate,
      yingshe85_Addr};
  Page[tarspeed_Order].Option[yingshe85_Order] = Option_yingshe85;
}

void ForkOutMenuInit()
{
    Option_InitTypeDef Option_speed85 = {
            speed85_Title,
            speed85_Order,
            speed85_Value,
            speed85_MaxValue,
            speed85_MinValue,
            speed85_Rate,
            speed85_Addr};
    Page[ForkOut_Order].Option[speed85_Order] = Option_speed85;

    Option_InitTypeDef Option_yingshe84_2 = {
            yingshe84_2_Title,
            yingshe84_2_Order,
            yingshe84_2_Value,
            yingshe84_2_MaxValue,
            yingshe84_2_MinValue,
            yingshe84_2_Rate,
            yingshe84_2_Addr};
    Page[ForkOut_Order].Option[yingshe84_2_Order] = Option_yingshe84_2;

    Option_InitTypeDef Option_yingshe85_2 = {
            yingshe85_2_Title,
            yingshe85_2_Order,
            yingshe85_2_Value,
            yingshe85_2_MaxValue,
            yingshe85_2_MinValue,
            yingshe85_2_Rate,
            yingshe85_2_Addr};
    Page[ForkOut_Order].Option[yingshe85_2_Order] = Option_yingshe85_2;


    Option_InitTypeDef Option_speed_86_87 = {
            speed_86_87_Title,
            speed_86_87_Order,
            speed_86_87_Value,
            speed_86_87_MaxValue,
            speed_86_87_MinValue,
            speed_86_87_Rate,
            speed_86_87_Addr};
    Page[ForkOut_Order].Option[speed_86_87_Order] = Option_speed_86_87;

      Option_InitTypeDef Option_yingshe86_2 = {
              yingshe86_2_Title,
              yingshe86_2_Order,
              yingshe86_2_Value,
              yingshe86_2_MaxValue,
              yingshe86_2_MinValue,
              yingshe86_2_Rate,
              yingshe86_2_Addr};
    Page[ForkOut_Order].Option[yingshe86_2_Order] = Option_yingshe86_2;

    Option_InitTypeDef Option_I_86_87 = {
            I_86_87_Title,
            I_86_87_Order,
            I_86_87_Value,
            I_86_87_MaxValue,
            I_86_87_MinValue,
            I_86_87_Rate,
            I_86_87_Addr};
    Page[ForkOut_Order].Option[I_86_87_Order] = Option_I_86_87;
}

/************************************************************************
函数名：存储数据
参数：ui8_Page---页面序号
ui8_Item---条目序号
************************************************************************/
uint8 status = 0;
void SaveData(uint8 ui8_Page, uint8 ui8_Item)
{

  uint32 write_buf[20];

  for (int i = 0; i < Page[ui8_Page].Page_Num_Item; i++)
    write_buf[i] = Page[ui8_Page].Option[i + 1].Item_Value;

  eeprom_erase_sector(ui8_Page); //擦除扇区，如果扇区已经有数据则必须擦除扇区之后才能再次写入新的数据

  for (int i = 0; i < Page[ui8_Page].Page_Num_Item; i++)
    eeprom_page_program(ui8_Page, i, &write_buf[i]);
}
