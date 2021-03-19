/**
  ******************************************************************************
  * @file           : platform_gpio.c
  * @brief          : Platform GPIO body
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
#include "platform_gpio.h"
#include "stm32f4xx_hal.h"


/*******************************************************************************
 *  PRIVATE
 ******************************************************************************/
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void __MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, BUZZER_PIN_Pin|RELAY_1_Pin|RELAY_2_Pin|RELAY_3_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(WIFI_RST_GPIO_Port, WIFI_RST_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, RELAY_4_Pin|RELAY_5_Pin|EEPROM_WP_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(HEARTBEAT_LED_GPIO_Port, HEARTBEAT_LED_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(RS485_ENABLE_GPIO_Port, RS485_ENABLE_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, RELAY_6_Pin|RELAY_7_Pin|RELAY_8_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : BUZZER_PIN_Pin RELAY_1_Pin RELAY_2_Pin RELAY_3_Pin */
	GPIO_InitStruct.Pin = BUZZER_PIN_Pin|RELAY_1_Pin|RELAY_2_Pin|RELAY_3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pins : POWER_MAINS_Pin LEVEL_SENS_5_Pin LEVEL_SENS_6_Pin */
	GPIO_InitStruct.Pin = POWER_MAINS_Pin|LEVEL_SENS_5_Pin|LEVEL_SENS_6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : WIFI_RST_Pin */
	GPIO_InitStruct.Pin = WIFI_RST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(WIFI_RST_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : RELAY_4_Pin RELAY_5_Pin */
	GPIO_InitStruct.Pin = RELAY_4_Pin|RELAY_5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : KEY_5_Pin LEVEL_SENS_4_Pin ESC_KEY_Pin LEVEL_SENS_3_Pin */
	GPIO_InitStruct.Pin = KEY_5_Pin|LEVEL_SENS_4_Pin|ESC_KEY_Pin|LEVEL_SENS_3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : ENTER_KEY_Pin LEVEL_SENS_2_Pin RIGHT_KEY_Pin LEVEL_SENS_1_Pin
						   LEFT_KEY_Pin PULSE_SENS_2_Pin PULSE_SENS_1_Pin */
	GPIO_InitStruct.Pin = ENTER_KEY_Pin|LEVEL_SENS_2_Pin|RIGHT_KEY_Pin|LEVEL_SENS_1_Pin
						  |LEFT_KEY_Pin|PULSE_SENS_2_Pin|PULSE_SENS_1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pin : HEARTBEAT_LED_Pin */
	GPIO_InitStruct.Pin = HEARTBEAT_LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(HEARTBEAT_LED_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : RS485_ENABLE_Pin */
	GPIO_InitStruct.Pin = RS485_ENABLE_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RS485_ENABLE_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : RELAY_6_Pin RELAY_7_Pin RELAY_8_Pin */
	GPIO_InitStruct.Pin = RELAY_6_Pin|RELAY_7_Pin|RELAY_8_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pin : EEPROM_WP_Pin */
	GPIO_InitStruct.Pin = EEPROM_WP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(EEPROM_WP_GPIO_Port, &GPIO_InitStruct);

}


/*******************************************************************************
 *  PUBLIC
 ******************************************************************************/
/**
  * @brief Platform GPIO Initialization Function
  * @param None
  * @retval None
  */
void platform_gpio_init()
{
	__MX_GPIO_Init();
}
