
#include "StdTypes.h"

#include "SEVEN_SEG_Int.h"
#include "SEVEN_SEG_Cfg.h"

#define F_CPU			8000000UL
#include <util/delay.h>

const static u8 segment_base_elem_CC[16] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
									  0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

void SEVEN_SEG_Init (void) 
{
	
}

void SEVEN_SEG_base_Write (u8 seg_no,u8 num)
{
	u8 i ; 
	if (seg_base_arr[seg_no].common == COMMON_CATHODE)
	{
		for (i=0 ; i<7 ;i++)
		{
			DIO_WritePin(seg_base_arr[seg_no].seg_pin[i],READ_BIT(segment_base_elem_CC[num],i));
		}
	}
	
	else  
	{
		for (i=0 ; i<7 ;i++)
		{
			DIO_WritePin(seg_base_arr[seg_no].seg_pin[i],!READ_BIT(segment_base_elem_CC[num],i));
		}
	}
}



void SEVEN_SEG_MUX2D_Write (u8 seg_no,u8 num)
{
	char d0 = num % 10 ;
	char d1 = num / 10 ;
	u8 i ; 
	if (seg_mux2d_arr[seg_no].common==COMMON_CATHODE)
	{
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[1],HIGH);
		for(i=0;i<7;i++)
		{
			DIO_WritePin(seg_mux2d_arr[seg_no].seg_pin[i],READ_BIT(segment_base_elem_CC[d1],i));
		}
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[0],LOW);
		_delay_ms(1);
		
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[0],HIGH);
		for(i=0;i<7;i++)
		{
			DIO_WritePin(seg_mux2d_arr[seg_no].seg_pin[i],READ_BIT(segment_base_elem_CC[d0],i));
		}
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[1],LOW);
		_delay_ms(1);
	}
	else 
	{
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[1],HIGH);
		for(i=0;i<7;i++)
		{
			DIO_WritePin(seg_mux2d_arr[seg_no].seg_pin[i],!READ_BIT(segment_base_elem_CC[d1],i));
		}
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[0],LOW);
		_delay_ms(1);
		
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[0],HIGH);
		for(i=0;i<7;i++)
		{
			DIO_WritePin(seg_mux2d_arr[seg_no].seg_pin[i],!READ_BIT(segment_base_elem_CC[d0],i));
		}
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[1],LOW);
		_delay_ms(1);
	}
	
}

void SEVEN_SEG_MUX2D_Write_HEX (u8 seg_no,u8 num)
{
	char d0 = num & 0x0F ;
	char d1 = num >>4 ;
	u8 i ;
	if (seg_mux2d_arr[seg_no].common==COMMON_CATHODE)
	{
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[1],HIGH);
		for(i=0;i<7;i++)
		{
			DIO_WritePin(seg_mux2d_arr[seg_no].seg_pin[i],READ_BIT(segment_base_elem_CC[d1],i));
		}
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[0],LOW);
		_delay_ms(1);
		
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[0],HIGH);
		for(i=0;i<7;i++)
		{
			DIO_WritePin(seg_mux2d_arr[seg_no].seg_pin[i],READ_BIT(segment_base_elem_CC[d0],i));
		}
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[1],LOW);
		_delay_ms(1);
	}
	else
	{
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[1],HIGH);
		for(i=0;i<7;i++)
		{
			DIO_WritePin(seg_mux2d_arr[seg_no].seg_pin[i],!READ_BIT(segment_base_elem_CC[d1],i));
		}
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[0],LOW);
		_delay_ms(1);
		
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[0],HIGH);
		for(i=0;i<7;i++)
		{
			DIO_WritePin(seg_mux2d_arr[seg_no].seg_pin[i],!READ_BIT(segment_base_elem_CC[d0],i));
		}
		DIO_WritePin(seg_mux2d_arr[seg_no].enable_pin_arr[1],LOW);
		_delay_ms(1);
	}
}

void SEVEN_SEG_BCD_Write (u8 seg_no,u8 num)
{
	u8 i ; 
	u8 l_num = num &0x0F ; 
	if (seg_bcd_arr[seg_no].common==COMMON_CATHODE)
	{
		for (i=0;i<4;i++)
		{
			DIO_WritePin(seg_bcd_arr[seg_no].seg_pin[i],READ_BIT(l_num,i));
		}
	}
	
	else
	{
		for (i=0;i<4;i++)
		{
			DIO_WritePin(seg_bcd_arr[seg_no].seg_pin[i],!READ_BIT(l_num,i));
		}
	}
}