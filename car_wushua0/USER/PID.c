#include "PID.h"
#include "headfile.h"

/************************************************
函数名：LocP_DCalc(PID *sptr,int16 Setpoint,int16 Turepoint)
功  能：位置式PID控制
参  数：PID *sptr,int16 Setpoint,int16 Turepoint
返回值：float a
************************************************/
int16 LocP_DCalc(PID*sptr,int16 Setpoint,int16 Turepoint)
{
    int16 iError,dError;
    int16 output;

    iError=Setpoint-Turepoint;  //偏差
    sptr->SumError+=iError;            //积分(采样时间很短时，用一阶差分代替一阶微分，用累加代替积分)
    dError=(int16)(iError-(sptr->LastError));     //微分
    sptr->LastError=iError;
    if(sptr->SumError>200) sptr->SumError=200;
    if(sptr->SumError<-200) sptr->SumError=-200;
    output=(int)(sptr->Kp*iError  //比例项
          +(sptr->Ki*sptr->SumError)//积分项
          +sptr->Kd*dError);        //微分项
    return(output);
}
/************************************************
函数名：LocP_DCalc(PID *sptr,int16 Setpoint,int16 Turepoint)
功  能：位置式PID控制
参  数：PID *sptr,int16 Setpoint,int16 Turepoint
返回值：float a
************************************************/
float Balance_nei_PID(PID*sptr,float Setpoint,float Turepoint)
{
    float dError,output,Error;

    Error=Setpoint-Turepoint;         //偏差
    sptr->SumError+=Error;            //积分(采样时间很短时,用一阶差分代替一阶微分,用累加代替积分)
    dError=Error-(sptr->LastError);   //微分

    sptr->LastError=Error;

    if(sptr->SumError>+1000) sptr->SumError=+1000;
    if(sptr->SumError<-1000) sptr->SumError=-1000;
    output=(sptr->Kp*Error  //比例项
          +sptr->Ki*sptr->SumError//积分项
          +sptr->Kd*dError);        //微分项
    return(output);
}
float Balance_wai_PID(PID*sptr,float Setpoint,float Turepoint)
{
    float iError,dError;
    float output;

    iError=Setpoint-Turepoint;  //偏差
    sptr->SumError+=iError;            //积分(采样时间很短时，用一阶差分代替一阶微分，用累加代替积分)
    dError=(int16)(iError-(sptr->LastError));     //微分
    sptr->LastError=iError;
    if(sptr->SumError>40) sptr->SumError=40;
    if(sptr->SumError<-40) sptr->SumError=-40;

    output=(sptr->Kp*iError  //比例项
          +sptr->Ki*sptr->SumError//积分项
          +sptr->Kd*dError);        //微分项
    return(output);
}
float Balance_Sudu_PID(PID*sptr,float Setpoint,float Turepoint)
{
    float iError,dError;
    float output;

    sptr->LastError=Setpoint-Turepoint;  //偏差
    iError = iError*0.7;
    iError = iError+sptr->LastError*0.3;
    sptr->SumError+=iError;            //积分(采样时间很短时，用一阶差分代替一阶微分，用累加代替积分)
    dError=(int16)(iError-(sptr->LastError));     //微分
    if(sptr->SumError>100) sptr->SumError=100;
    if(sptr->SumError<-100) sptr->SumError=-100;

    output=(sptr->Kp*iError  //比例项
          +sptr->Ki*sptr->SumError//积分项
          +sptr->Kd*dError);        //微分项
    return(output);
}
/************************************************
函数名：IncPIDCalc(PID *sptr,int16 Setpoint,int16 Turepoint)
功  能：增量式PID控制
参  数：PID *sptr,int16 Setpoint,int16 Turepoint
返回值：int32 iIncpid
************************************************/
int16 IncPIDCalc(PID *sptr,int16 Setpoint,int16 Turepoint)
{
    int16 iError,iIncpid,dError;
    //当前误差
    iError=Setpoint-Turepoint;      //偏差
    sptr->SumError+=iError;         //积分(采样时间很短时,用一阶差分代替一阶微分，用累加代替积分)
    dError=(int16)(iError-(sptr->LastError));//微分

    //增量计算
    iIncpid=(int)(sptr->Kp*(iError-sptr->LastError)
            +sptr->Ki*iError
            +sptr->Kd*(iError-2*sptr->LastError+sptr->LLastError));
    //储存误差，用于下次计算
    sptr->LLastError=sptr->LastError;
    sptr->LastError=iError;

    return(iIncpid);
}
