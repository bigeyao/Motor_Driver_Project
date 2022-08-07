

#ifndef __PID_A_H__
#define __PID_A_H__

#include "stm32f4xx.h"
//#include "SteeringWheel.h"
typedef struct _PID_TypeDef
{
	float PID_Type;
	float target;							//Ŀ��ֵ
//	float lastNoneZeroTarget;
	float kp;
	float ki;
	float kd;
	
	float measure;					//����ֵ
	float err;							//���
	float last_err;      		//�ϴ����
	
	float pout; 
	float iout;
	float dout;
	
	float DeadBand;         //����
	float output;						//�������
	float last_output;			//�ϴ����
	float MaxOutput;				//����޷�
	float IntegralLimit;
	float a;
} PID_TypDef;


typedef enum {
	Speed = 0,
	Angle ,
	Position,
	Orienta,
	Straight
}PID_Type;

extern PID_TypDef PID_Angle;
extern PID_TypDef PID_Speed;

void PID_Init(PID_TypDef* PID,int target,float MaxOutput,float IntegralLimit,float kp,float ki,float kd);	
void PID_Speed_Calculate(PID_TypDef* PID,float measure);
float PID_Calculate(PID_TypDef* PID,float measure);

#endif


