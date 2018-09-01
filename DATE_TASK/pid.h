#ifndef PID_H
#define PID_H

#include "sys.h"

#define NOW 0
#define LAST 1
#define LAST_LAST 2


typedef struct
{
    //PID 三参数
    double Kp;
    double Ki;
    double Kd;
		//最大输出 死区
		double max_out;  //最大输出
		double dead_band;//PID偏差死区
	  double intergral_limit;	//积分上限
		double max_error;//最大输入
    //PID输出值
    double output;
//		double output_compensation;
    //误差
    double Error[3];//0最新 1上一次 2上上次
	  double Error_Diff[2];//0最新 1上一次
		double I_Sum;
	struct
	{
		double send;
	}Cali_Limit;
} PidTypeDef;


float MyAbs(float num);

void PID_Init(PidTypeDef * pid,double kp,double ki,double kd,double dead_band,double max_error,double intergral_limit,double max_out);
void PID_Speed_Calc(PidTypeDef * pid,s16 Speed_Expectation,s16 Speed_Feedback);	//速度环PID

extern PidTypeDef CM1_Speed_Pid;
extern PidTypeDef CM2_Speed_Pid;


#endif
