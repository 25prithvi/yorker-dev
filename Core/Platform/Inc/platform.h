/**
  ******************************************************************************
  * @file           : platform.h
  * @brief          : Header for platform files.
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

#ifndef __PLATFORM_H
#define __PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "platform_gpio.h"
#include "stm32f4xx_hal.h"
#include "display.h"

extern unsigned long makeup_water_added;
extern unsigned long blowdown_water;

//Error
void Error_Handler(void);

//MISC
void platform_start_yorker(void);

//ADC
void platform_adc_init(void);

//RCC
void platform_sysclk_cfg(void);

//GPIO
void platform_gpio_init(void);

//RTC
void platform_rtc_init(void);

//UART
void platform_uart_init(void);
void lcd_send_cmd(char *pData, int Size);

//Timer
void platform_timer_init(void);
void platform_timer_start(void);
void platform_timer_stop(void);

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_H */

/*****************************END OF FILE****/
