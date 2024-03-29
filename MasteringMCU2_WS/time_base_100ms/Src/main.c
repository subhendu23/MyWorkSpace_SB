#include "stm32f4xx_hal.h"
#include "main.h"

#include <string.h>
#define TRUE 1
#define FALSE 0

void Error_handler(void);
void SystemClock_Config(void);
void TIMER6_Init(void);
void GPIO_Init(void);
TIM_HandleTypeDef htimer6;

int main(){

	HAL_Init();
	SystemClock_Config();
	GPIO_Init();
	TIMER6_Init();
	__HAL_RCC_BKPSRAM_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
	//Lets start timer
	HAL_TIM_Base_Start(&htimer6);

	while(1)
	{
		/* Loop until the update event flag is set */
		while( ! (TIM6->SR & TIM_SR_UIF) );
		/* The required time delay has been elapsed */
		/* User code can be executed */
		TIM6->SR = 0;
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);

	}
	return 0;
}
void SystemClock_Config(void)
{

}
void GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&ledgpio);
}
void TIMER6_Init(void)
{
	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler = 24;
	htimer6.Init.Period = 1600-1;
	if( HAL_TIM_Base_Init(&htimer6) != HAL_OK )// you will see mspinit implemented
	{
		Error_handler();
	}

}

void Error_handler(void)
{
	while(1);
}
