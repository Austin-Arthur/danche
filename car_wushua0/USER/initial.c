/*
 * initial.c
 *
 *  Created on: 2021年12月29日
 *      Author: 11609
 */
#include"initial.h"

uint16 ADC_val[5] ={0};
int speed,speed_angle;
void motor_Init();
void bianma_Init();
void ADC_Init();
void duoji_Init();
void _8_Init_Heading_Dir();
void beep_init();

void initial()
{
     icm20602_init();
    motor_Init();
    bianma_Init();
    ADC_Init();
    oled_init();
    duoji_Init();
     mt9v03x_init();
    _8_Init_Heading_Dir();
    beep_init();

}
/************************************************************************
*功能：舵机

*************************************************************************/
void duoji_Init()
{
     gtm_pwm_init(ATOM1_CH4_P22_3, 50, Servo_Center_Mid);//后轮//中820 +- 130  690-950
}
void duoji_control(int duty)
{
    if (duty >= Servo_Left_Max)                  //限制幅值
       duty = Servo_Left_Max;
    else if (duty <= Servo_Right_Min)            //限制幅值
       duty = Servo_Right_Min;
    pwm_duty(ATOM1_CH4_P22_3, duty);
}

/************************************************************************
*功能：电机

*************************************************************************/
int motor_pwm;
void motor_Init()
{
     gtm_pwm_init(ATOM0_CH0_P21_2, 14000, 0);
     gtm_pwm_init(ATOM0_CH1_P21_3, 14000, 0);


}
int motor1_max = 5000;
int motor1_die = 0;//700  7v
void motor_control1(float motor1)
{
    if(motor1>motor1_max) motor1=motor1_max;        // 动量电机限幅
    else if(motor1<-motor1_max) motor1=-motor1_max; //
    else if(motor1<-0) motor1 -=motor1_die;    // 死区
    else if(motor1>0) motor1+=motor1_die;      // 死区

    //动量轮
    if (motor1 > 0)
    {
        motor_control.dir = FORWARD;
        duty = (int)motor1;

    }

    else
    {
        motor_control.dir = REVERSE;
        duty = -(int)motor1;
    }

}

void motor_control2(float motor2)
{


    if(motor2>8000) motor2=8000;        // 后轮电机限幅
    else if(motor2<-8000) motor2=-8000; //
    else if(motor2<-0) motor2 -=400;    // 死区
    else if(motor2>0) motor2+=400;      // 死区

    if (motor2 > 0)
    {
        pwm_duty(ATOM0_CH0_P21_2, motor2);
        pwm_duty(ATOM0_CH1_P21_3, 0);

    }
    else
    {
        pwm_duty(ATOM0_CH0_P21_2, -motor2);
        pwm_duty(ATOM0_CH1_P21_3, 10000);
    }
}
/************************************************************************
*功能：编码器

*************************************************************************/
void bianma_Init()
{
    gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);    //编码器初始化
}

void Get_speed()
{
    speed = -gpt12_get(GPT12_T2)*0.5;
    gpt12_clear(GPT12_T2);

}

/************************************************************************
*功能：ADC

*************************************************************************/
void ADC_Init()
{
    adc_init(ADC_0, ADC0_CH0_A0);//初始化ADC0 通道0 使用A0引脚
    adc_init(ADC_0, ADC0_CH1_A1);//初始化ADC0 通道0 使用A0引脚
    adc_init(ADC_0, ADC0_CH2_A2);//初始化ADC0 通道0 使用A0引脚
    adc_init(ADC_0, ADC0_CH3_A3);//初始化ADC0 通道0 使用A0引脚
    adc_init(ADC_0, ADC0_CH4_A4);//初始化ADC0 通道0 使用A0引脚

}

void Get_ADC_Value()
{
    ADC_val[2] =    adc_mean_filter(ADC_0,ADC0_CH0_A0,ADC_12BIT,5);    //12位5次滤波
    ADC_val[4] =    adc_mean_filter(ADC_0,ADC0_CH1_A1,ADC_12BIT,5);    //12位5次滤波
    ADC_val[1] =    adc_mean_filter(ADC_0,ADC0_CH2_A2,ADC_12BIT,5);    //12位5次滤波
    ADC_val[0] =    adc_mean_filter(ADC_0,ADC0_CH3_A3,ADC_12BIT,5);    //12位5次滤波
    ADC_val[3] =    adc_mean_filter(ADC_0,ADC0_CH4_A4,ADC_12BIT,5);    //12位5次滤波


}


/************************************************************************
*功能：按键

*************************************************************************/
/*
void Key_Init()
{
    gpio_init(P21_5, GPI, 0,  PULLUP);//设置P20_8为输出 默认输出低电平  PUSHPULL：推挽输出
    gpio_init(P21_6, GPI, 0,  PULLUP);
    gpio_init(P21_7, GPI, 0,  PULLUP);
    gpio_init(P20_0, GPI, 0,  PULLUP);
    gpio_init(P20_2, GPI, 0,  PULLUP);


}
*/
/*
int KeyWork1()
{
    if((KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0))
    {
        systick_delay_ms(STM0, 50);

        if(KEY1==0)      return KEY1_PRES;
        else if(KEY2==0) return KEY2_PRES;
        else if(KEY3==0) return KEY3_PRES;
        else if(KEY4==0) return KEY4_PRES;
        else if(KEY5==0) return KEY5_PRES;
    }
    return 0;
}
void KeySwitch()
{
    int key = 0;
    key = KeyWork();
    switch(key)
    {
        case 1:break;
        case 2:break;
        case 3:break;
        case 4:break;
        case 5:break;
        default:break;
    }
}
*/

/************************************************************************
*功能：蜂鸣器

*************************************************************************/
void beep_on()
{
    gpio_set(P20_3, 0);
}
void beep_off()
{
    gpio_set(P20_3, 1);
}
void beep_init()
{
    gpio_init(P20_3, GPO, 1,  PUSHPULL);
}



