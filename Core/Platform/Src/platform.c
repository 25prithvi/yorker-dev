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

homescreen_settings yorker_homescreen_settings;

uint8_t save_settings = 0;


RTC_TimeTypeDef cTime = {0};
RTC_DateTypeDef cDate = {0};

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



	 platform_flashcfg_init(&yorker_homescreen_settings, &yorker_settings);

	 platform_timer_start();

	 while (1)
	   {
	     /* USER CODE END WHILE */
		 HAL_Delay(1000);


		 chemical1 = yorker_homescreen_settings.chemical_1;
		 chemical2 = yorker_homescreen_settings.chemical_2;

		 yorker_homescreen_settings.chemical_1++;
		 yorker_homescreen_settings.chemical_2++;

		 ph_inlet_water++;
		 ph_plant_water++;
		 tds_inlet_water++;
		 tds_plant_water++;

		 pump1_state = !pump1_state;
		 pump2_state = !pump2_state;

		makeup_water_added = yorker_homescreen_settings.mkup_water_added_pulse_cnt;
		blowdown_water = yorker_homescreen_settings.blowdown_water_pulse_cnt;

		 if(yorker_homescreen_settings.blowdown_water_pulse_cnt != makeup_water_added)
		 {
			platform_timer_stop();
			//platform_flashcfg_set_homescreen_settings(&yorker_homescreen_settings);
			platform_timer_start();
		 }

		 if(save_settings == 2)// don't remove this
		 {
			platform_timer_stop();
			platform_flashcfg_set_yorker_settings(&yorker_settings);
			platform_timer_start();
			save_settings = 0;
		 }
	     /* USER CODE BEGIN 3 */

		 platform_get_date_and_time(&cDate, &cTime);

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
