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




/*******************************************************************************
 *  PRIVATE
 ******************************************************************************/
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

void __update_chemical1(char *disp_che1_cmd,int *disp_che1_cmd_len)
{
	*disp_che1_cmd_len += snprintf (disp_che1_cmd+(*disp_che1_cmd_len),1024-(*disp_che1_cmd_len),"x2.val=%d%s",chemical1,end_char); //n12 block on display
}

void __update_chemical2(char *disp_che2_cmd,int *disp_che2_cmd_len)
{
	*disp_che2_cmd_len += snprintf (disp_che2_cmd+(*disp_che2_cmd_len),1024-(*disp_che2_cmd_len),"x3.val=%d%s",chemical2,end_char); //n13 block on display
}

void __update_ph_inlet_water(char *disp_ph_inlet_cmd,int *disp_ph_inlet_cmd_len)
{
	*disp_ph_inlet_cmd_len += snprintf (disp_ph_inlet_cmd+(*disp_ph_inlet_cmd_len),1024-(*disp_ph_inlet_cmd_len),"x0.val=%d%s",ph_inlet_water,end_char); //x0 block on display
}

void __update_ph_plant_water(char *disp_ph_plant_cmd,int *disp_ph_plant_cmd_len)
{
	*disp_ph_plant_cmd_len += snprintf (disp_ph_plant_cmd+(*disp_ph_plant_cmd_len),1024-(*disp_ph_plant_cmd_len),"x1.val=%d%s",ph_plant_water,end_char); //x1 block on display
}

void __update_tds_inlet_water(char *disp_tds_inlet_cmd,int *disp_tds_inlet_cmd_len)
{
	*disp_tds_inlet_cmd_len += snprintf (disp_tds_inlet_cmd+(*disp_tds_inlet_cmd_len),1024-(*disp_tds_inlet_cmd_len),"n14.val=%d%s",tds_inlet_water,end_char); //n14 block on display
}

void __update_tds_plant_water(char *disp_tds_plant_cmd,int *disp_tds_plant_cmd_len)
{
	*disp_tds_plant_cmd_len += snprintf (disp_tds_plant_cmd+(*disp_tds_plant_cmd_len),1024-(*disp_tds_plant_cmd_len),"n15.val=%d%s",tds_plant_water,end_char); //n15 block on display
}

void __update_pump1_status(char *disp_pump1_status_cmd,int *disp_pump1_status_cmd_len)
{
	if(pump1_state) //ON State
	{
		*disp_pump1_status_cmd_len += snprintf (disp_pump1_status_cmd+(*disp_pump1_status_cmd_len),1024-(*disp_pump1_status_cmd_len),"p3.pic=3%s",end_char); //p3 block on display
	}
	else //OFF State
	{
		*disp_pump1_status_cmd_len += snprintf (disp_pump1_status_cmd+(*disp_pump1_status_cmd_len),1024-(*disp_pump1_status_cmd_len),"p3.pic=2%s",end_char); //p3 block on display
	}

}

void __update_pump2_status(char *disp_pump2_status_cmd,int *disp_pump2_status_cmd_len)
{
	if(pump2_state) //ON State
	{
		*disp_pump2_status_cmd_len += snprintf (disp_pump2_status_cmd+(*disp_pump2_status_cmd_len),1024-(*disp_pump2_status_cmd_len),"p2.pic=3%s",end_char); //p2 block on display
	}
	else //OFF State
	{
		*disp_pump2_status_cmd_len += snprintf (disp_pump2_status_cmd+(*disp_pump2_status_cmd_len),1024-(*disp_pump2_status_cmd_len),"p2.pic=2%s",end_char); //p2 block on display
	}

}

/*******************************************************************************
 *  PUBLIC
 ******************************************************************************/
void homescreen_update()
{
	char homescreen_cmd[1024] = {0};
	int homescreen_cmd_len = 0;

	__update_makeup_water_added(homescreen_cmd,&homescreen_cmd_len);
	__update_blowdown_water(homescreen_cmd,&homescreen_cmd_len);
	__update_chemical1(homescreen_cmd,&homescreen_cmd_len);
	__update_chemical2(homescreen_cmd,&homescreen_cmd_len);
	__update_ph_inlet_water(homescreen_cmd,&homescreen_cmd_len);
	__update_ph_plant_water(homescreen_cmd,&homescreen_cmd_len);
	__update_tds_inlet_water(homescreen_cmd,&homescreen_cmd_len);
	__update_tds_plant_water(homescreen_cmd,&homescreen_cmd_len);
	__update_pump1_status(homescreen_cmd,&homescreen_cmd_len);
	__update_pump2_status(homescreen_cmd,&homescreen_cmd_len);

	lcd_send_cmd(homescreen_cmd,homescreen_cmd_len);

}
