#include "can.h"



ReceiveTypeDef CM1_Speed_Feedback={0};
ReceiveTypeDef CM2_Speed_Feedback={0};
ReceiveTypeDef CM3_Speed_Feedback={0};
ReceiveTypeDef CM4_Speed_Feedback={0};
ReceiveTypeDef CM1_Position_Feedback={0};
ReceiveTypeDef CM2_Position_Feedback={0};
ReceiveTypeDef CM3_Position_Feedback={0};
ReceiveTypeDef CM4_Position_Feedback={0};


void CAN1_Init(void)
{

  	GPIO_InitTypeDef GPIO_InitStructure; 
	  CAN_InitTypeDef        CAN_InitStructure;
  	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
   	NVIC_InitTypeDef  NVIC_InitStructure;

	    //ʹ�����ʱ��
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	
	
    //��ʼ��GPIO
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��PA11,PA12
	
	  //���Ÿ���ӳ������
	  GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11����ΪCAN1
	  GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12����ΪCAN1
		
	  
  	//CAN��Ԫ����
   	CAN_InitStructure.CAN_TTCM=DISABLE;	//��ʱ�䴥��ͨ��ģʽ   
  	CAN_InitStructure.CAN_ABOM=DISABLE;	//����Զ����߹���	  
  	CAN_InitStructure.CAN_AWUM=DISABLE;//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
  	CAN_InitStructure.CAN_NART=ENABLE;	//��ֹ�����Զ����� 
  	CAN_InitStructure.CAN_RFLM=DISABLE;	//���Ĳ�����,�µĸ��Ǿɵ�  
  	CAN_InitStructure.CAN_TXFP=DISABLE;	//���ȼ��ɱ��ı�ʶ������ 
  	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;	 //ģʽ���� 
  	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1=CAN_BS1_7tq; //Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq //8
  	CAN_InitStructure.CAN_BS2=CAN_BS2_6tq;//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler=3;  //��Ƶϵ��(Fdiv)Ϊbrp+1	
  	CAN_Init(CAN1, &CAN_InitStructure);   // ��ʼ��CAN1 
    
		//���ù�����
 	  CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32λID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
	
		CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0��Ϣ�Һ��ж�����.		  
  	
		NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1//0
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
		
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
    NVIC_Init(&NVIC_InitStructure);
}

CanRxMsg rx_message;
void CAN1_RX0_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
        CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
		    CAN_ClearFlag(CAN1, CAN_FLAG_FF0); 		
		    CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
				Motor_Data_Receive(&rx_message);
    }
}

void CAN1_TX_IRQHandler(void) //CAN TX
{
  if (CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET)    //if transmit mailbox is empty 
  {
	   CAN_ClearITPendingBit(CAN1,CAN_IT_TME);   
  }
}




void Set_CM_Speed(s16 cm1_iq,s16 cm2_iq,s16 cm3_iq,s16 cm4_iq)
{	
  CanTxMsg TxMessage;
  TxMessage.StdId=0x200;	 
  TxMessage.IDE=CAN_Id_Standard;		  
  TxMessage.RTR=CAN_RTR_Data;		  
  TxMessage.DLC=0x08;							
  TxMessage.Data[0] = (uint8_t)(cm1_iq >> 8);
  TxMessage.Data[1] = (uint8_t)cm1_iq;
  TxMessage.Data[2] = (uint8_t)(cm2_iq >> 8);
  TxMessage.Data[3] = (uint8_t)cm2_iq;   
	TxMessage.Data[4] = (uint8_t)(cm3_iq >> 8);
  TxMessage.Data[5] = (uint8_t)cm3_iq;
  TxMessage.Data[6] = (uint8_t)(cm4_iq >> 8);
  TxMessage.Data[7] = (uint8_t)cm4_iq;	
  CAN_Transmit(CAN1, &TxMessage);   	
}




void Motor_Data_Receive(CanRxMsg *msg)
{		
	CAN_Receive(CAN1, CAN_FIFO0, msg);//��ȡ����	
	switch(msg->StdId)
	{
		case 0x201:
		{
			Speed_Data_deal(&CM1_Speed_Feedback,msg);
			Position_Data_deal(&CM1_Position_Feedback,msg);
			break;
		}
		case 0x202:
		{
			Speed_Data_deal(&CM2_Speed_Feedback,msg);
			Position_Data_deal(&CM2_Position_Feedback,msg);
			break;
		}
		case 0x203:
		{
			Speed_Data_deal(&CM3_Speed_Feedback,msg);
			Position_Data_deal(&CM3_Position_Feedback,msg);
			break;
		}
		case 0x204:
		{
			Speed_Data_deal(&CM4_Speed_Feedback,msg);
			Position_Data_deal(&CM4_Position_Feedback,msg);
			break;
		}

		default:
		break;
	}
}



void Speed_Data_deal(ReceiveTypeDef *Receive,CanRxMsg * msg)
{
	Receive->calc=(msg->Data[2]<<8)|msg->Data[3];//���յ�����ʵ����ֵ  ����Ƶ��1KHz
}



void Position_Data_deal(ReceiveTypeDef *Receive,CanRxMsg * msg)
{
	Receive->calc=(msg->Data[0]<<8)|msg->Data[1];//���յ�����ʵ����ֵ  ����Ƶ��1KHz
	Position_To_Turns(Receive);
}




void Position_To_Turns(ReceiveTypeDef *Receive)	//����6�����������㣬��е�Ƕȹ�8192����λ���������ֲ�ֵΪ6826
{																								//ע���˺���δ�Ե�һ������ʱ�Ŀ��ܵ�Ȧ��ֱ��Ϊ1��ƫ���������������ڳ�ʼ���б궨��ʼ�Ƕ�ֵ��
	Receive->calc_diff=Receive->calc_last-Receive->calc;
	if(Receive->calc_diff>5460)
	{
		Receive->turns=Receive->turns+1;
	}
	else if(Receive->calc_diff<-5460)
	{
		Receive->turns=Receive->turns-1;
	}
	else
	{
	}
	Receive->calc_last=Receive->calc;
}




//void Speed_Data_deal(ReceiveTypeDef *Receive,CanRxMsg * msg)	//���Ǵ�ƽ��ֵ������
//{
//	Receive->real[Receive->count]=(msg->Data[2]<<8)|msg->Data[3];//���յ�����ʵ����ֵ
//	Receive->count++;
//	if(	Receive->count>1)//���δ���һ��ƽ��ֵ�����շ���Ƶ����1KHZ������ƽ��ֵ�����Ƶ��Ϊ500HZ��PID����Ƶ��Ϊ500HZ
//	{
//		Receive->calc=(Receive->real[0]+Receive->real[1])/2;//��������ƽ������ֵ
//		Receive->count=0;
//	}
//}
