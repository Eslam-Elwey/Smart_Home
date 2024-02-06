
#include "StdTypes.h"
#include "MemMap.h"
#include "BUTTON_Int.h"
#include "LCD_Int.h"
#include "LCD_Game_Int.h"
#include "ADC_Int.h"
#include "LED_Int.h"
#include "DIO_Int.h"
#include "UART_Int.h"
#include "UART_Services_Int.h"
#include "UART_Stack_Int.h"
#include "EXI_Int.h"

#define F_CPU		8000000UL
#include <util/delay.h>
#define LED_PORT			PB


static void ADC_func (void)  ;
static volatile u16 ldr_volt ;

static void EXI0_Func (void);

#define LDR_CHANNEL			ADC_CHANNEL_0

static u8 man_custom[8]= {0x04,0x04,0x1F,0x04,0x04,0x0A,0x11,0x00} ;
static u8 arrow[8]=	{0x08,0x04,0x02,0x1F,0x02,0x04,0x08,0x00} ;	
static u8 dead_man[8] = {0x15,0x0E,0x1F,0x04,0x04,0x0A,0x11,0x00}; 
static u8 init_flag = 0 ;
static u8 arr_pos = 2 ;
static volatile u8 UDR_Data ;
static volatile u8 pop_flag = 0 ;

void LCD_Game_Init (void)
{
	LCD_Write_String_Cursor(1,3,(u8*)"<<WELCOME>>");
	LCD_Write_String_Cursor(2,3,(u8*)"Hunting Game");
	_delay_ms(3000);
	LCD_Clear_Screen();
	LCD_Custom_Char(0,man_custom);
	LCD_Custom_Char(1,arrow);
	LCD_Custom_Char(2,dead_man);
}

void LCD_Game_Runnable (void)
{
	if (0==init_flag)
	{
		LCD_Clear_Screen();
		arr_pos = 2 ;
		LCD_Set_Cursor(1,1);
		LCD_Write_Character(0);
		LCD_Set_Cursor(1,16);
		LCD_Write_Character(0);
		LCD_Set_Cursor(1,arr_pos);
		LCD_Write_Character(1);
		init_flag = 1 ;
	}
	if (BUTTON_Get_status(0)==BUTTON_PRESSED)
	{
		_delay_ms(10);
		LCD_Clear_Cursor(1,arr_pos,1);
		arr_pos += 1 ;
		if (16==arr_pos)
		{
			LCD_Clear_Cursor(1,16,1);
			LCD_Set_Cursor(1,arr_pos);
			LCD_Write_Character(2);
			LCD_Write_String_Cursor(2,1,(u8*)"<Target Killed>");
			_delay_ms(3000);
			init_flag = 0 ;
		}
		else
		{
			LCD_Set_Cursor(1,arr_pos);
			LCD_Write_Character(1);
		}
		
		while (BUTTON_Get_status(0)==BUTTON_PRESSED); // Busy Wait
		_delay_ms(10);
	}
	if (BUTTON_Get_status(1)==BUTTON_PRESSED)
	{
		init_flag = 0 ;
		_delay_ms(10);
		while (BUTTON_Get_status(1)==BUTTON_PRESSED);
		_delay_ms(10);
	}
}

static void ADC_func (void) 
{
	ldr_volt = ADC_Read_Volt_No_Block() ;
	ADC_Start_Conversion(LDR_CHANNEL) ;
}

void LDR_Init (void) 
{
	LCD_Write_String_Cursor(1,4,(u8*)"LDR Test");
	ADC_Set_Call_Back(ADC_func);
	ADC_INTERRUPT_ENABLE();
	ADC_Start_Conversion(LDR_CHANNEL);
}

void LDR_Runnable (void) 
{
	u8 total_on_leds ;
	u16 x  ;
	LCD_Set_Cursor(2,1);
	LCD_Write_Number(ldr_volt);
	LCD_Write_String((u8*)"    ");
	x = ldr_volt ;
	if (ldr_volt>=1600)
	{
		x = 1600 ;
	}
	total_on_leds = 8 - (x /200) ;
	DIO_Write_Port(LED_PORT,0);
	LED_Count_turn_on (total_on_leds);
}


void Radio_Signal_Init(void)
{
	u8 full[8]= {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
		
	LCD_Custom_Char(4,full);
}

void Radio_Signal_Runnable(void)
{
	
	u16 adc_val = ADC_Read(POT_CHANNEL) ;
	u16 frag = (1024 / TOTAL_STEPS)-3 ;
	static u8 y;
	static u8 flag = 0 ;
	static u8 x;
	if (0== flag )
	{
		y = 0 ;
		flag = 1 ; 
	}
	else 
	{
		y = x ;
	}
	
	x = adc_val / frag ;
	u8 i ;
	LCD_Set_Cursor(1,1);
	LCD_Clear_Cursor(1,1,16);
	for (i=0;i<x;i++)
	{
		/*if (y<x)
		{
			LCD_Clear_Screen();
		}*/
		
		LCD_Write_Character(4);
	}
	LCD_Set_Cursor(2,1);
	LCD_Write_Number(adc_val);
	LCD_Write_String((u8*)"   ");
}


void UART_Button_print_Last_Data_Init(void)
{
	LCD_Write_String_Cursor(1,1,(u8*)"UART Last:");
	EXT_INT_Set_Call_Back(EXT_INT0,EXI0_Func);
	UART_Receive_charcters_Async();
}

void UART_Button_print_Last_Data_Runnable(void)
{
	if (1==pop_flag)
	{
		LCD_Set_Cursor(1,12);
		LCD_Write_Character(UDR_Data);
		pop_flag = 0 ;
	}
	else if (2==pop_flag)
	{
		LCD_Write_String_Cursor(2,5,(u8*)"Empty Buffer");
		_delay_ms(1000);
		LCD_Clear_Cursor(2,5,12);
		pop_flag = 0 ;
	}
	
}

static void EXI0_Func (void)
{
	u8 val ;
	uart_stack_status_t ret_val = UART_Stack_Pop(&val);
	if (ret_val==UART_STACK_EMPTY)
	{
		pop_flag = 2 ;
	}
	else 
	{
		UDR_Data = val ;
		pop_flag = 1 ;
	}
}