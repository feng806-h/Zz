
#include "PID.h"

//增量式PID参数（速度环）
PID motor_pid_l;
PID motor_pid_r;

//-------------------------------------------------------------------------------------------------------------------
//  函数简介      PID 增量式
//  参数说明      PID结构体  point 目标值    NowData实际值
//  返回参数      float
//  使用示例     PID_Increase(&,0,0);
//  备注信息
//-------------------------------------------------------------------------------------------------------------------
float PID_Increase(PID *PID,float NowData,float Point)
{
    PID->Error=Point-NowData;
    PID->Out_P=(PID->Error-PID->LastError);
    PID->Out_I=PID->Error;

    PID->Out_D=(PID->Error-2*PID->LastError+PID->PrevError);

    PID->PrevError=0.9*PID->LastError+0.1*PID->PrevError;
    PID->LastError=0.9*PID->Error+0.1*PID->LastError;

    PID->LastData=NowData;
    return(PID->Kp*PID->Out_P+PID->Ki*PID->Out_I+PID->Kd*PID->Out_D);
}


void PID_Init(PID* pid, float kp, float ki, float kd, float low_pass)
{
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->LowPass = low_pass;
    pid->Out_P = 0;
    pid->Out_I = 0;
    pid->Out_D = 0;
    pid->PrevError = 0;
    pid->LastError = 0;
    pid->Error = 0;
    pid->LastData = 0;
}