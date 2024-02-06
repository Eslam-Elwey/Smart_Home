
#include "StdTypes.h"
#include "DIO_Int.h"
#include "BUTTON_Int.h"
#include "BUTTON_Cfg.h"


void BUTTON_Init (void) 
{
	u8 i ; 
	
	for (i=0 ; i <TOTAL_BUTTONS ; i++)
	{
		if (button_arr[i].button_press_sig == SIG_LOW)
		{
			DIO_WritePin(button_arr[i].button_pin,HIGH);
		}
		else if (button_arr[i].button_press_sig == SIG_HIGH)
		{
			DIO_WritePin(button_arr[i].button_pin,LOW);
		}
	}
	
}


button_status_t BUTTON_Get_status (u8 but_no)
{
	button_status_t but_ret_status = BUTTON_RELEASED ; 
	if (button_arr[but_no].button_press_sig == SIG_LOW)
	{
		if (0==DIO_ReadPin(button_arr[but_no].button_pin))
		{
			but_ret_status = BUTTON_PRESSED ;
		}
		else 
		{
			but_ret_status = BUTTON_RELEASED ;
		}
	}
	else if (button_arr[but_no].button_press_sig == SIG_HIGH)
	{
		if (1==DIO_ReadPin(button_arr[but_no].button_pin))
		{
			but_ret_status = BUTTON_PRESSED ;
		}
		else
		{
			but_ret_status = BUTTON_RELEASED ;
		}
	}
	
	return but_ret_status ;
}