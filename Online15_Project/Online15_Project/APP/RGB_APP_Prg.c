
#include "StdTypes.h"
#include "RGB_Int.h"
#include "Timers_Int.h"
#include "Timers_Services_Int.h"
#include "LCD_Int.h"
#include "BUTTON_Int.h"
#include "RGB_APP_Int.h"
#include "EXI_Int.h"
#define F_CPU		8000000UL
#include <util/delay.h>

#define CHANGE_COLOR						0x55
#define FREE_RUN_MODE						0xAA


const u8 *color_names[TOTAL_RGB_COLOURS] = {
											"RED" ,
											"GREEN" ,
											"BLUE" ,
											"WHITE" ,
											"YELLOW" ,
											"CYAN" ,
											"ORANGE" ,
											"PURPLE" ,
											"LIGHT_BLUE" ,
											"BROWN" ,
											"LIGHT_GREEN" ,
											"LIGHT_RED" ,
											"GRAY" ,
											"BLACK" ,
											"PINK"
		
};

static volatile rgb_color_name_t current_color = RGB_RED ;
static volatile rgb_color_name_t next_color = RGB_GREEN ; 

static void INT0_Func(void) ;
static void INT1_Func(void) ;


static volatile u8 flag1 = 0 ;
static volatile u8 flag2 = CHANGE_COLOR ;

void RGB_APP_Init (void) 
{
	RGB_Colour_array(current_color);
	LCD_Write_String_Cursor(1,5,(u8*)"<<RGB>>");
	_delay_ms(1500) ;
	LCD_Clear_Screen() ;
	
	EXI_INT0_ENABLE();
	EXI_INT1_ENABLE();
	EXT_INT_Set_Call_Back(EXT_INT0,INT0_Func);
	EXT_INT_Set_Call_Back(EXT_INT1,INT1_Func);
	LCD_Write_String_Cursor(1,1,(u8*)"COLOR");
	LCD_Write_String_Cursor(2,1,color_names[current_color]);
}



/* INT0 For Change Colors 
INT1 For Free Run */
void RGB_APP_Runnable (void) 
{
	if (flag1==1)
	{
		
		flag1 = 0 ;
		if (current_color==TOTAL_RGB_COLOURS)
		{
			current_color = RGB_RED ;
		}
		/* Critical Section */
		GLOBAL_INTERRUPT_DISABLE();
		LCD_Clear_Cursor(2,1,16);
		LCD_Write_String_Cursor(2,1,color_names[current_color]);
		GLOBAL_INTERRUPT_ENABLE();
		RGB_Colour_array(current_color);
		
	}
	if (flag2 == FREE_RUN_MODE)
	{
		GLOBAL_INTERRUPT_DISABLE();
		LCD_Write_String_Cursor(1,1,(u8*)"Showroom Mode");
		GLOBAL_INTERRUPT_ENABLE();
		RGB_Convert_Colours(current_color,next_color) ;
		current_color = next_color ;
		next_color++ ;
		_delay_ms(1500);
		if (next_color == TOTAL_RGB_COLOURS)
		{
			next_color= 0 ;
		}
	}
}


static void INT0_Func(void) 
{
	flag1 = 1 ;
	current_color++;
	next_color = current_color + 1 ;
}


static void INT1_Func(void) 
{
	flag2 ^= 0xFF ;
	
	if (flag2==FREE_RUN_MODE)
	{
		LCD_Clear_Screen();
		EXI_INT0_DISABLE();
	}
	else if (flag2==CHANGE_COLOR)
	{
		EXI_INT0_ENABLE();
		LCD_Clear_Screen();
		LCD_Write_String_Cursor(1,1,(u8*)"COLOR");
		flag1 = 1 ;
	}
}