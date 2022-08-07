#include "ANO.h"
#include "stdio.h"
#include "usart.h"
// #include "main.h"
// #include "drv_uart.h"


// extern UART_HandleTypeDef huart6;

// //gjx
// extern UART_HandleTypeDef huart1;

uint8_t send_buf[15]= {0};
uint8_t send_bufs[35]= {0};
float Temp_Target[8] = {0};
int32_t User_TxBuff[8] = {0};

//��4ͨ��Ϊ���Ϊ16λ���ݣ���4ͨ��Ϊ���Ϊ32λ����
void ANO_Send_FloatData(float Target1, float Target2, float Target3, float Target4)
{
	int32_t User_TxBuff[8] = {0};
	User_TxBuff[0] = Target1;
	User_TxBuff[1] = Target2;
	User_TxBuff[2] = Target3;
	User_TxBuff[3] = Target4;
	int8_t data_sum = 0;
	int i = 0, cout = 0;
	send_bufs[cout++] = 0xAA;
	send_bufs[cout++] = 0x01;
	send_bufs[cout++] = 0xAF;
	send_bufs[cout++] = 0xF1;
	send_bufs[cout++] = 0;
	send_bufs[cout++] = User_TxBuff[0] >> 24;
	send_bufs[cout++] = ((User_TxBuff[0] >> 16) & 0x00ff);
	send_bufs[cout++] = ((User_TxBuff[0] >> 8) & 0x0000ff);
	send_bufs[cout++] = User_TxBuff[0];
	send_bufs[cout++] = User_TxBuff[1] >> 24;
	send_bufs[cout++] = ((User_TxBuff[1] >> 16) & 0x00ff);
	send_bufs[cout++] = ((User_TxBuff[1] >> 8) & 0x0000ff);
	send_bufs[cout++] = User_TxBuff[1];
	send_bufs[cout++] = User_TxBuff[2] >> 24;
	send_bufs[cout++] = ((User_TxBuff[2] >> 16) & 0x00ff);
	send_bufs[cout++] = ((User_TxBuff[2] >> 8) & 0x0000ff);
	send_bufs[cout++] = User_TxBuff[2];
	send_bufs[cout++] = User_TxBuff[3] >> 24;
	send_bufs[cout++] = ((User_TxBuff[3] >> 16) & 0x00ff);
	send_bufs[cout++] = ((User_TxBuff[3] >> 8) & 0x0000ff);
	send_bufs[cout++] = User_TxBuff[3];

	send_bufs[4] = cout - 5;
	for (i = 0; i < cout; i++)
	{
		data_sum += send_bufs[i];
	}
	send_bufs[cout++] = data_sum;

	for (i = 0; i < cout; i++)
	{
		HAL_UART_Transmit(&huart1,&send_bufs[i],1,0xffff);
		
//		while ((huart6.Instance->SR & 0X40) == 0)
//			;
//		huart6.Instance->DR = send_bufs[i];
//		printf("%c",send_bufs[i]);
		//gjx
//		while ((huart1.Instance->SR & 0X40) == 0);
//		huart1.Instance->DR = send_bufs[i];
	}
}

// void ANO_Send_Data_V4(float Temp_Target1, float Temp_Target2, float Temp_Target3, float Temp_Target4,
// 					  float Target1, float Target2, float Target3, float Target4)
// {
// 	int32_t User_TxBuff[8] = {0};
// 	User_TxBuff[0] = Temp_Target1;
// 	User_TxBuff[1] = Temp_Target2;
// 	User_TxBuff[2] = Temp_Target3;
// 	User_TxBuff[3] = Temp_Target4;
// 	User_TxBuff[4] = Target1;
// 	User_TxBuff[5] = Target2;
// 	User_TxBuff[6] = Target3;
// 	User_TxBuff[7] = Target4;

// 	int8_t data_sum = 0;
// 	int i = 0, cout = 0;
// 	send_bufs[cout++] = 0xAA;
// 	send_bufs[cout++] = 0x01;
// 	send_bufs[cout++] = 0xAF;
// 	send_bufs[cout++] = 0xF1;
// 	send_bufs[cout++] = 0;
// 	send_bufs[cout++] = User_TxBuff[0] >> 24;
// 	send_bufs[cout++] = ((User_TxBuff[0] >> 16) & 0x00ff);
// 	send_bufs[cout++] = ((User_TxBuff[0] >> 8) & 0x0000ff);
// 	send_bufs[cout++] = User_TxBuff[0];
// 	send_bufs[cout++] = User_TxBuff[1] >> 24;
// 	send_bufs[cout++] = ((User_TxBuff[1] >> 16) & 0x00ff);
// 	send_bufs[cout++] = ((User_TxBuff[1] >> 8) & 0x0000ff);
// 	send_bufs[cout++] = User_TxBuff[1];
// 	send_bufs[cout++] = User_TxBuff[2] >> 24;
// 	send_bufs[cout++] = ((User_TxBuff[2] >> 16) & 0x00ff);
// 	send_bufs[cout++] = ((User_TxBuff[2] >> 8) & 0x0000ff);
// 	send_bufs[cout++] = User_TxBuff[2];
// 	send_bufs[cout++] = User_TxBuff[3] >> 24;
// 	send_bufs[cout++] = ((User_TxBuff[3] >> 16) & 0x00ff);
// 	send_bufs[cout++] = ((User_TxBuff[3] >> 8) & 0x0000ff);
// 	send_bufs[cout++] = User_TxBuff[3];
// 	send_bufs[cout++] = User_TxBuff[4] >> 24;
// 	send_bufs[cout++] = ((User_TxBuff[4] >> 16) & 0x00ff);
// 	send_bufs[cout++] = ((User_TxBuff[4] >> 8) & 0x0000ff);
// 	send_bufs[cout++] = User_TxBuff[4];
// 	send_bufs[cout++] = User_TxBuff[5] >> 24;
// 	send_bufs[cout++] = ((User_TxBuff[5] >> 16) & 0x00ff);
// 	send_bufs[cout++] = ((User_TxBuff[5] >> 8) & 0x0000ff);
// 	send_bufs[cout++] = User_TxBuff[5];
// 	send_bufs[cout++] = User_TxBuff[6] >> 24;
// 	send_bufs[cout++] = ((User_TxBuff[6] >> 16) & 0x00ff);
// 	send_bufs[cout++] = ((User_TxBuff[6] >> 8) & 0x0000ff);
// 	send_bufs[cout++] = User_TxBuff[6];
// 	send_bufs[cout++] = User_TxBuff[7] >> 24;
// 	send_bufs[cout++] = ((User_TxBuff[7] >> 16) & 0x00ff);
// 	send_bufs[cout++] = ((User_TxBuff[7] >> 8) & 0x0000ff);
// 	send_bufs[cout++] = User_TxBuff[7];

