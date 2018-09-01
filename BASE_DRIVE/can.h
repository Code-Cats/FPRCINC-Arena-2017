#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
typedef struct
{
  s16 real[8];
//	u8  count;	//������ȡƽ��ֵ����
	s16 sum;
	s16 calc;	//	����һƽ���ĽǶ���ֵ
	
	s16 calc_diff;
	s16 calc_last;	//��һ�μ���ĽǶ�ֵ
	s16 turns;	//�������νǶ�ֵ֮��ó���Ȧ�����ֵ
} ReceiveTypeDef;
					    								 							 				    
void CAN1_Init(void);//CAN��ʼ��
void Set_CM_Speed(s16 cm1_iq,s16 cm2_iq,s16 cm3_iq,s16 cm4_iq);		//��������
void Motor_Data_Receive(CanRxMsg *msg);	//�������ݴ�����ܺ���
void Speed_Data_deal(ReceiveTypeDef *Receive,CanRxMsg * msg);
void Position_Data_deal(ReceiveTypeDef *Receive,CanRxMsg * msg);
void Position_To_Turns(ReceiveTypeDef *Receive);	//�ɽǶ�ֵ�õ�Ȧ��ֵ
#endif



extern ReceiveTypeDef CM1_Speed_Feedback;
extern ReceiveTypeDef CM2_Speed_Feedback;
extern ReceiveTypeDef CM3_Speed_Feedback;
extern ReceiveTypeDef CM4_Speed_Feedback;

extern ReceiveTypeDef CM1_Position_Feedback;
extern ReceiveTypeDef CM2_Position_Feedback;
extern ReceiveTypeDef CM3_Position_Feedback;
extern ReceiveTypeDef CM4_Position_Feedback;
