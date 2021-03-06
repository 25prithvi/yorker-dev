/**
  ******************************************************************************
  * @file           : platform_flashstorage.c
  * @brief          : Platform Flash Storage body
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

//Initialise

//Homescreen
#define MKUP_WATER_ADDED_PULSE_CNT_ADDRESS	0x081B0000
#define BLOWDOWN_WATER_PULSE_CNT_ADDRESS	0x081B0020
#define CHEMICAL_1_ADDRESS					0x081B0040
#define CHEMICAL_2_ADDRESS					0x081B0060

//Yorker Settings
#define OFFSET_MKUP_WATER_ADDRESS			0x081E0000
#define OFFSET_BLOWDOWN_ADDRESS				0x081E0008
#define PUMP1_LTS_PER_PULSE_ADDRESS			0x081E0024
#define PUMP2_LTS_PER_PULSE_ADDRESS			0x081E0040
#define RATIO_1_ADDRESS						0x081E0048
#define RATIO_2_ADDRESS						0x081E0064
#define AUTO_BLOWDOWN_ADDRESS				0x081E0080
#define SET_BLOWDOWN_TDS_ADDRESS			0x081E0088
#define SET_COOL_OFF_TIME_ADDRESS			0x081E0104
#define SET_BLOWDOWN_IN_M3_ADDRESS			0x081E0120
//PAGE2
#define SET_INLET_WATER_PH_MIN_ADDRESS		0x081E0128
#define SET_INLET_WATER_PH_MAX_ADDRESS		0x081E0144
#define SET_INLET_WATER_TDS_MIN_ADDRESS		0x081E0160
#define SET_INLET_WATER_TDS_MAX_ADDRESS		0x081E0168
#define SET_PLANT_WATER_PH_MIN_ADDRESS		0x081E0184
#define SET_PLANT_WATER_PH_MAX_ADDRESS		0x081E0200
#define SET_PLANT_WATER_TDS_MIN_ADDRESS		0x081E0208
#define SET_PLANT_WATER_TDS_MAX_ADDRESS		0x081E0224
#define PUMP1_CAPACITY_ADDRESS				0x081E0240
#define PUMP2_CAPACITY_ADDRESS				0x081E0248
#define PROCESSING_RATE_ADDRESS				0x081E0264

//HISTORY ALARMS
#define HISTORY_ALARMS_FLAG_ADDRESS			0x081C0000
#define HISTORY_ALARMS_DATE_ADDRESS			0x081C0004
#define HISTORY_ALARMS_MONTH_ADDRESS		0x081C0008
#define HISTORY_ALARMS_YEAR_ADDRESS			0x081C000C
#define HISTORY_ALARMS_HOURS_ADDRESS		0x081C0010
#define HISTORY_ALARMS_MINS_ADDRESS			0x081C0014
#define HISTORY_ALARMS_ALERT_ADDRESS		0x081C0018

/*******************************************************************************
 *  PRIVATE
 ******************************************************************************/

