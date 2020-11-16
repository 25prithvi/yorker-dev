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
#include "stdbool.h"

extern unsigned int makeup_water_added;
extern unsigned int blowdown_water;
extern unsigned int chemical1;
extern unsigned int chemical2;
extern uint16_t ph_inlet_water;
extern uint16_t ph_plant_water;
extern uint16_t tds_inlet_water;
extern uint16_t tds_plant_water;
extern bool pump1_state;
extern bool pump2_state;

typedef struct{
	int offset_mkupwater;
	int offset_blowdown;
	int pump1_lts_per_pulse;
	int pump2_lts_per_pulse;
	int ratio_1;
	int ratio_2;
	uint8_t auto_blowdown;
	int set_blowdown_tds;
	int set_blowdown_in_m3;
}settings;

extern settings yorker_settings;
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

//Display
void platform_display_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_H */

/*****************************END OF FILE****/
