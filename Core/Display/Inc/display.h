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
extern enum {
	GOTO_HOME_SCREEN,
	UPDATE_HOME_SCREEN,
	SETTINGS_SCREEN,
	ALARMS_SCREEN,
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
	SET_BLOWDOWN_IN_M3,
}EDIT_SETTINGS_SCREEN_STATE;

//KEYS
void keys_action(void);

//DISPLAY
void (*DisplayActions)();
void display_screens(void);
void display_edit_settings(void);

//HOME SCREEN
void homescreen_update(void);

#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_H */

/*****************************END OF FILE****/
