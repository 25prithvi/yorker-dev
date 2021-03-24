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

extern uint8_t save_settings;
typedef struct{
	int offset_mkupwater;
	int offset_blowdown;
	int pump1_lts_per_pulse;
	int pump2_lts_per_pulse;
	int ratio_1;
	int ratio_2;
	uint8_t auto_blowdown;
	int set_blowdown_tds;
	int set_cool_off_time;
	int set_blowdown_in_m3;
	int set_inlet_water_ph_min;
	int set_inlet_water_ph_max;
	int set_inlet_water_tds_min;
	int set_inlet_water_tds_max;
	int set_outlet_water_ph_min;
	int set_outlet_water_ph_max;
	int set_outlet_water_tds_min;
	int set_outlet_water_tds_max;
	int pump1_capacity;
	int pump2_capacity;
	int processing_rate;
}settings;

extern settings yorker_settings;

typedef struct{
	unsigned long mkup_water_added_pulse_cnt;
	unsigned long blowdown_water_pulse_cnt;
	unsigned int chemical_1;
	unsigned int chemical_2;
}homescreen_settings;

extern homescreen_settings yorker_homescreen_settings;

extern uint32_t pulse1_cnt_flag;
extern uint32_t pulse2_cnt_flag;

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
void platform_get_date_and_time(RTC_DateTypeDef *cDate, RTC_TimeTypeDef *cTime);

//UART
void platform_uart_init(void);
void lcd_send_cmd(char *pData, int Size);
void wifi_send_cmd(char *pData, int Size);

//Timer
void platform_timer_init(void);
void platform_timer_start(void);
void platform_timer_stop(void);

//Display
void platform_display_init(void);

//Flash Storage
void platform_flashcfg_init(homescreen_settings *flashcfg_yorker_homescreen_settings, settings *flashcfg_yorker_settings);
void platform_flashcfg_set_homescreen_settings(homescreen_settings *flash_yorker_homescreen_settings);
void platform_flashcfg_get_homescreen_settings(homescreen_settings *flash_yorker_homescreen_settings);
void platform_flashcfg_set_yorker_settings(settings *flash_yorker_settings);
void platform_flashcfg_get_yorker_settings(settings *flash_yorker_settings);

//I2C
void platform_i2c_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_H */

/*****************************END OF FILE****/
