
#include "StdTypes.h"
#include "DIO_Int.h"
#include "LED_Int.h"
#include "LED_Cfg.h"



void LED_Init(void)
{
	u8 i ; 
	for (i=0;i<LED_TOTAL_NUMBERS;i++)
	{
		if(led_arr[i].volt==ACTIVE_HIGH)
		{
			DIO_WritePin(led_arr[i].led_pin_no,LOW);
		}
		else
		{
			DIO_WritePin(led_arr[i].led_pin_no,HIGH);
		}
	}
}

void LED_Turn_On (u8 led_no)
{
	if(led_arr[led_no].volt==ACTIVE_HIGH)
	{
		DIO_WritePin(led_arr[led_no].led_pin_no,HIGH);
	}
	else 
	{
		DIO_WritePin(led_arr[led_no].led_pin_no,LOW);
	}
	
}


void LED_Turn_Off (u8 led_no)
{
	if(led_arr[led_no].volt==ACTIVE_HIGH)
	{
		DIO_WritePin(led_arr[led_no].led_pin_no,LOW);
	}
	else
	{
		DIO_WritePin(led_arr[led_no].led_pin_no,HIGH);
	}
	
}


void LED_Toggle_state (u8 led_no)
{
	DIO_Toggle_Pin(led_arr[led_no].led_pin_no);
}
	
void LED_Count_turn_on (u8 led_count)
{
	u8 i ; 
	for (i=0;i<led_count;i++)
	{
		if(led_arr[i].volt==ACTIVE_HIGH)
		{
			DIO_WritePin(led_arr[i].led_pin_no,HIGH);
		}
		else
		{
			DIO_WritePin(led_arr[i].led_pin_no,LOW);
		}
	}
}