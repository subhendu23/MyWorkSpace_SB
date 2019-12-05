
#include"stm32f4xx_hal.h"

void HAL_MspInit(void)
{
  // this is an optional setings
	//1. set up the priority grouping of the arm cortex processor

		HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); // this API is from stm32f4xx_hal_cortex.c

	//2. Enable the required system exceptions of the Cortex Mx processor
	SCB->SHCSR |= 0x7 <<16;// enabled usage fault , memory fault and bus fault exceptions

	//3. Configure the priority for the system exception
	HAL_NVIC_SetPriority( MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority( BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority( UsageFault_IRQn, 0, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

	GPIO_InitTypeDef gpio_uart;

	//here we are going to do the low level inits. of the USART2 peripheral
	//1.Enaable the clock for USART2 peripheral
	__HAL_RCC_USART2_CLK_ENABLE(); // enable clock for USART2
	__HAL_RCC_GPIOA_CLK_ENABLE(); // enable clock for GPIOA

	//2. Do the pin muxing.{ May be different for different microcontrollers
	gpio_uart.Pin=GPIO_PIN_2;
	gpio_uart.Mode=GPIO_MODE_AF_PP;
	gpio_uart.Pull=GPIO_PULLUP;
	gpio_uart.Speed=GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate=GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin=GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	//3. Enable the IRQ and set up the priorities ( i.e. NVIC setting)// optional..
	//asynchronous event - completion of transmission etc . If we do not configure this the periphersal will be at the polloing mode.
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn,15,0);
}
