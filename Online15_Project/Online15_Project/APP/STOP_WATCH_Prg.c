
#include "StdTypes.h"
#include "STOP_WATCH_Int.h"
#include "SEVEN_SEG_Int.h"
#include "BUTTON_Int.h"
#include "LED_Int.h"
#define F_CPU				8000000UL
#include <util/delay.h>



void Stop_Watch_Runnable(void)
{
	static char x = STOP_TIME , flag2 = 0 , y= STOP_TIME, temp , first_digit , adj_flag1 = 0 , adj_flag2 = 0 ;
	static int i , j  ;
	static char flag1 ;
	static state_t but_state = pause ;
	static reset_t reset_state = RESET_OFF ;
	static mode_t mode_state = RUNNABLE ;
	if(BUTTON_PRESSED == BUTTON_Get_status(SET_MODE))
	{
		for (i=0;i<ADJUST_DELAY;i++)
		{
			SEVEN_SEG_MUX2D_Write(0,x);
		}
		_delay_ms(PRESS_DELAY);
		if (0==flag2)
		{
			mode_state ^= 0xFF ;
			flag2 = 1 ;
			
		}
		
	}
	else
	{
		flag2 = 0 ;
	}
	
	
#if ADJUST_METHOD == ONE_BUTTON_INCREASE_OTHER_DECREASE

	if (ADJUST==mode_state)
	{
		but_state = pause ;
		if (BUTTON_PRESSED == BUTTON_Get_status(ADJUST_INCREASE))
		{
			_delay_ms(PRESS_DELAY);
			x++ ;
			
		}
		
		if(BUTTON_PRESSED == BUTTON_Get_status(ADJUST_DECREASE))
		{
			_delay_ms(PRESS_DELAY);
			x--;
		}
		
		if (x>=100)
		{
			x=0 ;
			
		}
		
		for (i=0;i<ADJUST_DELAY;i++)
		{
			SEVEN_SEG_MUX2D_Write(0,x);
		}
		
		y = x ;
		
	}
	
#elif ADJUST_METHOD == ONE_BUTTON_INCREASE_10_OTHER_INCREASE_1
	
	if (ADJUST==mode_state)
	{
		first_digit = y % 10 ;
		temp = (y/10) * 10 ;
		
		but_state = pause ;
		if (BUTTON_PRESSED == BUTTON_Get_status(ADJUST_INCREASE_10))
		{
			_delay_ms(PRESS_DELAY);
			if (0==adj_flag1)
			{
				x+=10 ;
				adj_flag1 = 1 ;
				if (x>=100)
				{
					x=first_digit ;
				}
			}
			
		}
		else
		{
			adj_flag1 = 0 ;
		}
		
		if(!BUTTON_Get_status(ADJUST_INCREASE_1))
		{
			_delay_ms(PRESS_DELAY);
			if (0==adj_flag2)
			{
				x++ ;
				adj_flag2 = 1 ;
			}
			
			
			if (x>=temp+10)
			{
				x = temp ;
			}
		}
		else
		{
			adj_flag2 = 0 ;
		}
		for (i=0;i<ADJUST_DELAY;i++)
		{
			SEVEN_SEG_MUX2D_Write(0,x);
		}
		
		if (x>=100)
		{
			x=first_digit ;
			for (i=0;i<ADJUST_DELAY;i++)
			{
				SEVEN_SEG_MUX2D_Write(0,x);
			}
		}
		
		if (0==x)
		{
			x=1 ;
		}
		y = x ;
		
	}

#endif

	else if (RUNNABLE==mode_state)
	{
		if (0==x)
		{
			x=1 ;
			y=x ;
		}
		if (resume == but_state)
		{
			if (0==flag1)
			{
				flag1 = 1 ;
			}
			else
			{
				x-- ;
			}
		}
		
		else
		{
			flag1 = 0 ;
		}
		
		if(RESET_ON==reset_state)
		{
			x = y ;
			flag1 = 0 ;
			but_state = pause ;
			reset_state = RESET_OFF ;
			BUZZER_TURN_OFF();
		}
		
		for (i=0;i<SEG_SHOW_DELAY;i++)
		{
			SEVEN_SEG_MUX2D_Write(0,x);
			if (0==x)
			{
				break ;
			}
			
			if(BUTTON_PRESSED == BUTTON_Get_status(SET_MODE))
			{
				_delay_ms(PRESS_DELAY);
				if (0==flag2)
				{
					mode_state ^= 0xFF ;
					flag2 = 1 ;
				}
				break ;
			}
			
			if (BUTTON_PRESSED == BUTTON_Get_status(REUME_PAUSE))
			{
				
				but_state ^= 0xFF ;
				while(BUTTON_PRESSED == BUTTON_Get_status(REUME_PAUSE))
				{
					SEVEN_SEG_MUX2D_Write(0,x);
				}
				break;
			}
			
			if(BUTTON_PRESSED == BUTTON_Get_status(RESET))
			{
				reset_state = RESET_ON ;
				while(BUTTON_PRESSED == BUTTON_Get_status(RESET))
				{
					SEVEN_SEG_MUX2D_Write(0,x);
				}
				break;
			}
			
		}
		
		if (0==x)
		{
			
			BUZZER_TURN_ON();
			for (i=0;i<BUZZER_DELAY_TIME;i++)
			{
				SEVEN_SEG_MUX2D_Write(0,0);
				LED_Toggle_state(0) ;
				LED_Toggle_state(1) ;
				LED_Toggle_state(2) ;
				LED_Toggle_state(3) ;
				LED_Toggle_state(4) ;
				LED_Toggle_state(5) ;
				LED_Toggle_state(6) ;
				for (j=0 ; j <10 ;j++)
				{
					SEVEN_SEG_MUX2D_Write(0,0);
					
					_delay_ms(1) ;
				}
				if(BUTTON_PRESSED == BUTTON_Get_status(RESET))
				{
					reset_state = RESET_ON ;
					while(BUTTON_PRESSED == BUTTON_Get_status(RESET))
					{
						SEVEN_SEG_MUX2D_Write(0,x);
					}
					LED_Turn_Off(0);
					LED_Turn_Off(1);
					LED_Turn_Off(2);
					LED_Turn_Off(3);
					LED_Turn_Off(4);
					LED_Turn_Off(5);
					LED_Turn_Off(6);
					BUZZER_TURN_OFF();
					break;
					
					
				}
			}
			LED_Turn_Off(0);
			LED_Turn_Off(1);
			LED_Turn_Off(2);
			LED_Turn_Off(3);
			LED_Turn_Off(4);
			LED_Turn_Off(5);
			LED_Turn_Off(6);
			BUZZER_TURN_OFF();
			x=y ;
			but_state = pause ;
		}
	}
}

