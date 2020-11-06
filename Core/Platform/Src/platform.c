/**
  ******************************************************************************
  * @file           : platform.c
  * @brief          : Platform body
  ******************************************************************************
  * @attention
  *
  *
  *
  *
  *
  ******************************************************************************
  */

#include "platform.h"
#include "stm32f4xx_hal.h"

void platform_start_yorker()
{
	 HAL_Init();
	 platform_sysclk_cfg();
	 platform_gpio_init();
	 platform_adc_init();
	 platform_uart_init();
	 platform_rtc_init();
	 platform_timer_init();

	 while (1)
	   {
	     /* USER CODE END WHILE */

	     /* USER CODE BEGIN 3 */
	   }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}
