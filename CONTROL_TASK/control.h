#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"


void Control_Task(void);
void Remove_Task(void);

void Start(void);//��������
void Ascend_Island(void);	//�ǵ�����
void In_Island(void);	//����״̬
void Island_Check(void);	//	���ϵ��¼��
void Island_Position(void);	//����ִ�ж�λ�ú���


extern u8 Res;	//	usart1
extern u8 Ascend_start;	//�ǵ��Ƿ�ʼ
extern u32 Ascend_time_record;
extern u8 Ascend_Can;


/***********************--����״̬--**********************/
typedef enum
{
		
    PREPARE_STATE,     		//׼��״̬
    NORMAL_STATE,			//����״̬
		CALI_STATE,    			//����У׼״̬
    IN_ISLAND,        	//����״̬
		OUT_ISLAND,				//����״̬
    ISLANDING,					//�ǵ���
}WorkState_e;

extern WorkState_e workState;
void SetWorkState(WorkState_e state);
WorkState_e GetWorkState(void);

#endif
