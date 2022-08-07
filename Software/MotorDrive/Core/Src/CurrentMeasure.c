#include "CurrentMeasure.h"
#include "adc.h"
#include "foc.h"
//#include "dma.h"
#define SmapleNum 4  
#define FilterDataLen  15
//int FilterDataLen = 15;
uint16_t ChannleNum = 0;
uint32_t ChannleData1,ChannleData2;
uint16_t ChannleDataBuff[2];

static int FiltertDataPos_1 = 0;
static int FiltertDataPos_2 = 0;
static int FiltertDataPos_3 = 0;
static float FiltertData_1[FilterDataLen];
static float FiltertData_2[FilterDataLen];
static float FiltertData_3[FilterDataLen];

//float VoltageZeroPoint = 2055.0f;
extern uint32_t ADC_DMA_DATA[2];
//void ReadCurrenStart(ADC_HandleTypeDef* hadc){
////	HAL_ADC_Start_DMA(hadc,ChannleDataBuff,2);
//}

/*********滑动滤波*********/
float SlideFiltert(float *Filtert, float Value, int *FiltertDataPos){
    float FiltertData = 0;
    if(*FiltertDataPos >= FilterDataLen){
        *FiltertDataPos = 0;
    }
    Filtert[*FiltertDataPos] = Value;
    *FiltertDataPos += 1;
    for(int i = 0; i < FilterDataLen; i++){
        FiltertData += Filtert[i];
    }
    return FiltertData/FilterDataLen;
}

//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

//		ChannleNum++;
//		switch(ChannleNum){
//			case 1:
//				ChannleData1 = HAL_ADC_GetValue(hadc);
//			break;
//			case 2:
//				ChannleData2 = HAL_ADC_GetValue(hadc);
//				ChannleNum = 0;
//			break;

//		}
////	HAL_ADC_Stop_IT(hadc);
//}

void Read_Current(FOCStruct_t *Foc_struct_t){
	float Ia,Ib,Ic;
	Ia = ADC_DMA_DATA[0] - VoltageZeroPoint;
	Ic = ADC_DMA_DATA[1] - VoltageZeroPoint;
	Ib = -(Ia+Ic);
	Foc_struct_t->Ia = SlideFiltert(FiltertData_1,Ia,&FiltertDataPos_1);
	Foc_struct_t->Ic = SlideFiltert(FiltertData_2,Ic,&FiltertDataPos_2);
	Foc_struct_t->Ib = SlideFiltert(FiltertData_3,Ib,&FiltertDataPos_3);
}

//uint32_t ADC_Get_ADCValue(uint8_t ch)
//{
//	ADC_ChannelConfTypeDef sConfig;		//通道初始化
//	uint32_t value_sum=0;	
//	uint8_t i;
//	switch(ch)							//选择ADC通道
//	{
//		case 1:sConfig.Channel = ADC_CHANNEL_1;break;	
//		case 2:sConfig.Channel = ADC_CHANNEL_2;break;
//		case 3:sConfig.Channel = ADC_CHANNEL_3;break;
//		case 4:sConfig.Channel = ADC_CHANNEL_4;break;
//		case 5:sConfig.Channel = ADC_CHANNEL_5;break;
//		case 6:sConfig.Channel = ADC_CHANNEL_6;break;
//	}
//	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;		//采用周期239.5周期
//	sConfig.Rank = 1;
//	HAL_ADC_ConfigChannel(&hadc1,&sConfig);											
//	for(i=0;i<SmapleNum;i++)
//	{
//		HAL_ADC_Start(&hadc1);								//启动转换
//		HAL_ADC_PollForConversion(&hadc1,30);				//等待转化结束
//		value_sum += HAL_ADC_GetValue(&hadc1);				//求和					
//		HAL_ADC_Stop(&hadc1);								//停止转换
//	}
//	return value_sum/SmapleNum;									//返回平均值
//}

