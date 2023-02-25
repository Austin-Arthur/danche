/*
 * MyMenu.c
 *
 *  Created on: 2022��1��2��
 *      Author: 11609
 */
/*
 * Menu.c
 *
 *  Created on: 2021��12��31��
 *      Author: 11609
 */
#include "MyMenu.h"

uint8 Key_Change = 0;

/*������ʼ��-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
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
        /*���/ɾ��ҳ�涼Ҫ�ı�*/
        {
            Debug_Title,
            Debug_Order,
            Debug_Num_Item},
        /*���/ɾ��ҳ�涼Ҫ�ı�*/
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
/*������ʼ��-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

/************************************************************************
��������DelayMs
�������ã���ʱ
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
����������ʼ���˵�
���ܣ��˵���ʼ��
ÿ��һ��ҳ�棬��һ��ҳ���ʼ��
************************************************************************/
void InitMenu(void)
{
  KeyInit();
  StartMenuInit(); // Startҳ���ʼ��
  DebugMenuInit(); // Initҳ���ʼ��
  RingMenuInit();
  pidMenuInit();
  ChooseMenuInit();
  yingsheMenuInit();
  tarspeedMenuInit();
  ForkOutMenuInit();
  DisplayPage(MCtrl.ui8_NowPage); //��ʼ�������ʾ��ҳ
}

/************************************************************************
��������KeyInit
���ܣ�������ʼ��
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
��������KeyWork
���ܣ���������
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
  {           //��ͷ����
    UP_ADT(); //ˢFlash
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
  {             //��ͷ����
    DOWN_ADT(); //ˢFlash
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
  //��ҳ
  if (Key_Change == 0) //��ҳ
  {
    while (LEFT)
    {
      LEFT_ADT();           //ˢFlash
      ChangeMenuPage(LEFT); //��ҳ
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
      RIGHT_ADT(); //ˢFLASH
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
  //���ݼӼ�
  else if (Key_Change == 1) //�ı�����
  {
    while (LEFT)
    {
      SUB_ADT(); //���ݼ� Flashδ�ı�
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
    { //���ݼ�
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
��������ADD�������ӹ���
************************************************************************/
void ADD_ADT(void)
{
  //ϵͳ��
  AddItemValue(MCtrl.ui8_NowPage, MCtrl.ui8_NowFlag);
  MCtrl.ui8_LastKey = KEY_SUB;
  MCtrl.ui8_ChangeValueFlag = 1;
}

/************************************************************************
��������SUB�������ӹ���
************************************************************************/
void SUB_ADT(void)
{
  //ϵͳ��
  SubItemValue(MCtrl.ui8_NowPage, MCtrl.ui8_NowFlag);
  MCtrl.ui8_LastKey = KEY_SUB;
  MCtrl.ui8_ChangeValueFlag = 1;
}
/************************************************************************
��������UP�������ӹ���
************************************************************************/
void UP_ADT(void)
{
  MCtrl.ui8_LastKey = KEY_UP;
  if (MCtrl.ui8_ChangeValueFlag) //�Ƿ�ı�
  {
    SaveData(MCtrl.ui8_NowPage, MCtrl.ui8_NowFlag); //�洢FLASH
    MCtrl.ui8_ChangeValueFlag = 0;                  //�ı��־���
  }
}

/************************************************************************
��������DOWN�������ӹ���
************************************************************************/
void DOWN_ADT(void)
{
  MCtrl.ui8_LastKey = KEY_DOWN;
  if (MCtrl.ui8_ChangeValueFlag) //�Ƿ�ı�
  {
    SaveData(MCtrl.ui8_NowPage, MCtrl.ui8_NowFlag); //�洢FLASH
    MCtrl.ui8_ChangeValueFlag = 0;
  }
}

/************************************************************************
��������LEFT�������ӹ���
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
��������RIGHT�������ӹ���
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
����������ȡֵ
���ܣ���ȡ��Ӧ��Ŀֵ
������ui8_Page---ҳ��λ��(���磺Start_Order)
      ui8_Item---��Ŀλ��(���磺Start_Delay_Order)
************************************************************************/
double GetItemValue(uint8 ui8_Page, uint8 ui8_Item)
{
  //��ȡ����ת��
  return Page[ui8_Page].Option[ui8_Item].Item_Value *
         Page[ui8_Page].Option[ui8_Item].Item_Rate;
}

