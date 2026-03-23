
#include "PID.h"

//增量式PID参数（速度环）
//PID motor_pid_l;
//PID motor_pid_r;
//pid_cycle_struct v_pid1;
//pid_cycle_struct v_pid2;

control_cascade_parameter control_cascade = {{0}};

//-------------------------------------
//------------------------------------------------------------------------------
//  函数简介      PID 初始化
//  参数说明      PID结构体  kp ki kd
//  返回参数      float
//  使用示例     PID_Increase(&,0,0,0);
//  备注信息
//-------------------------------------------------------------------------------------------------------------------

//void PID_Init(PID* pid, float kp, float ki, float kd, float low_pass)
//{
//    pid->Kp = kp;
//    pid->Ki = ki;
//    pid->Kd = kd;
//    pid->LowPass = low_pass;
//    pid->Out_P = 0;
//    pid->Out_I = 0;
//    pid->Out_D = 0;
//    pid->PrevError = 0;
//    pid->LastError = 0;
//    pid->Error = 0;
//    pid->LastData = 0;
//}


//-------------------------------------------------------------------------------------------------------------------
//  函数简介      PID 增量式
//  参数说明      PID结构体  point 目标值    NowData实际值
//  返回参数      float
//  使用示例     PID_Increase(&,0,0);
//  备注信息
//-------------------------------------------------------------------------------------------------------------------
//float PID_Increase(PID *PID,float NowData,float Point)
//{
//    PID->Error=Point-NowData;
//    PID->Out_P=(PID->Error-PID->LastError);
//    PID->Out_I=PID->Error;

//    PID->Out_D=(PID->Error-2*PID->LastError+PID->PrevError);

//    PID->PrevError=0.9*PID->LastError+0.1*PID->PrevError;
//    PID->LastError=0.9*PID->Error+0.1*PID->LastError;

//    PID->LastData=NowData;
//    return(PID->Kp*PID->Out_P+PID->Ki*PID->Out_I+PID->Kd*PID->Out_D);
//}
//-----------------------------------------------------------------------------------------
// 函数简介     PID闭环计算（位置式）
// 参数说明     pid_cycle                   PID参数结构体
// 参数说明     target                      目标值
// 参数说明     actual                      实际值
// 返回参数     void
// 使用示例     positon_pid_control(&direction_cycle,atmizh,yaw);
// 备注信息
//------------------------------------------------------------------------------------------
void positon_pid_control(pid_cycle_struct* pid_cycle,float target,float actual)
{
    float  proportion_value    = 0;                 // 比例量
    float  differential_value  = 0;                 // 微分量

    proportion_value = target - actual;             // 比例量 = 目标值 - 实际值

    /*积分分离
         if(fabsf(pid_cycle->intergal)< 阈值) {
              C=1;
         }
         else{
              C=0;
         }
         pid_cycle->out = (...... + C * pid_cycle->ki * pid_cycle->intergal );
    */

    /*变速积分
        C=1/(k*fabsf(proportion_value)+1);
        pid_cycle->intergal += C * proportion_value;
    */

    //变速积分也可以加积分限幅

    /*微分先行
         out_last = out;
         differential_value = out - out_last;
         pid_cycle->out = (...... + (-1) * pid_cycle->kd * differential_value );
    */
    if(pid_cycle->ki != 0){
    pid_cycle->intergal += proportion_value;                                   // 积分量

    pid_cycle->intergal = func_limit_ab(pid_cycle->intergal,-pid_cycle->intergal_max,pid_cycle->intergal_max);// 积分限幅
    }

    if(pid_cycle->kd != 0){
    differential_value = proportion_value - pid_cycle->last_error;             // 微分量 = 比例量 - 上次比例量
    }

    pid_cycle->out = (pid_cycle->kp * proportion_value + pid_cycle->ki * pid_cycle->intergal + pid_cycle->kd * differential_value);

    pid_cycle->out = func_limit_ab(pid_cycle->out,-pid_cycle->out_max,pid_cycle->out_max);// pid输出限幅

    /*输出偏移
         if(pid_cycle->out > 0){
             pid_cycle->out += 偏移值
         }
         else if(pid_cycle->out < 0){
             pid_cycle->out -= 偏移值
         }
         else{
             pid_cycle->out = 0;
         }
    */
    pid_cycle->last_error = proportion_value;                                             //保留上次比例量
}
//-----------------------------------------------------------------------------------------
// 函数简介     PID闭环计算（增量式）
// 参数说明     pid_cycle                   PID参数结构体
// 参数说明     target                      目标值
// 参数说明     actual                      实际值
// 返回参数     void
// 使用示例     Incremental_pid_control(&speed_cycle,target_speed,encoder);
// 备注信息     目前没有对总输出限幅
//------------------------------------------------------------------------------------------
void Incremental_pid_control(pid_cycle_struct* pid_cycle,float target,float actual)
{
    float  proportion_value    = 0;                 //比例量
    float  error_value      = 0;                    //误差
    float  differential_value  = 0;                 //微分量

    error_value   = target - actual;                                        //误差 = 目标值 - 实际值

    if(pid_cycle->kp != 0){
        proportion_value = error_value - pid_cycle->last_error;             //比例量 = 误差 - 上次误差
    }

    if(pid_cycle->kd != 0){
        //微分量 = 误差 + 上上次误差 - 2上次误差
        differential_value = error_value + pid_cycle->before_last_error - 2 * pid_cycle->last_error;
    }
    //pid增量
    pid_cycle->out_variation = (pid_cycle->kp * proportion_value + pid_cycle->ki * pid_cycle->intergal + pid_cycle->kd * differential_value);
    //pid增量限幅
    pid_cycle->out_variation = func_limit_ab(pid_cycle->out_variation,-pid_cycle->out_variation_max,pid_cycle->out_variation_max);

    pid_cycle->out += pid_cycle->out_variation;

    pid_cycle->before_last_error =pid_cycle->last_error;            //保留上上次误差

    pid_cycle->last_error = error_value;                            //保留上次误差
}
//------------------------------------------------------------------------------------------
// 函数简介     车子的所有pid参数函数
// 参数说明     无
// 返回参数     void
// 使用示例
// 备注信息     初始化调用一次
//------------------------------------------------------------------------------------------
void control_cascade_init (void)
{
	control_cascade.speed_pid1.kp=10.72;
	control_cascade.speed_pid1.ki=0.073;
	control_cascade.speed_pid1.intergal_max=10000;
	control_cascade.speed_pid1.out_max=2000;
	
	control_cascade.speed_pid2.kp=10.75;
	control_cascade.speed_pid2.ki=0.09;
	control_cascade.speed_pid2.intergal_max=10000;
	control_cascade.speed_pid2.out_max=2000;
	/*pid->last_error=0;
	pid->before_last_error=0;
	pid->intergal=0;
	pid->intergal_max=10000;
	pid->out=0;
	
	pid->out_variation=0;
	pid->out_variation_max=0;
	pid->ki=0.2;
	pid->kd=0;
	pid->kp=3;
	pid->out_max=2000;*/
}