/*
 * control.c
 *
 *  Created on: 2021年10月7日
 *      Author: 11609
 */

#include "control.h"
//动量轮PID参数
//角度环
float X_Balance_KP = 0; // *100
float X_Balance_KI = 0;
float X_Balance_KD = 0; //*10
//速度环
float X_Velocity_KP = 0;
float X_Velocity_KI = 0;
//角速度环
float X_AngleVelocity_KP = 0; // *100
float X_AngleVelocity_KD = 0;

float Zero_error = 0; //综合偏差

//转向环
float Balance_Kp = 0; // 舵机PID参数
float Balance_Kd = 0; // 舵机PID参数
float Balance_Ki = 0; // 舵机PID参数

//后轮电机速度环
float Motor_Kp = 0; // 后轮电机PID参数
float Motor_Ki = 0; // 后轮电机PID参数

float error_xunxian = 0;  //巡线偏差
int PWM_X, PWM_accel;     // PWM中间量
int MotorDutyA = 0;       // 飞轮电机驱动占空比数值
int MotorDutyB = 0;       // 后轮电机驱动占空比数值
short PWMMotor, PWMServo; // 电机舵机PMW变量中值

float Integration = 0;
float error_Integral = 0;
float Encoder_Integral = 0;
int Servo_PWM;

float AD_Integration = 0;

unsigned char Flag_Stop = 1; // 停止标志位
int stop = 1;
int test_x[10] = {0};
float yawan;
short Motor_Bias, Motor_Last_Bias, Motor_Integration; // 电机所用参数

extern int Test;

int time_measure_flag = 0;
extern int time_measure;
extern float gyro_lpf;

extern float yingshe;
extern int xzttt;
extern int wheel_flag;

/********************************************************
 *@函数名: 输出滤波
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-26 14:29:34
 ********************************************************/

float ditui(float input)
{
    float result;
    static float Before_Result[5] = {0}; //之前三次的
    for (int i = 0; i < 4; i++)
    {
        Before_Result[i] = Before_Result[i + 1];
    }

    Before_Result[4] = input;

    result = (float)(Before_Result[0] * 0.1 + Before_Result[1] * 0.1 + Before_Result[2] * 0.2 + Before_Result[3] * 0.3 + Before_Result[4] * 0.3);
    return result;
}

