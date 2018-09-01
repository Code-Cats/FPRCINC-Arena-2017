#ifndef DATE_DEAL_H
#define DATE_DEAL_H

#include "sys.h"

#define FAR 2
#define NEAR 3



void Infrare_Convert(void);	//红外传感器
void Get_Enemy(void);	//

//attitude

typedef struct
{
	volatile u8 Sign_Bit;	//定义有效位数
	volatile u16 position[12];
	volatile u16 distance[12];	
	volatile u16 Front_distance;
}AttitudeTypeDef;

extern volatile u16  CONVERT_2Y0A02[2][47];
extern volatile u16  CONVERT_2Y0A21[2][47];
extern AttitudeTypeDef Attitude;

#endif
