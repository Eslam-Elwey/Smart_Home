
#include "StdTypes.h"
#include "LCD_Int.h"
#include "KeyPad_Int.h"
#include "Stepper_Int.h"
#include "StepperAPP_Int.h"
#define F_CPU		8000000UL
#include <util/delay.h>

/********************** Private Functions *********************************************/

static stepper_state_t motor_state ;
static void define_state (void) ;
static void reset_system(void);
static void Get_Choice (void) ;
static void print_Choice (void) ;
static void Fill_Buffer (void) ;
static void operate_motor(void);

/*************************************************************************************/

static u8 init_flag = 0 ;
static u8 key ;
static s32 data ; 
static u8 str_buffer[10];
static u8 i = 0 ;
static u8 operate_flag = 0 ;

/*************************************************************************************/
void Stepper_APP_Init(void)
{
	LCD_Write_String_Cursor(1,3,(u8*)"<<WELCOME>>");
	LCD_Write_String_Cursor(2,2,(u8*)"STEPPER MOTOR");
	_delay_ms(3000);
	LCD_Clear_Screen();
}

void Stepper_APP_Runnable(void)
{
	if (0==init_flag)
	{
		define_state();
		Get_Choice() ; 
		print_Choice();
		init_flag = 1 ;
	}
	key = KeyPad_Get_Key() ;
	
	if (key!=NO_KEY)
	{
		if (((key>='0')&&(key<='9'))||(('-'==key)&&(0==i)))
		{
			if (1==operate_flag)
			{
				if (ANGLE == motor_state)
				{
					LCD_Clear_Cursor(1,8,10);
					LCD_Set_Cursor(1,8);
				}
				else
				{
					LCD_Clear_Cursor(1,9,10);
					LCD_Set_Cursor(1,9);
				}
				operate_flag = 0 ;
			}
			LCD_Write_Character(key);
			Fill_Buffer();
		}
		if ((i!=0)&&('='==key)&&(0==operate_flag))
		{
			operate_flag = 1 ;
			operate_motor();
		}
		if (key == 'C')
		{
			reset_system();
			Stepper_APP_Runnable();
		}
	}
	
}

static void define_state (void)
{
	LCD_Write_String_Cursor(1,1,(u8*)"Choice:");
	LCD_Write_String_Cursor(2,1,(u8*)"1.ANGLE");
	LCD_Write_String_Cursor(2,9,(u8*)"2.ROTATE");
	LCD_Set_Cursor(1,9);
}

static void reset_system(void)
{
	init_flag = 0 ;
	LCD_Clear_Screen();
	i = 0 ;
	operate_flag = 0 ;
}

static void Get_Choice (void) 
{
	u8  check_flag = 1 ;
	u8 i ;
	
	while (check_flag)
	{
		key = KeyPad_Get_Key() ;
		if (key!=NO_KEY)
		{
			if ('C'==key)
			{
				reset_system();
				Stepper_APP_Runnable();
				break ;
			}
			else if ((key=='1')||(key=='2'))
			{
				if ('1'==key)
				{
					motor_state = ANGLE ;
				}
				else
				{
					motor_state = ROTATE ; 
				}
				LCD_Write_Character(key);
				for (i=0;i<50;i++)
				{
					key = KeyPad_Get_Key() ;
					if ('C'==key)
					{
						reset_system();
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
				LCD_Write_String_Cursor(1,1,(u8*)"Choice:");
				LCD_Set_Cursor(1,9);
			}
		}
		
	}
}

static void print_Choice (void)
{
	if (ANGLE == motor_state)
	{
		LCD_Write_String_Cursor(1,1,(u8*)"Angle:");
		LCD_Write_String_Cursor(2,1,(u8*)"POS>>CW");
		LCD_Write_String_Cursor(2,9,(u8*)"NEG>>CCW");
		LCD_Set_Cursor(1,8);
	}
	else 
	{
		LCD_Write_String_Cursor(1,1,(u8*)"no.Rot:");
		LCD_Write_String_Cursor(2,1,(u8*)"POS>>CW");
		LCD_Write_String_Cursor(2,9,(u8*)"NEG>>CCW");
		LCD_Set_Cursor(1,9);
	}
}

static void Fill_Buffer (void)
{
	str_buffer[i] = key ;
	i++ ;
}

static void operate_motor(void)
{
	str_buffer[i] = '\0';
	i=0 ;
	data = String_To_Int(str_buffer);
	
	if (ANGLE == motor_state)
	{
		if (data>=0)
		{
			while(data>360)
			{
				data -= 360 ;
			}
			Stepper_Rotate_CW_By_Angle(data);
		}
		else 
		{
			while(data<(s32)-360)
			{
				data += 360 ;
			}
			data *= -1 ;
			Stepper_Rotate_Counter_CW_By_Angle(data);
		}
	}
	else
	{
		if (data>=0)
		{
			Stepper_Rotate_CW_By_nof_Rotations(data);
		}
		else
		{
			data *= -1 ;
			Stepper_Rotate_Counter_CW_By_nof_Rotations(data);
		}
	}
}