#include "zf_common_headfile.h"


#define  pid_limit 200

extern float motor_lduty;
extern float motor_rduty;
void speed_set(pwm_channel_enum pin1,gpio_pin_enum pin2,float speed,uint8 just,uint8 lose);
void Motor_Control(float speed_L,float speed_R);