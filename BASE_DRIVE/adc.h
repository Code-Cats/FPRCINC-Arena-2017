#ifndef ADC_H
#define ADC_H
#include "sys.h"

void Adc_Init(void); 				//ADC通道初始化
u16  Get_Adc(u8 ch); 				//获得某个通道值 

#endif
