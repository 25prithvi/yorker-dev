/**
  ******************************************************************************
  * @file           : display.c
  * @brief          : display body
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
#include "display.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"

int current_screen_state = GOTO_HOME_SCREEN;
int past_screen_state = GOTO_HOME_SCREEN;

unsigned char end_char[4] = {0xff,0xff,0xff,'\0'};
char disp_cmd[100];
int disp_cmd_len = 0;

void display_screens(){

	switch (current_screen_state){

	case GOTO_HOME_SCREEN:
		disp_cmd_len = sprintf(disp_cmd,"page 1%s",end_char);
		lcd_send_cmd(disp_cmd,disp_cmd_len);
		current_screen_state = UPDATE_HOME_SCREEN;
		break;


	case UPDATE_HOME_SCREEN:
		if(key_pressed == NONE_KEY_PRESSED)
		{
			homescreen_update();
		}
		else if(key_pressed == RIGHT_KEY_PRESSED)
		{
			settings_update();
//			disp_cmd_len = sprintf(disp_cmd,"page 1%s",end_char);
//			lcd_send_cmd(disp_cmd,disp_cmd_len);
			key_pressed = NONE_KEY_PRESSED;
			current_screen_state = SETTINGS_SCREEN;
		}
		else if(key_pressed == LEFT_KEY_PRESSED)
		{
			disp_cmd_len = sprintf(disp_cmd,"page 4%s",end_char);
			lcd_send_cmd(disp_cmd,disp_cmd_len);
			key_pressed = NONE_KEY_PRESSED;
			current_screen_state = ALARMS_SCREEN;
		}
		break;

	case SETTINGS_SCREEN:
		if(key_pressed == NONE_KEY_PRESSED)
		{
//			if(save_settings == 2)
//			{
//				settings_update();
//			}
		}
		else if(key_pressed == RIGHT_KEY_PRESSED)
		{
			settings2_update();
//			disp_cmd_len = sprintf(disp_cmd,"page 2%s",end_char);
//			lcd_send_cmd(disp_cmd,disp_cmd_len);
			key_pressed = NONE_KEY_PRESSED;
			current_screen_state = SETTINGS_SCREEN2;
		}
		else if(key_pressed == LEFT_KEY_PRESSED)
		{
			disp_cmd_len = sprintf(disp_cmd,"page 1%s",end_char);
			lcd_send_cmd(disp_cmd,disp_cmd_len);
			key_pressed = NONE_KEY_PRESSED;
			current_screen_state = UPDATE_HOME_SCREEN;
		}
		else if(key_pressed == ENTER_KEY_PRESSED)
		{
			DisplayActions = display_edit_settings;
			key_pressed = NONE_KEY_PRESSED;
		}
		break;

	case SETTINGS_SCREEN2:
		if(key_pressed == NONE_KEY_PRESSED)
		{
//			if(save_settings == 2)
//			{
//				settings2_update();
//			}
		}
		else if(key_pressed == RIGHT_KEY_PRESSED)
		{
			disp_cmd_len = sprintf(disp_cmd,"page 4%s",end_char);
			lcd_send_cmd(disp_cmd,disp_cmd_len);
			key_pressed = NONE_KEY_PRESSED;
			current_screen_state = ALARMS_SCREEN;
		}
		else if(key_pressed == LEFT_KEY_PRESSED)
		{
			settings_update();
//			disp_cmd_len = sprintf(disp_cmd,"page 1%s",end_char);
//			lcd_send_cmd(disp_cmd,disp_cmd_len);
			key_pressed = NONE_KEY_PRESSED;
			current_screen_state = SETTINGS_SCREEN;
		}
		else if(key_pressed == ENTER_KEY_PRESSED)
		{
			DisplayActions = display_edit_settings;
			key_pressed = NONE_KEY_PRESSED;
		}
		break;

	case ALARMS_SCREEN:
		if(key_pressed == NONE_KEY_PRESSED)
		{

		}
		else if(key_pressed == RIGHT_KEY_PRESSED)
		{
			disp_cmd_len = sprintf(disp_cmd,"page 1%s",end_char);
			lcd_send_cmd(disp_cmd,disp_cmd_len);
			key_pressed = NONE_KEY_PRESSED;
			current_screen_state = UPDATE_HOME_SCREEN;
		}
		else if(key_pressed == LEFT_KEY_PRESSED)
		{
			settings2_update();
//			disp_cmd_len = sprintf(disp_cmd,"page 2%s",end_char);
//			lcd_send_cmd(disp_cmd,disp_cmd_len);
			key_pressed = NONE_KEY_PRESSED;
			current_screen_state = SETTINGS_SCREEN2;
		}
		break;

	}

}
