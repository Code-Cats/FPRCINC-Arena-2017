#ifndef BASE_DEAL_H
#define BASE_DEAL_H
#include "sys.h"

void InfraredSensor_Scanf(void);

void Servo_PWM_Init(void);
void Steer_Set(u16 set1);



typedef struct
{
	struct
	{
		volatile	u16 rawdate[10];
		volatile	u16 distance[10][2][2];	//厘米为单位	//第一个值代表传感器编号，第二个值代表是近距还是远距，第三个值代表数值区间
		volatile u8 number;	//编号
	}Infrare;
	struct
	{
		volatile	u16 rawdate[4];
		volatile	u16 distance[4];	//厘米为单位
		u8 number;	//编号
	}Gray;
	volatile u8 Infrared_digital[6];
}SensorTypeDef;



extern SensorTypeDef Sensor;

#endif