/************************************************************************
������������ֵ
���ܣ����ö�Ӧ��Ŀֵ
������ui8_Page---ҳ��λ��(���磺Start_Order)
      ui8_Item---��Ŀλ��(���磺Start_Delay_Order)
      d_Value----��Ŀֵ
************************************************************************/
void SetItemValue(uint8 ui8_Page, uint8 ui8_Item, double d_Value)
{
  //д�뱶��ת��
  d_Value /= Page[ui8_Page].Option[ui8_Item].Item_Rate;
  //�ж���Χ
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
���������ı��־
���ܣ�ѡ��ı��־
������ui8_UpDown---��־�ƶ�����
************************************************************************/
void ChangeMenuFlag(uint8 ui8_UpDown)
{
  //��¼��ǰѡ����

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

  //ˢ����ʾ
  DisplayPage(MCtrl.ui8_NowPage);
}

/************************************************************************
���������ı�ҳ��
���ܣ��ı�ҳ�����
������ui8_LeftRight---�л�ҳ�淽��
************************************************************************/
void ChangeMenuPage(uint8 ui8_LeftRight)
{
  //��¼��ǰѡ��ҳ
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
����������ʾҳ��
���ܣ���ʾ��ǰҳ��
������ui8_Page---ҳ�����
************************************************************************/
void DisplayPage(uint8 ui8_Page)
{
  //������ʾʱ��¼��ǰѡ��ҳ
  MCtrl.ui8_NowPage = ui8_Page;
  DisplayMenu(Page[ui8_Page]);
}

/************************************************************************
����������ֵ
���ܣ����ݵ�ǰ��־��ѡ������ֵ�Ľṹ��
������ui8_Page---ҳ�����
     ui8_Item---��Ŀ���
************************************************************************/
void AddItemValue(uint8 ui8_Page, uint8 ui8_Item)
{
  //��Χ��ѭ����
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
����������ֵ
���ܣ����ݵ�ǰ��־��ѡ�����ֵ�Ľṹ��
������ui8_Page---ҳ�����
      ui8_Item---��Ŀ���
************************************************************************/
void SubItemValue(uint8 ui8_Page, uint8 ui8_Item)
{ //��Χ��ѭ����
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
����������ʾ�˵�
���ܣ���ʾ��Ӧ�˵�����
������M---��Ŀ�ṹͼ
************************************************************************/
void DisplayMenu(Menu_InitTypeDef M)
{

  uint8 ui8_MaxItem = (MCtrl.ui8_NowDisPage * 6) > M.Page_Num_Item ? M.Page_Num_Item : (MCtrl.ui8_NowDisPage * 6);

  //����
  oled_fill(0);
  //��ʾҳ�����ͷָ���
  oled_p8x16str(0, 0, M.Page_Title);
  // oled_p6x8str(40, 0, "|");

  for (uint8 ui8_I = (MCtrl.ui8_NowDisPage - 1) * 6 + 1; ui8_I <= ui8_MaxItem; ui8_I++)
  {
    //��ʾ��Ŀ����
    oled_p6x8str(12, M.Option[ui8_I].Item_Order + 1 - (MCtrl.ui8_NowDisPage - 1) * 6,
                 M.Option[ui8_I].Item_Title);
    //��ʾ��Ŀֵ
    DisplayItemValue(M.Option[ui8_I].Item_Value, M.Option[ui8_I].Item_Order + 1);
  }

  //��ʾѡ�б�־
  DisplayItemFlag();
  //��ʾ״̬��־
  DisplayIcon();
}

/************************************************************************
����������ʾͼ��
���ܣ���ʾ״̬
************************************************************************/
void DisplayIcon(void)
{

  //��ʾ���ڰ汾��
  oled_p6x8str(48, 1, IC_VERSION);
  //��ť�л�
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
����������ʾֵ
���ܣ���ʾ��Ӧ��ֵ
������i16_Value---ֵ
      ui8_Row---������
************************************************************************/
void DisplayItemValue(int16 i16_Value, uint8 ui8_Row)
{
  uint8 ui8_Fu = 0;

  //��¼����
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

  //���ҵ�����ʾ
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
����������ʾ��־
���ܣ���ʾ�������־
************************************************************************/
void DisplayItemFlag(void)
{
  oled_p6x8str(0, MCtrl.ui8_NowFlag % 7 + MCtrl.ui8_NowDisPage, "->");
}

/************************************************************************
��������Initҳ���ʼ��
���ܣ���ʼ����ʼ��ҳ��ṹ��
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
��������Startҳ���ʼ��
���ܣ���ʼ����ʼҳ��ṹ��
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
��������pidҳ���ʼ��
���ܣ���ʼ����ʼҳ��ṹ��
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
��������Ringҳ���ʼ��
���ܣ���ʼ����ʼҳ��ṹ��
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
��������Chooseҳ���ʼ��
���ܣ���ʼ����ʼҳ��ṹ��
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
��������yingsheҳ���ʼ��
���ܣ���ʼ����ʼҳ��ṹ��
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
��������tarspeedMenuInitҳ���ʼ��
���ܣ���ʼ����ʼҳ��ṹ��
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
���������洢����
������ui8_Page---ҳ�����
ui8_Item---��Ŀ���
************************************************************************/
uint8 status = 0;
void SaveData(uint8 ui8_Page, uint8 ui8_Item)
{

  uint32 write_buf[20];

  for (int i = 0; i < Page[ui8_Page].Page_Num_Item; i++)
    write_buf[i] = Page[ui8_Page].Option[i + 1].Item_Value;

  eeprom_erase_sector(ui8_Page); //������������������Ѿ�������������������֮������ٴ�д���µ�����

  for (int i = 0; i < Page[ui8_Page].Page_Num_Item; i++)
    eeprom_page_program(ui8_Page, i, &write_buf[i]);
}
