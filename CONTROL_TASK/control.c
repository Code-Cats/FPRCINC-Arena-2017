#include "control.h"
#include "pid.h"
#include "can.h"
#include "date_deal.h"
#include "base_deal.h"
#include "timer.h"


s16 Vx=0;
s16 Vw=0;

s16 CM1_Speed=0;
s16 CM2_Speed=0;


u16 tem=500;

void Control_Task(void)	//2ms
{
	//	Infrare_Convert();	//main.c
	
	Infrare_Convert();
	Attitude.Sign_Bit=0;	//清零标志位
	Get_Enemy();
	//////////////////////////////////////////////
	//////////////////////////////////////////////
	
	if(GetWorkState()==OUT_ISLAND)	//在岛下执行什么任务
	{
		if(Ascend_Can==0)
		{
		Ascend_start=0;	//清空登岛执行标志位
		Island_Position();
		}
		else if(Ascend_Can==1)
		{
		Ascend_Island();	//待调教上岛后滑行距离
		}
	}
	else if(GetWorkState()==IN_ISLAND)//在岛上执行什么任务
	{
		Island_Check();
			In_Island();
	}

	if(GetWorkState()==PREPARE_STATE)	//准备状态下不工作
	{
		Start();
	}
	else
	{
	Steer_Set(tem);
	
	Remove_Task();
	}
}


u16 Infrared_digital_Last=0;
void Start(void)//启动函数	//记录:
{
	if(Sensor.Infrared_digital[1]==0&&Infrared_digital_Last==1)
	{
		SetWorkState(OUT_ISLAND);
	}
	Infrared_digital_Last=Sensor.Infrared_digital[1];
}

//思路初始状态下
//每次control开始检测是否为台下
//若为台上，则执行IN_ISLAND
//若为台下，对位置标志位清零执行对位置操作
#define ISLAND_CHECK 5
void Island_Check(void)	//	岛上岛下检测
{
	if(Attitude.Sign_Bit>ISLAND_CHECK)
	{
		SetWorkState(OUT_ISLAND);
		Ascend_Can=0;
	}
}



u8 Ascend_start=0;	//登岛是否开始
u32 Ascend_time_record=0;
void Ascend_Island(void)	//登岛函数
{
	if(Ascend_start==0)
	{
		Vx=-3000;
		tem=2000;
		Ascend_time_record=time_2ms_count;
		Ascend_start=1;
	}
	if((Ascend_time_record+1000)==time_2ms_count)
	{
		Vx=0;
		tem=500;
	}
	else if((Ascend_time_record+1500)==time_2ms_count)
	{
		Vx=-6000;
	}
	else if((Ascend_time_record+1900)==time_2ms_count)
	{
		tem=750;
	}
	else if((Ascend_time_record+2300)==time_2ms_count)
	{
		SetWorkState(IN_ISLAND);
		Vx=0;
	}
}


//   前
//  0   1

