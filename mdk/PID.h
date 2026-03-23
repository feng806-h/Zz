#include "zf_common_headfile.h"
typedef struct
{
float last_error;
float before_last_error;
float intergal;
float intergal_max;
float out;
float out_max;
float out_variation;
float out_variation_max;
float kp;
float ki;
float kd;
}pid_cycle_struct;

typedef struct{
        pid_cycle_struct speed_pid1;
        pid_cycle_struct speed_pid2;
}control_cascade_parameter;



extern control_cascade_parameter control_cascade;

void positon_pid_control(pid_cycle_struct* pid_cycle,float target,float actual);
void Incremental_pid_control(pid_cycle_struct* pid_cycle,float target,float actual);
void control_cascade_init (void);