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

unsigned int makeup_water_added = 0;
unsigned int blowdown_water = 0;
unsigned int chemical1 = 0;
unsigned int chemical2 = 0;
uint16_t ph_inlet_water = 0;
uint16_t ph_plant_water = 0;
uint16_t tds_inlet_water = 0;
uint16_t tds_plant_water = 0;
bool pump1_state = false;
bool pump2_state = true;

settings yorker_settings = {0};


void platform_start_yorker()
{
	 HAL_Init();
	 platform_sysclk_cfg();
	 platform_gpio_init();
	 platform_adc_init();
	 platform_uart_init();
	 platform_display_init();
	 platform_rtc_init();
	 platform_timer_init();

	 platform_timer_start();

	 while (1)
	   {
	     /* USER CODE END WHILE */
		 HAL_Delay(500);
		 makeup_water_added++;
		 blowdown_water++;
		 chemical1++;
		 chemical2++;
		 ph_inlet_water++;
		 ph_plant_water++;
		 tds_inlet_water++;
		 tds_plant_water++;
		 pump1_state = !pump1_state;
		 pump2_state = !pump2_state;

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
