#include "Svpwm.h"
#include "tim.h"


void Moto1_Svpwm_Duty_Set(float Channels1DutyV,float Channels2DutyV,float Channels3DutyV){
	
	Motor_Time1.Instance->CCR1 = CounterV*Channels1DutyV/100;
	Motor_Time1.Instance->CCR2 = CounterV*Channels2DutyV/100;
	Motor_Time1.Instance->CCR3 = CounterV*Channels3DutyV/100;
}



int SectorsJudge(Svpwm_Struct_t *SVPWM_Strutc){
    float U = SVPWM_Strutc->UBate;
    float V = SVPWM_Strutc->UAlpha * Sqrt3_2 - SVPWM_Strutc->UBate / 2.0f;
    float W = -SVPWM_Strutc->UAlpha * Sqrt3_2 - SVPWM_Strutc->UBate / 2.0f;
    SVPWM_Strutc->SectorsNum = 0;
    int N = 0;
    if(U>0){
        N += 1;
    }
    if(V>0){
        N += 2;
    }
    if(W>0){
        N += 4;     
    }
    switch (N)
    {
    case 3:
        SVPWM_Strutc->SectorsNum = 1;
        break;
    case 1:
        SVPWM_Strutc->SectorsNum = 2;
        break;  
    case 5:
        SVPWM_Strutc->SectorsNum = 3;
        break;
    case 4:
        SVPWM_Strutc->SectorsNum = 4;
        break;
    case 6:
        SVPWM_Strutc->SectorsNum = 5;
        break;
    case 2:
       SVPWM_Strutc->SectorsNum = 6;
        break;  
    default:
        break;
    }
    return SVPWM_Strutc->SectorsNum;
}

/**
  * @brief  SVPWM分配到六个基向量的时间计算
  * @param  Svpwm 为svpwm的结构体
  * @retval NULL
  */

void Time_Calculate(Svpwm_Struct_t *Svpwm){
    float K = (Svpwm->Ts * Sqrt3)/Svpwm->Uad;
    float U1 = Svpwm->UBate; 
    float U2 = (Sqrt3_2 * Svpwm->UAlpha - Svpwm->UBate * 0.5f);
    float U3 = (-Sqrt3_2 * Svpwm->UAlpha - Svpwm->UBate * 0.5f);
    float Temp = 0;
    switch (Svpwm->SectorsNum)
    {
			case 0:
					Svpwm->TU = 0;
					Svpwm->TV = 0;
					Svpwm->TW = 0;
					break;			
			case 1:
					Svpwm->T4 = K*U2 * 0.5f;
					Svpwm->T6 = K*U1 * 0.5f;
					Temp = Svpwm->T4 + Svpwm->T6;
					if(Temp > Svpwm->Ts){
							Svpwm->T4 = Svpwm->T4/Temp * Svpwm->Ts;
							Svpwm->T6 = Svpwm->T6/Temp * Svpwm->Ts;            
					}
					Svpwm->T0 = (Svpwm->Ts - Svpwm->T4 -Svpwm->T6)*0.25f;    
					Svpwm->TU = Svpwm->T4 + Svpwm->T6 + Svpwm->T0;
					Svpwm->TV = Svpwm->T6 + Svpwm->T0;
					Svpwm->TW = Svpwm->T0;
					break;
			case 2:
					Svpwm->T6 = -K*U3 * 0.5f;
					Svpwm->T2 = -K*U2 * 0.5f;
					Temp = Svpwm->T2 + Svpwm->T6;
					if(Temp > Svpwm->Ts){
							Svpwm->T2 = Svpwm->T2/Temp * Svpwm->Ts;
							Svpwm->T6 = Svpwm->T6/Temp * Svpwm->Ts;            
					}
					Svpwm->T0 = (Svpwm->Ts - Svpwm->T2 -Svpwm->T6)*0.25f;
					Svpwm->TV = Svpwm->T2 + Svpwm->T6 + Svpwm->T0;
					Svpwm->TU = Svpwm->T6 + Svpwm->T0;
					Svpwm->TW = Svpwm->T0;
					break; 
			case 3:

					Svpwm->T2 = K*U1 * 0.5f;
					Svpwm->T3 = K*U3 * 0.5f;
					Temp = Svpwm->T2 + Svpwm->T3;
					if(Temp > Svpwm->Ts){
							Svpwm->T2 = Svpwm->T3/Temp * Svpwm->Ts;
							Svpwm->T2 = Svpwm->T3/Temp * Svpwm->Ts;            
					}
					Svpwm->T0 = (Svpwm->Ts - Svpwm->T2 -Svpwm->T3)*0.25f;
					Svpwm->TV = Svpwm->T2 + Svpwm->T3 + Svpwm->T0;
					Svpwm->TW = Svpwm->T3 + Svpwm->T0;
					Svpwm->TU = Svpwm->T0;
					break; 
			case 4:
					Svpwm->T1 = -K*U1 * 0.5f;
					Svpwm->T3 = -K*U2 * 0.5f;
					Temp = Svpwm->T3 + Svpwm->T1;
					if(Temp > Svpwm->Ts){
							Svpwm->T3 = Svpwm->T3/Temp * Svpwm->Ts;
							Svpwm->T1 = Svpwm->T1/Temp * Svpwm->Ts;            
					}
					Svpwm->T0 = (Svpwm->Ts - Svpwm->T1 -Svpwm->T3)*0.25f;
					Svpwm->TW = Svpwm->T1 + Svpwm->T3 + Svpwm->T0;
					Svpwm->TV = Svpwm->T3 + Svpwm->T0;
					Svpwm->TU = Svpwm->T0;
					break;  
			case 5:
					Svpwm->T1 = K*U3 * 0.5f;
					Svpwm->T5 = K*U2 * 0.5f;
					Temp = Svpwm->T1 + Svpwm->T5;
					if(Temp > Svpwm->Ts){
							Svpwm->T1 = Svpwm->T1/Temp * Svpwm->Ts;
							Svpwm->T5 = Svpwm->T5/Temp * Svpwm->Ts;            
					}
					Svpwm->T0 = (Svpwm->Ts - Svpwm->T1 -Svpwm->T5)*0.25f;
					Svpwm->TW = Svpwm->T1 + Svpwm->T5 + Svpwm->T0;
					Svpwm->TU = Svpwm->T5 + Svpwm->T0;
					Svpwm->TV = Svpwm->T0;
					break;  
			case 6:
					Svpwm->T4 = -K*U3 * 0.5f;
					Svpwm->T5 = -K*U1 * 0.5f;
					Temp = Svpwm->T4 + Svpwm->T5;
					if(Temp > Svpwm->Ts){
							Svpwm->T4 = Svpwm->T4/Temp * Svpwm->Ts;
							Svpwm->T5 = Svpwm->T5/Temp * Svpwm->Ts;            
					}
					Svpwm->T0 = (Svpwm->Ts - Svpwm->T4 -Svpwm->T5)*0.25f;
					Svpwm->TU = Svpwm->T4 + Svpwm->T5 + Svpwm->T0;
					Svpwm->TW = Svpwm->T5 + Svpwm->T0;
					Svpwm->TV = Svpwm->T0;
					break; 
			default:
					break;
    }
}

