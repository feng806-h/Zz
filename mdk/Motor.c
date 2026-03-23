#include "Motor.h"

//motor motor_l={1};
//motor motor_r={3};
void Motor_Init(void)
{
    gpio_init(MotorL_turn1, GPO, 1, GPO_PUSH_PULL);
    pwm_init(MotorL_pwm1,5000,0);
    gpio_init(MotorR_turn2, GPO, 1, GPO_PUSH_PULL);
    pwm_init(MotorR_pwm2,5000,0);
}

void MotorL_SetSpeed(int pwm)
{	
    if(pwm>=0)
    {
   gpio_set_level(MotorL_turn1,1);
   pwm_set_duty(MotorL_pwm1,pwm);
   gpio_set_level(MotorR_turn2,1);
   pwm_set_duty(MotorR_pwm2,pwm);
    }
    else
    {
     gpio_set_level(MotorL_turn1,0);
     pwm_set_duty(MotorL_pwm1,-pwm);
     gpio_set_level(MotorR_turn2,0);
     pwm_set_duty(MotorR_pwm2,-pwm);
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  函数简介     编码器初始化
//  参数说明
//  返回参数
//  使用示例    Encoder_Init();
//  备注信息
//-------------------------------------------------------------------------------------------------------------------
void Encoder_Init(void)
{
    //左编码器
    encoder_dir_init(TIM0_ENCOEDER,IO_P24,TIM0_ENCOEDER_P34);

    //右编码器
   encoder_dir_init(TIM3_ENCOEDER,IO_P26,TIM3_ENCOEDER_P04);
}

//-------------------------------------------------------------------------------------------------------------------
//  函数简介     编码器数据获取
//  参数说明
//  返回参数
//  使用示例   Encoder_data_get();
//  备注信息
//-------------------------------------------------------------------------------------------------------------------
//void Encoder_data_get(void)
//{.
//motor_l.encoder_raw=encoder_get_count(TIM0_ENCOEDER);
//motor_l.encoder_speed=motor_l.encoder_speed*0.2+motor_l.encoder_raw*0.8;  //左编码器速度
//motor_l.total_encoder+=motor_l.encoder_raw;                             //记录路程
//encoder_clear_count(TIM0_ENCOEDER);

//motor_r.encoder_raw=encoder_get_count(TIM3_ENCOEDER);
//motor_r.encoder_speed=motor_r.encoder_speed*0.2+motor_r.encoder_raw*0.8;  //右编码器速度
//motor_r.total_encoder+=motor_r.encoder_raw;
//encoder_clear_count(TIM3_ENCOEDER);
//}

