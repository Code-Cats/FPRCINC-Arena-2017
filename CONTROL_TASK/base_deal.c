#include "base_deal.h"
#include "adc.h"
#include "Mydefine.h"
#include "pwm.h"
#include "key.h"

/************************adc*******************************/
SensorTypeDef Sensor={0};

u32 Sensor_count=0;

void InfraredSensor_Scanf(void)	//���ºŷ���
{
	Sensor_count++;
	for(Sensor.Infrare.number=0;Sensor.Infrare.number<16;Sensor.Infrare.number++)
	{
		if(Sensor.Infrare.number<12)
		{
			if(Sensor.Infrare.number<6)
			{
				Sensor.Infrare.rawdate[Sensor.Infrare.number]=Get_Adc(Sensor.Infrare.number); //���0��Ӧͨ��0
			}
			else if(Sensor.Infrare.number>7)
			{
				Sensor.Infrare.rawdate[Sensor.Infrare.number-2]=Get_Adc(Sensor.Infrare.number); 	//���6��Ӧͨ��8
			}
		}
		else
		{
			Sensor.Gray.rawdate[Sensor.Infrare.number-12]=Get_Adc(Sensor.Infrare.number);	//�Ҷȴ�����0:12��1:13��2:14��3:15
		}
	}
	Sensor.Infrared_digital[0]=PC2;
	Sensor.Infrared_digital[1]=PC3;
	Sensor.Infrared_digital[2]=PC4;
	Sensor.Infrared_digital[3]=PC5;
	
	Sensor.Infrared_digital[4]=PD9;
	
	Sensor.Infrared_digital[5]=PA5;	//���ù��;
}

/********************************************************/

/*******************pwm.c********************************/


void Servo_PWM_Init(void)
{
	TIM4_PWM_Init(ESC_CYCLE-1,84-1);	//84Mʱ�� 1000�������1ms���һ��
  Steer_Set(STEER_INIT);
}

void Steer_Set(u16 set1)//PB6
{
	TIM_SetCompare1(TIM4,ESC_CYCLE-set1);
}
/*************************************************************/

