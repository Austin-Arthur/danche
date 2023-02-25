/*
 * fuse.h
 *
 *  Created on: 2022年5月19日
 *      Author: 11609
 */

#ifndef USER_FUSE_H_
#define USER_FUSE_H_



#include "headfile.h"
#include "common.h"

// 任务结构
typedef struct
{
      uint8 Run;                 // 程序运行标记：0-不运行，1运行
      uint8 Timer;              // 计时器，用于运行起来变化的量
      uint8 ItvTime;              // 任务运行间隔时间
      void (*TaskHook)(void);    // 要运行的任务函数
}TASK_COMPONENTS;

// 任务清单
typedef enum _TASK_LIST
{
    task_Balance_endocyclic,
    task_Balance_outcyclic,
    task_Speed_control,
    task_state_machine,
    task_Speed_run,
    task_online,
    //...........
    TASKS_MAX         // 总的可供分配的定时任务数目
}TASK_LIST;

extern float Target_Angle_Y,Tar_Ang_Vel_Y ;

extern uint8 Int_Ok;
extern int16 PWM_Break;
extern int32 PWM_DLL;
extern int16 motor_PWM;
extern float Angle_Zero;
extern int wheel_flag,xzttt,tar_sp;
//函数声明
int16 range_protect(int32 duty, int16 min, int16 max);
void TaskRemarks(void);
void TaskProcess(void);
void Balance_endocyclic();
void Balance_outcyclic();
void Speed_control();
void state_machine();
void Speed_run();
void online();




#endif /* USER_FUSE_H_ */
