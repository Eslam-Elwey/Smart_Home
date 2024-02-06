
#include "StdTypes.h"
#include "DIO_Int.h"
#include "MemMap.h"
#include "LCD_Int.h"
#include "LCD_Cfg.h"
#define F_CPU		8000000UL
#include <util/delay.h>


#define DISPLAY_DELAY				500

static void Write_Data (u8 data) ;
static void Write_Instruction (u8 ins) ;



#if LCD_MODE == LCD_4_BIT 

static void Write_Data (u8 data) 
{
	s8 i ;
	u8 low_nib = data&0x0F ; 
	u8 High_nib = data >> 4 ;
	
	DIO_WritePin(LCD_Pin_control.Reigster_Sel,HIGH);
	
	for (i=3 ; i>=0 ;i--)
	{
		DIO_WritePin(LCD_Pin_control.DataPins[i],READ_BIT(High_nib,i));
	}
	DIO_WritePin(LCD_Pin_control.Enable_pin,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_Pin_control.Enable_pin,LOW);
	_delay_ms(1);
	
	for (i=3 ; i>=0 ;i--)
	{
		DIO_WritePin(LCD_Pin_control.DataPins[i],READ_BIT(low_nib,i));
	}
	DIO_WritePin(LCD_Pin_control.Enable_pin,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_Pin_control.Enable_pin,LOW);
	_delay_ms(1);
}

