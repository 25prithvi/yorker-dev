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
char edit_settings_cmd[300];
int edit_settings_cmd_len = 0;
int settings_semaphore = 0;
static int current_digit_loc = FIRST_DIGIT;
static uint8_t new_digits[6] = {0};
static int new_four_digits = 0;
static uint8_t button_state = 0;
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
	if(save_settings == 1)
	{
		save_settings = 2;
	}
	DisplayActions = display_screens;
	key_pressed = NONE_KEY_PRESSED;
	current_edit_settings_state = GOTO_OFFSET_MAKE_UP_WATER;
}

void
__select_six_digits(uint8_t src)
{
	char select_six_digits_cmd[100] = {0};
	int select_six_digits_cmd_len = 0;
	for(int i = src; i < (src + 6); i++)
	{
		select_six_digits_cmd_len += snprintf (select_six_digits_cmd+select_six_digits_cmd_len,100-select_six_digits_cmd_len,"n%d.pco=63488%s",i,end_char);
	}
	edit_settings_cmd_len = sprintf(edit_settings_cmd,select_six_digits_cmd);
	lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
	DisplayActions = display_edit_digits;
	key_pressed = NONE_KEY_PRESSED;
}

void
__select_four_digits(uint8_t src)
{
	edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.pco=63488%s",src,end_char);
	lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
	DisplayActions = display_edit_digits;
	key_pressed = NONE_KEY_PRESSED;
}

void
__select_button(uint8_t src)
{
	edit_settings_cmd_len = sprintf(edit_settings_cmd,"b%d.pco=63488%sb%d.pco2=63488%s",src,end_char,src,end_char);
	lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
	DisplayActions = display_edit_digits;
	key_pressed = NONE_KEY_PRESSED;
}

void
__store_six_digits(int *set_val, uint8_t onscreen_digit_loc)
{
	onscreen_digit_loc += current_digit_loc;
	if(key_pressed == RIGHT_KEY_PRESSED)
	{
		if(new_digits[current_digit_loc] == 0)
		{
			new_digits[current_digit_loc] = 9;
		}
		else
		{
			new_digits[current_digit_loc]--;
		}
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%s",onscreen_digit_loc,new_digits[current_digit_loc],end_char);
		lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
		key_pressed = NONE_KEY_PRESSED;
	}
	else if(key_pressed == LEFT_KEY_PRESSED)
	{
		if(new_digits[current_digit_loc] == 9)
		{
			new_digits[current_digit_loc] = 0;
		}
		else
		{
			new_digits[current_digit_loc]++;
		}
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%s",onscreen_digit_loc,new_digits[current_digit_loc],end_char);
		lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
		key_pressed = NONE_KEY_PRESSED;
	}
	else if(key_pressed == ENTER_KEY_PRESSED)
	{
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.pco=0%s",onscreen_digit_loc,end_char);
		lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
		key_pressed = NONE_KEY_PRESSED;
		current_digit_loc = (current_digit_loc == SIXTH_DIGIT) ? FIRST_DIGIT : current_digit_loc+1;
		settings_semaphore = 2;
		return;
	}
	else if(key_pressed == ESC_KEY_PRESSED)
	{
		char digit_color_cmd[100] = {0};
		int digit_color_cmd_len = 0;
		for(int i = onscreen_digit_loc; i < (onscreen_digit_loc - current_digit_loc + 6); i++)
		{
			digit_color_cmd_len += snprintf (digit_color_cmd+digit_color_cmd_len,100-digit_color_cmd_len,"n%d.pco=0%s",i,end_char);
		}
		char digit_val_cmd[100] = {0};
		int digit_val_cmd_len = 0;
		int temp = *set_val;
		int digit = 0;
		for(int i = onscreen_digit_loc-current_digit_loc; i < (onscreen_digit_loc - current_digit_loc + 6); i++)
		{
			digit = temp % 10;
			temp = temp / 10;
			digit_val_cmd_len += snprintf (digit_val_cmd+digit_val_cmd_len,100-digit_val_cmd_len,"n%d.val=%d%s",i,digit,end_char);
		}
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"%s%s",digit_color_cmd,digit_val_cmd);
		lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
		settings_semaphore = 0;
		current_digit_loc = FIRST_DIGIT;
		key_pressed = NONE_KEY_PRESSED;
		DisplayActions = display_edit_settings;
		return;
	}
}

void
__check_and_print_four_digits_limit(uint8_t src)
{
	if(new_four_digits < 0)
	{
		new_four_digits = 10000 + new_four_digits;
	}
	else if(new_four_digits > 9999)
	{
		new_four_digits = new_four_digits - 10000;
	}
	edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%s",src,new_four_digits,end_char);
	lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
	key_pressed = NONE_KEY_PRESSED;
}

