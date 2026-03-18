#include "control.h"
#include "Motor.h"
#include "PID.h"


//-------------------------------------------------------------------------------------------------------------------
//  函数简介        设计电机引脚，方向，速度
//  参数说明      pwm_channel_enum pin1    gpio_pin_enum pin2    int speed速度设置    uint8 just高电平   uint8 lose低电平
//  返回参数
//  使用示例    speed_set(pwm_channel_enum pin1,gpio_pin_enum pin2,2000,0,1);
//  备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
void speed_set(pwm_channel_enum pin1,gpio_pin_enum pin2,int speed,uint8 just,uint8 lose)
{
    if(speed>0)
    {
        pwm_set_duty(pin1,speed);
        gpio_set_level(pin2,just);
    }
    else
    {
        pwm_set_duty(pin1,-speed);
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

void Motor_Control(int speed_L,int speed_R)
{
    motor_l.target_speed= speed_L;
    motor_r.target_speed= speed_R;

    motor_l.duty=motor_l.duty +PID_Increase(&motor_pid_l,(float)motor_l.encoder_speed,(float)motor_l.target_speed);
    motor_r.duty=motor_r.duty +PID_Increase(&motor_pid_r,(float)motor_r.encoder_speed,(float)motor_r.target_speed);

    speed_set(MotorL_pwm1,MotorL_turn1,motor_r.duty,0,1);
    speed_set(MotorR_pwm2,MotorR_turn2,motor_l.duty,1,0);
}