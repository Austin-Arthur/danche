/*
 * initial.c
 *
 *  Created on: 2021��12��29��
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
*���ܣ����

*************************************************************************/
void duoji_Init()
{
     gtm_pwm_init(ATOM1_CH4_P22_3, 50, Servo_Center_Mid);//����//��820 +- 130  690-950
}
void duoji_control(int duty)
{
    if (duty >= Servo_Left_Max)                  //���Ʒ�ֵ
       duty = Servo_Left_Max;
    else if (duty <= Servo_Right_Min)            //���Ʒ�ֵ
       duty = Servo_Right_Min;
    pwm_duty(ATOM1_CH4_P22_3, duty);
}

/************************************************************************
*���ܣ����

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
    if(motor1>motor1_max) motor1=motor1_max;        // ��������޷�
    else if(motor1<-motor1_max) motor1=-motor1_max; //
    else if(motor1<-0) motor1 -=motor1_die;    // ����
    else if(motor1>0) motor1+=motor1_die;      // ����

    //������
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


    if(motor2>8000) motor2=8000;        // ���ֵ���޷�
    else if(motor2<-8000) motor2=-8000; //
    else if(motor2<-0) motor2 -=400;    // ����
    else if(motor2>0) motor2+=400;      // ����

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
*���ܣ�������

*************************************************************************/
void bianma_Init()
{
    gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);    //��������ʼ��
}

void Get_speed()
{
    speed = -gpt12_get(GPT12_T2)*0.5;
    gpt12_clear(GPT12_T2);

}

/************************************************************************
*���ܣ�ADC

*************************************************************************/
void ADC_Init()
{
    adc_init(ADC_0, ADC0_CH0_A0);//��ʼ��ADC0 ͨ��0 ʹ��A0����
    adc_init(ADC_0, ADC0_CH1_A1);//��ʼ��ADC0 ͨ��0 ʹ��A0����
    adc_init(ADC_0, ADC0_CH2_A2);//��ʼ��ADC0 ͨ��0 ʹ��A0����
    adc_init(ADC_0, ADC0_CH3_A3);//��ʼ��ADC0 ͨ��0 ʹ��A0����
    adc_init(ADC_0, ADC0_CH4_A4);//��ʼ��ADC0 ͨ��0 ʹ��A0����

}

void Get_ADC_Value()
{
    ADC_val[2] =    adc_mean_filter(ADC_0,ADC0_CH0_A0,ADC_12BIT,5);    //12λ5���˲�
    ADC_val[4] =    adc_mean_filter(ADC_0,ADC0_CH1_A1,ADC_12BIT,5);    //12λ5���˲�
    ADC_val[1] =    adc_mean_filter(ADC_0,ADC0_CH2_A2,ADC_12BIT,5);    //12λ5���˲�
    ADC_val[0] =    adc_mean_filter(ADC_0,ADC0_CH3_A3,ADC_12BIT,5);    //12λ5���˲�
    ADC_val[3] =    adc_mean_filter(ADC_0,ADC0_CH4_A4,ADC_12BIT,5);    //12λ5���˲�


}


/************************************************************************
*���ܣ�����

*************************************************************************/
/*
void Key_Init()
{
    gpio_init(P21_5, GPI, 0,  PULLUP);//����P20_8Ϊ��� Ĭ������͵�ƽ  PUSHPULL���������
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
*���ܣ�������

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



