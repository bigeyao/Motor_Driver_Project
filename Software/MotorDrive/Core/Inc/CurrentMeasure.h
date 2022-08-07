#ifndef _CURRENTMEAS_H_
#define _CURRENTMEAS_H_
#include "adc.h"
#include "foc.h"
#define VoltageZeroPoint 2055.0f
extern uint16_t ChannleDataBuff[2];
extern uint32_t ChannleData1,ChannleData2;
extern int FilterDataLen;
void Read_Current(FOCStruct_t *Foc_struct_t);
void ReadCurrenStart(ADC_HandleTypeDef* hadc);
//uint32_t ADC_Get_ADCValue(uint8_t ch);
#endif

