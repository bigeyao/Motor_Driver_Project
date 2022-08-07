
#include <stdio.h>
//#include "stm32f407xx.h" 
#include "foc.h"
#include "tim.h"
#include "gpio.h"

#include "adc.h"
#include "CurrentMeasure.h"
#include "ANO.h"


#define BLDC_MCPWM_TIMER_U 0
#define BLDC_MCPWM_TIMER_V 1
#define BLDC_MCPWM_TIMER_W 2
#define UadValue 24
#define TS 100
#define Moto1_Time_init() MX_TIM1_Init()
#define Moto2_Time_Init() MX_TIM1_Init()

float AddTestAngle = 0;
extern FOCStruct_t Foc_struct_t;
static int Read_Current_Num = 0;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(Read_Current_Num == 2){
		Read_Current(&Foc_struct_t);
		Read_Current_Num = 0;
	}
	Read_Current_Num++;
}

/**
  * @brief  FOC initialization.
  * @param  Foc_struct_t Foc structure Potion
  * @retval NULL
  */
void Foc_Init(FOCStruct_t *Foc_struct_t){
	Foc_struct_t->Angle = 0;
  Foc_struct_t->SVPWM_Strutc.Ts = TS;
  Foc_struct_t->SVPWM_Strutc.Uad = UadValue;
	
	MX_GPIO_Init();
	if(Foc_struct_t->Motor_num == MOTOR_1){
		Moto1_Time_init();
		Motor_Start(Foc_struct_t->Motor_num);
		HAL_TIM_Base_Start_IT(&Motor_Time1);
	}else if(Foc_struct_t->Motor_num == MOTOR_2){
		Moto2_Time_Init();
		Motor_Start(Foc_struct_t->Motor_num);
		HAL_TIM_Base_Start_IT(Motor_Time2);
	}else if(Foc_struct_t->Motor_num == MOTOR1_AND_MOTOR2){
		Moto1_Time_init();	
		Moto2_Time_Init();
	}
	Motor_Start(Foc_struct_t->Motor_num);
	HAL_TIM_Base_Start_IT(&Motor_Time1);
	PID_Init(&(Foc_struct_t->Id_PID),200.0f,Foc_struct_t->SVPWM_Strutc.Uad,Foc_struct_t->SVPWM_Strutc.Uad,0.02,0.002,0);
	PID_Init(&(Foc_struct_t->Iq_PID),0,Foc_struct_t->SVPWM_Strutc.Uad,10.0f,0.02,0.002,0);
}

/**
  * @brief  Start the Motor PWM signal generation.
  * @param  MOTOR  Motor Number
  * @retval NULL
  */
void Motor_Start(MOTONUM MOTOR){
	if(MOTOR == MOTOR_1){
		HAL_TIM_PWM_Start(&Motor_Time1,TIM_CHANNEL_1);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(&Motor_Time1,TIM_CHANNEL_1);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Start(&Motor_Time1,TIM_CHANNEL_2);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(&Motor_Time1,TIM_CHANNEL_2);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Start(&Motor_Time1,TIM_CHANNEL_3);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(&Motor_Time1,TIM_CHANNEL_3);//在互补输出上开始PWM信号的产生。
	}else if(MOTOR == MOTOR_2){
		HAL_TIM_PWM_Start(Motor_Time2,TIM_CHANNEL_1);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(Motor_Time2,TIM_CHANNEL_1);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Start(Motor_Time2,TIM_CHANNEL_2);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(Motor_Time2,TIM_CHANNEL_2);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Start(Motor_Time2,TIM_CHANNEL_3);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(Motor_Time2,TIM_CHANNEL_3);//在互补输出上开始PWM信号的产生。		
	}else if(MOTOR == MOTOR1_AND_MOTOR2){
		HAL_TIM_PWM_Start(&Motor_Time1,TIM_CHANNEL_1);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(&Motor_Time1,TIM_CHANNEL_1);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Start(&Motor_Time1,TIM_CHANNEL_2);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(&Motor_Time1,TIM_CHANNEL_2);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Start(&Motor_Time1,TIM_CHANNEL_3);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(&Motor_Time1,TIM_CHANNEL_3);//在互补输出上开始PWM信号的产生。
		
		HAL_TIM_PWM_Start(Motor_Time2,TIM_CHANNEL_1);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(Motor_Time2,TIM_CHANNEL_1);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Start(Motor_Time2,TIM_CHANNEL_2);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(Motor_Time2,TIM_CHANNEL_2);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Start(Motor_Time2,TIM_CHANNEL_3);//开始产生PWM信号
		HAL_TIMEx_PWMN_Start(Motor_Time2,TIM_CHANNEL_3);//在互补输出上开始PWM信号的产生。	
	}
}

