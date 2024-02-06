
#include "StdTypes.h"
#include "KeyPad_Int.h"
#include "LCD_Int.h"
#include "Number_Converter_Int.h"
#include "MemMap.h"
#define F_CPU		8000000UL
#include <util/delay.h>

/*************************** Private Functions **************************/

static void Converter_Input_Choice(void);
static void Converter_Output_Choice(void);
static void Converter_print_system(void);
static void Converter_Reset(void);
static u32 power_fun(u32 num , u8 pow);
static void Fill_buffer(void);
static void Result_print(void);
static u32 Binary_To_Integer(void);
static u32 Hex_To_Integer(void) ;
static void Print_Hex_sys(u32 num);
static void Print_Binary_sys(u32 num) ;


/***********************************************************************************/
static u8 init_flag = 0 ;
static u8 buffer_flag = 0 ;
static u8 result_flag = 0 ;
static u8 hex_num_flag = 0 ;
static u8 hex_set_flag = 0 ;
static u8 key ; 
static u8 hex_char = 'A';
static u8 pos_hex = 7 ;
static num_t input_sys ;
static num_t output_sys ;

static u32 num ;
static u8 str_buffer[10];
static u8 i=0 ; 
static u8 counter ; 

/***********************************************************************************/



void Number_Converter_Init(void) 
{
	LCD_Write_String_Cursor(1,3,(u8*)"<<WELCOME>>");
	LCD_Write_String_Cursor(2,1,(u8*)"Number Converter");
	_delay_ms(3000);
	LCD_Clear_Screen();
}


void Number_Converter_Runnable (void) 
{
	if (0==init_flag)
	{
		Converter_Input_Choice();
		Converter_Output_Choice();
		Converter_print_system();
		init_flag = 1 ;
	}
	
	key = KeyPad_Get_Key();
	if (key!=NO_KEY)
	{
		if ((result_flag==1)&&(key!='=')&&(key!='+')&&(key!='-'))
		{
			
			
			switch (input_sys)
			{
				case DECIMAL :
					if ((key>='0')&&(key<='9'))
					{
						buffer_flag = 0 ;
						result_flag = 0 ;
						LCD_Clear_Cursor(1,10,7);
						switch (output_sys)
						{
							case DECIMAL :
							LCD_Clear_Cursor(2,9,8);
							break;
							
							case BINARY :
							LCD_Clear_Cursor(2,9,9);
							break;
							
							case HEXADEC :
							LCD_Clear_Cursor(2,7,11);
							break;
						}
						
						LCD_Set_Cursor(1,10);
					}
				break ;
				
				case BINARY :
					if ((key=='0')||(key=='1'))
					{
						buffer_flag = 0 ;
						result_flag = 0 ;
						LCD_Clear_Cursor(1,8,10);
						switch (output_sys)
						{
							case DECIMAL :
							LCD_Clear_Cursor(2,9,8);
							break;
							
							case BINARY :
							LCD_Clear_Cursor(2,9,9);
							break;
							
							case HEXADEC :
							LCD_Clear_Cursor(2,7,11);
							break;
						}
						LCD_Set_Cursor(1,8);
					}
				break ;
				
				case HEXADEC :
					if (key!='*')
					{
						buffer_flag = 0 ;
						result_flag = 0 ;
						LCD_Clear_Cursor(1,7,10);
						pos_hex = 7 ;
						hex_char = 'A';
						hex_num_flag = 0 ;
						hex_set_flag = 0 ;
						switch (output_sys)
						{
							case DECIMAL :
							LCD_Clear_Cursor(2,9,8);
							break;
							
							case BINARY :
							LCD_Clear_Cursor(2,9,9);
							break;
							
							case HEXADEC :
							LCD_Clear_Cursor(2,7,11);
							break;
						}
						LCD_Set_Cursor(1,7);
					}
					
					
				break ;
				
			}
			buffer_flag = 0 ;
		}
		if ('C'==key)
		{
			Converter_Reset();
		}
		
		if (('='==key)&&(0==result_flag))
		{
			buffer_flag = 1 ;
			Result_print();
		}
		
		else if (0==buffer_flag)
		{
			Fill_buffer();
		}
	}
	
	
	
	
	
	
}

