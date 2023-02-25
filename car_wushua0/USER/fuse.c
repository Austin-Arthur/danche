#include "headfile.h"
#include "fuse.h"

#define speed_NUM 2
//动量轮
PID Ang_Vel_PID = {
    .Kp = 140.001, // 140.001
    .Ki = 0,       // 5
    .Kd = 0        // 10
};
PID Angle_PID = {
    .Kp = 10.001, // 10
    .Ki = 0,      // 0
    .Kd = 0       // 0.5
};

PID MOTOR_PID = {
    .Kp = 0.151, // 0.151
    .Ki = 0,     // 0.008
    .Kd = 0      // 0
};
//后轮
PID SpeedPID = {
    .Kp = 11.0,
    .Ki = 1,
    .Kd = 0};
PID rampPID = {
    .Kp = 2, // 0.151
    .Ki = 3, // 0.008
    .Kd = 0};
float Target_Angle_Y, //串级目标角速度
    Tar_Ang_Vel_Y;    //串级目标角度

uint8 Int_Ok; //初始化成功标志位
int16 PWM_Break;
int32 PWM_DLL;
int16 PWM_DL;
int16 motor_PWM;
int target_speed; // 速度，定时周期内为60个脉冲，龙邱带方向512编码器

TxPack txpack;
RxPack rxpack;
STATE State = INITING;
float Angle_Zero = 0.0; //角度零点
// 别名

int wheel_flag, xzttt, tar_sp;
float yingshe;
static TASK_COMPONENTS TaskComps[] =
    {
        {0, 5, 5, Balance_endocyclic},  //动量轮角速度内环2ms
        {0, 10, 10, Balance_outcyclic}, //动量轮角度外环10ms
        {0, 20, 20, Speed_control},     //动量轮速度外环20ms
        {0, 10, 10, state_machine},     //状态机
        {0, 5, 5, Speed_run},           //后轮速度环
        {0, 10, 10, online},
};
/**************************************************************************************
 * FunctionName   : TaskRemarks()
 * Description    : 任务标志处理
 * EntryParameter : None
 * ReturnValue    : None
 * attention      : ***在定时器中断中调用此函数即可***
 **************************************************************************************/
void TaskRemarks(void)
{
    uint8 i;
    for (i = 0; i < TASKS_MAX; i++) // 逐个任务时间处理
    {
        if (TaskComps[i].Timer) // 时间不为0
        {
            TaskComps[i].Timer--;        // 减去一个节拍
            if (TaskComps[i].Timer == 0) // 时间减完了
            {
                TaskComps[i].Timer = TaskComps[i].ItvTime; // 恢复计时器值，从新下一次
                TaskComps[i].Run = 1;                      // 任务可以运行
            }
        }
    }
}

/**************************************************************************************
 * FunctionName   : TaskProcess()
 * Description    : 任务处理|判断什么时候该执行那一个任务
 * EntryParameter : None
 * ReturnValue    : None
 * * attention      : ***放在mian的while(1)即可***
 **************************************************************************************/
void TaskProcess(void)
{
    uint8 i;
    for (i = 0; i < TASKS_MAX; i++) // 逐个任务时间处理
    {
        if (TaskComps[i].Run) // 时间不为0
        {
            TaskComps[i].TaskHook(); // 运行任务
            TaskComps[i].Run = 0;    // 标志清0
        }
    }
}
/**************************************************************************************
* FunctionName   : state_machine()
* Description    : 状态机
* EntryParameter : None
* ReturnValue    : None

**************************************************************************************/
int xztt1;
void state_machine()
{
    switch (State)
    {
    case INITING:
        State_Init();
        break; //初始化
    case DEBUG:
        State_Debug();
        break; //调试
    case RUN:
        State_Run();
        break; //运行
    case STOP:
        State_Stop();
        break; //停止
    default:
        break;
    }

    if (readValuePack(&rxpack))
    {

        wheel_flag = rxpack.integers[0];
        xzttt = rxpack.integers[1];
        tar_sp = rxpack.integers[2];
        yingshe = rxpack.floats[0];
    }

    if (wheel_flag == 0)
    {
        SpeedPID.SumError = 0;
        SpeedPID.LastError = 0;
        SpeedPID.LLastError = 0;
    }

    //   beep_on();
    printf("%f,%f,%f,%f,%f,%f,%f\n", (float)state,(float)error_xunxian,
           (float)(Servo_PWM), (float)speed, (float)((Angle)), (float)( DI.Angle_error), (float)-speed_filter.data_average
           //  (float)(speed), (float)(target_speed), (float)(motor_PWM)
    ); // (float)speed_filter.data_average); // Angle Motor_Bias
    // printf("%f,%f,%f,%f\n", (float)state, (float)Servo_PWM, (float)speed, (float)target_speed); // Angle Motor_Bias
    //   printf("%f,%f,%f,%f,%f\n", (float)PWM_DLL, (float)PWM_DL, (float)Servo_PWM2, (float)Servo_PWM,(float)Angle); // Angle Motor_Bias
}
/********************************************************
 *@函数名: 图传
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-29 15:42:28
 ********************************************************/
