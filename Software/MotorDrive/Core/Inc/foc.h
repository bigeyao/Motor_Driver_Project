#ifndef __FOC_H__
#define __FOC_H__

#include <math.h>
#include "PID.h"
#include "Svpwm.h"
//#include "stm32f407xx.h"
typedef enum{
	MOTOR_1 = 0,
	MOTOR_2,
	MOTOR1_AND_MOTOR2
}MOTONUM;

typedef enum{
    False = 0,
    True
}Bool;


typedef struct {
   MOTONUM Motor_num;
   Svpwm_Struct_t SVPWM_Strutc;
	 PID_TypDef Id_PID;
	 PID_TypDef Iq_PID;
   float Alpha;
   float Bate;
   float Id;
   float Iq;
	 float LastAngle;
   float Angle;
	 float Angle_1;
   float Ia;
   float Ib;
   float Ic;
}FOCStruct_t;

extern float VoltageZeroPoint;
extern float AddTestAngle;


void Time_Calculate(Svpwm_Struct_t *Svpwm);
void Foc_Init(FOCStruct_t *Foc_struct_t);
void Motor_Start(MOTONUM MOTOR);
void RevPark(float Id, float Iq, FOCStruct_t *Focstruct);
void Park(FOCStruct_t *Focstruct);
void Clark(FOCStruct_t *Focstruct);
int SectorsJudge(Svpwm_Struct_t *SVPWM_Strutc);
void SVPWM_Calculate(float Id,float Iq,FOCStruct_t *focstruct);
void SVPWM_Start(FOCStruct_t *focstruct);
void FOC_Calculate(FOCStruct_t *Foc_struct_t);
void Mos_Low(FOCStruct_t *focstruct);
#endif