//  3   2
#define Edge_Speedx 10000
#define Edge_Speedw 4200
#define FAR_SPEEDx 8500
#define NEAR_SPEEDx 13000
#define FAR_SPEEDw 3500
#define NEAR_SPEEDw 6000
#define LOCK_TIME 200	//锁的时间500=1s
u8 Enemy_Check_Lock=0;
u32 Lock_Time_Record=0;
void In_Island(void)	//岛上状态
{
	if(Sensor.Infrared_digital[0]==1)	//光电传感器出去时为1		//锁位置
	{
		Vx=-Edge_Speedx;
		Vw=-Edge_Speedw;
		Enemy_Check_Lock=1;
		Lock_Time_Record=time_2ms_count;
	}
	else if(Sensor.Infrared_digital[1]==1)
	{
		Vx=-Edge_Speedx;
		Vw=Edge_Speedw;
		Enemy_Check_Lock=1;
		Lock_Time_Record=time_2ms_count;
	}
	else if(Sensor.Infrared_digital[2]==1)
	{
		Vx=Edge_Speedx;
		Vw=Edge_Speedw;
		Enemy_Check_Lock=1;
		Lock_Time_Record=time_2ms_count;
	}
	else if(Sensor.Infrared_digital[3]==1)
	{
		Vx=Edge_Speedx;
		Vw=-Edge_Speedw;
		Enemy_Check_Lock=1;
		Lock_Time_Record=time_2ms_count;
	}
	
	
	if(Enemy_Check_Lock!=1)	//未在边缘时的检测程序
	{
		if(Attitude.position[0]==10||Attitude.position[0]==9||Attitude.position[1]==9||Attitude.position[2]==9||Attitude.position[3]==9)	//前方
		{	//直行前进
			if(Attitude.distance[0]==FAR)
			{
				Vx=FAR_SPEEDx;
				Vw=0;
			}
			else if(Attitude.distance[0]==NEAR)
			{
				Vx=NEAR_SPEEDx;
				Vw=0;
			}
		}	//下面的是靠近时光电为
		else  if(Sensor.Infrared_digital[5]==1||Attitude.position[0]==4||Attitude.position[0]==5||Attitude.position[1]==4||Attitude.position[1]==5||Attitude.position[2]==4||Attitude.position[2]==5)
		{	//直行后退
			if(Attitude.distance[0]==NEAR||Attitude.distance[1]==NEAR||Attitude.distance[2]==NEAR)
			{
				Vx=-NEAR_SPEEDx;
				Vw=0;
			}
			else
			{
				Vx=-FAR_SPEEDx;
				Vw=0;
			}
		}	
		else if(Attitude.position[0]==1||Attitude.position[0]==2||Attitude.position[1]==1||Attitude.position[1]==2||Attitude.position[2]==1||Attitude.position[2]==2)
		{//前右转	//这里加不加Vx是表现攻击性或者撤退性
			if(Attitude.distance[0]==NEAR||Attitude.distance[1]==NEAR||Attitude.distance[2]==NEAR)
			{
				Vw=NEAR_SPEEDw;
				
				Vx=FAR_SPEEDx;
			}
			else
			{
				Vw=FAR_SPEEDw;
				
				Vx=FAR_SPEEDx;
			}
		}
		else if(Attitude.position[0]==3||Attitude.position[1]==3||Attitude.position[2]==3)
		{	//后右转
			if(Attitude.distance[0]==NEAR||Attitude.distance[1]==NEAR||Attitude.distance[2]==NEAR)
			{
				Vw=-NEAR_SPEEDw;
				
				Vx=-FAR_SPEEDx;
			}
			else
			{
				Vw=-FAR_SPEEDw;
				
				Vx=-FAR_SPEEDx;
			}
		}
		else if(Attitude.position[0]==6||Attitude.position[1]==6||Attitude.position[2]==6)
		{	//后左转
			if(Attitude.distance[0]==NEAR||Attitude.distance[1]==NEAR||Attitude.distance[2]==NEAR)
			{
				Vw=NEAR_SPEEDw;
				
				Vx=-FAR_SPEEDx;
			}
			else
			{
				Vw=FAR_SPEEDw;
				
				Vx=-FAR_SPEEDx;
			}
		}
		else if(Attitude.position[0]==7||Attitude.position[0]==8||Attitude.position[1]==7||Attitude.position[1]==8||Attitude.position[2]==7||Attitude.position[2]==8)
		{	//前左转
			if(Attitude.distance[0]==NEAR||Attitude.distance[1]==NEAR||Attitude.distance[2]==NEAR)
			{
				Vw=-NEAR_SPEEDw;
				
				Vx=FAR_SPEEDx;
			}
			else
			{
				Vw=-FAR_SPEEDw;
				
				Vx=FAR_SPEEDx;
			}
		}
		//锁括号结束
	}
	
	
	if(Enemy_Check_Lock==1)
	{
		if(Lock_Time_Record+LOCK_TIME<time_2ms_count)
		{
			Enemy_Check_Lock=0;
		}
	}
	
	
}










u8 Ascend_Can=1;	//初始化为1，立刻登岛
void Island_Position(void)	//岛下执行对位置函数
{
	if(Ascend_Can==0)
	{
		Vx=0;
		Vw=1500;
		if((MyAbs(Sensor.Infrare.distance[1][1][1]-Sensor.Infrare.distance[8][1][1])<2)&&Sensor.Infrared_digital[4]==0)
		{
			Ascend_Can=1;
			Vw=0;
		}
	}
}


//位置识别函数在date_deal













void Remove_Task(void)	//2ms进一次中断
{
	CM1_Speed=Vw+Vx;	//+x
	CM2_Speed=Vw-Vx;	//-x
	
	PID_Speed_Calc(&CM1_Speed_Pid,CM1_Speed,CM1_Speed_Feedback.calc);
	PID_Speed_Calc(&CM2_Speed_Pid,CM2_Speed,CM2_Speed_Feedback.calc);

	
	Set_CM_Speed((int)CM1_Speed_Pid.output,(int)CM2_Speed_Pid.output,0,0);
}
















//工作状态设置
/***************************************************************************/
WorkState_e workState = PREPARE_STATE;

void SetWorkState(WorkState_e state)
{
    workState = state;
}

WorkState_e GetWorkState(void)
{
	return workState;
}
/***************************************************************************/








