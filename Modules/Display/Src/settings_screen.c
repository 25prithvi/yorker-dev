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
static int new_input_digits = 0;
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
__esc_settings_selection(uint8_t src, int8_t float_src, int8_t int_src)
{
	if(int_src != -1)
	{
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"t%d.pco=65535%sn%d.bco=65535%s",src,end_char,int_src,end_char);
	}
	else if(float_src != -1)
	{
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"t%d.pco=65535%sx%d.bco=65535%s",src,end_char,float_src,end_char);
	}
	else
	{
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"t%d.pco=65535%s",src,end_char);
	}
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
__select_digits(uint8_t src, uint8_t has_float)
{
	if(has_float != 1)
	{
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.pco=63488%s",src,end_char);
	}
	else
	{
			edit_settings_cmd_len = sprintf(edit_settings_cmd,"x%d.pco=63488%s",src,end_char);
	}
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
	if(new_input_digits < 0)
	{
		new_input_digits = 10000 + new_input_digits;
	}
	else if(new_input_digits > 9999)
	{
		new_input_digits = new_input_digits - 10000;
	}
	edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%s",src,new_input_digits,end_char);
	lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
	key_pressed = NONE_KEY_PRESSED;
}

void
__check_and_print_two_digits_limit(uint8_t src, uint8_t has_float, uint8_t has_ph)
{
	uint8_t max_limit = 99;
	if(has_ph == 1)
	{
		max_limit = 140;
	}
	if(new_input_digits < 0)
	{
		new_input_digits = (max_limit+1) + new_input_digits;
	}
	else if(new_input_digits > max_limit)
	{
		new_input_digits = new_input_digits - (max_limit+1);
	}
	if(has_float != 1)
	{
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%s",src,new_input_digits,end_char);
	}
	else
	{
		edit_settings_cmd_len = sprintf(edit_settings_cmd,"x%d.val=%d%s",src,new_input_digits,end_char);
	}
	lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
	key_pressed = NONE_KEY_PRESSED;
}

