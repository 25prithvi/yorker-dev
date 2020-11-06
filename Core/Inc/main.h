/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_PIN_Pin GPIO_PIN_6
#define BUZZER_PIN_GPIO_Port GPIOE
#define POWER_MAINS_Pin GPIO_PIN_13
#define POWER_MAINS_GPIO_Port GPIOC
#define WIFI_UART_TX_Pin GPIO_PIN_2
#define WIFI_UART_TX_GPIO_Port GPIOA
#define WIFI_UART_RX_Pin GPIO_PIN_3
#define WIFI_UART_RX_GPIO_Port GPIOA
#define LCD_UART_RX_Pin GPIO_PIN_7
#define LCD_UART_RX_GPIO_Port GPIOE
#define LCD_UART_TX_Pin GPIO_PIN_8
#define LCD_UART_TX_GPIO_Port GPIOE
#define RELAY_1_Pin GPIO_PIN_13
#define RELAY_1_GPIO_Port GPIOE
#define RELAY_2_Pin GPIO_PIN_14
#define RELAY_2_GPIO_Port GPIOE
#define RELAY_3_Pin GPIO_PIN_15
#define RELAY_3_GPIO_Port GPIOE
#define RELAY_4_Pin GPIO_PIN_10
#define RELAY_4_GPIO_Port GPIOB
#define RELAY_5_Pin GPIO_PIN_11
#define RELAY_5_GPIO_Port GPIOB
#define KEY_5_Pin GPIO_PIN_12
#define KEY_5_GPIO_Port GPIOB
#define LEVEL_SENS_4_Pin GPIO_PIN_13
#define LEVEL_SENS_4_GPIO_Port GPIOB
#define ESC_KEY_Pin GPIO_PIN_14
#define ESC_KEY_GPIO_Port GPIOB
#define LEVEL_SENS_3_Pin GPIO_PIN_15
#define LEVEL_SENS_3_GPIO_Port GPIOB
#define ENTER_KEY_Pin GPIO_PIN_8
#define ENTER_KEY_GPIO_Port GPIOD
#define LEVEL_SENS_2_Pin GPIO_PIN_9
#define LEVEL_SENS_2_GPIO_Port GPIOD
#define RIGHT_KEY_Pin GPIO_PIN_10
#define RIGHT_KEY_GPIO_Port GPIOD
#define LEVEL_SENS_1_Pin GPIO_PIN_11
#define LEVEL_SENS_1_GPIO_Port GPIOD
#define LEFT_KEY_Pin GPIO_PIN_12
#define LEFT_KEY_GPIO_Port GPIOD
#define PULSE_SENS_2_Pin GPIO_PIN_13
#define PULSE_SENS_2_GPIO_Port GPIOD
#define PULSE_SENS_1_Pin GPIO_PIN_14
#define PULSE_SENS_1_GPIO_Port GPIOD
#define LEVEL_SENS_5_Pin GPIO_PIN_6
#define LEVEL_SENS_5_GPIO_Port GPIOC
#define LEVEL_SENS_6_Pin GPIO_PIN_7
#define LEVEL_SENS_6_GPIO_Port GPIOC
#define HEARTBEAT_LED_Pin GPIO_PIN_10
#define HEARTBEAT_LED_GPIO_Port GPIOA
#define RS485_ENABLE_Pin GPIO_PIN_11
#define RS485_ENABLE_GPIO_Port GPIOC
#define RS485_TX_Pin GPIO_PIN_12
#define RS485_TX_GPIO_Port GPIOC
#define RS485_RX_Pin GPIO_PIN_2
#define RS485_RX_GPIO_Port GPIOD
#define RELAY_6_Pin GPIO_PIN_3
#define RELAY_6_GPIO_Port GPIOD
#define RELAY_7_Pin GPIO_PIN_4
#define RELAY_7_GPIO_Port GPIOD
#define RELAY_8_Pin GPIO_PIN_5
#define RELAY_8_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