int fork1_Filter(float input)
{
    int result;
    static float Fork1_Result[5] = {0}; //之前三次的
    for (int i = 0; i < 4; i++)
    {
        Fork1_Result[i] = Fork1_Result[i + 1];
    }

    Fork1_Result[4] = input;

    result = (float)(Fork1_Result[0] * 0.1 + Fork1_Result[1] * 0.1 + Fork1_Result[2] * 0.2 + Fork1_Result[3] * 0.3 + Fork1_Result[4] * 0.3);
    return result;
}
float Fork2_Result[3] = {0}; //之前三次的
int fork2_Filter(float input)
{
    int result;
    for (int i = 0; i < 2; i++)
    {
        Fork2_Result[i] = Fork2_Result[i + 1];
    }

    Fork2_Result[2] = input;

    result = (int)(Fork2_Result[0] * 0.2 + Fork2_Result[1] * 0.3 + Fork2_Result[2] * 0.5);
    return result;
}
float sliding_window[ACC_FILTER_NUM];
int momentum_wheel_Filter(float input)
{
    uint8 i;
    float temp1 = 0;
    float result;

    sliding_window[0] = input; // 更新滑动窗口数组

    for (i = 0; i < ACC_FILTER_NUM; i++)
    {
        temp1 += sliding_window[i];
    }

    result = temp1 / ACC_FILTER_NUM * 1.0;
    for (i = 0; i < ACC_FILTER_NUM - 1; i++)
    {
        sliding_window[ACC_FILTER_NUM - 1 - i] = sliding_window[ACC_FILTER_NUM - 2 - i];
    }
    return result;
}
/**************************************************************************
平衡主程序
**************************************************************************/
//总流程大概20ms
int Servo_PWM, Servo_PWM1, Servo_PWM2; // 舵机PID
uint8 AD_flag = 0;
float ramp_yingshe = 1;
void Balance(void)
{
    int motor_error;
    //    int Servo_PWM; // 舵机PID
    Get_Elec_err(); //读取电磁值

    /* 获取编码器值 */
    Get_speed();                          //编码器读值
    DI.LengthCnt += speed;                //编码器计数
    DI.Length = (int)(DI.LengthCnt / 56); //转化为厘米单位

    /*舵机电机控制*/

    DI.MidLine = Get_midline();
    error_xunxian = DI.MidLine - 47;

    // //电磁巡线
    // DI.ad_p = 3;
    // DI.ad_d = 1;

    // Balance_Kp = DI.ad_p;
    // Balance_Kd = DI.ad_d;
    // Servo_PWM1 = AD_Get_BalancePID(DI.AD_err); //角速度作用为阻碍舵机倒下

    //摄像头巡线b'n'n'n'n'n'n'n'n'n'n'n'n'n'n'n'n'n'n

    {
        Balance_Kp = Fuzzy_Update(&Agnle_P_TableOne, error_xunxian, 62 - DI.SightDistance); //获得舵机P值
    //    if(state>=84&&state<=87&&DI.ForkCnt == fork_right)
    //     Balance_Kp = 2.0;
//
        //  Balance_Kd = Balance_Kp / 3.0;
//       Balance_Kd = Balance_Kp*5 ;
               Balance_Kd = Balance_Kp ;
    }
    Servo_PWM2 = SBB_Get_BalancePID(error_xunxian);
//   Servo_PWM2-=(Angle-Angle_Zero)*0.3;
    // Servo_PWM2-=(Angle-DI.Angle_error)*1;

    /*坡道*/
    if (state >= 31 && state < 35)
    {
        switch (state)
        {
        case 31:
            /* code */
            {
                Servo_PWM = Servo_PWM2;
                if (Servo_PWM > 40)
                    Servo_PWM = 40;
                if (Servo_PWM < -40)
                    Servo_PWM = -40;
                ramp_yingshe = GetItemValue(yingshe_Order, rampy_Order) / 100.0; // 0.54
                // ramp_yingshe = 0.54; // 0.54
            }
            break;
        case 32:
            /* code */
            {
                Servo_PWM = Servo_PWM2;
                if (Servo_PWM > 20)
                    Servo_PWM = 20;
                if (Servo_PWM < -20)
                    Servo_PWM = -20;
                ramp_yingshe = GetItemValue(pid_Order, yingshe32_Order) / 100.0; // 0.54
//                 ramp_yingshe = 0.2; // 0.54
            }
            break;
        case 33:
            /* code */
            {
                Servo_PWM = Servo_PWM2;
                if (Servo_PWM > 20)
                    Servo_PWM = 20;
                if (Servo_PWM < -20)
                Servo_PWM = -20;
                ramp_yingshe = GetItemValue(pid_Order, yingshe32_Order) / 100.0; // 0.54
//                 ramp_yingshe = 0.2; // 0.54
            }
            break;
        case 34:
            /* code */
            {
                Servo_PWM = Servo_PWM2;
                if (Servo_PWM > 20)
                    Servo_PWM = 20;
                if (Servo_PWM > -20)
                    Servo_PWM = -20;
                ramp_yingshe = GetItemValue(Ring_Order, yingshe35_Order) / 100.0; // 0.54

                // ramp_yingshe = 0.2; // 0.54
            }
            break;
        default:
        {
            Servo_PWM = Servo_PWM2;
            // if (Servo_PWM > 40)
            //     Servo_PWM = 40;
            // if (Servo_PWM < -40)
            //     Servo_PWM = -40;
            ramp_yingshe = GetItemValue(Ring_Order, yingshe35_Order) / 100.0; // 0.54

            // ramp_yingshe = 0.54; // 0.54
        }
        break;
        }
    }
    /*环岛16*/
    else if (state == 17)
    {
        Servo_PWM = Servo_PWM2;
        ramp_yingshe = GetItemValue(yingshe_Order, ring16_Order) / 100.0; // 0.8
    }
    else if(state>=12&&state<17)
    {
        Servo_PWM = Servo_PWM2;
//        if(Servo_PWM>-95)
//        {
//            Servo_PWM = -95;
//        }
        ramp_yingshe = GetItemValue(yingshe_Order, ring16_Order) / 100.0; // 0.8
    }
    /*入三叉前*/
    else if (state == 80)
    {
        Servo_PWM = Servo_PWM2;
        // if (Servo_PWM > 50)
        //     Servo_PWM = 50;
        if(DI.top_Y > 63&&DI.ForkCnt == fork_left)
        {
            if (Servo_PWM < -10)
            Servo_PWM = -10;
        }

        ramp_yingshe = GetItemValue(yingshe_Order, fork0_Order) / 100.0; // 0.8
    }

    /*入三叉*/
    else if (
        state == 81 ||
        state == 82
        //  || state == 85
        //  || state == 86
    )
    {
        Servo_PWM = Servo_PWM2;
//        Servo_PWM = fork1_Filter(Servo_PWM);
        // if (Servo_PWM > 50)
        //     Servo_PWM = 50;
        // if (Servo_PWM < -40)
        //     Servo_PWM = -40;
        //        if (Servo_PWM < 60)
        //        Servo_PWM = 60;
        if(DI.ForkCnt == fork_right)
            ramp_yingshe = GetItemValue(Start_Order, yingshe83_Order) / 100.0;
        else
         ramp_yingshe = GetItemValue(Ring_Order, yingshe81_Order) / 100.0; // 0.54
         
//        ramp_yingshe = GetItemValue(yingshe_Order, fork0_Order) / 100.0; // 0.8

        // ramp_yingshe = 0.54; // 0.54
    }

    /*三叉内*/
    else if (state == 83)
    {

        Servo_PWM = Servo_PWM2;
        // if (Servo_PWM > 40)
        //     Servo_PWM = 40;
        if(DI.ForkCnt == fork_left)
        {
            if (Servo_PWM < -20)
                Servo_PWM = -20;
        }

        // ramp_yingshe = GetItemValue(yingshe_Order, fork0_Order) / 100.0; // 0.54
//        if(DI.ForkCnt == fork_left)
            ramp_yingshe = GetItemValue(Start_Order, yingshe83_Order) / 100.0; // 0.54
//        else if (DI.ForkCnt == fork_right)
//            ramp_yingshe = GetItemValue(Start_Order, yingshe81_Order) / 100.0; // 0.54
    }
    /*出坡道*/
    // else if (state == 35)
    // {
    //     Servo_PWM = Servo_PWM2;
    //     Servo_PWM = fork2_Filter(Servo_PWM);
    //     if (Servo_PWM > 110)
    //         Servo_PWM = 110;
    //     if (Servo_PWM < -110)
    //         Servo_PWM = -110;
    //     ramp_yingshe = GetItemValue(Ring_Order, yingshe35_Order) / 100.0; // 0.54
    // }
    else if (state == 84)
    {
        Servo_PWM = Servo_PWM2;
        // Servo_PWM = fork2_Filter(Servo_PWM);
        // if (Servo_PWM > 110)
        //     Servo_PWM = 110;
        // if (Servo_PWM < -110)
        //     Servo_PWM = -110;
        if(DI.ForkCnt == fork_left)
        ramp_yingshe = GetItemValue(Start_Order, yingshe84_Order) / 100.0; // 0.54
        else if(DI.ForkCnt == fork_right)
        ramp_yingshe = GetItemValue(ForkOut_Order, yingshe84_2_Order) / 100.0;
    }
    else if (state == 85 )
    {
        Servo_PWM = Servo_PWM2;
        // Servo_PWM = momentum_wheel_Filter(Servo_PWM);
        // if (Servo_PWM > 100)
        //     Servo_PWM = 100;
        // if (Servo_PWM < -100)
        //     Servo_PWM = -100;
//        if(DI.ForkCnt == fork_right)
//        {
//            if (Servo_PWM < -30)
//             Servo_PWM = -30;
//        }
        if(DI.ForkCnt == fork_left)
            ramp_yingshe = GetItemValue(tarspeed_Order, yingshe85_Order) / 100.0; // 0.54
        else if(DI.ForkCnt == fork_right)
            ramp_yingshe = GetItemValue(ForkOut_Order, yingshe85_2_Order) / 100.0;
    }


    /*入库*/
    else if (
            state == 86)
    {
        Servo_PWM = Servo_PWM2;
        if(DI.ForkCnt == fork_left)
        {
                    if (Servo_PWM > 90)
                        Servo_PWM = 90;
                    else if (Servo_PWM < -90)
                        Servo_PWM = -90;
        }
        if(DI.ForkCnt == fork_right)
        {
                    if (Servo_PWM > 70)
                        Servo_PWM = 70;
                    else if (Servo_PWM < -70)
                        Servo_PWM = -70;
        }

        // ramp_yingshe = 1.20; // 0.8
        if(DI.ForkCnt == fork_left)
            ramp_yingshe = GetItemValue(Start_Order, yingshe86_Order) / 100.0; // 0.54
        else if(DI.ForkCnt == fork_right)
            ramp_yingshe = GetItemValue(ForkOut_Order, yingshe86_2_Order) / 100.0; // 0.54
    }
    else if (state == 87)
    {
        Servo_PWM = Servo_PWM2;
//        if(DI.ForkCnt == fork_right)
//        {
//            if (Servo_PWM > 100)
//             Servo_PWM = 100;
//        }
        if(DI.ForkCnt == fork_left)
        {
                    if (Servo_PWM > 90)
                        Servo_PWM = 90;
                    if (Servo_PWM < -90)
                        Servo_PWM = -90;
        }
        if(DI.ForkCnt == fork_right)
        {
            if (Servo_PWM > 70)
                Servo_PWM = 70;
            if (Servo_PWM < -70)
                Servo_PWM = -70;
        }

        // ramp_yingshe = 1.20; // 0.8
        if(DI.ForkCnt == fork_left)
            ramp_yingshe = GetItemValue(Ring_Order, yingshe87_Order) / 100.0; // 0.54
        else if(DI.ForkCnt == fork_right)
            ramp_yingshe = GetItemValue(pid_Order, yingshe87_2_Order) / 100.0; // 0.54
    }
    // else if ( state == 51)
    // {
    //     Servo_PWM = Servo_PWM2;

    //     // if (Servo_PWM > 100)
    //     //     Servo_PWM = 100;
    //     // if (Servo_PWM < -100)
    //     //     Servo_PWM = -100;
    //     // ramp_yingshe = 1.2; // 0.54
    //     ramp_yingshe = GetItemValue(Ring_Order, yingshe52_Order) / 100.0; // 0.8
    // }
    else if (state == 52 || state == 51)
    {
        Servo_PWM = Servo_PWM2;
        
        // Servo_PWM = fork2_Filter(Servo_PWM);
        // if (Servo_PWM > 70)
        //     Servo_PWM = 70;
        // if (Servo_PWM < -70)
        //     Servo_PWM = -70;
        // ramp_yingshe = 1.2; // 0.54
        ramp_yingshe = GetItemValue(Ring_Order, yingshe52_Order) / 100.0; // 0.8
    }
    /*出库*/
    else if (state >= 60 && state < 80) //库
    {
        //状态内操作Servo_PWM
        Servo_PWM = Servo_PWM2;
        ramp_yingshe = GetItemValue(yingshe_Order, ChuKuy_Order) / 100.0; // 0.7
    }
    /*圆环*/
    else if (state >= 10 && state < 30 && state != 16)
    {
        ramp_yingshe = GetItemValue(yingshe_Order, ringy_Order) / 100.0; // 1
        Servo_PWM = Servo_PWM2;
    }
    else
    {
        Servo_PWM = Servo_PWM2;
//        if (DI.Length - DI.LengthCheku < 100)
//        {
//            ramp_yingshe = GetItemValue(yingshe_Order, ChuKuy_Order) / 100.0; // 0.7
//        }
//        else
        {
            ramp_yingshe = GetItemValue(yingshe_Order, yingsheS_Order) / 100.0; // 0.8
        }
    }

    Servo_PWM = (int)ditui(Servo_PWM);
    /*保护*/
    if (Test == 1 || ((Angle > 40) || (Angle < -40))
         || (state == 99)
        // || ((DI.Length - DI.LengthCheku > 100) && state != 99 && DI.AD_L < 100 && DI.AD_M < 100 && DI.AD_R < 100)
    )
        Servo_PWM = 0;

    duoji_control(Servo_Center_Mid - Servo_PWM);
    //    yawan = Fuzzy_Update_angle(&table, Servo_PWM);
    // DI.Angle_error = 172.3 * atan(0.00001546 * Servo_PWM * speed) * ramp_yingshe;
    DI.Angle_error = (33.16 * atan(0.0002096  *speed* Servo_PWM-0.0043*Servo_PWM-0.0004888*speed)+2.337)* ramp_yingshe;
    //动态零点
    //    DI.Angle_error = (float)((-0.0747 * (Servo_Center_Mid - Servo_PWM) + 61.973) * yingshe); //拟合曲线
    //    DI.Angle_error = (float)(DI.Angle_error * (0.0265 * (speed)-0.0726));

    //    DI.Angle_error = (float)((-0.000202 * (Servo_Center_Mid - Servo_PWM)*(Servo_Center_Mid - Servo_PWM)+0.2054 * (Servo_Center_Mid - Servo_PWM)-31.55)); //拟合曲线
    //    if(Servo_PWM<0)
    //        DI.Angle_error = (float)(DI.Angle_error * (0.0001872 * (speed)* (speed)+0.002651* (speed)+0.603)*yingshe*0.72 );
    //    else
    //        DI.Angle_error = (float)(DI.Angle_error * (0.0001872 * (speed)* (speed)+0.002651* (speed)+0.603)*yingshe*1.02 );
    //    DI.Angle_error = (float)(DI.Angle_error * (0.0001872 * (speed)* (speed)+0.002651* (speed)+0.603)*yingshe );
    //
    //    DI.Angle_error = (float)((-0.119 * (Servo_Center_Mid - Servo_PWM) + 99.818) ); //拟合曲线
    //    DI.Angle_error = (float)(DI.Angle_error * (0.0265 * (speed)-0.0726)*yingshe);                    //拟合曲线  速度

    /*第三版*/
    // DI.Angle_error = (float)(0.0000001394 * (Servo_Center_Mid - Servo_PWM) * (Servo_Center_Mid - Servo_PWM) * (Servo_Center_Mid - Servo_PWM) - 0.0003764 * (Servo_Center_Mid - Servo_PWM) * (Servo_Center_Mid - Servo_PWM) + 0.2255 * (Servo_Center_Mid - Servo_PWM) - 7.374); //拟合曲线
    // DI.Angle_error = (float)(DI.Angle_error * (0.0001872 * (speed) * (speed) + 0.002651 * (speed) + 0.603) * yingshe);

    /*第四版*/
    // DI.Angle_error=172.3*atan(0.00001546*Servo_PWM*speed)*(-0.00001008*Servo_PWM*Servo_PWM+ 0.0002372*Servo_PWM + 1.239);
    //     if(Servo_PWM<0)
    //         DI.Angle_error=172.3*atan(0.00001546*Servo_PWM*speed)*(0.002334*Servo_PWM + 1.38);
    //     else
    //         DI.Angle_error=172.3*atan(0.00001546*Servo_PWM*speed)*( -0.0004286*Servo_PWM + 1.173);
    // DI.Angle_error=172.3*atan(0.00001546*Servo_PWM*speed)*(0.00000009028*Servo_PWM*Servo_PWM*Servo_PWM-0.00001008*Servo_PWM*Servo_PWM -0.001087*Servo_PWM+ 1.239);
    /*均值滤波*/
    //  DI.Angle_error = momentum_wheel_Filter(DI.Angle_error);
    // yawan = Fuzzy_Update_angle(&table, Servo_PWM);

    // DI.Angle_error = momentum_wheel_Filter(DI.Angle_error);
    // DI.Angle_error = momentum_wheel_Filter(DI.Angle_error);//滤波

    //距离滤波
    // if (DI.Angle_target <= DI.Angle_error)
    // {
    //     DI.Angle_target = DI.Angle_target + (float)(DI.Length - DI.Length_angle) * 0.2;
    //     DI.Length_angle = DI.Length;
    // }
    // else
    // {
    //     DI.Angle_target = DI.Angle_target - (float)(DI.Length - DI.Length_angle) * 0.2;
    //     DI.Length_angle = DI.Length;
    // }
}

