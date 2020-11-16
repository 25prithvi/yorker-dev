/**
  ******************************************************************************
  * @file           : keys.c
  * @brief          : Keys body
  ******************************************************************************
  * @attention
  *
  *
  *
  *
  *
  ******************************************************************************
  */

#include "display.h"
#include "platform_gpio.h"
#include "stm32f4xx_hal.h"

int key_pressed_flag;
int key_pressed = NONE_KEY_PRESSED;

void keys_action(){

	if(HAL_GPIO_ReadPin(LEFT_KEY_GPIO_Port,LEFT_KEY_Pin) == 1 && key_pressed_flag == NONE_KEY_PRESSED )
	{
		key_pressed_flag = LEFT_KEY_PRESSED;
	}
	else if(HAL_GPIO_ReadPin(LEFT_KEY_GPIO_Port,LEFT_KEY_Pin) == 0 && key_pressed_flag == LEFT_KEY_PRESSED)
	{
		key_pressed = LEFT_KEY_PRESSED;
		key_pressed_flag = NONE_KEY_PRESSED;
	}
	else if(HAL_GPIO_ReadPin(RIGHT_KEY_GPIO_Port,RIGHT_KEY_Pin) == 1 && key_pressed_flag == NONE_KEY_PRESSED )
	{
		key_pressed_flag = RIGHT_KEY_PRESSED;
	}
	else if(HAL_GPIO_ReadPin(RIGHT_KEY_GPIO_Port,RIGHT_KEY_Pin) == 0 && key_pressed_flag == RIGHT_KEY_PRESSED)
	{
		key_pressed = RIGHT_KEY_PRESSED;
		key_pressed_flag = NONE_KEY_PRESSED;
	}
	else if(HAL_GPIO_ReadPin(ENTER_KEY_GPIO_Port,ENTER_KEY_Pin) == 1 && key_pressed_flag == NONE_KEY_PRESSED )
	{
		key_pressed_flag = ENTER_KEY_PRESSED;
	}
	else if(HAL_GPIO_ReadPin(ENTER_KEY_GPIO_Port,ENTER_KEY_Pin) == 0 && key_pressed_flag == ENTER_KEY_PRESSED)
	{
		key_pressed = ENTER_KEY_PRESSED;
		key_pressed_flag = NONE_KEY_PRESSED;
	}
	else if(HAL_GPIO_ReadPin(ESC_KEY_GPIO_Port,ESC_KEY_Pin) == 1 && key_pressed_flag == NONE_KEY_PRESSED )
	{
		key_pressed_flag = ESC_KEY_PRESSED;
	}
	else if(HAL_GPIO_ReadPin(ESC_KEY_GPIO_Port,ESC_KEY_Pin) == 0 && key_pressed_flag == ESC_KEY_PRESSED)
	{
		key_pressed = ESC_KEY_PRESSED;
		key_pressed_flag = NONE_KEY_PRESSED;
	}

}
