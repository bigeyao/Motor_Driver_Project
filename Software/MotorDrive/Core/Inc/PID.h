

#ifndef __PID_A_H__
#define __PID_A_H__

#include "stm32f4xx.h"
//#include "SteeringWheel.h"
typedef struct _PID_TypeDef
{
	float PID_Type;
	float target;							//目标值
//	float lastNoneZeroTarget;
	float kp;
	float ki;
	float kd;
	
	float measure;					//测量值
	float err;							//误差
	float last_err;      		//上次误差
	
	float pout; 
	float iout;
	float dout;
	
	float DeadBand;         //死区
	float output;						//本次输出
	float last_output;			//上次输出
	float MaxOutput;				//输出限幅
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


