#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "can.h"
#include "timer.h"
#include "base_deal.h"
#include "date_deal.h"
#include "adc.h"
#include "pid.h"
#include "Mydefine.h"
#include "control.h"



int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
//	uart_init(115200);		//初始化串口波特率为115200
	SetWorkState(PREPARE_STATE);
	PID_Init(&CM1_Speed_Pid,AM_SPEEDPID_P,AM_SPEEDPID_I,AM_SPEEDPID_D,AM_SPEEDPID_DEAD,AM_SPEEDPID_MER,AM_SPEEDPID_I_MAX,AM_SPEEDPID_MAXOUT);
	PID_Init(&CM2_Speed_Pid,AM_SPEEDPID_P,AM_SPEEDPID_I,AM_SPEEDPID_D,AM_SPEEDPID_DEAD,AM_SPEEDPID_MER,AM_SPEEDPID_I_MAX,AM_SPEEDPID_MAXOUT);
	
	Servo_PWM_Init();
	
  LED_Init();
	KEY_Init();
	CAN1_Init();
	TIM3_Int_Init(20-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数20次为2ms  
	Adc_Init();
	
	

	while(1)
	{
		
	InfraredSensor_Scanf();
	LED2=0;//亮
	LED3=0;
	}
}





