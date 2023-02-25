/*
 * State.c
 *
 *  Created on: 2022年1月2日
 *      Author: 11609
 */
#include "State.h"



extern float Angle_Zero;
int Test = 0;
extern int test_x[10];

extern int MotorDutyB;
extern int target_speed;
extern int state_dx;
extern float Angle_yaw;
extern float Angle_pitch;
extern int16 PWM_DL;
extern int time_measure;
extern int run_flag;
extern float Balance_Kp;
extern float pwm_v, pwm_a_v, pwm_a;

extern int xzttt, target_sped;
extern float yingshe;
extern int U1Rule[4]; //偏差  偏差的变化率  采用的四条规则
void Set_Data()
{

//    SetItemValue(Start_Order, Ang_vel_P_Order, 0.0);
//    SetItemValue(Start_Order, Ang_vel_I_Order, 0.0);
//    SetItemValue(Start_Order, Ang_vel_D_Order, 0.0);
//    SetItemValue(pid_Order, Ang_P_Order, 0);
//    SetItemValue(pid_Order, Ang_D_Order, 0);
//    SetItemValue(Debug_Order, Debug_Threshold_Order, 140);
}
void Get_Data()
{
        Ang_Vel_PID.Kp = GetItemValue(Start_Order, Ang_vel_P_Order);
        Ang_Vel_PID.Ki = 0;
        Ang_Vel_PID.Kd = 0;
        Angle_PID.Kp = GetItemValue(pid_Order, Ang_P_Order) / 10.0;
        Angle_PID.Kd = 0;
        MOTOR_PID.Kp = GetItemValue(pid_Order, speed_P_Order) / 10.0;
        MOTOR_PID.Ki = 0;
//        rampPID.Kp = GetItemValue(pid_Order, rampP_Order)/10;
//        rampPID.Ki = GetItemValue(pid_Order, rampI_Order)/10;
        Test = GetItemValue(Debug_Order, Debug_Test_Order);
        DI.Two_Cam = GetItemValue(Debug_Order, Debug_AD_Cam_Order);

        target_speed = GetItemValue(Debug_Order, Debug_Speed_Order);

        Angle_Zero = (float)(GetItemValue(Start_Order, Angle_zreo_Order) / 10);

        DI.RingSumCnt = (int)GetItemValue(Ring_Order, Ring_RingNum_Order); //赛道中圆环个数
        ringSize[0] = (int)GetItemValue(Ring_Order, Ring_Ring1_Order);     //第1个圆环大小
//        ringSize[1] = (int)GetItemValue(Ring_Order, Ring_Ring2_Order);     //第2个圆环大小
//        ringSize[2] = (int)GetItemValue(Ring_Order, Ring_Ring3_Order);     //第3个圆环大小
//        ringSize[3] = (int)GetItemValue(Ring_Order, Ring_Ring4_Order);     //第4个圆环大小

        is_checkZebro = GetItemValue(Choose_Order, is_checkZebro_Order);
        is_ChuKu = GetItemValue(Choose_Order, is_ChuKu_Order);    //第4个圆环大小
    //    oled_printf_float(0,7,(int)X_Velocity_KP,3,1);

    if (MCtrl.ui8_NowPage == Debug_Order)
    {
        if (GetItemValue(Debug_Order, Debug_DrawData_Order) == 1)
        {
//            GarageInPatchLine(86,DI.Top_max_Y[86],cheku_line);//补线
            LCD_MT9V032(image);

//            oled_printf_p6x8str_add_int32(96, 0, "P",1,(int)(Servo_PWM), 3); //109
//            oled_printf_p6x8str_add_int32(96,1,"e",1,test1_zebor,3);
//            oled_printf_p6x8str_add_int32(96,2,"e",1,test2_zebor,3);
//            oled_printf_int32(96,1,(DI.Length - DI.tempLength),3);
//            oled_printf_p6x8str_add_int32(96, 2, "P",1,(int)(Servo_PWM1), 3); //109
//            oled_printf_p6x8str_add_int32(96, 3, "P",1,(int)(Servo_PWM2), 3); //109
//            oled_printf_p6x8str_add_int32(96, 0, "L",1,(int)(DI.Length), 4); //109
//            oled_printf_p6x8str_add_int32(96, 1, "t",1, (int)(DI.tempLength), 4); //109
//            oled_printf_p6x8str_add_int32(96, 2, "C",1,(int)(DI.rampCnt), 4); //109
//            oled_printf_p6x8str_add_int32(96, 3, "R",1,(int)(DI.IEX[M_R][0]), 4); //109
//            oled_printf_p6x8str_add_int32(96, 4, "L",1,(int)(DI.IEX[M_L][0]), 4); //109

//            oled_printf_p6x8str_add_int32(96,2,"x",1,DI.MaxY[0],3);

            //            oled_printf_float(96,0,(float)(DI.MidLine -47),2,1);
            //            oled_printf_float(96,1,(float)(DI.AD_err),3,1);
            //            oled_printf_int32(96,2,(int)(62-DI.SightDistance),3);
//                        oled_printf_int32(96,0,(int)(state),3);//speed
//                                    oled_printf_p6x8str_add_int32(96,1,"Fla",3,flag_xxx,1);
//                                    oled_printf_p6x8str_add_int32(96,2,"LX",2,abs(DI.Top_edge_Y[test_G[M_R][2] = G_point[M_R][2]] - DI.Top_edge_Y[test_G[M_R][2] = G_point[M_R][2] - 1]) ,2);
//                                    oled_printf_p6x8str_add_int32(96,3,"K1",3,(GetSlope2(test_G[M_R][2], DI.Top_edge_Y[test_G[M_R][2]], test_G[M_R][2] - 3, DI.Top_edge_Y[test_G[M_R][2] - 3]) + GetSlope2(test_G[M_R][2] + 3, DI.Top_edge_Y[test_G[M_R][2] + 3], test_G[M_R][2], DI.Top_edge_Y[test_G[M_R][2]])),1);
//                                    oled_printf_int32(96,4,(int)(test_G[M_R][0]),2);//speed
//                                    oled_printf_int32(96,5,(int)(test_G[M_R][2]),2);//speed

            //            oled_printf_float(96,4,(float)(Balance_Kp),2,1);


//                        oled_printf_int32(96,0,DI.Line_Selected_Y[0],2);
//                        oled_printf_int32(96,1,DI.Line_Selected_Y[1],2);
//                        oled_printf_int32(96,2,DI.Line_Selected_Y[2],2);
//                        oled_printf_int32(96,3,DI.Line_Selected_Y[3],2);
//                        oled_printf_int32(96,4,DI.Line_Selected_Y[4],2);
//                        oled_printf_int32(96,5,DI.Line_Selected_Y[5],2);
//                        oled_printf_int32(96,6,DI.Line_Selected_Y[6],2);
//            oled_printf_p6x8str_add_int32(96,1,"e",1,error_xunxian,3);
//            oled_printf_int32(96,0,Servo_Center_Mid - Servo_PWM,3);
//            oled_printf_p6x8str_add_int32(96,0,"B",1, bottom_pointY,2);
//            oled_printf_p6x8str_add_int32(96,1,"Y",1,DI.top_Y,3);

//            oled_printf_p6x8str_add_int32(96,0,"A",1,(bottom_pointX - fork_L_x),2);
//            oled_printf_p6x8str_add_int32(96,1,"B",1,(fork_R_x - bottom_pointX),3);
//            oled_printf_p6x8str_add_int32(96,2,"C",1,(abs(fork_L_k)),2);
//            oled_printf_p6x8str_add_int32(96,3,"C",1,(abs(fork_R_k)),3);
//            oled_printf_p6x8str_add_int32(96,4,"D",1,((DI.Top_edge_Y[fork_R_x] - DI.Top_edge_Y[bottom_pointX])),2);
//            oled_printf_p6x8str_add_int32(96,5,"D",1,((DI.Top_edge_Y[fork_L_x] - DI.Top_edge_Y[bottom_pointX])),3);
//            oled_printf_p6x8str_add_int32(96,6,"E",1,(bottom_pointY),3);
//            oled_printf_p6x8str_add_int32(96,7,"F",1,( DI.top_Y),3);


//
//            oled_printf_p6x8str_add_int32(96,3,"x",1,DI.IEX[M_L][3],3);
//            oled_printf_p6x8str_add_int32(96,4,"x",1,DI.IEX[M_R][3],3);
//            oled_printf_p6x8str_add_int32(96,5,"x",1,DI.Ladder_RBorder[3],3);
//            oled_printf_p6x8str_add_float(96,2,"A",1, DI.Angle_error,3,1);

//                         oled_printf_int32(96,3,CI.cnst,3);
            // oled_printf_int32(96,0,G_point[M_R][0],2);
            // oled_printf_int32(96,1,G_point[M_R][1],2);
            // oled_printf_int32(96,3,G_point[M_R][2],2);
            // oled_printf_int32(96,4,G_point[M_R][3],2);

//            oled_printf_p6x8str_add_float(96,6,"A",2, Angle,2,1);
//            oled_printf_p6x8str_add_int32(96,0,"f",1,flag_cir,2);
//            oled_printf_p6x8str_add_int32(96,1,"x",1,circleLx,2);
//            oled_printf_p6x8str_add_int32(96,2,"y",1,circleLy,2);
            
//              oled_printf_p6x8str_add_int32(96,6,"r",1,flag_rrr,2);
//
//               oled_printf_p6x8str_add_int32(96,1,"L",1,DI.Ladder_LBorder[0],2);
//               oled_printf_p6x8str_add_int32(96,2,"R",1,DI.Ladder_RBorder[0],2);
//               oled_printf_p6x8str_add_int32(96,3,"L",1,DI.Ladder_LBorder[1],2);
//               oled_printf_p6x8str_add_int32(96,4,"R",1,DI.Ladder_RBorder[1],2);
                        //            oled_printf_p6x8str_add_int32(96,3,"x",1,DI.IEX[M_L][3],3);
//                                    oled_printf_p6x8str_add_int32(96,2,"x",1,DI.MaxY[0],3);
//                                    oled_printf_p6x8str_add_int32(96,3,"x",1,DI.MaxY[10],3);
//                                    oled_printf_p6x8str_add_int32(96,4,"x",1,DI.Data[37],3);
//                        oled_printf_p6x8str_add_int32(96,5,"N",1,rampN,2);
//                        oled_printf_p6x8str_add_int32(96,6,"r",1,Is_ramp(1),1);
            oled_p6x8str(96, 7, state_name);
//            oled_printf_p6x8str_add_float(96,3,"P",1,(int)(Angle_pitch),3,1);
//            oled_printf_p6x8str_add_int32(96,4,"T",1,DI.top_Y,2); //20
//            oled_printf_int32(96, 5, (int)(DI.Length), 4); //109
//            oled_printf_int32(96, 6, (int)(DI.tempLength), 4); //25
            oled_printf_p6x8str_add_int32(96,0,"e",1,error_xunxian,3);
            oled_printf_p6x8str_add_float(96,1,"e",1,Balance_Kp,3,1);
//            oled_printf_p6x8str_add_int32(96,1,"e",1,Servo_PWM,3);
//            oled_printf_p6x8str_add_int32(96,3,"A",1,DI.AD_err,3);
//            oled_printf_p6x8str_add_int32(96,4,"A",1,Servo_PWM1,3);


//            oled_printf_int32(96,5,DI.AD_L,4);//递推权重滤波后电感值
//            oled_printf_int32(96,6,DI.AD_M,4);//递推权重滤波后电感值

//            oled_printf_int32(96,7,DI.AD_R,4);
            // oled_printf_int32(96,4,(int)(U1Rule[0]),3);//DI.Top_max_Y[1]
            // oled_printf_int32(96,5,(int)(U1Rule[1]),3);
//            oled_printf_p6x8str_add_int32(96,0,"B",1, bottom_pointY,2);
//            oled_printf_p6x8str_add_int32(96,1,"F",1,DI.ForkLength,2);

//            oled_printf_p6x8str_add_float(96,2,"L",1, Is_straight_abs(1,10,DI.IEX[M_L]),3,1);
//            oled_printf_p6x8str_add_float(96,3,"R",1, Is_straight_abs(1,10,DI.IEX[M_R]),3,1);
//            oled_printf_p6x8str_add_int32(96,4,"T",1,DI.top_Y,2);
//            oled_printf_p6x8str_add_int32(96,5,"Out",3,Is_OutGarage(),1);
//            oled_printf_p6x8str_add_float(96,2,"g",1, Angle,3,1);
//            oled_printf_p6x8str_add_float(96,3,"z",1, Angle_Zero,3,1);
            oled_printf_int32(96, 2, (int)(hang), 1); // CI.cnst
            oled_printf_int32(96, 3, (int)(lei), 1);  // CI.cnst
            oled_printf_int32(96, 4, (int)(Servo_PWM2), 4); // CI.cnst
//            oled_printf_int32(96, 5, (int)(DI.Length), 3);  // CI.cnst

//            oled_printf_int32(96, 5, (int)(DI.top_Y), 4);
//            oled_printf_int32(96, 5, (int)(DI.ForkCnt), 4);

//            oled_printf_p6x8str_add_int32(96,6,"f",1,Is_fork3(),1);
//            oled_p6x8str(80, 7, state_name);
//            oled_printf_int32(96, 5, (int)(DI.tempLength), 4);
//            oled_printf_int32(96, 6, (int)(DI.LengthRing), 4);

            /*
                        oled_printf_int32(96,4,(int)(DI.Length),3);//DI.Top_max_Y[1]
                        oled_printf_int32(96,5,(int)(DI.tempLength),3);
                        oled_printf_int32(96,6,(int)(DI.LengthRamp),3);//CI.cnst
                        oled_printf_int32(96,7,(int)(CI.cnst),3);//CI.cnst

                        */
            /*
                        oled_printf_int32(96,1,(int)(DI.Ladder_LBorder[DI.Line_Selected_Y[0]]),3);
                        oled_printf_int32(96,2,(int)(ImageWide[DI.Line_Selected_Y[0]]/2),3);
                        oled_printf_int32(96,3,(int)(1.0*(DI.Ladder_LBorder[DI.Line_Selected_Y[0]]+ImageWide[DI.Line_Selected_Y[0]]/2)),3);
                        image[62-DI.Line_Selected_Y[0]][(int)1.0*(DI.Ladder_LBorder[DI.Line_Selected_Y[0]]+ImageWide[DI.Line_Selected_Y[0]]/2)] = 0;
            */
        }
        if (GetItemValue(Debug_Order, Debug_DrawData_Order) == 2)
        {
            ShowPath();
            oled_printf_float(96, 0, (float)(DI.MidLine - 47), 3, 1);
            oled_printf_int32(96, 1, (int)(62 - DI.SightDistance), 5);
            oled_printf_int32(96, 2, (int)(state), 5);

        }

        if (GetItemValue(Debug_Order, Debug_DrawData_Order) == 3)
        {
            Show8Path();
            oled_printf_p6x8str_add_float(96,2,"A",1, Angle,3,1);
        }
        if (GetItemValue(Debug_Order, Debug_DrawData_Order) == 4)
        {
            Show8Path0();

            oled_printf_p6x8str_add_int32(96,0,"f",1,flag_cir,2);
            oled_printf_p6x8str_add_int32(96,1,"x",1,circleLx,2);
            oled_printf_p6x8str_add_int32(96,2,"y",1,circleLy,2);


            // oled_printf_int32(96,0,G_point[M_L][1],2);
            // oled_printf_int32(96,1,G_point[M_L][3],2);
            // oled_printf_int32(96,3,G_point[M_R][1],2);
            // oled_printf_int32(96,4,G_point[M_R][3],2);
//            oled_printf_p6x8str_add_int32(96,0,"s",1,SmallS(),2);
//            oled_printf_p6x8str_add_int32(96,1,"Sms",3,Is_SmallS(),1);
//            oled_printf_p6x8str_add_int32(96,2,"Y",1,L_Move.AllMaxY,2);
//            oled_printf_p6x8str_add_int32(96,3,"T",1,DI.Top_edge_Y[39],2);
//            oled_printf_p6x8str_add_int32(96,4,"O",1,DI.Top_edge_Y[47],2);
//            oled_printf_p6x8str_add_int32(96,5,"P",1,DI.Top_edge_Y[55],2);

        }
        if (GetItemValue(Debug_Order, Debug_DrawData_Order) == 5)
        {
            Show8Path1(); //显示外边界



//            oled_printf_int32(96, 0, (int)(( (DI.Top_edge_Y[G_point[M_L][2]]))), 2);
//            oled_printf_int32(96, 1, (int)(DI.Top_edge_Y[G_point[M_L][2]]), 2);
//            oled_printf_float(96, 2,(DI.Top_edge_Y[G_point[M_L][2]] - DI.Top_edge_Y[G_point[M_L][2] + 2]) , 3, 1);
//            oled_printf_float(96, 3, (DI.Top_edge_Y[G_point[M_L][2]] - DI.Top_edge_Y[G_point[M_L][2] + 3]) , 3, 1);
//            oled_printf_int32(96, 3, (int)(fork_R_y), 2);
//            oled_printf_float(96, 4, (int)((GetSlope2(G_point[M_L][2], DI.Top_edge_Y[G_point[M_L][2]], G_point[M_L][2] - 3, DI.Top_edge_Y[G_point[M_L][2] - 3]) + GetSlope2(G_point[M_L][2] + 3, DI.Top_edge_Y[G_point[M_L][2] + 3], G_point[M_L][2], DI.Top_edge_Y[G_point[M_L][2]])) ), 3, 1);
//            oled_printf_float(96, 5, (int)((GetSlope2(G_point[M_L][2], DI.Top_edge_Y[G_point[M_L][2]], G_point[M_L][2] - 3, DI.Top_edge_Y[G_point[M_L][2] - 3]) + GetSlope2(G_point[M_L][2] + 3, DI.Top_edge_Y[G_point[M_L][2] + 3], G_point[M_L][2], DI.Top_edge_Y[G_point[M_L][2]])) ), 3, 1);
//            oled_printf_int32(96, 6, (int)bottom_pointY, 2);

//            oled_printf_int32(96, 0, (int)(bottom_pointX - fork_L_x), 2);
//            oled_printf_int32(96, 1, (int)(fork_R_x - bottom_pointX), 2);
//            oled_printf_p6x8str_add_float(96,2,"L",1, abs(fork_L_k),3,1);
//            oled_printf_p6x8str_add_float(96,3,"R",1, abs(fork_R_k),3,1);
//            oled_printf_int32(96, 4, (int)(DI.Top_edge_Y[fork_R_x]-DI.Top_edge_Y[bottom_pointX]), 2);
//            oled_printf_int32(96, 5, (int)(DI.Top_edge_Y[bottom_pointX]-DI.Top_edge_Y[fork_L_x]), 2);
//            oled_printf_int32(96, 6, (int)bottom_pointY, 2);

//            oled_printf_p6x8str_add_int32(96,1,"Fla",3,flag_xxx,1);
//            oled_printf_p6x8str_add_int32(96,6,"f",1,Is_fork3(),1);
//            oled_printf_p6x8str_add_int32(96,2,"x1",2,G_point[M_L][0],2);
//            oled_printf_p6x8str_add_int32(96,3,"y2",2,G_point[M_L][3],2);
//            oled_printf_p6x8str_add_int32(96,4,"as",2,abs(G_point[M_L][0] - G_point[M_L][2]),2);



//            oled_printf_int32(96, 6, (int)(DI.Length), 4);

//
//            oled_printf_int32(96,0,G_point[M_R][0],2);
//            oled_printf_int32(96,1,G_point[M_R][1],2);
//            oled_printf_int32(96,3,Top_edge_Y[x_82],2);
//            oled_printf_int32(96,4,(63 - Top_edge_Y[0] - (1 - 0)),2);
//            oled_printf_p6x8str_add_int32(96,5,"Fla",3,flag_xxx,1);
//
//            oled_printf_float(96,5, (GetSlope2(G_point[M_R][2], Top_edge_Y[G_point[M_R][2]], G_point[M_R][2] - 3, Top_edge_Y[G_point[M_R][2] - 3]) - GetSlope2(G_point[M_R][2] + 3, Top_edge_Y[G_point[M_R][2] + 3], G_point[M_R][2], Top_edge_Y[G_point[M_R][2]])),3,1);
//                        oled_printf_p6x8str_add_int32(96,0,"A",1,(bottom_pointX - fork_L_x),2);
//                        oled_printf_p6x8str_add_int32(96,1,"B",1,(fork_R_x - bottom_pointX),3);
//                        oled_printf_p6x8str_add_int32(96,2,"C",1,(abs(fork_L_k)),2);
//                        oled_printf_p6x8str_add_int32(96,3,"C",1,(abs(fork_R_k)),3);
//                        oled_printf_p6x8str_add_int32(96,4,"D",1,((DI.Top_edge_Y[fork_R_x] - DI.Top_edge_Y[bottom_pointX])),2);
//                        oled_printf_p6x8str_add_int32(96,5,"D",1,((DI.Top_edge_Y[fork_L_x] - DI.Top_edge_Y[bottom_pointX])),3);


//                        oled_printf_p6x8str_add_int32(96,0,"A",1,(corner_Rx - fork_R_x),2);
//                        oled_printf_p6x8str_add_int32(96,1,"B",1,((fork_R_x - bottom_pointX)),3);
//                        oled_printf_p6x8str_add_int32(96,2,"C",1,(bottom_pointX),2);
//                        oled_printf_p6x8str_add_int32(96,3,"C",1,(fork_R_x),3);
////                        oled_printf_p6x8str_add_int32(96,4,"D",1,(fork_L_x),2);
//                        oled_printf_p6x8str_add_int32(96,5,"D",1,(abs(fork_L_k)),3);
//                        oled_printf_p6x8str_add_int32(96,6,"E",1,(abs(fork_R_k)),3);
//                        oled_printf_p6x8str_add_int32(96,7,"F",1,(bottom_pointY),3);


//
//            oled_printf_p6x8str_add_int32(96,0,"A",1,DI.top_Y,2);
//            oled_printf_p6x8str_add_int32(96,1,"Y",1,L_Move.AllMaxY,2);
            oled_printf_p6x8str_add_int32(96,0,"A",1,(break_p1),2);
            oled_printf_p6x8str_add_int32(96,1,"A",1,(break_p2),2);
            oled_printf_p6x8str_add_int32(96,2,"A",1,(break_p3),2);
            oled_printf_p6x8str_add_int32(96,3,"A",1,(break_p2-break_p1),2);
            oled_printf_p6x8str_add_int32(96,4,"A",1,(break_p3-break_p2),2);
//            oled_printf_p6x8str_add_int32(96,3,"A",1,(Top_edge_Y[btn_82]),2);





//           oled_p6x8str(96, 7, state_name);
        }
    }

    if (GetItemValue(Debug_Order, Debug_Run_Order) == 1)
    {
        State = RUN;
        stop = 0;
        run_flag = 1;
        oled_fill(0);
    }
}
void State_Init()
{
    disableInterrupts(); //关闭中断
    get_clk();           //获取时钟频率  务必保留

    initial();
    InitMenu();

    uart_init(UART_2, 38400, UART2_TX_P10_5, UART2_RX_P10_6); //手机

    uart_init(UART_1, 38400, UART1_TX_P11_12, UART1_RX_P11_10); // vofa

    //    uart_init(UART_2, 2000000, UART2_TX_P10_5, UART2_RX_P10_6); //图传上位机

    pit_interrupt_ms(CCU6_0, PIT_CH1, 1);
    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);

    //    Set_Data();

    enableInterrupts(); //开启中断

    memset(variable, 0, 10); //清零
    State = DEBUG;
}
void State_Debug()
{
    KeyWork();
    Get_Data();
}
void State_Run()
{
    KeyWork();

   oled_printf_p6x8str_add_float(0,2,"Ag",2, Angle,3,1);
   oled_printf_p6x8str_add_float(0,3,"Ae",2, DI.Angle_error,3,1);
//    oled_printf_float(0,4,PWM_DLL,5,1);//
//    oled_printf_int32(0,1, Servo_PWM,5);
//    oled_printf_int32(0,2, Servo_PWM1,5);
//    oled_printf_int32(0,3, Servo_PWM2,5);
//    oled_printf_p6x8str_add_int32(70,3,"speed",5,(int)(speed),3);
//    oled_printf_p6x8str_add_int32(70,4,"speed",5,(int)(target_speed),3);
//    oled_printf_p6x8str_add_int32(70,5,"motor",5,(int)(motor_PWM),3);

//    oled_printf_int32(0,4,DI.AD_L,5);//递推权重滤波后电感值
//    oled_printf_int32(0,5,DI.AD_M,5);
//    oled_printf_int32(0,6,DI.AD_R,5);
//        oled_printf_int32(0,4,(int)(SpeedPID.Kp*((tar_sp-speed)-SpeedPID.LastError)),5);//递推权重滤波后电感值
//        oled_printf_int32(0,5,SpeedPID.Ki*(tar_sp-speed),5);
//        oled_printf_int32(0,6,DI.AD_R,5);

//        oled_printf_float(0,0,Angle,3,1);
//        oled_printf_float(0,1,GYRO_Real.X,4,1);
//        oled_printf_float(0,2,GYRO_Real.Y,4,1);
//        oled_printf_float(0,3,GYRO_Real.Z,4,1);
//
//
        oled_printf_float(0,4,DI.ForkCnt ,4,1);
        oled_printf_float(0,5,DI.top_Y,4,1);
        oled_p6x8str(96, 7, state_name);
//        oled_printf_float(0,6,ACC_Real.Z,4,1);//speed_filter.data_average




    // oled_printf_float(0, 0, Angle, 3, 1); // Angle_Zero
    // oled_printf_float(30, 0, gyro_roll, 3, 1);
    // oled_printf_float(60, 0, Angle - Angle_Zero, 3, 1);

    // oled_printf_int32(90, 0, speed_filter.data_average, 5); // duty

    /*
        oled_printf_int32(0,1,MotorDutyA,5);
        oled_printf_int32(40,1,PWM_X,5);
        oled_printf_int32(80,1,PWM_accel,5);

        oled_printf_float(0,2,test_x[0],3,1);
        oled_printf_float(30,2,test_x[1],3,1);
        oled_printf_float(60,2,test_x[2],3,1);
        oled_printf_int32(90,2,MotorDutyB,5);

        oled_printf_int32(0,3,speed,5);
        oled_printf_int32(30,3,target_speed,5);
    */

    // oled_printf_float(0, 1, Ang_Vel_PID.Kp, 5, 2);
    // oled_printf_float(40, 1, Ang_Vel_PID.Ki, 5, 2);
    // oled_printf_float(80, 1, Ang_Vel_PID.Kd, 5, 2);

    // oled_printf_float(0, 2, Angle_PID.Kp, 5, 2);
    // oled_printf_float(40, 2, Angle_PID.Kd, 5, 2);

    // oled_printf_float(0, 3, MOTOR_PID.Kp, 5, 2);
    // oled_printf_float(40, 3, MOTOR_PID.Ki, 5, 2);

    /*
        oled_printf_float(0,4,Target_Angle_Y,5,2);//速度环结果
        oled_printf_float(0,5,Tar_Ang_Vel_Y,5,1);//角度环结果
        oled_printf_float(0,6,PWM_DLL,5,1);//



        oled_printf_float(80,5,start_flag,5,1);

        oled_printf_float(80,6,speed,5,1);//start_flag

    */
//    oled_printf_float(40,6,speed_filter.data_average,5,1);//speed
    /*
        oled_printf_int32(0,4,DI.AD_L,5);//递推权重滤波后电感值
        oled_printf_int32(40,4,DI.AD_M,5);
        oled_printf_int32(80,4,DI.AD_R,5);
        oled_printf_int32(0,5,DI.AD_VL,5);
        oled_printf_int32(40,5,DI.AD_VR,5);
        oled_printf_int32(80,5,DI.AD_err,5);//DI.Angle_error
    */

    // oled_printf_int32(0, 4, xzttt, 5);
    // oled_printf_int32(40, 4, target_speed, 5);
    // oled_printf_float(80, 4, yingshe, 2, 1);

    // oled_printf_int32(0, 5, speed, 5);
    // oled_printf_float(40, 5, DI.Angle_error, 2, 1);


    
    // oled_printf_p6x8str_add_float(96,4,"2",1,fork_R_k,2,1);

//    oled_printf_p6x8str_add_int32(70,0,"CUK",3,(int)(is_ChuKu),1);
//    oled_printf_p6x8str_add_int32(70,1,"TOP",3,(int)(DI.top_Y),4);
//    oled_printf_p6x8str_add_int32(70,2,"LeB",3,(int)(DI.Ladder_LBorder[0]),4);
//    oled_printf_p6x8str_add_int32(70,3,"ReB",3,(int)(DI.Ladder_RBorder[0]),4);
//    oled_printf_p6x8str_add_int32(80,4,"Len",3,(int)(DI.Length),4);
//    oled_printf_float(80, 5, SpeedPID.Kp, 3, 1);

//                oled_printf_int32(96, 4, (int)(DI.Length), 4);
//                oled_printf_int32(80, 5, (int)(DI.tempLength), 4);
//    oled_printf_p6x8str_add_int32(96,1,"F",1,(DI.ForkCnt % 1),2);
//    oled_p6x8str(80, 7, state_name);
    if (MCtrl.ui8_NowPage == Debug_Order)
    {
        if (GetItemValue(Debug_Order, Debug_Run_Order) == 0)
        {
            State = DEBUG;
            stop = 1;
            run_flag = 0;
            DisplayPage(MCtrl.ui8_NowPage);
        }
    }
    
}
void State_Stop()
{
    oled_printf_p6x8str_add_float(0,4,"length",6, DI.Length,4,1);
    oled_printf_int32(96,1,(DI.Length - DI.tempLength),3);
    oled_p6x8str(80, 7, state_name);
}
