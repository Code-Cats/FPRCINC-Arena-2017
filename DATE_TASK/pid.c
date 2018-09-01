#include "pid.h"

PidTypeDef CM1_Speed_Pid={0};
PidTypeDef CM2_Speed_Pid={0};





void PID_Init(PidTypeDef * pid,double kp,double ki,double kd,double dead_band,double max_error,double intergral_limit,double max_out)
{
	pid->Kp=kp;
	pid->Ki=ki;
	pid->Kd=kd;
	pid->max_out=max_out;
	pid->dead_band=dead_band;
//	pid->intergral_dead_band=i_deadband;
	pid->max_error=max_error;
	//PID输出值
	pid->output=0;
	//误差
	
	//积分运算相关
	pid->intergral_limit=intergral_limit;	//积分饱和上限
	pid->I_Sum=0;
	
	pid->Error[LAST]=0;
	pid->Error[NOW]=0;
	pid->Error_Diff[LAST]=0;
	pid->Error_Diff[NOW]=0;
}




void PID_Speed_Calc(PidTypeDef * pid,s16 Speed_Expectation,s16 Speed_Feedback)	//速度环PID
{
	pid->Error[NOW]=Speed_Expectation-Speed_Feedback;

	if(pid->Error[NOW]>pid->max_error)	//限制最大输入，实现爬坡效果
	{
		pid->Error[NOW]=pid->max_error;
	}
	else if(pid->Error[NOW]<-(pid->max_error))
	{
		pid->Error[NOW]=-(pid->max_error);
	}
	else if(MyAbs(pid->Error[NOW])<pid->dead_band)	//死区
	{
		pid->Error[NOW]=0;
	}
	
	pid->Error_Diff[NOW]=pid->Error[NOW]-pid->Error[LAST]-pid->Error[LAST]+pid->Error[LAST_LAST];
	
	pid->I_Sum=pid->I_Sum*0.99f+pid->Ki*pid->Error[NOW];
	if(pid->I_Sum>pid->intergral_limit)
	{
		pid->I_Sum=pid->intergral_limit;
	}
	else if(pid->I_Sum<-pid->intergral_limit)
	{
		pid->I_Sum=-pid->intergral_limit;
	}
	
	
	pid->output=pid->Kp*pid->Error[NOW]-pid->Kd*pid->Error_Diff[NOW]+pid->I_Sum;	//	位置式PID计算
	
	pid->Error[LAST_LAST]=pid->Error[LAST];
	pid->Error[LAST]=pid->Error[NOW];
	//pid->Error_Diff[LAST]=pid->Error_Diff[NOW];
	
	if(pid->output>pid->max_out)
	{
		pid->output=pid->max_out;
	}
	else if(pid->output<-pid->max_out)
	{
		pid->output=-pid->max_out;
	}
	
}


float MyAbs(float num)
{
	if(num>=0)
		return num;
	else 
		return -num;	
}







