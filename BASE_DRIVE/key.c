#include "key.h"

//������ʼ������
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4; //KEY2 KEY3��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; //�ĸ��Ҷȶ�Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //�ĸ��Ҷȶ�Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOED9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //�ĸ��Ҷȶ�Ӧ����	//��ԭ����5�ź��⻻�ɺ��ù��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOED9
	
	 
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0			////����ADC����
 
} 
