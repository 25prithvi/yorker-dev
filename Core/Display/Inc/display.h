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
extern enum {
	GOTO_HOME_SCREEN,
	UPDATE_HOME_SCREEN,
}SCREEN_STATE;


//KEYS
void keys_action(void);

//DISPLAY
void screen_actions(void);

#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_H */

/*****************************END OF FILE****/
