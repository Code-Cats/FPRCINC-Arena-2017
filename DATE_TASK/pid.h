#ifndef PID_H
#define PID_H

#include "sys.h"

#define NOW 0
#define LAST 1
#define LAST_LAST 2


typedef struct
{
    //PID ������
    double Kp;
    double Ki;
    double Kd;
		//������ ����
		double max_out;  //������
		double dead_band;//PIDƫ������
	  double intergral_limit;	//��������
		double max_error;//�������
    //PID���ֵ
    double output;
//		double output_compensation;
    //���
    double Error[3];//0���� 1��һ�� 2���ϴ�
	  double Error_Diff[2];//0���� 1��һ��
		double I_Sum;
	struct
	{
		double send;
	}Cali_Limit;
} PidTypeDef;


float MyAbs(float num);

void PID_Init(PidTypeDef * pid,double kp,double ki,double kd,double dead_band,double max_error,double intergral_limit,double max_out);
void PID_Speed_Calc(PidTypeDef * pid,s16 Speed_Expectation,s16 Speed_Feedback);	//�ٶȻ�PID

extern PidTypeDef CM1_Speed_Pid;
extern PidTypeDef CM2_Speed_Pid;


#endif
