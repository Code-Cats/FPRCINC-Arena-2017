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
		volatile	u16 distance[10][2][2];	//����Ϊ��λ	//��һ��ֵ����������ţ��ڶ���ֵ�����ǽ��໹��Զ�࣬������ֵ������ֵ����
		volatile u8 number;	//���
	}Infrare;
	struct
	{
		volatile	u16 rawdate[4];
		volatile	u16 distance[4];	//����Ϊ��λ
		u8 number;	//���
	}Gray;
	volatile u8 Infrared_digital[6];
}SensorTypeDef;



extern SensorTypeDef Sensor;

#endif