void __FLASH_Program_Word(uint32_t Address, uint32_t Data){
  /* Check the parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

  HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data);
}

uint32_t __FLASH_READ(uint32_t Flash_address){
	uint32_t Flash_data;

	Flash_data = *(uint32_t*) Flash_address;

	return Flash_data;

}

//void __flashcfg_init(uint32_t *flashcfg)
//{
//	HAL_FLASH_Unlock();
//
//	FLASH_Erase_Sector(FLASH_SECTOR_22,FLASH_VOLTAGE_RANGE_3);
//
//	__FLASH_Program_Word(FLASHCFG_INIT_ADDRESS, &flashcfg);
//
//	HAL_Delay(2);
//
//	HAL_FLASH_Lock();
//}

/*******************************************************************************
 *  PRIVATE
 ******************************************************************************/
void platform_flashcfg_init(homescreen_settings *flashcfg_yorker_homescreen_settings, settings *flashcfg_yorker_settings)
{
//	uint32_t *check_flash_init;
//	*check_flash_init = __FLASH_READ(FLASHCFG_INIT_ADDRESS);
//
//	if(check_flash_init != 2873)
//	{
		flashcfg_yorker_homescreen_settings->mkup_water_added_pulse_cnt = 0;
		flashcfg_yorker_homescreen_settings->blowdown_water_pulse_cnt = 0;
		flashcfg_yorker_homescreen_settings->chemical_1 = 0;
		flashcfg_yorker_homescreen_settings->chemical_2 = 0;
//
//		platform_flashcfg_set_homescreen_settings(flashcfg_yorker_homescreen_settings);
//
//		check_flash_init = 2873;
//		__flashcfg_init(check_flash_init);
//	}
//	else
//	{
		platform_flashcfg_get_homescreen_settings(flashcfg_yorker_homescreen_settings);
		platform_flashcfg_get_yorker_settings(flashcfg_yorker_settings);
		platform_flashcfg_get_history_alarms();
//	}
}

void platform_flashcfg_set_homescreen_settings(homescreen_settings *flash_yorker_homescreen_settings)
{
	HAL_FLASH_Unlock();

	FLASH_Erase_Sector(FLASH_SECTOR_21,FLASH_VOLTAGE_RANGE_3);

	__FLASH_Program_Word(MKUP_WATER_ADDED_PULSE_CNT_ADDRESS, flash_yorker_homescreen_settings->mkup_water_added_pulse_cnt);
	__FLASH_Program_Word(BLOWDOWN_WATER_PULSE_CNT_ADDRESS, flash_yorker_homescreen_settings->blowdown_water_pulse_cnt);
	__FLASH_Program_Word(CHEMICAL_1_ADDRESS, flash_yorker_homescreen_settings->chemical_1);
	__FLASH_Program_Word(CHEMICAL_2_ADDRESS, flash_yorker_homescreen_settings->chemical_2);

	HAL_Delay(2);

	HAL_FLASH_Lock();
}

void platform_flashcfg_get_homescreen_settings(homescreen_settings *flash_yorker_homescreen_settings)
{
	flash_yorker_homescreen_settings->mkup_water_added_pulse_cnt = __FLASH_READ(MKUP_WATER_ADDED_PULSE_CNT_ADDRESS);
	flash_yorker_homescreen_settings->blowdown_water_pulse_cnt = __FLASH_READ(BLOWDOWN_WATER_PULSE_CNT_ADDRESS);
	flash_yorker_homescreen_settings->chemical_1 = __FLASH_READ(CHEMICAL_1_ADDRESS);
	flash_yorker_homescreen_settings->chemical_2 = __FLASH_READ(CHEMICAL_2_ADDRESS);
}

void platform_flashcfg_set_yorker_settings(settings *flash_yorker_settings)
{
	HAL_FLASH_Unlock();

	FLASH_Erase_Sector(FLASH_SECTOR_23,FLASH_VOLTAGE_RANGE_3);

	__FLASH_Program_Word(OFFSET_MKUP_WATER_ADDRESS, flash_yorker_settings->offset_mkupwater);
	__FLASH_Program_Word(OFFSET_BLOWDOWN_ADDRESS, flash_yorker_settings->offset_blowdown);
	__FLASH_Program_Word(PUMP1_LTS_PER_PULSE_ADDRESS, flash_yorker_settings->pump1_lts_per_pulse);
	__FLASH_Program_Word(PUMP2_LTS_PER_PULSE_ADDRESS, flash_yorker_settings->pump2_lts_per_pulse);
	__FLASH_Program_Word(RATIO_1_ADDRESS, flash_yorker_settings->ratio_1);
	__FLASH_Program_Word(RATIO_2_ADDRESS, flash_yorker_settings->ratio_2);
	__FLASH_Program_Word(AUTO_BLOWDOWN_ADDRESS, flash_yorker_settings->auto_blowdown);
	__FLASH_Program_Word(SET_BLOWDOWN_TDS_ADDRESS, flash_yorker_settings->set_blowdown_tds);
	__FLASH_Program_Word(SET_COOL_OFF_TIME_ADDRESS, flash_yorker_settings->set_cool_off_time);
	__FLASH_Program_Word(SET_BLOWDOWN_IN_M3_ADDRESS, flash_yorker_settings->set_blowdown_in_m3);
	__FLASH_Program_Word(SET_INLET_WATER_PH_MIN_ADDRESS, flash_yorker_settings->set_inlet_water_ph_min);
	__FLASH_Program_Word(SET_INLET_WATER_PH_MAX_ADDRESS, flash_yorker_settings->set_inlet_water_ph_max);
	__FLASH_Program_Word(SET_INLET_WATER_TDS_MIN_ADDRESS, flash_yorker_settings->set_inlet_water_tds_min);
	__FLASH_Program_Word(SET_INLET_WATER_TDS_MAX_ADDRESS, flash_yorker_settings->set_inlet_water_tds_max);
	__FLASH_Program_Word(SET_PLANT_WATER_PH_MIN_ADDRESS, flash_yorker_settings->set_plant_water_ph_min);
	__FLASH_Program_Word(SET_PLANT_WATER_PH_MAX_ADDRESS, flash_yorker_settings->set_plant_water_ph_max);
	__FLASH_Program_Word(SET_PLANT_WATER_TDS_MIN_ADDRESS, flash_yorker_settings->set_plant_water_tds_min);
	__FLASH_Program_Word(SET_PLANT_WATER_TDS_MAX_ADDRESS, flash_yorker_settings->set_plant_water_tds_max);
	__FLASH_Program_Word(PUMP1_CAPACITY_ADDRESS, flash_yorker_settings->pump1_capacity);
	__FLASH_Program_Word(PUMP2_CAPACITY_ADDRESS, flash_yorker_settings->pump2_capacity);
	__FLASH_Program_Word(PROCESSING_RATE_ADDRESS, flash_yorker_settings->processing_rate);

	HAL_Delay(2);

	HAL_FLASH_Lock();
}

void platform_flashcfg_get_yorker_settings(settings *flash_yorker_settings)
{
	flash_yorker_settings->offset_mkupwater = __FLASH_READ(OFFSET_MKUP_WATER_ADDRESS);
	flash_yorker_settings->offset_blowdown = __FLASH_READ(OFFSET_BLOWDOWN_ADDRESS);
	flash_yorker_settings->pump1_lts_per_pulse = __FLASH_READ(PUMP1_LTS_PER_PULSE_ADDRESS);
	flash_yorker_settings->pump2_lts_per_pulse = __FLASH_READ(PUMP2_LTS_PER_PULSE_ADDRESS);
	flash_yorker_settings->ratio_1 = __FLASH_READ(RATIO_1_ADDRESS);
	flash_yorker_settings->ratio_2 = __FLASH_READ(RATIO_2_ADDRESS);
	flash_yorker_settings->auto_blowdown = __FLASH_READ(AUTO_BLOWDOWN_ADDRESS);
	flash_yorker_settings->set_blowdown_tds = __FLASH_READ(SET_BLOWDOWN_TDS_ADDRESS);
	flash_yorker_settings->set_cool_off_time = __FLASH_READ(SET_COOL_OFF_TIME_ADDRESS);
	flash_yorker_settings->set_blowdown_in_m3 = __FLASH_READ(SET_BLOWDOWN_IN_M3_ADDRESS);
	flash_yorker_settings->set_inlet_water_ph_min = __FLASH_READ(SET_INLET_WATER_PH_MIN_ADDRESS);
	flash_yorker_settings->set_inlet_water_ph_max = __FLASH_READ(SET_INLET_WATER_PH_MAX_ADDRESS);
	flash_yorker_settings->set_inlet_water_tds_min = __FLASH_READ(SET_INLET_WATER_TDS_MIN_ADDRESS);
	flash_yorker_settings->set_inlet_water_tds_max = __FLASH_READ(SET_INLET_WATER_TDS_MAX_ADDRESS);
	flash_yorker_settings->set_plant_water_ph_min = __FLASH_READ(SET_PLANT_WATER_PH_MIN_ADDRESS);
	flash_yorker_settings->set_plant_water_ph_max = __FLASH_READ(SET_PLANT_WATER_PH_MAX_ADDRESS);
	flash_yorker_settings->set_plant_water_tds_min = __FLASH_READ(SET_PLANT_WATER_TDS_MIN_ADDRESS);
	flash_yorker_settings->set_plant_water_tds_max = __FLASH_READ(SET_PLANT_WATER_TDS_MAX_ADDRESS);
	flash_yorker_settings->pump1_capacity = __FLASH_READ(PUMP1_CAPACITY_ADDRESS);
	flash_yorker_settings->pump2_capacity = __FLASH_READ(PUMP2_CAPACITY_ADDRESS);
	flash_yorker_settings->processing_rate = __FLASH_READ(PROCESSING_RATE_ADDRESS);

}

void platform_flashcfg_set_history_alarms()
{
	HAL_FLASH_Unlock();

	FLASH_Erase_Sector(FLASH_SECTOR_22,FLASH_VOLTAGE_RANGE_3);

	for(int i = 0; i < SIZE_OF_ACTIVE_ALARMS; i++)
	{
		__FLASH_Program_Word(HISTORY_ALARMS_FLAG_ADDRESS + (i * 0x1C), history_alarms[i].flag);
		__FLASH_Program_Word(HISTORY_ALARMS_DATE_ADDRESS + (i * 0x1C), history_alarms[i].date);
		__FLASH_Program_Word(HISTORY_ALARMS_MONTH_ADDRESS + (i * 0x1C), history_alarms[i].month);
		__FLASH_Program_Word(HISTORY_ALARMS_YEAR_ADDRESS + (i * 0x1C), history_alarms[i].year);
		__FLASH_Program_Word(HISTORY_ALARMS_HOURS_ADDRESS + (i * 0x1C), history_alarms[i].hours);
		__FLASH_Program_Word(HISTORY_ALARMS_MINS_ADDRESS + (i * 0x1C), history_alarms[i].mins);
		__FLASH_Program_Word(HISTORY_ALARMS_ALERT_ADDRESS + (i * 0x1C), history_alarms[i].alert);
	}

	HAL_Delay(2);

	HAL_FLASH_Lock();
}

void platform_flashcfg_get_history_alarms()
{
	for(int i = 0; i < SIZE_OF_ACTIVE_ALARMS; i++)
	{
		history_alarms[i].flag = __FLASH_READ(HISTORY_ALARMS_FLAG_ADDRESS + (i * 0x1C));
		history_alarms[i].date = __FLASH_READ(HISTORY_ALARMS_DATE_ADDRESS + (i * 0x1C));
		history_alarms[i].month = __FLASH_READ(HISTORY_ALARMS_MONTH_ADDRESS + (i * 0x1C));
		history_alarms[i].year = __FLASH_READ(HISTORY_ALARMS_YEAR_ADDRESS + (i * 0x1C));
		history_alarms[i].hours = __FLASH_READ(HISTORY_ALARMS_HOURS_ADDRESS + (i * 0x1C));
		history_alarms[i].mins = __FLASH_READ(HISTORY_ALARMS_MINS_ADDRESS + (i * 0x1C));
		history_alarms[i].alert = __FLASH_READ(HISTORY_ALARMS_ALERT_ADDRESS + (i * 0x1C));
	}
}
