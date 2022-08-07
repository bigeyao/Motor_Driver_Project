#ifndef _ANO_H 
#define _ANO_H 

// typedef float float;
// #include "struct_typedef.h"
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef unsigned int   uint32_t;
typedef char  int8_t;
typedef short int16_t;
typedef int   int32_t;


void ANO_Send_Data_V1(float Temp_Target1,float Temp_Now1,float Temp_Target2,float Temp_Now2);
void ANO_Send_Data_V2(float Temp_Target1,float Temp_Now1,float Temp_Target2,float Temp_Now2);
void ANO_Send_Data_V3(float Temp_Target1,float Temp_Now1,float Temp_Target2,float Temp_Now2);
void ANO_Send_Data_Init(float Target1,float Target2,float Target3,float Target4);
void ANO_Send_FloatData(float Target1, float Target2, float Target3, float Target4);
void ANO_Send_Data_V4(float Temp_Target1, float Temp_Target2, float Temp_Target3, float Temp_Target4,float Target1, float Target2, float Target3, float Target4);
#endif 



