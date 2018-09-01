#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"


void Control_Task(void);
void Remove_Task(void);

void Start(void);//启动函数
void Ascend_Island(void);	//登岛函数
void In_Island(void);	//岛上状态
void Island_Check(void);	//	岛上岛下检测
void Island_Position(void);	//岛下执行对位置函数


extern u8 Res;	//	usart1
extern u8 Ascend_start;	//登岛是否开始
extern u32 Ascend_time_record;
extern u8 Ascend_Can;


/***********************--工作状态--**********************/
typedef enum
{
		
    PREPARE_STATE,     		//准备状态
    NORMAL_STATE,			//正常状态
		CALI_STATE,    			//调试校准状态
    IN_ISLAND,        	//岛上状态
		OUT_ISLAND,				//岛下状态
    ISLANDING,					//登岛中
}WorkState_e;

extern WorkState_e workState;
void SetWorkState(WorkState_e state);
WorkState_e GetWorkState(void);

#endif