void online()
{
    // ShowPathOnLine();
    // ZW_Send_Image(image);
}

//深度井滤波
float speed_window[speed_NUM];
float speed_Filter(float input)
{
    uint8 i;
    float temp1 = 0;
    float result;

    speed_window[0] = input; // 更新滑动窗口数组

    for (i = 0; i < speed_NUM; i++)
    {
        temp1 += speed_window[i];
    }

    result = temp1 / speed_NUM * 1.0;
    for (i = 0; i < speed_NUM - 1; i++)
    {
        speed_window[speed_NUM - 1 - i] = speed_window[speed_NUM - 2 - i];
    }
    return result;
}

/********************************************************
 *@函数名: 后轮速度环
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-29 15:42:37
 ********************************************************/
extern int run_flag;
int target_speed_last, target_speed_true;
void Speed_run()
{

    if (run_flag != 2                      //
        || ((Angle > 40) || (Angle < -40)) //

        // || ((DI.Length - DI.LengthCheku > 100)
        // && state != 99
        // && DI.AD_L < 100 && DI.AD_M < 100 && DI.AD_R < 100) //
    )
    // if (wheel_flag != 0 || ((Angle > 40) || (Angle < -40)))
    {
        //motor_PWM = 0;
        SpeedPID.SumError = 0;
        SpeedPID.LastError = 0;
        SpeedPID.LLastError = 0;
        SpeedPID.Kp = 0;
        SpeedPID.Ki = 0;
        SpeedPID.Kd = 0;
        target_speed = 0;
    }
    /*环内*/
    else if (state > 10 && state < 30 && state != 17)
    {
        SpeedPID.Kp = 10;
        SpeedPID.Ki = 15;
        SpeedPID.Kd = 0;
        target_speed = GetItemValue(tarspeed_Order, ringt_Order);
        if (state == 11)
        {
            target_speed = target_speed - 2;
        }
    }
    /*出车库*/
    else if (state >= 60 && state < 80) //库减速
    {
        SpeedPID.Kp = 10;
        SpeedPID.Ki = 15;
        SpeedPID.Kd = 0;
        target_speed = GetItemValue(tarspeed_Order, ChuKut_Order);
    }
    /*三叉前*/
    else if (state == 80)
    {
        SpeedPID.Kp = 10;
        SpeedPID.Ki = 15;
        SpeedPID.Kd = 0;
        target_speed = GetItemValue(tarspeed_Order, Fork0_Order);
    }
    //环岛16
    else if (state == 17)
    {
        SpeedPID.Kp = 10;
        SpeedPID.Ki = 15;
        SpeedPID.Kd = 0;
        target_speed = GetItemValue(tarspeed_Order, ring16_sp_Order);
    }
    /*三叉内*/
    else if ((state > 80 && state < 90) || (state >= 30 && state < 40)) //三叉减速  坡道减速
    {

        if (state == 31||state == 32||state == 33 || state == 34)
        {
            SpeedPID.Kp = GetItemValue(Choose_Order, r_f_p_Order) / 10.0;
            SpeedPID.Ki = GetItemValue(Choose_Order, r_f_I_Order) / 10.0;
            SpeedPID.Kd = 20;

//            SpeedPID.Kp = 5;
//            SpeedPID.Kd = 20;
//            SpeedPID.Ki = 0;

//            SpeedPID.Kp = 5;
//            SpeedPID.Kd = 40;
//            SpeedPID.Ki = 5;

                target_speed = GetItemValue(Choose_Order, speed34_Order);
        }
        // else if (state == 32) //上坡
        // {
        //     SpeedPID.Kp = 5;
        //     SpeedPID.Ki = 1;
        //     target_speed = GetItemValue(tarspeed_Order, rampt_Order);
        // }
        // else if (state == 35)
        // {
        //     SpeedPID.Kp = GetItemValue(Choose_Order, r_f_p_Order) / 10.0;
        //     SpeedPID.Ki = GetItemValue(Choose_Order, r_f_I_Order) / 10.0;
        //     // SpeedPID.Kp = 11;
        //     // SpeedPID.Ki = 1;
        //     target_speed = GetItemValue(Ring_Order, yingshe35_Order);
        // }
        else if (state == 84)
        {
//            SpeedPID.Kp = GetItemValue(pid_Order, P84_Order) / 10.0;
//            SpeedPID.Ki = GetItemValue(pid_Order, I84_Order) / 10.0;
            if (DI.ForkCnt == fork_left)
            {
              SpeedPID.Kp = GetItemValue(pid_Order, P84_Order) / 10.0;
              SpeedPID.Ki = GetItemValue(pid_Order, I84_Order) / 10.0;
              SpeedPID.Kd = 20;
            }
            else if (DI.ForkCnt == fork_right)
            {
                SpeedPID.Kp = 5;
                SpeedPID.Kd = 20;
                SpeedPID.Ki = 0;
            }


//            SpeedPID.Kp = 0.5;
//            SpeedPID.Kd = 20;
//            SpeedPID.Ki = 1;
            if (DI.ForkCnt == fork_left)
            {
                target_speed = GetItemValue(Choose_Order, speed34_Order);
            }
            else if (DI.ForkCnt == fork_right)
            target_speed = GetItemValue(Choose_Order, speed84_Order);
        }
        else if (state == 85)
        {

            // SpeedPID.Kp = GetItemValue(pid_Order, rampP_Order) / 10.0;
            // SpeedPID.Ki = GetItemValue(pid_Order, rampI_Order) / 10.0;
            SpeedPID.Kp = 5;
            SpeedPID.Kd = 20;
            SpeedPID.Ki = 0;

//            SpeedPID.Kp = 0.5;
//            SpeedPID.Kd = 20;
//            SpeedPID.Ki = 1;

            // target_speed = GetItemValue(Choose_Order, speed84_Order);
            // SpeedPID.Kp = 0;
            
            // SpeedPID.Ki = 3;

            // target_speed = 60;
//            SpeedPID.Kp = GetItemValue(ForkOut_Order, yingshe84_2_Order) / 100.0;
//            SpeedPID.Ki = GetItemValue(ForkOut_Order, I_85_Order) / 10.0;
            if (DI.ForkCnt == fork_left)
            {
                target_speed = GetItemValue(Choose_Order, speed34_Order)+5;
            }

            else if (DI.ForkCnt == fork_right)
            target_speed = GetItemValue(ForkOut_Order, speed85_Order); 


        }
        else if (state == 86||state==87)
        {
            // SpeedPID.Kp = 0.5;
            // SpeedPID.Kd = 30;
            // SpeedPID.Ki = 0;


           SpeedPID.Kp = 0.5;
           SpeedPID.Kd = 10;
           SpeedPID.Ki = 0.5;

//            SpeedPID.Kp = GetItemValue(ForkOut_Order, P_86_87_Order) / 10.0;
//            SpeedPID.Ki = GetItemValue(ForkOut_Order, I_86_87_Order) / 10.0;

//            target_speed = GetItemValue(ForkOut_Order, speed_86_87_Order);

            if (DI.ForkCnt == fork_left)
            {
                if(state==87)target_speed = GetItemValue(ForkOut_Order, speed_86_87_Order)+10;
                else target_speed = GetItemValue(ForkOut_Order, speed_86_87_Order);
            }
            else if (DI.ForkCnt == fork_right)
                target_speed = GetItemValue(ForkOut_Order, speed85_Order);


            // target_speed = GetItemValue(tarspeed_Order, rampt_Order);
        }
        // else if (state == 87)
        // {
        //     SpeedPID.Kp = 0;
        //     SpeedPID.Ki = 3;
        //     target_speed = 80;

        //     // target_speed = GetItemValue(tarspeed_Order, rampt_Order);
        // }
        else //81 82 83
        {
            SpeedPID.Kp = 5;
            SpeedPID.Kd = 20;
            SpeedPID.Ki = 0;
//            target_speed = GetItemValue(tarspeed_Order, rampt_Order);
            if (DI.ForkCnt == fork_left)
            target_speed = GetItemValue(tarspeed_Order, rampt_Order);//65
            else
            target_speed = GetItemValue(tarspeed_Order, Fork0_Order);
        }
    }
    /*入库*/
    else if (state == 51||state == 52)
    {
            // SpeedPID.Kp = 10;
            // SpeedPID.Ki = 3;
        SpeedPID.Kp = 0;
        SpeedPID.Kd = 0;
        SpeedPID.Ki = 3;
        // target_speed = GetItemValue(Debug_Order, Debug_Speed_Order) - 5;
        target_speed = 70;
    }
    // else if (state == 52)
    // {
    //     // SpeedPID.Kp = 0.3;
    //     // SpeedPID.Ki = 0.2;
    //     SpeedPID.Kp = 0;
    //     SpeedPID.Ki = 2;
    //     // target_speed = GetItemValue(Debug_Order, Debug_Speed_Order) - 5;
    //     target_speed = 70;
    // }
    else if (state == 99)
    {
        SpeedPID.Kp = 0;
        SpeedPID.Ki = 15;
        SpeedPID.Kd = 0;

        target_speed = 0;
    }
    else
    {
//        SpeedPID.Kp = 10;
//        SpeedPID.Ki = 15;
//        SpeedPID.Kp = 5;
//        SpeedPID.Kd = 20;
        SpeedPID.Kp = 10;
        SpeedPID.Kd = 0;
        SpeedPID.Ki = 15;
        target_speed = GetItemValue(Debug_Order, Debug_Speed_Order);
    }
    // else
    // {
    // SpeedPID.Kp = xzttt / 10.0;
    // SpeedPID.Ki = yingshe / 10.0;
    // SpeedPID.Kp = GetItemValue(pid_Order, rampP_Order) / 10.0;
    // SpeedPID.Ki = GetItemValue(pid_Order, rampI_Order) / 10.0;
    // target_speed = GetItemValue(Debug_Order, Debug_Speed_Order);
    // target_speed = 70;
    // motor_PWM = motor_PWM + IncPIDCalc(&SpeedPID, 50, speed);
    // }
    motor_PWM = motor_PWM + IncPIDCalc(&SpeedPID, target_speed, speed);
    if(((Angle > 40) || (Angle < -40)))
    motor_PWM=0;
    // target_speed = speed_Filter(target_speed);
    // motor_PWM = motor_PWM + IncPIDCalc(&SpeedPID, target_speed, speed);
    // if(state==99)motor_PWM = 0;

    motor_control2(motor_PWM); // 电机控制
}
/********************************************************
 *@函数名: 动量轮控制
 *@说明: none
 *@函数功能: none
 *@Date: 2022-06-29 15:42:54
 ********************************************************/