/*******************************************************************
【函数名】摄像头 位置式PID
【功  能】舵机打角控制PID
【参数值】float Angle,电单车左右倾角
【参数值】float Gyro 电单车左右角速度
【返回值】小车平衡，舵机转向PID

*****************************************************************/
int SBB_Get_BalancePID(float error)
{
    float Bias;
    static float Bias_last;
    int SBB_BalancePID;
    Bias = error;
//    Integration += Bias; // 积分
//    if (Integration < -380)
//        Integration = -380; //限幅
//    else if (Integration > 380)
//        Integration = 380; //限幅
    //===计算平衡控制的舵机PWM  PID控制 kp是P系数 ki式I系数 kd是D系数
    SBB_BalancePID = Balance_Kp * Bias
//            + Balance_Ki * Integration
            + Balance_Kd * (Bias - Bias_last);
    Bias_last = Bias;

    if (SBB_BalancePID >= 120) //限制幅值
        SBB_BalancePID = 120;
    else if (SBB_BalancePID <= -120) //限制幅值
        SBB_BalancePID = -120;
    return SBB_BalancePID;
}
/********************************************************
 *@函数名: 电磁 位置式PID
 *@说明: none
 *@函数功能: none
 *@Date: 2022-07-05 14:15:58
 ********************************************************/
