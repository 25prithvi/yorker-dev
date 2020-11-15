/**
  ******************************************************************************
  * @file           : edit_setting_screen.c
  * @brief          : Edit Settings Screen body
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


int current_edit_settings_state = GOTO_OFFSET_MAKE_UP_WATER;
char edit_settings_cmd[100];
int edit_settings_cmd_len = 0;


/*******************************************************************************
 *  PRIVATE
 ******************************************************************************/
void
__settings_selection(uint8_t src, uint8_t dest)
{
	edit_settings_cmd_len = sprintf(edit_settings_cmd,"t%d.pco=65535%st%d.pco=63488%s",src,end_char,dest,end_char);
	lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
	key_pressed = NONE_KEY_PRESSED;
}

void
__esc_settings_selection(uint8_t src)
{
	edit_settings_cmd_len = sprintf(edit_settings_cmd,"t%d.pco=65535%s",src,end_char);
	lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
	DisplayActions = display_screens;
	key_pressed = NONE_KEY_PRESSED;
	current_edit_settings_state = GOTO_OFFSET_MAKE_UP_WATER;
}
/*******************************************************************************
 *  PUBLIC
 ******************************************************************************/
void display_edit_settings()
{
	switch(current_edit_settings_state)
	{
		case GOTO_OFFSET_MAKE_UP_WATER:
			edit_settings_cmd_len = sprintf(edit_settings_cmd,"t7.pco=63488%s",end_char);
			lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
			current_edit_settings_state = OFFSET_MAKE_UP_WATER;
			break;

		case OFFSET_MAKE_UP_WATER:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(7,9);
				current_edit_settings_state = OFFSET_BLOWDOWN;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(7,18);
				current_edit_settings_state = SET_BLOWDOWN_IN_M3;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(7);
			}
			break;
		case OFFSET_BLOWDOWN:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(9,19);
				current_edit_settings_state = PUMP1_LTS_PER_PULSE;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(9,7);
				current_edit_settings_state = OFFSET_MAKE_UP_WATER;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(9);
			}
			break;
		case PUMP1_LTS_PER_PULSE:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(19,21);
				current_edit_settings_state = PUMP2_LTS_PER_PULSE;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(19,9);
				current_edit_settings_state = OFFSET_BLOWDOWN;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(19);
			}
			break;
		case PUMP2_LTS_PER_PULSE:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(21,13);
				current_edit_settings_state = RATIO_1;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(21,19);
				current_edit_settings_state = PUMP1_LTS_PER_PULSE;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(21);
			}
			break;
		case RATIO_1:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(13,29);
				current_edit_settings_state = RATIO_2;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(13,21);
				current_edit_settings_state = PUMP2_LTS_PER_PULSE;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(13);
			}
			break;
		case RATIO_2:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(29,24);
				current_edit_settings_state = AUTO_BLOWDOWN;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(29,13);
				current_edit_settings_state = RATIO_1;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(29);
			}
			break;
		case AUTO_BLOWDOWN:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(24,14);
				current_edit_settings_state = SET_BLOWDOWN_TDS;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(24,29);
				current_edit_settings_state = RATIO_2;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(24);
			}
			break;
		case SET_BLOWDOWN_TDS:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(14,18);
				current_edit_settings_state = SET_BLOWDOWN_IN_M3;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(14,24);
				current_edit_settings_state = AUTO_BLOWDOWN;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(14);
			}
			break;
		case SET_BLOWDOWN_IN_M3:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(18,7);
				current_edit_settings_state = OFFSET_MAKE_UP_WATER;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(18,14);
				current_edit_settings_state = SET_BLOWDOWN_TDS;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(18);
			}
			break;
	}
}