static void Converter_Input_Choice(void)
{
	u8  check_flag = 1 ;
	u8 i ; 
	LCD_Write_String_Cursor(1,1,(u8*)"Convert From: ");
	LCD_Write_String_Cursor(2,1,(u8*)"1DEC");
	LCD_Write_String_Cursor(2,7,(u8*)"2BIN");
	LCD_Write_String_Cursor(2,13,(u8*)"3HEX");
	
	
	
	while (check_flag)
	{
		key = KeyPad_Get_Key() ;
		if (key!=NO_KEY)
		{
			if ('C'==key)
			{
				Converter_Reset();
				break ;
			}
			else if (('1'==key)||('2'==key)||('3'==key))
			{
				LCD_Set_Cursor(1,15);
				LCD_Write_Character(key);
				check_flag = 0 ;
				switch (key)
				{
					case '1' :
						input_sys = DECIMAL ;
					break ;
					
					case '2' :
						input_sys = BINARY ;
					break ;
					
					case '3' :
						input_sys = HEXADEC ;
					break ;
				}
				for (i=0;i<50;i++)
				{
					key = KeyPad_Get_Key() ;
					 if ('C'==key)
					 {
						 Converter_Reset();
						 break ;
					 }
					_delay_ms(10);
				}
				LCD_Clear_Screen();
			}
			else
			{
				LCD_Clear_Cursor(1,1,16);
				LCD_Write_String_Cursor(1,1,(u8*)"Wrong Entry!!");
				_delay_ms(1000);
				LCD_Clear_Cursor(1,1,16);
				LCD_Write_String_Cursor(1,1,(u8*)"Convert From: ");
				LCD_Set_Cursor(1,15);
			}
		}
		
	}
	
}

static void Converter_Output_Choice(void)
{
	u8  check_flag = 1 , i ;
	u8 pos_flag = 0 ;
	LCD_Write_String_Cursor(1,1,(u8*)"Convert To: ");
	switch(input_sys)
	{
		case DECIMAL :
		LCD_Write_String_Cursor(2,1,(u8*)"1.BIN");
		LCD_Write_String_Cursor(2,10,(u8*)"2.HEXA");
		pos_flag = 1 ;
		break;
		
		case BINARY :
		LCD_Write_String_Cursor(2,1,(u8*)"1.DEC");
		LCD_Write_String_Cursor(2,10,(u8*)"2.HEXA");
		pos_flag = 2 ; 
		break;
		
		case HEXADEC :
		LCD_Write_String_Cursor(2,1,(u8*)"1.BIN");
		LCD_Write_String_Cursor(2,10,(u8*)"2.DEC");
		pos_flag = 3; 
		break;
	}
	
	
	
	while (check_flag)
	{
		key = KeyPad_Get_Key() ;
		if (key!=NO_KEY)
		{
			if ('C'==key)
			{
				Converter_Reset();
				break ;
			}
			else if (('1'==key)||('2'==key))
			{
				LCD_Set_Cursor(1,13);
				LCD_Write_Character(key);
				check_flag = 0 ;
				switch (pos_flag)
				{
					case 1 :
						if ('1'==key)
						{
							output_sys = BINARY ;
						}
						else if ('2'==key)
						{
							output_sys = HEXADEC ;
						}
						
					break ;
					
					case 2 :
						if ('1'==key)
						{
							output_sys = DECIMAL ;
						}
						else if ('2'==key)
						{
							output_sys = HEXADEC ;
						}
					break ;
					
					case 3 :
						if ('1'==key)
						{
							output_sys = BINARY ;
						}
						else if ('2'==key)
						{
							output_sys = DECIMAL ;
						}
					break ;
				}
				
				for (i=0;i<50;i++)
				{
					key = KeyPad_Get_Key() ;
					if ('C'==key)
					{
						Converter_Reset();
						break ;
					}
					_delay_ms(10);
				}
				check_flag = 0 ;
				LCD_Clear_Screen();
			} 
			else
			{
				LCD_Clear_Cursor(1,1,16);
				LCD_Write_String_Cursor(1,1,(u8*)"Wrong Entry!!");
				_delay_ms(1000);
				LCD_Clear_Cursor(1,1,16);
				LCD_Write_String_Cursor(1,1,(u8*)"Convert To: ");
				LCD_Set_Cursor(1,13);
			}
		}
	}
}

static void Converter_Reset(void)
{
	init_flag = 0 ;
	i=0 ;
	pos_hex = 7 ; 
	hex_char = 'A';
	buffer_flag = 0 ;
	result_flag = 0 ;
	hex_num_flag = 0 ; 
	LCD_Clear_Screen();
	Number_Converter_Runnable();
}

static void Converter_print_system(void)
{
	
	
	switch(output_sys)
	{
		case DECIMAL :
		LCD_Write_String_Cursor(2,1,(u8*)"DECIMAL:");
		break;
		
		case BINARY :
		LCD_Write_String_Cursor(2,1,(u8*)"BINARY:");
		break;
		
		case HEXADEC :
		LCD_Write_String_Cursor(2,1,(u8*)"HEXA:");
		break;
	}
	
	switch(input_sys)
	{
		case DECIMAL :
		LCD_Write_String_Cursor(1,1,(u8*)"DECIMAL:");
		LCD_Set_Cursor(1,10);
		break;
		
		case BINARY :
		LCD_Write_String_Cursor(1,1,(u8*)"BINARY:");
		LCD_Set_Cursor(1,8);
		break;
		
		case HEXADEC :
		LCD_Write_String_Cursor(1,1,(u8*)"HEXA:");
		LCD_Set_Cursor(1,7);
		break;
	}
}

static u32 power_fun(u32 num , u8 pow)
{
	u32 res = 1 ;
	u8 i ;
	for (i=0;i<pow;i++)
	{
		res*= num ;
	}
	return res ;
}

