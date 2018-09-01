#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 


/*下面的方式是通过直接操作库函数方式读取IO*/
#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	//PE3 

#define PC2 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2) //PC2
#define PC3 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3) //PC2
#define PC4 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4) //PC2
#define PC5 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) //PC2

#define PD9 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9) //PC2	//对位置
#define PA5 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) //PC2	//后置光电

//#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //PE2
//#define WK_UP 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0		//ADC1_0


/*下面方式是通过位带操作方式读取IO*/
/*
#define KEY0 		PEin(4)   	//PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 	PAin(0)		//PA0
*/


#define KEY0_PRES 	1
#define KEY1_PRES	2

#define WKUP_PRES   4

void KEY_Init(void);	//IO初始化
	

#endif
