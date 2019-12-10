#include "main.h"

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

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)
{

	//1. enable the clock for the TIM6 peripheral
	__HAL_RCC_TIM6_CLK_ENABLE();

	//2. Enable the IRQ of TIM6
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	//3. setup the priority for TIM6_DAC_IRQn
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn,15,0);

}
