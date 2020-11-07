/**
  ******************************************************************************
  * @file           : homescreen.c
  * @brief          : Home Screen body
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

char homescreen_cmd[1024] = {0};

void __update_makeup_water_added(char *disp_mwa_cmd, int *disp_mwa_cmd_len)
{
	uint8_t n[6];
	int temp = makeup_water_added;
	for(int i = 0; i < 6; i++)
	{
		n[i] = temp % 10;
		temp = temp / 10;
		*disp_mwa_cmd_len += snprintf (disp_mwa_cmd+(*disp_mwa_cmd_len),1024-(*disp_mwa_cmd_len),"n%d.val=%d%s",i,n[i],end_char);
	}
}

void __update_blowdown_water(char *disp_bd_cmd,int *disp_bd_cmd_len)
{
	uint8_t n[6];
	int temp = blowdown_water;
	for(int i = 0; i < 6; i++)
	{
		n[i] = temp % 10;
		temp = temp / 10;
		*disp_bd_cmd_len += snprintf (disp_bd_cmd+(*disp_bd_cmd_len),1024-(*disp_bd_cmd_len),"n%d.val=%d%s",i+6,n[i],end_char);
	}
}

void homescreen_update()
{
	char homescreen_cmd[1024] = {0};
	int homescreen_cmd_len = 0;
	__update_makeup_water_added(homescreen_cmd,&homescreen_cmd_len);
	__update_blowdown_water(homescreen_cmd,&homescreen_cmd_len);
	lcd_send_cmd(homescreen_cmd,homescreen_cmd_len);

}