int AD_Get_BalancePID(float AD_err)
{
    static float AD_err_last;
    int result;
    AD_Integration += AD_err; // 积分
    if (AD_Integration < -380)
        AD_Integration = -380; //限幅
    else if (AD_Integration > 380)
        AD_Integration = 380; //限幅
    //===计算平衡控制的舵机PWM  PID控制 kp是P系数 ki式I系数 kd是D系数
    result = Balance_Kp * AD_err + Balance_Ki * AD_Integration + Balance_Kd * (AD_err - AD_err_last);
    AD_err_last = AD_err;

    if (result >= 120) //限制幅值
        result = 120;
    else if (result <= -120) //限制幅值
        result = -120;
    return result;
}
/****************************************************************
【函数名】int SBB_Get_MotorPI (int Encoder,int Target)
【功  能】电机控制增量式PI
【参数值】int Encoder 编码器脉采集的冲数
【参数值】int Target  期望脉冲数
【返回值】电机PWM

******************************************************************/
int SBB_Get_MotorPI(int Encoder, int Target)
{
    static int Pwm;

    Motor_Bias = Target - Encoder; // 计算偏差
    Pwm += Motor_Kp * (Motor_Bias - Motor_Last_Bias) + Motor_Ki * Motor_Bias;
    // ==增量式PI控制器
    if (Pwm > 7000)
        Pwm = 7000; // 限幅
    else if (Pwm < -7000)
        Pwm = -7000;              // 限幅
    Motor_Last_Bias = Motor_Bias; // 保存上一次偏差

    if (wheel_flag == 0)
    {
        Pwm = 0;
        Motor_Last_Bias = 0;
        Motor_Bias = 0;
    }
    return Pwm; // 增量输出
}
