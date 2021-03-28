/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    display.h
  * @brief   This file contains the headers of the display.
  ******************************************************************************
  * @attention
  *
  *
  *
  *
 ******************************************************************************
  */
/* USER CODE END Header */
#ifndef __DISPLAY_H
#define __DISPLAY_H

#ifdef __cplusplus
 extern "C" {
#endif


extern int key_pressed_flag;
extern int key_pressed;
extern enum {
	NONE_KEY_PRESSED,
	LEFT_KEY_PRESSED,
	RIGHT_KEY_PRESSED,
	ENTER_KEY_PRESSED,
	ESC_KEY_PRESSED,
}key_state;


extern int current_screen_state;
extern int current_edit_settings_state;
extern unsigned char end_char[4];
extern int settings_semaphore;
extern enum {
	GOTO_HOME_SCREEN,
	UPDATE_HOME_SCREEN,
	SETTINGS_SCREEN,
	SETTINGS_SCREEN2,
	ACTIVE_ALARMS_SCREEN,
	HISTORY_ALARMS_SCREEN,
}SCREEN_STATE;

extern enum {
	GOTO_OFFSET_MAKE_UP_WATER,
	OFFSET_MAKE_UP_WATER,
	OFFSET_BLOWDOWN,
	PUMP1_LTS_PER_PULSE,
	PUMP2_LTS_PER_PULSE,
	RATIO_1,
	RATIO_2,
	AUTO_BLOWDOWN,
	SET_BLOWDOWN_TDS,
	SET_COOL_OFF_TIME,
	SET_BLOWDOWN_IN_M3,
	GOTO_SET_INLET_WATER_PH_MIN,
	SET_INLET_WATER_PH_MIN,
	SET_INLET_WATER_PH_MAX,
	SET_INLET_WATER_TDS_MIN,
	SET_INLET_WATER_TDS_MAX,
	SET_PLANT_WATER_PH_MIN,
	SET_PLANT_WATER_PH_MAX,
	SET_PLANT_WATER_TDS_MIN,
	SET_PLANT_WATER_TDS_MAX,
	PUMP1_CAPACITY,
	PUMP2_CAPACITY,
	PROCESSING_RATE,
}EDIT_SETTINGS_SCREEN_STATE;

extern enum	{
	FIRST_DIGIT,
	SECOND_DIGIT,
	THIRD_DIGIT,
	FOURTH_DIGIT,
	FIFTH_DIGIT,
	SIXTH_DIGIT,
}DIGITS_LOC;

//KEYS
void keys_action(void);

//DISPLAY
void (*DisplayActions)();
void display_screens(void);
void display_edit_settings(void);
void display_edit_digits(void);

//HOME SCREEN
void homescreen_update(void);

//SETTINGS
void settings_update(void);
void settings2_update(void);

//ALARMS
void active_alarms_screen_update(void);
void history_alarms_screen_update(void);

#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_H */

/*****************************END OF FILE****/