static void Write_Instruction (u8 ins)
{
	s8 i ;
	u8 low_nib = ins&0x0F ;
	u8 High_nib = ins >> 4 ;
	
	DIO_WritePin(LCD_Pin_control.Reigster_Sel,LOW);
	
	for (i=3 ; i>=0 ;i--)
	{
		DIO_WritePin(LCD_Pin_control.DataPins[i],READ_BIT(High_nib,i));
	}
	DIO_WritePin(LCD_Pin_control.Enable_pin,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_Pin_control.Enable_pin,LOW);
	_delay_ms(1);
	
	for (i=3 ; i>=0 ;i--)
	{
		DIO_WritePin(LCD_Pin_control.DataPins[i],READ_BIT(low_nib,i));
	}
	DIO_WritePin(LCD_Pin_control.Enable_pin,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_Pin_control.Enable_pin,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	Write_Instruction(0x02);
	Write_Instruction(0x28);
	_delay_ms(1);
	Write_Instruction(LCD_DIS_ON_CUR_OFF_BLI_OFF);
	_delay_ms(1);
	Write_Instruction(LCD_CLEAR_DISPALY);
	_delay_ms(5);
	Write_Instruction(LCD_INCREASE_ADD_NO_SHIFT);
	
}

#elif LCD_MODE == LCD_8_BIT 

static void Write_Data (u8 data)
{
	u8 i ; 
	DIO_WritePin(LCD_Pin_control.Reigster_Sel,HIGH);
	
	for (i=0 ; i<8 ;i++)
	{
		DIO_WritePin(LCD_Pin_control.DataPins[i],READ_BIT(data,i));
	}
	
	DIO_WritePin(LCD_Pin_control.Enable_pin,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_Pin_control.Enable_pin,LOW);
	_delay_ms(1);
}

static void Write_Instruction (u8 ins)
{
	u8 i ;
	DIO_WritePin(LCD_Pin_control.Reigster_Sel,LOW);
	
	for (i=0 ; i<8 ;i++)
	{
		DIO_WritePin(LCD_Pin_control.DataPins[i],READ_BIT(ins,i));
	}
	
	DIO_WritePin(LCD_Pin_control.Enable_pin,HIGH);
	_delay_ms(1);
	DIO_WritePin(LCD_Pin_control.Enable_pin,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	Write_Instruction(LCD_8_BIT_MODE);
	_delay_ms(1);
	Write_Instruction(LCD_DIS_ON_CUR_OFF_BLI_OFF);
	_delay_ms(1);
	Write_Instruction(LCD_CLEAR_DISPALY);
	_delay_ms(5);
	Write_Instruction(LCD_INCREASE_ADD_NO_SHIFT);
	
}

#endif






void LCD_Write_Character(u8 chr)
{
	Write_Data(chr);
}

void LCD_Write_String(u8 *str)
{
	u8 i = 0 ;
	while (str[i]!='\0')
	{
		LCD_Write_Character(str[i]);
		i++ ;
	}
}

void LCD_Write_Number(s32 num)
{
	u8 num_arr[20] , i = 0 ;
	s8 j ; 
	if (0==num)
	{
		LCD_Write_Character('0');
	}
	if (num < 0)
	{
		LCD_Write_Character('-');
		num = -1 * num ; 
	}
	while (num > 0)
	{
		num_arr[i] = num % 10 ; 
		num /= 10 ;
		i++ ;
	}
	j = i-1 ; 
	while (j>=0)
	{
		LCD_Write_Character(num_arr[j]-0+'0');
		j-- ;
	}
	
}


void LCD_Set_Cursor(u8 line , u8 cell)
{
	if (line == 1)
	{
		Write_Instruction(0x80|(cell-1));
	}
	else if (line==2)
	{
		Write_Instruction((0x80+0x40)|(cell-1));
	}
}

void LCD_Custom_Char(u8 address , u8 *Pattern)
{
	u8 i ;
	address &= 0x07 ;
	Write_Instruction(0x40|(address*8));
	for (i=0;i<8;i++)
	{
		Write_Data(Pattern[i]);
	}
	Write_Instruction(0x80);
}

void LCD_Clear_Screen(void)
{
	Write_Instruction(LCD_CLEAR_DISPALY);
}

void LCD_Write_String_Cursor(u8 line , u8 cell , u8 *str)
{
	LCD_Set_Cursor(line,cell);
	LCD_Write_String(str);
}

void LCD_Clear_Cursor(u8 line , u8 cell , u8 num)
{
	u8 i ;
	LCD_Set_Cursor(line,cell);
	for (i=0;i<num;i++)
	{
		LCD_Write_Character(' ');
	}
	LCD_Set_Cursor(line,cell);
}

void LCD_Print_Binary(u16 num)
{
	s8 i ; 
	if (num >255)
	{
		for (i=15;i>=0;i--)
		{
			LCD_Write_Number(READ_BIT(num,i));
		}
		return ; 
	}
	LCD_Write_String((u8*)"0b");
	for (i=7;i>=0;i--)
	{
		LCD_Write_Number(READ_BIT(num,i));
	}
}

void LCD_Print_Hexa(u8 num)
{
	u8 Low_Nib , High_Nib ;
	
	High_Nib = (num >>4)&0x0F ;
	Low_Nib = num & 0x0F ;
	LCD_Write_String((u8*)"0x");
	if (High_Nib>=10)
	{
		LCD_Write_Character(High_Nib-10+'A');
	}
	else
	{
		LCD_Write_Number(High_Nib);
	}
	if (Low_Nib>=10)
	{
		LCD_Write_Character(Low_Nib-10+'A');
	}
	else
	{
		LCD_Write_Number(Low_Nib);
	}
}

void LCD_Snake_Word(u8 *str)
{
	u8 length ;
	s8 i  ; 
	for (i=0;str[i];i++);
	length = i ;
	
	for (i=1;str[i];i++)
	{
		LCD_Write_String(str+length-i);
		_delay_ms(DISPLAY_DELAY);
		LCD_Clear_Screen();
	}
	for (i=1;i<=16;i++)
	{
		LCD_Set_Cursor(1,i);
		LCD_Write_String(str);
		_delay_ms(DISPLAY_DELAY);
		LCD_Clear_Screen();
	}
	for (i=1;str[i];i++)
	{
		LCD_Set_Cursor(2,1);
		LCD_Write_String(str+length-i);
		_delay_ms(DISPLAY_DELAY);
		LCD_Clear_Screen();
	}
	for (i=1;i<=16;i++)
	{
		LCD_Set_Cursor(2,i);
		LCD_Write_String(str);
		_delay_ms(DISPLAY_DELAY);
		LCD_Clear_Screen();
	}
}

void LCD_Write_Number_Cursor(u8 line , u8 cell , s32 num)
{
	LCD_Set_Cursor(line,cell);
	LCD_Write_Number(num);
}

void LCD_Write_Number_4_Digits (u32 num)
{
	LCD_Write_Character(((num%10000)/1000)-0+'0');
	LCD_Write_Character(((num%1000)/100)-0+'0');
	LCD_Write_Character(((num%100)/10)-0+'0');
	LCD_Write_Character(((num%10)/1)-0+'0');
}

s32 String_To_Int (u8 *str)
{
	u8 i=0 , flag = 0  ;
	s32 num = 0 ;
	
	if (str[0] == '-' )
	{
		flag = 1 ;
		i = 1 ;
	}
	
	
	for (;str[i];i++)
	{
		if ((str[i]>='0')&&(str[i]<='9'))
		{
			num = (num * 10) + (str[i] - '0') ;
		}
		
		
	}
	if (1==flag)
	{
		num *= -1 ;
	}
	
	
	return num ;
}