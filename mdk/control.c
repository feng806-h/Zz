#include "control.h"
#include "Motor.h"
#include "PID.h"
#include "Init.h"
float motor_lduty=0;
float motor_rduty=0;
//-------------------------------------------------------------------------------------------------------------------
//  函数简介        设计电机引脚，方向，速度
//  参数说明      pwm_channel_enum pin1    gpio_pin_enum pin2    int speed速度设置    uint8 just高电平   uint8 lose低电平
//  返回参数
//  使用示例    speed_set(pwm_channel_enum pin1,gpio_pin_enum pin2,2000,0,1);
//  备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
void speed_set(pwm_channel_enum pin1,gpio_pin_enum pin2,float speed,uint8 just,uint8 lose)
{
    if(speed>0)
    { 
        pwm_set_duty(pin1,(int)(speed));
        gpio_set_level(pin2,just);
    }
    else
    {
        pwm_set_duty(pin1,-(int)(speed));
        gpio_set_level(pin2,lose);
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  函数简介      电机闭环控制
//  参数说明
//  返回参数
//  使用示例  Motor_Control(int speed_L,int speed_R);
//  备注信息
//-------------------------------------------------------------------------------------------------------------------

void Motor_Control(float speed_L,float speed_R)
{
    //motor_l.target_speed= speed_L;
    //motor_r.target_speed= speed_R;
	
	positon_pid_control(&control_cascade.speed_pid1,speed_L,(float)speed_l2);
	 motor_lduty=control_cascade.speed_pid1.out;
	
	positon_pid_control(&control_cascade.speed_pid2,speed_R,(float)speed_r2);
	 motor_rduty=control_cascade.speed_pid2.out;
	//positon_pid_control(&speed_pid,motor_l.target_speed,motor_l.encoder_speed);
	//positon_pid_control(&speed_pid,motor_r.target_speed,motor_r.encoder_speed);
	//motor_r.duty=motor_l.duty;
    /*motor_l.duty=motor_l.duty +PID_Increase(&motor_pid_l,motor_l.encoder_speed,motor_l.target_speed);
    motor_r.duty=motor_r.duty +PID_Increase(&motor_pid_r,motor_r.encoder_speed,motor_r.target_speed);
	
	  motor_l.duty=Limit(-800.0,motor_l.duty,800.0);
	  motor_r.duty=Limit(-800.0,motor_r.duty,800.0);*/
    speed_set(MotorL_pwm1,MotorL_turn1,motor_lduty,1,0);
    speed_set(MotorR_pwm2,MotorR_turn2,motor_rduty,1,0);
}