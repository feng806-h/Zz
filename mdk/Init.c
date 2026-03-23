#include "Init.h"
#include "PID.h"
int speed_l2=0;
int speed_r2=0;

void init(void)
{
Motor_Init();     //电机初始化
Encoder_Init();   //编码器初始化
imu660rb_init();  //姿态传感器初始化
pit_hanlder1 ();
control_cascade_init();
//control_cascade_init(&speed_pid2);
//pit_hanlder2 ();
}



//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 的中断处理函数 这个函数将在 PIT 对应的定时器中断调用 
// 参数说明     void
// 返回参数     void
// 使用示例     pit_hanlder();
//-------------------------------------------------------------------------------------------------------------------
void pit_hanlder1 (void)
{
speed_l2=speed_l2*0.2+encoder_get_count(TIM0_ENCOEDER)*0.8;
encoder_clear_count(TIM0_ENCOEDER);
	
	
speed_r2=speed_r2*0.2+encoder_get_count(TIM3_ENCOEDER)*0.8;
encoder_clear_count(TIM3_ENCOEDER);
	//Encoder_data_get();
Motor_Control(150.0,150.0);
	//    imu660rb_get_acc();                                                         // 获取 IMU660RB 的加速度测量数值
//    imu660rb_get_gyro();                                                        // 获取 IMU660RB 的角速度测量数值
}

//void pit_hanlder2 (void)
//{
//Motor_Control(50,50);
//}

float Limit(float a,float b,float c)
{
   if((b>=a)&&(b<=c))
   {
       return b;
   }
   else if(b<a)
   {
       return a;
   }
   else if(b>c)
   {
       return c;
   }
   return 0;
}