//串级的基本思想，最内环角速度环，内环角度环，外环速度环，外环的输出作为内环的输入，外环输出内环目标值。比如速度环输出的是角度环的目标角度，目标角度
//与实际解算角度做偏差进行PID计算输出角速度环，角度环和角速度环相同道理，最内环角速度环输出PWM控制电机。
void Balance_endocyclic() //角速度最内环2ms中断
{

    PWM_DLL = Balance_nei_PID(&Ang_Vel_PID, (gyro_roll * 0.1), -Tar_Ang_Vel_Y); //角速度环输出PWM控制电机
    PWM_DL = range_protect(PWM_DLL, -5000, 5000);                               // PWM输出限幅
    /*
        if(PWM_DLL<-0) PWM_DLL -=500;    //死区（暂时不用，没必要用，要用的话自己测一下死区占空比）
        else if(PWM_DLL>0) PWM_DLL+=500; //死区
        if((PWM_DLL<500)&&(PWM_DLL>-500))
            PWM_DLL=0;
    */
    //    PWM_DL =  -PWM_DL;

    if ((Angle > 45) || (Angle < -45)
        // || ((DI.Length - DI.LengthCheku > 100) && state != 99 && DI.AD_L < 100 && DI.AD_M < 100 && DI.AD_R < 100)
        || (state == 99&&((Angle > 45) || (Angle < -45)))
        ) //摔倒停车判断
    {
        motor_control1(0); // angle_offset_vertical为加速度计两轴反正切求得角度
    }
    else
        motor_control1(PWM_DL); //动量轮电机输出
}