/**
  * @brief  Stops the Motor PWM signal generation.
  * @param  MOTOR Motor Number
  * @retval NULL
  */
void Motor_Stop(MOTONUM MOTOR){
	if(MOTOR == MOTOR_1){
		HAL_TIM_PWM_Stop(&Motor_Time1,TIM_CHANNEL_1);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(&Motor_Time1,TIM_CHANNEL_1);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Stop(&Motor_Time1,TIM_CHANNEL_2);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(&Motor_Time1,TIM_CHANNEL_2);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Stop(&Motor_Time1,TIM_CHANNEL_3);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(&Motor_Time1,TIM_CHANNEL_3);//在互补输出上开始PWM信号的产生。
	}else if(MOTOR == MOTOR_2){
		HAL_TIM_PWM_Stop(Motor_Time2,TIM_CHANNEL_1);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(Motor_Time2,TIM_CHANNEL_1);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Stop(Motor_Time2,TIM_CHANNEL_2);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(Motor_Time2,TIM_CHANNEL_2);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Stop(Motor_Time2,TIM_CHANNEL_3);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(Motor_Time2,TIM_CHANNEL_3);//在互补输出上开始PWM信号的产生。		
	}else if(MOTOR == MOTOR1_AND_MOTOR2){
		HAL_TIM_PWM_Stop(&Motor_Time1,TIM_CHANNEL_1);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(&Motor_Time1,TIM_CHANNEL_1);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Stop(&Motor_Time1,TIM_CHANNEL_2);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(&Motor_Time1,TIM_CHANNEL_2);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Stop(&Motor_Time1,TIM_CHANNEL_3);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(&Motor_Time1,TIM_CHANNEL_3);//在互补输出上开始PWM信号的产生。
		
		HAL_TIM_PWM_Stop(Motor_Time2,TIM_CHANNEL_1);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(Motor_Time2,TIM_CHANNEL_1);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Stop(Motor_Time2,TIM_CHANNEL_2);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(Motor_Time2,TIM_CHANNEL_2);//在互补输出上开始PWM信号的产生。
		HAL_TIM_PWM_Stop(Motor_Time2,TIM_CHANNEL_3);//开始产生PWM信号
		HAL_TIMEx_PWMN_Stop(Motor_Time2,TIM_CHANNEL_3);//在互补输出上开始PWM信号的产生。	
		
	}
}
/**
  * @brief  SVPWM calculation and outputn.
  * @param  Id  ID value of the coordinate
	* @param  Iq  IQ value of the coordinat
	* @param  Foc_struct_t  Foc structure Potion
  * @retval NULL
  */

void SVPWM_Calculate(float Id,float Iq,FOCStruct_t *focstruct){
    RevPark(Id,Iq,focstruct);
    SectorsJudge(&(focstruct->SVPWM_Strutc));
    Time_Calculate(&(focstruct->SVPWM_Strutc));
		Moto1_Svpwm_Duty_Set(focstruct->SVPWM_Strutc.TU,focstruct->SVPWM_Strutc.TV,focstruct->SVPWM_Strutc.TW);
}

/**
  * @brief  Park Change
  * @param  Foc_struct_t  Foc structure Potio
  * @retval NULL
  */
void Park(FOCStruct_t *Focstruct){
    float Id = Focstruct->Alpha * cos(PI*(Focstruct->Angle+AddTestAngle)/180.0f) + Focstruct->Bate * sin(PI*(Focstruct->Angle+AddTestAngle)/180.0f);
		float Iq = Focstruct->Bate *	cos(PI*(Focstruct->Angle+AddTestAngle)/180.0f) - Focstruct->Alpha * sin(PI*(Focstruct->Angle+AddTestAngle)/180.0f);
    Focstruct->Id = Id;
    Focstruct->Iq = Iq;
}

