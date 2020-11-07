/**
  ******************************************************************************
  * @file           : platform.c
  * @brief          : Platform body
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

char disp_cmd[50];

void screen_actions(){

	switch (current_screen_state){

	case GOTO_HOME_SCREEN:
		sprintf(disp_cmd,"page 2%s",end_char);
		//lcd_send_cmd(disp_cmd,strlen(disp_cmd));
		current_screen_state = UPDATE_HOME_SCREEN;
		break;


	case UPDATE_HOME_SCREEN:
		break;

	}

}