// 	send_bufs[4] = cout - 5;
// 	for (i = 0; i < cout; i++)
// 	{
// 		data_sum += send_bufs[i];
// 	}
// 	send_bufs[cout++] = data_sum;

// 	for (i = 0; i < cout; i++)
// 	{
// 		// while ((USART6->SR & 0X40) == 0)
// 		// 	;
// 		// huart6.Instance->DR = send_bufs[i];
// 	}
// }





// void ANO_Send_Data_V3(float Temp_Target1,float Temp_Now1,float Temp_Target2,float Temp_Now2)
// {
//   int8_t data_sum=0;
// 	int i=0,cout=0;
// 	send_buf[cout++]=0xAA;                   //0
// 	send_buf[cout++]=0x01;                   //1
// 	send_buf[cout++]=0xAF;                   //2
// 	send_buf[cout++]=0xF1;                   //3
// 	send_buf[cout++]=0;                      //4
// 	send_buf[cout++]=Temp_Target1>>8;        //5
// 	send_buf[cout++]=Temp_Target1;           //6
// 	send_buf[cout++]=Temp_Now1>>8;           //7
// 	send_buf[cout++]=Temp_Now1;              //8
// 	send_buf[cout++]=Temp_Target2>>8;        //9
// 	send_buf[cout++]=Temp_Target2;           //10
// 	send_buf[cout++]=Temp_Now2>>8;           //11
// 	send_buf[cout++]=Temp_Now2;              //12
// 	send_buf[4]=cout-5;
// 	for(i=0;i<cout;i++)
// 	{
// 	data_sum+=send_buf[i];
// 	}
// 	send_buf[cout++]=data_sum;
	
// 	for(i=0;i<cout;i++)
// 	{
// //	USART_sendChar(USART2,send_buf[i]);
// 	}
// }


// void ANO_Send_Data_V1(float Temp_Target1,float Temp_Now1,float Temp_Target2,float Temp_Now2)
// {
// 	int8_t data_sum=0;
// 	int i=0;
// 	send_buf[0]=0xAA;
// 	send_buf[1]=0x01;
// 	send_buf[2]=0xAF;
// 	send_buf[3]=0x02;
// 	send_buf[4]=0x08;
// 	send_buf[5]=Temp_Target1>>8;
// 	send_buf[6]=Temp_Target1;
// 	send_buf[7]=Temp_Now1>>8;
// 	send_buf[8]=Temp_Now1;
// 	send_buf[9]=Temp_Target2>>8;
// 	send_buf[10]=Temp_Target2;
// 	send_buf[11]=Temp_Now2>>8;
// 	send_buf[12]=Temp_Now2;
// 	for(i=0;i<13;i++)
// 	{
// 	data_sum+=send_buf[i];
// 	}
// 	send_buf[13]=data_sum;
// 	for(i=0;i<14;i++)
// 	{
// //	USART_sendChar(USART2,send_buf[i]);
// 	}

// }




// void ANO_Send_Data_V2(float Temp_Target1,float Temp_Now1,float Temp_Target2,float Temp_Now2)
// {
// 	int8_t data_sum=0;
// 	int i=0,cout=0;
// 	send_buf[cout++]=0xAA;
// 	send_buf[cout++]=0x01;
// 	send_buf[cout++]=0xAF;
// 	send_buf[cout++]=0x02;
// 	send_buf[cout++]=0;
// 	send_buf[cout++]=Temp_Target1>>8;
// 	send_buf[cout++]=Temp_Target1;
// 	send_buf[cout++]=Temp_Now1>>8;
// 	send_buf[cout++]=Temp_Now1;
// 	send_buf[cout++]=Temp_Target2>>8;
// 	send_buf[cout++]=Temp_Target2;
// 	send_buf[cout++]=Temp_Now2>>8;
// 	send_buf[cout++]=Temp_Now2;
// 	send_buf[4]=cout-5;
// 	for(i=0;i<cout;i++)
// 	{
// 	data_sum+=send_buf[i];
// 	}
// 	send_buf[cout++]=data_sum;
	
// 	for(i=0;i<cout;i++)
// 	{
// //	USART_sendChar(USART2,send_buf[i]);
// 	}

// }





