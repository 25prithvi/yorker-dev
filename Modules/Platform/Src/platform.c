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
#include "stdio.h"
#include "string.h"

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

IWDG_HandleTypeDef hiwdg; //

static void MX_IWDG_Init(void); //

RTC_TimeTypeDef cTime = {0};
RTC_DateTypeDef cDate = {0};

static uint8_t hours;
static uint8_t mins;

char wifi_cmd[1024] = {0};
int wifi_cmd_len = 0;

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
	 platform_i2c_init();

	 //MX_IWDG_Init(); //

	 platform_flashcfg_init(&yorker_homescreen_settings, &yorker_settings);

	 platform_timer_start();

	 HAL_Delay(1000);
	 HAL_GPIO_WritePin(GPIOA, WIFI_RST_Pin, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOA, HEARTBEAT_LED_Pin, GPIO_PIN_RESET);

	 HAL_Delay(1000);
	 HAL_GPIO_WritePin(GPIOA, WIFI_RST_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOA, HEARTBEAT_LED_Pin, GPIO_PIN_RESET);

	 HAL_Delay(1000);
	 HAL_GPIO_WritePin(GPIOA, WIFI_RST_Pin, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOA, HEARTBEAT_LED_Pin, GPIO_PIN_RESET);
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

		 if(ph_inlet_water > 140 || ph_plant_water > 140)
		 {
			 ph_inlet_water = 0;
			 ph_plant_water = 0;
		 }

		 if(cTime.Minutes != mins)
		 {
			 mins = cTime.Minutes;
			 wifi_cmd_len = sprintf(wifi_cmd, "waterQuality={\"WaterQualityDateTime\":\"20%02x-%02x-%02xT%02x:%02x:%02x\",\"MakeUpWater\":%d,\"BlowdownWater\":%d,\"pHInletWater\":%0.1f,\"pHPlantWater\":%0.1f,\"TDSInletWater\":%d,\"TDSPlantWater\":%d,\"DosingSystemID\":1003,\"WaterQualityChemicals\":[{\"ChemicalID\":3,\"Chemicalkgs\":1.1,\"PumpStatus\":true,\"TankStatus\":1},{\"ChemicalID\":4,\"Chemicalkgs\":0.6,\"PumpStatus\":true,\"TankStatus\":1}]}",cDate.Year,cDate.Month,cDate.Date,cTime.Hours,cTime.Minutes,cTime.Seconds,makeup_water_added,blowdown_water,(ph_inlet_water/10.0),(ph_plant_water/10.0),tds_inlet_water,tds_plant_water);
			 wifi_send_cmd(wifi_cmd,wifi_cmd_len);
		 }
	   }
}


/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

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
