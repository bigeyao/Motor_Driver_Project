#include "PID.h"
#include "math.h"
#include "stm32f4xx.h"
//#include "mytype.h"
PID_TypDef PID_Speed;
PID_TypDef PID_Angle;


void PID_Init(PID_TypDef* PID,
		                int target,
											float MaxOutput,
													float IntegralLimit,
														 float kp,
																 float ki,
																		float kd)								            
{
//	PID->PID_Type = PID_Type;
	PID->target = target;
	PID->MaxOutput = MaxOutput;
	PID->IntegralLimit = IntegralLimit;
	PID->kp = kp;
	PID->ki = ki;
	PID->kd = kd;
	PID->last_err = 0;
}

float PID_Calculate(PID_TypDef* PID,float measure)
{
//	if(PID->PID_Type == Angle)    //判断死区
//	{
//		if((PID->target>=0) && (PID->target<=2191)){
//			if(measure>=6000&&measure<=8191) measure -= 8191;
//		}else if((PID->target >= 6000) && (PID->target <= 8191)){
//			if(measure>=0&&measure<=2191) measure += 8191;
//		}
//	}
//	uint16_t KD = 300;
	PID->measure = measure;
	PID->err = PID->target - PID->measure;
	PID->pout = (PID->err * PID->kp);
	
//	if(PID->PID_Type == Position){
//		KD = 2000;
//	}
	if(PID->PID_Type == Straight && fabs(PID->err) < 10)     //单跑直线误差小于10时不做矫正
	{
		PID->output = 0;
		return PID->output;
	}else if(PID->PID_Type == Orienta){
		if(PID->err < 40){
			PID->dout = (PID->err - PID->last_err) * PID->kd; 
		}else PID->dout = 0;
	}else{
		PID->dout = (PID->err - PID->last_err) * PID->kd;
	}
		PID->iout += (PID->err * PID->ki);
		if(PID->iout>PID->IntegralLimit) {PID->iout = (int)PID->IntegralLimit;}   //积分限制幅
		else if(PID->iout < -PID->IntegralLimit){PID->iout = -(int)PID->IntegralLimit;}
		
//	if(fabs(PID->err)<KD){
////			PID->a = PID->err - PID->last_err;
//		PID->dout = (PID->err - PID->last_err) * PID->kd; 
//	}
//	else {PID->dout = 0;}
	
	
	  PID->last_err = PID->err;
	
//   if(PID->err > PID->DeadBand){   
		PID->output = (int)(PID->pout + PID->iout + PID->dout);
		
		if(PID->output > PID->MaxOutput)    //输出限幅
		{
			PID->output=PID->MaxOutput;
		}
		else if(PID->output < -PID->MaxOutput)    //输出限幅
		{
			PID->output= - PID->MaxOutput;
		}
//}else PID->output=(int)PID->last_output;
		return PID->output;
}
