/**
  ******************************************************************************
  * @file           : alarms_screen.c
  * @brief          : Alarms Screen body
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

void __update_alarms(char *disp_alarm_cmd,int *disp_alarm_cmd_len)
{
	for(int i = 0; i < SIZE_OF_ACTIVE_ALARMS; i++)
	{
		if(active_alarms[i].flag == CONFIRMS_ALERT)
		{
			*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"%02x/%02x/20%x\"%s",(12+(i*3)),active_alarms[i].date,active_alarms[i].month,active_alarms[i].year,end_char);

			*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"%02x:%02x\"%s",(13+(i*3)),active_alarms[i].hours,active_alarms[i].mins,end_char);

			switch(active_alarms[i].alert)
			{
				case CHEMICAL1_LOW:
					*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"Chemical 1 Level-LOW\"%s",(14+(i*3)),end_char);
					break;

				case CHEMICAL2_LOW:
					*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"Chemical 2 Level-LOW\"%s",(14+(i*3)),end_char);
					break;

				case INLET_WATER_PH_HIGH:
					*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"Inlet Water pH-HIGH\"%s",(14+(i*3)),end_char);
					break;

				case PLANT_WATER_PH_HIGH:
					*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"Plant Water pH-HIGH\"%s",(14+(i*3)),end_char);
					break;

				case INLET_WATER_PH_LOW:
					*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"Inlet Water pH-LOW\"%s",(14+(i*3)),end_char);
					break;

				case PLANT_WATER_PH_LOW:
					*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"Plant Water pH-LOW\"%s",(14+(i*3)),end_char);
					break;

				case INLET_WATER_TDS_HIGH:
					*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"Inlet Water TDS-HIGH\"%s",(14+(i*3)),end_char);
					break;

				case PLANT_WATER_TDS_HIGH:
					*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"Plant Water TDS-HIGH\"%s",(14+(i*3)),end_char);
					break;

				case PLANT_WATER_AB_COMPLETE:
					*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"Plant Water Auto Blowdown-COMPLETE\"%s",(14+(i*3)),end_char);
					break;
			}
		}
		else
		{
			*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"-\"%s",(12+(i*3)),end_char);

			*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"-\"%s",(13+(i*3)),end_char);

			*disp_alarm_cmd_len += snprintf (disp_alarm_cmd+(*disp_alarm_cmd_len),1024-(*disp_alarm_cmd_len),"t%d.txt=\"-\"%s",(14+(i*3)),end_char);
		}
	}

}

/*******************************************************************************
 *  PUBLIC
 ******************************************************************************/
void alarms_screen_update()
{
	char alarms_screen_cmd[1024] = {0};
	int alarms_screen_cmd_len = 0;

	if(current_screen_state != ALARMS_SCREEN)
	{
		alarms_screen_cmd_len = sprintf(alarms_screen_cmd,"page 4%s",end_char);
	}

	__update_alarms(alarms_screen_cmd,&alarms_screen_cmd_len);

	lcd_send_cmd(alarms_screen_cmd,alarms_screen_cmd_len);

	active_alarms_updated = 0;
}
