
#include "StdTypes.h"
#include "KeyPad_Int.h"
#include "LCD_Int.h"
#include "Calculator_Int.h"
#define F_CPU		8000000UL
#include <util/delay.h>

static void Result_Print(void);
static void calc_reset(void);

static s32 num1 = 0 ;
static s32 num2 = 0 ;
static s32 Result = 0 ;
static u8 Str_Buffer[15];
static u8 Oper ;
static u8 i = 0 ;
static u8 clr_flag = 0 ;
static u8 incremntal_flag = 0 ;
static u8 Init_flag = 0 ;
static u8 negative_flag = 0 ;
static u8 one_elem_flag = 0 ;
static u8 oper_flag = 0 ;
static u8 equal_flag = 0 ;
static u8 indic_flag = 0 ;
static u8 printed_flag = 0 ;
static u8 cmp_flag = 0 ;
static u8 check_flag = 0 ;





void Calculator_Init(void)
{
	
	LCD_Write_String_Cursor(1,3,(u8*)"<<WELCOME>>");
	LCD_Write_String_Cursor(2,1,(u8*)"Calculator Prog ");
	_delay_ms(3000);
	LCD_Clear_Screen() ;
	
	/*u8 i ;
	for (i=0;i<10;i++)
	{
		LCD_Write_String_Cursor(1,3,"<<WELCOME>>");
		LCD_Write_String_Cursor(2,1,"Calculator Prog ");
		_delay_ms(190);
		LCD_Clear_Screen() ;
		_delay_ms(10);
	}*/
}

void Calculator_Runnable(void)
{
	static u8 key = NO_KEY ;
	printed_flag = 0 ;
	key = KeyPad_Get_Key() ;
	
	if ((key!=NO_KEY)&&(key!='=')&&(key!='C'))
	{
		equal_flag = 0 ;
		if (clr_flag == 0 )
		{
			
			LCD_Clear_Screen() ;
			LCD_Set_Cursor(1,1) ;
			clr_flag = 1 ;
			negative_flag = 0 ;
			cmp_flag = 0 ;
			check_flag = 0 ;
			if ((1==incremntal_flag)&&((key=='+')||(key=='*')||(key=='/')||(key=='-')))
			{
				LCD_Write_Number(num1);
				incremntal_flag = 2 ;
				
			}
		}
		if ((0==i)&&('-'==key))
		{
			Str_Buffer[i]='-';
			i++;
			negative_flag = 1 ;
			
		}
		if (((1==oper_flag)||(Init_flag==0))&&((key=='+')||(key=='*')||(key=='/')))
		{
			
		}
		else
		{
			if (('-'==key)&&(0==indic_flag)&&(100!=negative_flag)&&(cmp_flag<2)&&(3!=check_flag))
			{
				LCD_Write_Character('-');
				printed_flag = 1 ;
			}
			else if (('-'!=key)&&(cmp_flag<2)&&(3!=check_flag))
			{
				LCD_Write_Character(key);
				printed_flag = 1 ;
			}
		}
		
	}
	
	if ('C'==key)
	{
		calc_reset();
	}
	
	if (('='==key)&&(1==Init_flag)&&(0==equal_flag))
	{
		Str_Buffer[i] = '\0' ;
		if (0==one_elem_flag)
		{
			num1 = String_To_Int (Str_Buffer);
		}
		else if ((Str_Buffer[0]=='-')&&(100==negative_flag))
		{
			num2 = String_To_Int (Str_Buffer);
		}
		else
		{
			num2 = String_To_Int (Str_Buffer);
		}
		i=0;
		Result_Print();
		negative_flag = 0 ;
		oper_flag = 0 ;
		indic_flag = 0 ;
	}
	
	if (1==printed_flag)
	{
		if (((key=='+')||(key=='*')||(key=='/')||('-'==key)))
		{
			if (('-'==key)&&(Str_Buffer[0]=='-')&&(1==negative_flag)&&(incremntal_flag != 2)&&(2!=check_flag))
			{
				oper_flag = 0 ;
				indic_flag = 1 ;
				check_flag += 1 ;
			}
			else if (('-'==key)&&(Str_Buffer[0]!='-')&&(1==negative_flag)&&(incremntal_flag != 2))
			{
				if (0==oper_flag)
				{
					Str_Buffer[i] = '\0' ;
					if (2==incremntal_flag)
					{
						num1 = Result ;
						incremntal_flag = 0 ;
					}
					else
					{
						num1= String_To_Int(Str_Buffer);
					}
					one_elem_flag = 1 ;
					
					Oper = key ;
					indic_flag = 0 ;
					i=0;
				}
				oper_flag = 1 ;
				check_flag += 1 ;
			}
			
			else if (2!=check_flag)
			{
				if (0==oper_flag)
				{
					Str_Buffer[i] = '\0' ;
					if (2==incremntal_flag)
					{
						num1 = Result ;
						incremntal_flag = 0 ;
					}
					else
					{
						num1= String_To_Int(Str_Buffer);
					}
					one_elem_flag = 1 ;
					negative_flag = 100 ;
					Oper = key ;
					i=0;
				}
				oper_flag = 1 ;
				cmp_flag += 1 ;
				check_flag += 1 ;
				if (cmp_flag<2)
				{
					indic_flag = 0 ;
				}
				
			}
			if (2==check_flag)
			{
				oper_flag = 1 ;
			}
			
		}
	}

	
	

if ((key>='0')&&(key<='9'))
{
	indic_flag = 0 ;
	negative_flag = 0 ;
	Str_Buffer[i] = key ;
	i++ ;
	Init_flag = 1 ;
}



}


static void Result_Print(void)
{
	LCD_Set_Cursor(2,1);
	if (0==one_elem_flag)
	{
		Result = num1 ;
	}
	
	else if (1==one_elem_flag)
	{
		switch (Oper)
		{
			case '+':
			Result = num1 + num2 ;
			break ;
			
			case '-':
			Result = num1 - num2 ;
			break ;
			
			case '*':
			Result = num1 * num2 ;
			break ;
			
			case '/':
			if (0==num2)
			{
				LCD_Write_String((u8*)"Can't div By 0");
				clr_flag = 0 ;
				Init_flag = 0 ;
				return ;
			}
			Result = num1 / num2 ;
			break ;
			
			default:
			Result = num1 + num2 ;
			break ;
		}
	}
	one_elem_flag = 0 ;
	LCD_Write_Number(Result);
	num1 = Result ;
	incremntal_flag = 1 ;
	clr_flag = 0 ;
	equal_flag = 1 ;
	negative_flag = 0 ;
	oper_flag = 0 ;
	i = 0 ;
}

static void calc_reset(void)
{
	
	LCD_Clear_Screen();
	i=0;
	one_elem_flag = 0 ;
	negative_flag = 0 ;
	oper_flag = 0 ;
	Init_flag = 0 ;
	equal_flag = 0 ;
	indic_flag = 0 ;
	clr_flag = 1 ;
	cmp_flag = 0 ;
	check_flag = 0 ;
}