void
__edit_six_digits(int *settings_val, uint8_t src)
{
	if(settings_semaphore == 0)
	{
		settings_semaphore = 1;
		int temp = *settings_val;
		for(int i = 0; i < 6; i++)
		{
			new_digits[i] = temp % 10;
			temp = temp / 10;
		}
	}
	else
	{
		switch(current_digit_loc)
		{
			case FIRST_DIGIT:
				__store_six_digits(settings_val,src);
				break;
			case SECOND_DIGIT:
				__store_six_digits(settings_val,src);
				break;
			case THIRD_DIGIT:
				__store_six_digits(settings_val,src);
				break;
			case FOURTH_DIGIT:
				__store_six_digits(settings_val,src);
				break;
			case FIFTH_DIGIT:
				__store_six_digits(settings_val,src);
				break;
			case SIXTH_DIGIT:
				__store_six_digits(settings_val,src);
				if(current_digit_loc == FIRST_DIGIT && settings_semaphore == 2)
				{
					save_settings = 1;
					DisplayActions = display_edit_settings;
					settings_semaphore = 0;
					*settings_val = 0;
					int place_val = 1;
					for(int i = 0 ; i < 6; i++)
					{
						*settings_val += new_digits[i] * place_val;
						place_val *= 10;
					}
				}
				break;
		}
	}
}

void
__edit_four_digits(int *settings_val, uint8_t src)
{
	if(settings_semaphore == 0)
	{
		settings_semaphore = 1;
		new_four_digits = *settings_val;
	}
	else if(settings_semaphore == 1)
	{
		if(key_pressed == LEFT_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			new_four_digits++;
			__check_and_print_four_digits_limit(src);
		}
		else if(key_pressed == RIGHT_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			new_four_digits--;
			__check_and_print_four_digits_limit(src);
		}
		else if(key_pressed == ENTER_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			settings_semaphore++;
			key_pressed = NONE_KEY_PRESSED;
		}
		else if(key_pressed == ESC_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%sn%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
			settings_semaphore = 0;
			key_pressed = NONE_KEY_PRESSED;
			DisplayActions = display_edit_settings;
		}
	}
	else if(settings_semaphore == 2)
	{
		if(key_pressed == LEFT_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			new_four_digits+=10;
			__check_and_print_four_digits_limit(src);
		}
		else if(key_pressed == RIGHT_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			new_four_digits-=10;
			__check_and_print_four_digits_limit(src);
		}
		else if(key_pressed == ENTER_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			*settings_val = new_four_digits;
			settings_semaphore=0;
			edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%sn%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
			key_pressed = NONE_KEY_PRESSED;
			save_settings = 1;
			DisplayActions = display_edit_settings;
		}
		else if(key_pressed == ESC_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%sn%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
			settings_semaphore = 0;
			key_pressed = NONE_KEY_PRESSED;
			DisplayActions = display_edit_settings;
		}
	}
}

void
__edit_button_selection(uint8_t *settings_val)
{
	if(key_pressed == LEFT_KEY_PRESSED)
	{
		button_state = 1;
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"b1.pco=63488%sb1.pco2=63488%sb0.pco=65535%sb1.pco2=65535%s",end_char,end_char,end_char,end_char);
		lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
		key_pressed = NONE_KEY_PRESSED;
	}
	else if(key_pressed == RIGHT_KEY_PRESSED)
	{
		button_state = 0;
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"b0.pco=63488%sb0.pco2=63488%sb1.pco=65535%sb1.pco2=65535%s",end_char,end_char,end_char,end_char);
		lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
		key_pressed = NONE_KEY_PRESSED;
	}
	else if(key_pressed == ENTER_KEY_PRESSED)
	{
		*settings_val = button_state;
		if(button_state == 0)
		{
			edit_settings_cmd_len = sprintf(edit_settings_cmd,"b0.pic=6%sb1.pic=5%sb1.pco=65535%sb1.pco2=65535%sb0.pco=65535%sb0.pco2=65535%s",end_char,end_char,end_char,end_char,end_char,end_char);
		}
		else if(button_state == 1)
		{
			edit_settings_cmd_len = sprintf(edit_settings_cmd,"b1.pic=4%sb0.pic=5%sb1.pco=65535%sb1.pco2=65535%sb0.pco=65535%sb0.pco2=65535%s",end_char,end_char,end_char,end_char,end_char,end_char);
		}

		lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
		key_pressed = NONE_KEY_PRESSED;
		save_settings = 1;
		DisplayActions = display_edit_settings;
	}
	else if(key_pressed == ESC_KEY_PRESSED)
	{
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"b1.pco=65535%sb1.pco2=65535%sb0.pco=65535%sb0.pco2=65535%s",end_char,end_char,end_char,end_char);
		lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
		key_pressed = NONE_KEY_PRESSED;
		DisplayActions = display_edit_settings;
	}
}

