/**
  ******************************************************************************
  * @file           : platform_gpio.h
  * @brief          : Header for platform gpio file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  *
  *
  *
  *
  ******************************************************************************
  */

#ifndef __PLATFORM_GPIO_H
#define __PLATFORM_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#define BUZZER_PIN_Pin GPIO_PIN_6
#define BUZZER_PIN_GPIO_Port GPIOE
#define POWER_MAINS_Pin GPIO_PIN_13
#define POWER_MAINS_GPIO_Port GPIOC
#define WIFI_UART_TX_Pin GPIO_PIN_2
#define WIFI_UART_TX_GPIO_Port GPIOA
#define WIFI_UART_RX_Pin GPIO_PIN_3
#define WIFI_UART_RX_GPIO_Port GPIOA
#define WIFI_RST_Pin GPIO_PIN_4
#define WIFI_RST_GPIO_Port GPIOA
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
#define EEPROM_WP_Pin GPIO_PIN_5
#define EEPROM_WP_GPIO_Port GPIOB
#define EEPROM_SCL_Pin GPIO_PIN_6
#define EEPROM_SCL_GPIO_Port GPIOB
#define EEPROM_SDA_Pin GPIO_PIN_7
#define EEPROM_SDA_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_GPIO_H */

/*****************************END OF FILE****/
