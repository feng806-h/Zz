/*********************************************************************************************************************
* STC32G Opensourec Library 即（STC32G 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是STC 开源库的一部分
*
* STC32G 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK FOR C251
* 适用平台          STC32G
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者           备注
* 2024-08-01        大W            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#include "Init.h"
#include "PID.h"
#include "control.h"

void main()
{
    clock_init(SYSTEM_CLOCK_30M);
	debug_init();
	init();   //总体初始化
	 //Encoder_Init();  
//	PID_Init(&motor_pid_l, 0, -0.2, 0, 1);
//  PID_Init(&motor_pid_r, 0, -0.2, 0, 1);
//	
	tim1_irq_handler = pit_hanlder1;	
	pit_ms_init(TIM1_PIT, 5);

//	tim2_irq_handler = pit_hanlder2;	
//	pit_ms_init(TIM2_PIT, 1);
	// 此处编写用户代码 例如外设初始化代码等
	
    while(1)
    {
//		printf("%d,%d,%d,%d\n",motor_l.encoder_raw, motor_r.encoder_raw,motor_l.duty, motor_r.duty);
				printf("%f,%f,%d,%d,%d\n",motor_lduty,motor_rduty,speed_l2, speed_r2,150);
		system_delay_ms(10);
//	MotorL_SetSpeed(1000);
	   
			  // 此处编写需要循环执行的代码
		
    }
}