/**
  * @brief  RevPark Change
  * @param  Foc_struct_t  Foc structure Potio
  * @retval NULL
  */
void RevPark(float Id, float Iq, FOCStruct_t *Focstruct){
    Focstruct->SVPWM_Strutc.UAlpha = Id * cos(PI*Focstruct->Angle/180.0f) - Iq * sin(PI*Focstruct->Angle/180.0f);
    Focstruct->SVPWM_Strutc.UBate = Id * sin(PI*Focstruct->Angle/180.0f) + Iq * cos(PI*Focstruct->Angle/180.0f);
}
/**
  * @brief  Clark Change
  * @param  Foc_struct_t  Foc structure Potio
  * @retval NULL
  */
void Clark(FOCStruct_t *Focstruct){
    Focstruct->Alpha = Focstruct->Ia - Focstruct->Ib*0.5f - Focstruct->Ic*0.5f;
    Focstruct->Bate = Focstruct->Ib*0.866025403784f - Focstruct->Ic*0.866025403784f;
}

/**
  * @brief  Calculate electric field Angle
  * @param  Foc_struct_t  Foc structure Potio
  * @retval NULL
  */
void Angle_Calculate(FOCStruct_t *Foc_struct_t){
	float z = sqrt(powf(Foc_struct_t->Alpha,2) + powf(Foc_struct_t->Bate,2)); 
	if(Foc_struct_t->Alpha>0 && Foc_struct_t->Bate>=0)
	{
		Foc_struct_t->Angle = acos(fabsf((float)Foc_struct_t->Alpha)/z)*180.0/3.1416; 
	}else if(Foc_struct_t->Alpha<=0 && Foc_struct_t->Bate>0)
	{
		Foc_struct_t->Angle = acos(fabsf((float)Foc_struct_t->Bate)/z)*180.0/3.1416 + 90.0;
	}else if(Foc_struct_t->Alpha<0 && Foc_struct_t->Bate<=0)
	{
		Foc_struct_t->Angle = acos(fabsf((float)Foc_struct_t->Alpha)/z)*180.0/3.1416 + 180.0;
	}else if(Foc_struct_t->Alpha>=0 && Foc_struct_t->Bate<0)
	{
		Foc_struct_t->Angle = acos(fabsf((float)Foc_struct_t->Bate)/z)*180.0/3.1416 + 270.0;
	}
}
/**
  * @brief  Determining the direction of rotation
  * @param  Foc_struct_t  Foc structure Potio
  * @retval NULL
  */
float Orienter_Judge(FOCStruct_t *Foc_struct_t){
	if((Foc_struct_t->Angle < Foc_struct_t->LastAngle && Foc_struct_t->LastAngle - 180.0f < Foc_struct_t->Angle)|| Foc_struct_t->Angle - 180.0f > Foc_struct_t->LastAngle){
		Foc_struct_t->LastAngle = Foc_struct_t->Angle;
		return Foc_struct_t->Id *= -1;
	}else{
		Foc_struct_t->LastAngle = Foc_struct_t->Angle;
		return Foc_struct_t->Id;
	}
}

void FOC_Calculate(FOCStruct_t *Foc_struct_t){
		Clark(Foc_struct_t);
		Angle_Calculate(Foc_struct_t);
		Foc_struct_t->Alpha = Foc_struct_t->Alpha * 1.6113f;       //6600.0f / 4096.0f ;
		Foc_struct_t->Bate = Foc_struct_t->Bate * 1.6113f;         //6600.0f / 4096.0f;
		Park(Foc_struct_t);
		Orienter_Judge(Foc_struct_t);
		SVPWM_Calculate(PID_Calculate(&(Foc_struct_t->Iq_PID),Foc_struct_t->Iq),PID_Calculate(&(Foc_struct_t->Id_PID),Foc_struct_t->Id),Foc_struct_t);
}
