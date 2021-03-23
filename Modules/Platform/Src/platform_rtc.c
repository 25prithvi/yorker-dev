/**
  ******************************************************************************
  * @file           : platform_rtc.c
  * @brief          : Platform RTC body
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

RTC_HandleTypeDef hrtc;

/*******************************************************************************
 *  PRIVATE
 ******************************************************************************/
/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
void __MX_RTC_Init(void)
{
  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
	Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x21;
  sTime.Minutes = 0x35;
  sTime.Seconds = 0x00;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
//  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
//  {
//	Error_Handler();
//  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_MARCH;
  sDate.Date = 0x22;
  sDate.Year = 0x21;

//  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
//  {
//	Error_Handler();
//  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/*******************************************************************************
 *  PUBLIC
 ******************************************************************************/
void platform_rtc_init()
{
	__MX_RTC_Init();
}

void platform_get_date_and_time(RTC_DateTypeDef *cDate, RTC_TimeTypeDef *cTime)
{
	HAL_RTC_GetTime(&hrtc, cTime, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, cDate, RTC_FORMAT_BCD);
}
