#include "zf_common_headfile.h"
typedef struct PID
{
        float Kp;
        float Ki;
        float Kd;
        float LowPass;
        

        float Out_P;
        float Out_I;
        float Out_D;
       

        float PrevError;
        float LastError;
        float Error;
        float LastData;
     
}PID;

#define PID_CREATE(_kp,_ki,_kd,_low_pass)\
{                                        \
    .Kp=_kp,                             \
    .Ki=_ki,                             \
    .Kd=_kd,                             \
    .LowPass=_low_pass,                  \
    .Out_P=0,                            \
    .Out_I=0,                            \
    .Out_D=0,                            \
}


extern PID motor_pid_l;
extern PID motor_pid_r;


float PID_Increase(PID *PID,float NowData,float Point);
void PID_Init(PID* pid, float kp, float ki, float kd, float low_pass);