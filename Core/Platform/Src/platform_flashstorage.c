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
#define FLASHCFG_INIT_ADDRESS						0x081D0000

//Homescreen
#define MKUP_WATER_ADDED_PULSE_CNT_ADDRESS	0x081B0000
#define BLOWDOWN_WATER_PULSE_CNT_ADDRESS	0x081B0020
#define CHEMICAL_1_ADDRESS					0x081B0040
#define CHEMICAL_2_ADDRESS					0x081B0060

//Yorker Settings
#define OFFSET_MKUP_WATER_ADDRESS			0x081E0000
#define OFFSET_BLOWDOWN_ADDRESS				0x081E0008
#define PUMP1_LTS_PER_PULSE_ADDRESS			0x081E0016
#define PUMP2_LTS_PER_PULSE_ADDRESS			0x081E0024
#define RATIO_1_ADDRESS						0x081E0040
#define RATIO_2_ADDRESS						0x081E0048
#define AUTO_BLOWDOWN_ADDRESS				0x081E0056
#define SET_BLOWDOWN_TDS					0x081E0064
#define SET_BLOWDOWN_IN_M3					0x081E0072

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
	__FLASH_Program_Word(SET_BLOWDOWN_TDS, flash_yorker_settings->set_blowdown_tds);
	__FLASH_Program_Word(SET_BLOWDOWN_IN_M3, flash_yorker_settings->set_blowdown_in_m3);

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
	flash_yorker_settings->set_blowdown_tds = __FLASH_READ(SET_BLOWDOWN_TDS);
	flash_yorker_settings->set_blowdown_in_m3 = __FLASH_READ(SET_BLOWDOWN_IN_M3);
}
