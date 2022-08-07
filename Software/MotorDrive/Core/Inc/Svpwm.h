#ifndef __SVPWM_H_
#define __SVPWM_H_
#define CounterV  1000
#define Motor_Time1 htim1
#define Motor_Time2 &htim1
#define PI 3.1415926535897932384626433f
#define Sqrt3 1.732050807568877293f
#define Sqrt3_2  0.86602540378443864676f  //¸ùºÅ3·ÖÖ®2
typedef struct 
{
    float Uad;
    float UAlpha;
    float UBate;
    int SectorsNum;
    float Ts;
    float T0;
    float T1;
    float T2;
    float T3;
    float T4;
    float T5;
    float T6;
    float TU;
    float TV;
    float TW;
}Svpwm_Struct_t;
void Moto1_Svpwm_Duty_Set(float Channels1DutyV,float Channels2DutyV,float Channels3DutyV);

#endif
