/**
  ******************************************************************************
  * @file           : platform_alarms.c
  * @brief          : Platform Alarms body
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


alerts active_alarms[SIZE_OF_ACTIVE_ALARMS];

struct alert_flags{
	uint8_t flag;
	uint8_t seconds;
};

static struct alert_flags chemical1_low_flag;
static struct alert_flags chemical2_low_flag;
static struct alert_flags inlet_water_ph_high_flag;
static struct alert_flags plant_water_ph_high_flag;
static struct alert_flags inlet_water_ph_low_flag;
static struct alert_flags plant_water_ph_low_flag;
static struct alert_flags inlet_water_tds_high_flag;
static struct alert_flags plant_water_tds_high_flag;
static struct alert_flags plant_water_ab_complete_flag;

RTC_TimeTypeDef triggering_time = {0};
RTC_DateTypeDef triggering_date = {0};

uint8_t active_alarms_updated = 0;
/*******************************************************************************
 *  PRIVATE
 ******************************************************************************/
uint8_t
__trigger_time_elapsed(uint8_t init_time, uint8_t current_time)
{
	if(init_time > current_time)
	{
		current_time += 0x60;
	}
	if(current_time - init_time >= 0x10)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void
__add_to_active_alerts(uint8_t new_alert_flag, RTC_DateTypeDef new_alert_date, RTC_TimeTypeDef new_alert_time, uint8_t new_alert)
{
	for(int i = 1 ; i < SIZE_OF_ACTIVE_ALARMS ; i++)
	{
		active_alarms[SIZE_OF_ACTIVE_ALARMS - i].flag = active_alarms[SIZE_OF_ACTIVE_ALARMS - i - 1].flag;
		active_alarms[SIZE_OF_ACTIVE_ALARMS - i].date = active_alarms[SIZE_OF_ACTIVE_ALARMS - i - 1].date;
		active_alarms[SIZE_OF_ACTIVE_ALARMS - i].month = active_alarms[SIZE_OF_ACTIVE_ALARMS - i - 1].month;
		active_alarms[SIZE_OF_ACTIVE_ALARMS - i].year = active_alarms[SIZE_OF_ACTIVE_ALARMS - i - 1].year;
		active_alarms[SIZE_OF_ACTIVE_ALARMS - i].hours = active_alarms[SIZE_OF_ACTIVE_ALARMS - i - 1].hours;
		active_alarms[SIZE_OF_ACTIVE_ALARMS - i].mins = active_alarms[SIZE_OF_ACTIVE_ALARMS - i - 1].mins;
		active_alarms[SIZE_OF_ACTIVE_ALARMS - i].alert = active_alarms[SIZE_OF_ACTIVE_ALARMS - i - 1].alert;
	}

	active_alarms[0].flag = new_alert_flag;
	active_alarms[0].date = new_alert_date.Date;
	active_alarms[0].month = new_alert_date.Month;
	active_alarms[0].year = new_alert_date.Year;
	active_alarms[0].hours = new_alert_time.Hours;
	active_alarms[0].mins = new_alert_time.Minutes;
	active_alarms[0].alert = new_alert;
}

void
__check_chemical1_low_alert()
{
//	if(ph_inlet_water > yorker_settings.set_inlet_water_ph_max && inlet_water_ph_high_flag.flag == NO_ALERT)
//	{
//		inlet_water_ph_high_flag.flag = DETECTS_ALERT;
//		inlet_water_ph_high_flag.seconds = triggering_time.Seconds;
//		HAL_GPIO_WritePin(GPIOA, HEARTBEAT_LED_Pin, GPIO_PIN_SET);
//	}
//	else if(ph_inlet_water > yorker_settings.set_inlet_water_ph_max &&
//			inlet_water_ph_high_flag.flag == DETECTS_ALERT &&
//			__trigger_time_elapsed(inlet_water_ph_high_flag.seconds,triggering_time.Seconds))
//	{
//		inlet_water_ph_high_flag.flag = CONFIRMS_ALERT;
//		inlet_water_ph_high_flag.seconds = triggering_time.Seconds;
//		__add_to_active_alerts(inlet_water_ph_high_flag.flag,triggering_date,triggering_time,CHEMICAL1_LOW);
//		HAL_GPIO_WritePin(GPIOA, HEARTBEAT_LED_Pin, GPIO_PIN_RESET);
//		active_alarms_updated = 1;
//	}
}

void
__check_chemical2_low_alert()
{
//	if(ph_inlet_water > yorker_settings.set_inlet_water_ph_max && inlet_water_ph_high_flag.flag == NO_ALERT)
//	{
//		inlet_water_ph_high_flag.flag = DETECTS_ALERT;
//		inlet_water_ph_high_flag.seconds = triggering_time.Seconds;
//		HAL_GPIO_WritePin(GPIOA, HEARTBEAT_LED_Pin, GPIO_PIN_SET);
//	}
//	else if(ph_inlet_water > yorker_settings.set_inlet_water_ph_max &&
//			inlet_water_ph_high_flag.flag == DETECTS_ALERT &&
//			__trigger_time_elapsed(inlet_water_ph_high_flag.seconds,triggering_time.Seconds))
//	{
//		inlet_water_ph_high_flag.flag = CONFIRMS_ALERT;
//		inlet_water_ph_high_flag.seconds = triggering_time.Seconds;
//		__add_to_active_alerts(inlet_water_ph_high_flag.flag,triggering_date,triggering_time,CHEMICAL2_LOW);
//		HAL_GPIO_WritePin(GPIOA, HEARTBEAT_LED_Pin, GPIO_PIN_RESET);
//		active_alarms_updated = 1;
//	}
}

void
__check_inlet_water_ph_high_alert()
{
	if(ph_inlet_water > yorker_settings.set_inlet_water_ph_max && inlet_water_ph_high_flag.flag == NO_ALERT)
	{
		inlet_water_ph_high_flag.flag = DETECTS_ALERT;
		inlet_water_ph_high_flag.seconds = triggering_time.Seconds;

	}
	else if(ph_inlet_water > yorker_settings.set_inlet_water_ph_max &&
			inlet_water_ph_high_flag.flag == DETECTS_ALERT &&
			__trigger_time_elapsed(inlet_water_ph_high_flag.seconds,triggering_time.Seconds))
	{
		inlet_water_ph_high_flag.flag = CONFIRMS_ALERT;
		inlet_water_ph_high_flag.seconds = triggering_time.Seconds;
		__add_to_active_alerts(inlet_water_ph_high_flag.flag,triggering_date,triggering_time,INLET_WATER_PH_HIGH);
		active_alarms_updated = 1;
	}
}

void
__check_plant_water_ph_high_alert()
{
	if(ph_plant_water > yorker_settings.set_plant_water_ph_max && plant_water_ph_high_flag.flag == NO_ALERT)
	{
		plant_water_ph_high_flag.flag = DETECTS_ALERT;
		plant_water_ph_high_flag.seconds = triggering_time.Seconds;
	}
	else if(ph_plant_water > yorker_settings.set_plant_water_ph_max &&
			plant_water_ph_high_flag.flag == DETECTS_ALERT &&
			__trigger_time_elapsed(plant_water_ph_high_flag.seconds,triggering_time.Seconds))
	{
		plant_water_ph_high_flag.flag = CONFIRMS_ALERT;
		plant_water_ph_high_flag.seconds = triggering_time.Seconds;
		__add_to_active_alerts(plant_water_ph_high_flag.flag,triggering_date,triggering_time,PLANT_WATER_PH_HIGH);
		active_alarms_updated = 1;
	}
}

void
__check_inlet_water_ph_low_alert()
{
	if(ph_inlet_water < yorker_settings.set_inlet_water_ph_min && inlet_water_ph_low_flag.flag == NO_ALERT)
	{
		inlet_water_ph_low_flag.flag = DETECTS_ALERT;
		inlet_water_ph_low_flag.seconds = triggering_time.Seconds;

	}
	else if(ph_inlet_water < yorker_settings.set_inlet_water_ph_min &&
			inlet_water_ph_low_flag.flag == DETECTS_ALERT &&
			__trigger_time_elapsed(inlet_water_ph_low_flag.seconds,triggering_time.Seconds))
	{
		inlet_water_ph_low_flag.flag = CONFIRMS_ALERT;
		inlet_water_ph_low_flag.seconds = triggering_time.Seconds;
		__add_to_active_alerts(inlet_water_ph_low_flag.flag,triggering_date,triggering_time,INLET_WATER_PH_LOW);
		active_alarms_updated = 1;
	}
}

void
__check_plant_water_ph_low_alert()
{
	if(ph_plant_water < yorker_settings.set_plant_water_ph_min && plant_water_ph_low_flag.flag == NO_ALERT)
	{
		plant_water_ph_low_flag.flag = DETECTS_ALERT;
		plant_water_ph_low_flag.seconds = triggering_time.Seconds;
	}
	else if(ph_plant_water < yorker_settings.set_plant_water_ph_min &&
			plant_water_ph_low_flag.flag == DETECTS_ALERT &&
			__trigger_time_elapsed(plant_water_ph_low_flag.seconds,triggering_time.Seconds))
	{
		plant_water_ph_low_flag.flag = CONFIRMS_ALERT;
		plant_water_ph_low_flag.seconds = triggering_time.Seconds;
		__add_to_active_alerts(plant_water_ph_low_flag.flag,triggering_date,triggering_time,PLANT_WATER_PH_LOW);
		active_alarms_updated = 1;
	}
}

void
__check_inlet_water_tds_high_alert()
{
	if(tds_inlet_water > yorker_settings.set_inlet_water_tds_max && inlet_water_tds_high_flag.flag == NO_ALERT)
	{
		inlet_water_tds_high_flag.flag = DETECTS_ALERT;
		inlet_water_tds_high_flag.seconds = triggering_time.Seconds;

	}
	else if(tds_inlet_water > yorker_settings.set_inlet_water_tds_max &&
			inlet_water_tds_high_flag.flag == DETECTS_ALERT &&
			__trigger_time_elapsed(inlet_water_tds_high_flag.seconds,triggering_time.Seconds))
	{
		inlet_water_tds_high_flag.flag = CONFIRMS_ALERT;
		inlet_water_tds_high_flag.seconds = triggering_time.Seconds;
		__add_to_active_alerts(inlet_water_tds_high_flag.flag,triggering_date,triggering_time,INLET_WATER_TDS_HIGH);
		active_alarms_updated = 1;
	}
}

void
__check_plant_water_tds_high_alert()
{
	if(tds_plant_water > yorker_settings.set_plant_water_tds_max && plant_water_tds_high_flag.flag == NO_ALERT)
	{
		plant_water_tds_high_flag.flag = DETECTS_ALERT;
		plant_water_tds_high_flag.seconds = triggering_time.Seconds;
	}
	else if(tds_plant_water > yorker_settings.set_plant_water_tds_max &&
			plant_water_tds_high_flag.flag == DETECTS_ALERT &&
			__trigger_time_elapsed(plant_water_tds_high_flag.seconds,triggering_time.Seconds))
	{
		plant_water_tds_high_flag.flag = CONFIRMS_ALERT;
		plant_water_tds_high_flag.seconds = triggering_time.Seconds;
		__add_to_active_alerts(plant_water_tds_high_flag.flag,triggering_date,triggering_time,PLANT_WATER_TDS_HIGH);
		active_alarms_updated = 1;
	}
}

void
__check_plat_water_ab_complete_alert()
{
//	if(ph_inlet_water > yorker_settings.set_inlet_water_ph_max && inlet_water_ph_high_flag.flag == NO_ALERT)
//	{
//		inlet_water_ph_high_flag.flag = DETECTS_ALERT;
//		inlet_water_ph_high_flag.seconds = triggering_time.Seconds;
//		HAL_GPIO_WritePin(GPIOA, HEARTBEAT_LED_Pin, GPIO_PIN_SET);
//	}
//	else if(ph_inlet_water > yorker_settings.set_inlet_water_ph_max &&
//			inlet_water_ph_high_flag.flag == DETECTS_ALERT &&
//			__trigger_time_elapsed(inlet_water_ph_high_flag.seconds,triggering_time.Seconds))
//	{
//		inlet_water_ph_high_flag.flag = CONFIRMS_ALERT;
//		inlet_water_ph_high_flag.seconds = triggering_time.Seconds;
//		__add_to_active_alerts(inlet_water_ph_high_flag.flag,triggering_date,triggering_time,CHEMICAL2_LOW);
//		HAL_GPIO_WritePin(GPIOA, HEARTBEAT_LED_Pin, GPIO_PIN_RESET);
//		active_alarms_updated = 1;
//	}
}
/*******************************************************************************
 *  PUBLIC
 ******************************************************************************/
void platform_check_alarms()
{
	platform_get_date_and_time(&triggering_date, &triggering_time);

	__check_chemical1_low_alert();
	__check_chemical2_low_alert();
	__check_inlet_water_ph_high_alert();
	__check_plant_water_ph_high_alert();
	__check_inlet_water_ph_low_alert();
	__check_plant_water_ph_low_alert();
	__check_inlet_water_tds_high_alert();
	__check_plant_water_tds_high_alert();
	__check_plat_water_ab_complete_alert();
}
