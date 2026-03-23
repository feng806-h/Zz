#include "zf_common_headfile.h"


//typedef struct 
//{
//        float target_speed;
//        float duty;
//        float encoder_speed;   //记录速度，低空滤波

//        float encoder_raw;     //记录中断时间内的脉冲信号
//        float total_encoder;      //累加值，记录路程
//}motor;



#define MotorL_pwm1 PWMA_CH2P_P62
#define MotorR_pwm2 PWMA_CH4P_P66
#define MotorL_turn1 IO_P60
#define MotorR_turn2 IO_P64

//extern  motor motor_l;
//extern  motor motor_r;




void Motor_Init(void);
void MotorL_SetSpeed(int pwm);
void Encoder_Init(void);
void Encoder_data_get(void);