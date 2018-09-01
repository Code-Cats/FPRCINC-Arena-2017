#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F407VET6开发板
//定时器 驱动代码	   								  
////////////////////////////////////////////////////////////////////////////////// 	

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM5_CH1_Cap_Init(u32 arr,u16 psc);
#endif
extern volatile u32 time_2ms_count;
extern u8  TIM5CH2_CAPTURE_STA;
extern u32  TIM5CH2_CAPTURE_VAL;