void Balance_outcyclic() //角度内环10ms
{
    // Tar_Ang_Vel_Y = Balance_wai_PID(&Angle_PID, (Angle - (Angle_Zero + DI.Angle_error)), Target_Angle_Y); //角度环输出目标角速度
    Tar_Ang_Vel_Y = Balance_wai_PID(&Angle_PID, (Angle - (DI.Angle_error)), Target_Angle_Y); //角度环输出目标角速度
    // Tar_Ang_Vel_Y = Balance_wai_PID(&Angle_PID, (Angle - (Angle_Zero + DI.Angle_target)), Target_Angle_Y); //角度环输出目标角速度

    // Tar_Ang_Vel_Y=Balance_wai_PID(&Angle_PID,(Angle-Angle_Zero),0);  //角度环输出目标角速度
}
void Speed_control() //速度外环100ms
{
    //动量轮速度环
    Target_Angle_Y = Balance_Sudu_PID(&MOTOR_PID, 0, -speed_filter.data_average); //速度环输出目标角度
    Target_Angle_Y = Target_Angle_Y * 0.01;                                       //缩小目标角度 ,也可以不用缩小,调小PID参数也行
}
/************************************************
函数名：range_protect(int32 duty, int32 min, int32 max)
功  能：限幅保护
参  数：void
返回值：void
************************************************/
int16 range_protect(int32 duty, int16 min, int16 max) //限幅保护
{
    if (duty >= max)
    {
        return max;
    }
    if (duty <= min)
    {
        return min;
    }
    else
    {
        return duty;
    }
}
