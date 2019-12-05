#include "stm32f4xx_hal.h"
#include "main.h"
#include <string.h>
#define TRUE 1
#define FALSE 0

uint8_t rcvd_data;
uint8_t data_buffer[100];
uint8_t count=0;

char *user_data ="The application is running USART2 \r\n";

void SystemClockConfig();
void UART2_Init(void);
void Error_Handler(void);
uint8_t convert_to_capital(uint8_t data);
uint8_t reception_complete = FALSE;
UART_HandleTypeDef huart2;

int main(){

	HAL_Init();
	// when you need special clock setting
	SystemClockConfig();
	UART2_Init();
	uint16_t len_of_data=strlen(user_data);
	if (HAL_UART_Transmit(&huart2,(uint8_t*) user_data,len_of_data,HAL_MAX_DELAY)!= HAL_OK)
	{
		Error_Handler();
	}
	while(reception_complete != TRUE)
		HAL_UART_Receive_IT(&huart2,&rcvd_data,1);

	while(1);
	return 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(rcvd_data=='\r')
	{
		reception_complete =TRUE;
		data_buffer[count++]='\r';
		HAL_UART_Transmit(&huart2,data_buffer,count,HAL_MAX_DELAY);
	}
	else
	{
		data_buffer[count++]=rcvd_data;
	}

}
void SystemClockConfig()
{


}

uint8_t convert_to_capital(uint8_t data)
{
	if(data >='a' && data <= 'z' )
		{
			data=data-('a'-'A');

		}
	return data;

}
void UART2_Init(void)
{
	huart2.Instance=USART2;
	huart2.Init.BaudRate=115200;
	huart2.Init.WordLength=UART_WORDLENGTH_8B;
	huart2.Init.StopBits=UART_STOPBITS_1;
	huart2.Init.Parity=UART_PARITY_NONE;
	huart2.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	huart2.Init.Mode=UART_MODE_TX_RX;
	if (HAL_UART_Init(&huart2)!=HAL_OK)
	{
		// there is a error
		Error_Handler();
	}
}


void Error_Handler(void)
{

}
