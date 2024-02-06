
#include "StdTypes.h"
#include "DIO_Int.h"

#define KEYPAD_PROG				1
#include "KeyPad_Int.h"
#include "KeyPad_Cfg.h"

#define F_CPU		8000000UL
#include <util/delay.h>



void KeyPad_Init (void) 
{
	u8 i = 0 ;
	for (i=0;i<KEYPAD_ROWS;i++)
	{
		DIO_WritePin(key_cofig.output[i],HIGH) ;
	}
}

u8 KeyPad_Get_Key (void)
{
	u8 r ,c , key = NO_KEY ;
	
	for (r=0 ;r<KEYPAD_ROWS;r++)
	{
		DIO_WritePin(key_cofig.output[r],LOW) ;
		for(c=0;c<KEYPAD_COLS;c++)
		{
			if (!DIO_ReadPin(key_cofig.input[c]))
			{
				key = KeyPad_arr[r][c] ;
				_delay_ms(10);
				while(!DIO_ReadPin(key_cofig.input[c]));
				_delay_ms(10);
			}
		}
		DIO_WritePin(key_cofig.output[r],HIGH) ;
	}
	
	return key ;
}