void
__check_and_print_time_limit(uint8_t src)
{
	if(new_input_digits < 0)
	{
		new_input_digits = 2425 + new_input_digits;
	}
	else if(new_input_digits > 2400)
	{
		new_input_digits = new_input_digits - 2425;
	}
	edit_settings_cmd_len = sprintf(edit_settings_cmd,"x%d.val=%d%s",src,new_input_digits,end_char);
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
__edit_digits(int *settings_val, uint8_t src, uint8_t no_of_digits, uint8_t has_float, uint8_t has_ph)
{
	if(settings_semaphore == 0)
	{
		settings_semaphore = 1;
		new_input_digits = *settings_val;
	}
	else if(settings_semaphore == 1)
	{
		if(key_pressed == LEFT_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			new_input_digits++;
			if(no_of_digits == 4)
			{
				__check_and_print_four_digits_limit(src);
			}
			else if(no_of_digits == 2)
			{
				__check_and_print_two_digits_limit(src,has_float,has_ph);
			}
		}
		else if(key_pressed == RIGHT_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			new_input_digits--;
			if(no_of_digits == 4)
			{
				__check_and_print_four_digits_limit(src);
			}
			else if(no_of_digits == 2)
			{
				__check_and_print_two_digits_limit(src,has_float,has_ph);
			}
		}
		else if(key_pressed == ENTER_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			settings_semaphore++;
			key_pressed = NONE_KEY_PRESSED;
		}
		else if(key_pressed == ESC_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			if(has_float != 1)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%sn%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			}
			else
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"x%d.val=%d%sx%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			}
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
			new_input_digits+=10;
			if(no_of_digits == 4)
			{
				__check_and_print_four_digits_limit(src);
			}
			else if(no_of_digits == 2)
			{
				__check_and_print_two_digits_limit(src,has_float,has_ph);
			}
		}
		else if(key_pressed == RIGHT_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			new_input_digits-=10;
			if(no_of_digits == 4)
			{
				__check_and_print_four_digits_limit(src);
			}
			else if(no_of_digits == 2)
			{
				__check_and_print_two_digits_limit(src,has_float,has_ph);
			}
		}
		else if(key_pressed == ENTER_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			*settings_val = new_input_digits;
			settings_semaphore=0;
			if(has_float != 1)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%sn%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			}
			else
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"x%d.val=%d%sx%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			}
			lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
			key_pressed = NONE_KEY_PRESSED;
			save_settings = 1;
			DisplayActions = display_edit_settings;
		}
		else if(key_pressed == ESC_KEY_PRESSED && key_pressed_flag == NONE_KEY_PRESSED)
		{
			if(has_float != 1)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"n%d.val=%d%sn%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			}
			else
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"x%d.val=%d%sx%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			}
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

void
__edit_cool_down_time(int *settings_val, uint8_t src)
{
	if(settings_semaphore == 0)
		{
			settings_semaphore = 1;
			new_input_digits = *settings_val;
			if(new_input_digits % 25 !=0 )
			{
				new_input_digits = (new_input_digits/25) * 25;
			}
		}

	else if(settings_semaphore == 1)
	{
		if(key_pressed == LEFT_KEY_PRESSED)
		{
			new_input_digits += 25;
			__check_and_print_time_limit(src);
		}
		else if(key_pressed == RIGHT_KEY_PRESSED)
		{
			new_input_digits -= 25;
			__check_and_print_time_limit(src);
		}
		else if(key_pressed == ENTER_KEY_PRESSED)
		{
			*settings_val = new_input_digits;
			edit_settings_cmd_len = sprintf(edit_settings_cmd,"x%d.val=%d%sx%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
			settings_semaphore = 0;
			key_pressed = NONE_KEY_PRESSED;
			save_settings = 1;
			DisplayActions = display_edit_settings;
		}
		else if(key_pressed == ESC_KEY_PRESSED)
		{
			edit_settings_cmd_len = sprintf(edit_settings_cmd,"x%d.val=%d%sx%d.pco=0%s",src, *settings_val,end_char,src,end_char);
			lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
			settings_semaphore = 0;
			key_pressed = NONE_KEY_PRESSED;
			DisplayActions = display_edit_settings;
		}
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

void __update_set_cool_off_time(char *disp_cft_cmd, int *disp_cft_cmd_len)
{
	*disp_cft_cmd_len += snprintf (disp_cft_cmd+(*disp_cft_cmd_len),1024-(*disp_cft_cmd_len),"x%d.val=%d%s",0,yorker_settings.set_cool_off_time,end_char);
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

void __update_inlet_water_ph(char *disp_cft_cmd, int *disp_cft_cmd_len)
{
	*disp_cft_cmd_len += snprintf (disp_cft_cmd+(*disp_cft_cmd_len),1024-(*disp_cft_cmd_len),"x%d.val=%d%sx%d.val=%d%s",0,yorker_settings.set_inlet_water_ph_min,end_char,1,yorker_settings.set_inlet_water_ph_max,end_char);
}

void __update_inlet_water_tds(char *disp_cft_cmd, int *disp_cft_cmd_len)
{
	*disp_cft_cmd_len += snprintf (disp_cft_cmd+(*disp_cft_cmd_len),1024-(*disp_cft_cmd_len),"n%d.val=%d%sn%d.val=%d%s",2,yorker_settings.set_inlet_water_tds_min,end_char,3,yorker_settings.set_inlet_water_tds_max,end_char);
}

void __update_plant_water_ph(char *disp_cft_cmd, int *disp_cft_cmd_len)
{
	*disp_cft_cmd_len += snprintf (disp_cft_cmd+(*disp_cft_cmd_len),1024-(*disp_cft_cmd_len),"x%d.val=%d%sx%d.val=%d%s",2,yorker_settings.set_plant_water_ph_min,end_char,3,yorker_settings.set_plant_water_ph_max,end_char);
}

void __update_plant_water_tds(char *disp_cft_cmd, int *disp_cft_cmd_len)
{
	*disp_cft_cmd_len += snprintf (disp_cft_cmd+(*disp_cft_cmd_len),1024-(*disp_cft_cmd_len),"n%d.val=%d%sn%d.val=%d%s",7,yorker_settings.set_plant_water_tds_min,end_char,6,yorker_settings.set_plant_water_tds_max,end_char);
}

void __update_pump_capacity(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%sn%d.val=%d%s",8,yorker_settings.pump1_capacity,end_char,9,yorker_settings.pump2_capacity,end_char);
}

void __update_processing_rate(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%s",10,yorker_settings.processing_rate,end_char);
}
/*******************************************************************************
 *  PUBLIC
 ******************************************************************************/
void display_edit_settings()
{
	if(current_screen_state == SETTINGS_SCREEN2 && current_edit_settings_state == GOTO_OFFSET_MAKE_UP_WATER)
	{
		current_edit_settings_state = GOTO_SET_INLET_WATER_PH_MIN;
	}
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
				__esc_settings_selection(7,-1,-1);
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
				__esc_settings_selection(9,-1,-1);
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
				__esc_settings_selection(19,-1,-1);
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
				__esc_settings_selection(21,-1,-1);
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
				__esc_settings_selection(13,-1,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(24,0);
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
				__esc_settings_selection(29,-1,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(25,0);
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
				__esc_settings_selection(24,-1,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_button(0);
			}
			break;
		case SET_BLOWDOWN_TDS:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(14,23);
				current_edit_settings_state = SET_COOL_OFF_TIME;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(14,24);
				current_edit_settings_state = AUTO_BLOWDOWN;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(14,-1,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(26,0);
			}
			break;
		case SET_COOL_OFF_TIME:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				__settings_selection(23,18);
				current_edit_settings_state = SET_BLOWDOWN_IN_M3;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				__settings_selection(23,14);
				current_edit_settings_state = SET_BLOWDOWN_TDS;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(23,-1,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(0,1);
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
				__settings_selection(18,23);
				current_edit_settings_state = SET_COOL_OFF_TIME;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(18,-1,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_six_digits(27);
			}
			break;
		case GOTO_SET_INLET_WATER_PH_MIN:
			edit_settings_cmd_len = sprintf(edit_settings_cmd,"t7.pco=63488%sx0.bco=33808%s",end_char,end_char);
			lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
			current_edit_settings_state = SET_INLET_WATER_PH_MIN;
			break;
		case SET_INLET_WATER_PH_MIN:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"x0.bco=65535%sx1.bco=33808%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_INLET_WATER_PH_MAX;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t7.pco=65535%sx0.bco=65535%st15.pco=63488%s",end_char,end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = PROCESSING_RATE;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(7,0,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(0,1);
			}
			break;
		case SET_INLET_WATER_PH_MAX:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t7.pco=65535%sx1.bco=65535%st8.pco=63488%sn2.bco=33808%s",end_char,end_char,end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_INLET_WATER_TDS_MIN;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"x1.bco=65535%sx0.bco=33808%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_INLET_WATER_PH_MIN;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(7,1,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(1,1);
			}
			break;
		case SET_INLET_WATER_TDS_MIN:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"n2.bco=65535%sn3.bco=33808%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_INLET_WATER_TDS_MAX;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t8.pco=65535%sn2.bco=65535%st7.pco=63488%sx1.bco=33808%s",end_char,end_char,end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_INLET_WATER_PH_MAX;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(8,-1,2);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(2,0);
			}
			break;
		case SET_INLET_WATER_TDS_MAX:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t8.pco=65535%sn3.bco=65535%st9.pco=63488%sx2.bco=33808%s",end_char,end_char,end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_PLANT_WATER_PH_MIN;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"n3.bco=65535%sn2.bco=33808%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_INLET_WATER_TDS_MIN;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(8,-1,3);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(3,0);
			}
			break;
		case SET_PLANT_WATER_PH_MIN:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"x2.bco=65535%sx3.bco=33808%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_PLANT_WATER_PH_MAX;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t9.pco=65535%sx2.bco=65535%st8.pco=63488%sn3.bco=33808%s",end_char,end_char,end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_INLET_WATER_TDS_MAX;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(9,2,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(2,1);
			}
			break;
		case SET_PLANT_WATER_PH_MAX:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t9.pco=65535%sx3.bco=65535%st10.pco=63488%sn7.bco=33808%s",end_char,end_char,end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_PLANT_WATER_TDS_MIN;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"x3.bco=65535%sx2.bco=33808%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_PLANT_WATER_PH_MIN;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(9,3,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(3,1);
			}
			break;
		case SET_PLANT_WATER_TDS_MIN:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"n7.bco=65535%sn6.bco=33808%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_PLANT_WATER_TDS_MAX;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t10.pco=65535%sn7.bco=65535%st9.pco=63488%sx3.bco=33808%s",end_char,end_char,end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_PLANT_WATER_PH_MAX;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(10,-1,7);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(7,0);
			}
			break;
		case SET_PLANT_WATER_TDS_MAX:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t10.pco=65535%sn6.bco=65535%st13.pco=63488%s",end_char,end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = PUMP1_CAPACITY;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"n6.bco=65535%sn7.bco=33808%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_PLANT_WATER_TDS_MIN;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(10,-1,6);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(6,0);
			}
			break;
		case PUMP1_CAPACITY:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t13.pco=65535%st14.pco=63488%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = PUMP2_CAPACITY;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t13.pco=65535%st10.pco=63488%sn6.bco=33808%s",end_char,end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_PLANT_WATER_TDS_MAX;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(13,-1,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(8,0);
			}
			break;
		case PUMP2_CAPACITY:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t14.pco=65535%st15.pco=63488%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = PROCESSING_RATE;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t14.pco=65535%st13.pco=63488%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = PUMP1_CAPACITY;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(14,-1,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(9,0);
			}
			break;
		case PROCESSING_RATE:
			if(key_pressed == RIGHT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t15.pco=65535%st7.pco=63488%sx0.bco=33808%s",end_char,end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = SET_INLET_WATER_PH_MIN;
			}
			else if(key_pressed == LEFT_KEY_PRESSED)
			{
				edit_settings_cmd_len = sprintf(edit_settings_cmd,"t15.pco=65535%st14.pco=63488%s",end_char,end_char);
				lcd_send_cmd(edit_settings_cmd,edit_settings_cmd_len);
				key_pressed = NONE_KEY_PRESSED;
				current_edit_settings_state = PUMP2_CAPACITY;
			}
			else if(key_pressed == ESC_KEY_PRESSED)
			{
				__esc_settings_selection(15,-1,-1);
			}
			else if(key_pressed == ENTER_KEY_PRESSED)
			{
				__select_digits(10,0);
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
			__edit_digits(&yorker_settings.ratio_1,24,4,0,0);
			break;
		case RATIO_2:
			__edit_digits(&yorker_settings.ratio_2,25,4,0,0);
			break;
		case AUTO_BLOWDOWN:
			__edit_button_selection(&yorker_settings.auto_blowdown);
			break;
		case SET_BLOWDOWN_TDS:
			__edit_digits(&yorker_settings.set_blowdown_tds,26,4,0,0);
			break;
		case SET_COOL_OFF_TIME:
			__edit_cool_down_time(&yorker_settings.set_cool_off_time,0);
			break;
		case SET_BLOWDOWN_IN_M3:
			__edit_six_digits(&yorker_settings.set_blowdown_in_m3,27);
			break;
		case SET_INLET_WATER_PH_MIN:
			__edit_digits(&yorker_settings.set_inlet_water_ph_min,0,2,1,1);
			break;
		case SET_INLET_WATER_PH_MAX:
			__edit_digits(&yorker_settings.set_inlet_water_ph_max,1,2,1,1);
			break;
		case SET_INLET_WATER_TDS_MIN:
			__edit_digits(&yorker_settings.set_inlet_water_tds_min,2,4,0,0);
			break;
		case SET_INLET_WATER_TDS_MAX:
			__edit_digits(&yorker_settings.set_inlet_water_tds_max,3,4,0,0);
			break;
		case SET_PLANT_WATER_PH_MIN:
			__edit_digits(&yorker_settings.set_plant_water_ph_min,2,2,1,1);
			break;
		case SET_PLANT_WATER_PH_MAX:
			__edit_digits(&yorker_settings.set_plant_water_ph_max,3,2,1,1);
			break;
		case SET_PLANT_WATER_TDS_MIN:
			__edit_digits(&yorker_settings.set_plant_water_tds_min,7,4,0,0);
			break;
		case SET_PLANT_WATER_TDS_MAX:
			__edit_digits(&yorker_settings.set_plant_water_tds_max,6,4,0,0);
			break;
		case PUMP1_CAPACITY:
			__edit_digits(&yorker_settings.pump1_capacity,8,2,0,0);
			break;
		case PUMP2_CAPACITY:
			__edit_digits(&yorker_settings.pump2_capacity,9,2,0,0);
			break;
		case PROCESSING_RATE:
			__edit_digits(&yorker_settings.processing_rate,10,4,0,0);
			break;
	}
}

void settings_update()
{
	char settings_cmd[1024] = {0};
	int settings_cmd_len = 0;

	settings_cmd_len = sprintf(settings_cmd,"page 2%s",end_char);
	__update_offset_makeup_water_added(settings_cmd,&settings_cmd_len);
	__update_offset_blowdown_water(settings_cmd,&settings_cmd_len);
	__update_pump1_lts_per_pulse(settings_cmd,&settings_cmd_len);
	__update_pump2_lts_per_pulse(settings_cmd,&settings_cmd_len);
	__update_ratio_1(settings_cmd,&settings_cmd_len);
	__update_ratio_2(settings_cmd,&settings_cmd_len);
	__update_auto_blowdown(settings_cmd,&settings_cmd_len);
	__update_set_blowdown_tds(settings_cmd,&settings_cmd_len);
	__update_set_cool_off_time(settings_cmd,&settings_cmd_len);
	__update_set_blowdown_in_m3(settings_cmd,&settings_cmd_len);

	lcd_send_cmd(settings_cmd,settings_cmd_len);
}

void settings2_update()
{
	char settings_cmd[1024] = {0};
	int settings_cmd_len = 0;

	settings_cmd_len = sprintf(settings_cmd,"page 3%s",end_char);
	__update_inlet_water_ph(settings_cmd,&settings_cmd_len);
	__update_inlet_water_tds(settings_cmd,&settings_cmd_len);
	__update_plant_water_ph(settings_cmd,&settings_cmd_len);
	__update_plant_water_tds(settings_cmd,&settings_cmd_len);
	__update_pump_capacity(settings_cmd,&settings_cmd_len);
	__update_processing_rate(settings_cmd,&settings_cmd_len);

	lcd_send_cmd(settings_cmd,settings_cmd_len);
}