static void Fill_buffer(void)
{
	
	switch(input_sys)
	{
		case DECIMAL :
			if ((key>='0')&&(key<='9'))
			{
				LCD_Write_Character(key);
				str_buffer[i]=key ;
				i++;
			}
			
		break;
		
		case BINARY :
			if ((key=='1')||(key=='0'))
			{
				LCD_Write_Character(key);
				str_buffer[i]=key ;
				i++;
			}
			
		break;
		
		case HEXADEC :
			if ((1==hex_set_flag)&&(!((key>='0')&&(key<='9'))))
			{
				hex_set_flag = 0 ;
				
			}
			
			if ((key>='0')&&(key<='9'))
			{
				hex_set_flag = 0 ;
				hex_char = 'A' ;
				str_buffer[i] = key ;
			}
			
			if (((key>='0')&&(key<='9'))||(key=='/')||(key=='*'))
			{
				if ((key=='/')&&(hex_set_flag==0))
				{
					LCD_Clear_Cursor(1,pos_hex,1);
					LCD_Set_Cursor(1,pos_hex);
					LCD_Write_Character(hex_char);
					
					if ((0!=i)&&(hex_num_flag==1))
					{
						i--;
					}
					
					
					hex_num_flag = 1 ;
				}
				else if (key=='*')
				{
					hex_set_flag = 0 ;
					hex_num_flag = 0 ;
					hex_char = 'A' ;
					pos_hex += 1 ;
						
					
				}
				else 
				{
					pos_hex += 1 ;
					LCD_Write_Character(key);
				}
				
				if (key!='*')
				{
					if (key=='/')
					{
						str_buffer[i] = hex_char ;
						hex_char += 1 ;
						if ('G'==hex_char)
						{
							hex_char = 'A' ;
						}
					}
					
					i++;
				}
				
			}
			
		break;
	}
}

static void Result_print(void)
{
	str_buffer[i] = '\0';
	counter = i - 1 ;
	switch(input_sys)
	{
		case DECIMAL :
			num = String_To_Int((u8*)str_buffer) ;
		break;
		
		case BINARY :
			num = Binary_To_Integer();
		break;
		
		case HEXADEC :
			num = Hex_To_Integer();
		break;
	}
	
	switch(output_sys)
	{
		case DECIMAL :
			LCD_Set_Cursor(2,9);
			LCD_Write_Number(num);
		break;
		
		case BINARY :
			LCD_Set_Cursor(2,9);
			Print_Binary_sys(num);
		break;
		
		case HEXADEC :
			LCD_Set_Cursor(2,7);
			Print_Hex_sys(num);
		break;
	}
	i=0 ;
	result_flag = 1 ;
}


static u32 Binary_To_Integer(void)
{
	s8 i ; 
	u8 pow = 0 ;
	u32 res = 0 ;
	for (i=counter;i>=0;i--)
	{
		res +=((str_buffer[i]-'0')* power_fun(2,pow)) ;
		pow++;
	}
	return res ; 
}

static u32 Hex_To_Integer(void)
{
	s8 i ;
	u8 pow = 0 ;
	u32 res = 0 ;
	for (i=counter;i>=0;i--)
	{
		if ((str_buffer[i]>='0')&&(str_buffer[i]<='9'))
		{
			res +=((str_buffer[i]-'0') * power_fun(16,pow) ) ;
		}
		else if ((str_buffer[i]>='A')&&(str_buffer[i]<='F'))
		{
			res +=(((str_buffer[i]-'A')+10) * power_fun(16,pow) ) ;
		}
		pow++;
	}
	return res ;
}

static void Print_Binary_sys(u32 num)
{
	s8 i ;
	if (num >255)
	{
		for (i=15;i>=0;i--)
		{
			LCD_Write_Number(READ_BIT(num,i));
		}
	}
	else
	{
		for (i=7;i>=0;i--)
		{
			LCD_Write_Number(READ_BIT(num,i));
		}
	}
	
}

static void Print_Hex_sys(u32 number)
{
	
	if (num<=255)
	{
		u8 Low_Nib , High_Nib ;
		
		High_Nib = (num&0x00F0)>>4;
		Low_Nib = num & 0x0F ;
		
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
	else 
	{
		u8 Low_Nib , High_Nib , sec_nib , fir_nib ;
		High_Nib = (num&0xF000)>>12;
		sec_nib	 = (num&0x0F00)>>8;
		fir_nib	 = (num&0x00F0)>>4;
		Low_Nib = num & 0x0F ;
		if (High_Nib>=10)
		{
			LCD_Write_Character(High_Nib-10+'A');
		}
		else
		{
			LCD_Write_Number(High_Nib);
		}
		
		if (sec_nib>=10)
		{
			LCD_Write_Character(sec_nib-10+'A');
		}
		else
		{
			LCD_Write_Number(sec_nib);
		}
		
		if (fir_nib>=10)
		{
			LCD_Write_Character(fir_nib-10+'A');
		}
		else
		{
			LCD_Write_Number(fir_nib);
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
	
}