void __update_offset_makeup_water_added(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	uint8_t n[6];
	int temp = yorker_settings.offset_mkupwater;
	for(int i = 0; i < 6; i++)
	{
		n[i] = temp % 10;
		temp = temp / 10;
		*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%s",i,n[i],end_char);
	}
}

void __update_offset_blowdown_water(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	uint8_t n[6];
	int temp = yorker_settings.offset_blowdown;
	for(int i = 0; i < 6; i++)
	{
		n[i] = temp % 10;
		temp = temp / 10;
		*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%s",i+6,n[i],end_char);
	}
}

void __update_pump1_lts_per_pulse(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	uint8_t n[6];
	int temp = yorker_settings.pump1_lts_per_pulse;
	for(int i = 0; i < 6; i++)
	{
		n[i] = temp % 10;
		temp = temp / 10;
		*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%s",i+12,n[i],end_char);
	}
}

void __update_pump2_lts_per_pulse(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	uint8_t n[6];
	int temp = yorker_settings.pump2_lts_per_pulse;
	for(int i = 0; i < 6; i++)
	{
		n[i] = temp % 10;
		temp = temp / 10;
		*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%s",i+18,n[i],end_char);
	}
}

void __update_ratio_1(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%s",24,yorker_settings.ratio_1,end_char);
}

void __update_ratio_2(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%s",25,yorker_settings.ratio_2,end_char);
}

void __update_auto_blowdown(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	if( yorker_settings.auto_blowdown == 0)
	{
		*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"b0.pic=6%sb1.pic=5%sb1.pco=65535%sb1.pco2=65535%sb0.pco=65535%sb0.pco2=65535%s",end_char,end_char,end_char,end_char,end_char,end_char);
	}
	else if(yorker_settings.auto_blowdown == 1)
	{
		*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"b1.pic=4%sb0.pic=5%sb1.pco=65535%sb1.pco2=65535%sb0.pco=65535%sb0.pco2=65535%s",end_char,end_char,end_char,end_char,end_char,end_char);
	}
}

void __update_set_blowdown_tds(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%s",26,yorker_settings.set_blowdown_tds,end_char);
}

void __update_set_blowdown_in_m3(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	uint8_t n[6];
	int temp = yorker_settings.set_blowdown_in_m3;
	for(int i = 0; i < 6; i++)
	{
		n[i] = temp % 10;
		temp = temp / 10;
		*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%s",i+27,n[i],end_char);
	}
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
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_six_digits(0);
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
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_six_digits(6);
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
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_six_digits(12);
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
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_six_digits(18);
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
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_four_digits(24);
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
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_four_digits(25);
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
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_button(0);
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
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_four_digits(26);
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
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_six_digits(27);
			}
			break;
	}
}

void display_edit_digits()
{
	switch(current_edit_settings_state)
	{
		case OFFSET_MAKE_UP_WATER:
			__edit_six_digits(&yorker_settings.offset_mkupwater,0);
			break;
		case OFFSET_BLOWDOWN:
			__edit_six_digits(&yorker_settings.offset_blowdown,6);
			break;
		case PUMP1_LTS_PER_PULSE:
			__edit_six_digits(&yorker_settings.pump1_lts_per_pulse,12);
			break;
		case PUMP2_LTS_PER_PULSE:
			__edit_six_digits(&yorker_settings.pump2_lts_per_pulse,18);
			break;
		case RATIO_1:
			__edit_four_digits(&yorker_settings.ratio_1,24);
			break;
		case RATIO_2:
			__edit_four_digits(&yorker_settings.ratio_2,25);
			break;
		case AUTO_BLOWDOWN:
			__edit_button_selection(&yorker_settings.auto_blowdown);
			break;
		case SET_BLOWDOWN_TDS:
			__edit_four_digits(&yorker_settings.set_blowdown_tds,26);
			break;
		case SET_BLOWDOWN_IN_M3:
			__edit_six_digits(&yorker_settings.set_blowdown_in_m3,27);
			break;
	}
}

void settings_update()
{
	char settings_cmd[1024] = {0};
	int settings_cmd_len = 0;

	settings_cmd_len = sprintf(settings_cmd,"page 1%s",end_char);
	__update_offset_makeup_water_added(settings_cmd,&settings_cmd_len);
	__update_offset_blowdown_water(settings_cmd,&settings_cmd_len);
	__update_pump1_lts_per_pulse(settings_cmd,&settings_cmd_len);
	__update_pump2_lts_per_pulse(settings_cmd,&settings_cmd_len);
	__update_ratio_1(settings_cmd,&settings_cmd_len);
	__update_ratio_2(settings_cmd,&settings_cmd_len);
	__update_auto_blowdown(settings_cmd,&settings_cmd_len);
	__update_set_blowdown_tds(settings_cmd,&settings_cmd_len);
	__update_set_blowdown_in_m3(settings_cmd,&settings_cmd_len);

	lcd_send_cmd(settings_cmd,settings_cmd_len);
}
