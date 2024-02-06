/********************************* Includes *********************************/
#include "StdTypes.h"
#include "SENSORS_Int.h"
#include "DIO_Int.h"
#include "MOTOR_Int.h"
#include "LCD_Int.h"
#include "LED_Int.h"
#include "KeyPad_Int.h"
#include "EEPROM_Int.h"
#include "ADC_Int.h"
#include "Fire_System_Int.h"
#include "MemMap.h"

#define F_CPU		8000000UL
#include <util/delay.h>


/************** GLobal Variables *******************/

static u8 password[PASSWORD_SIZE]  ;
static volatile u16 temp ;
static volatile u16 smoke_per ;
static u8 pass_buffer[PASSWORD_SIZE];
static u16 First_address ;
static volatile u16 smoke_val ;
static system_state_t state = FINE_STATE ;
static u8 fire_flag = 0 ;
static u8 new_flag = 0 ;
static u8 old_flag =0 ;
static u8 reset_flag = 0 ;

/********************* Prototypes ****************************/
static void ADC_Fun (void);
static void Pass_Fill (u8 *pass); 
static password_status_t Pass_Compare (u8 *pass1,u8 *pass2);
static void Set_New_Password (u8 *new);
static void old_Pass_Fill (u8 *pass) ;
static void new_Pass_Fill (u8 *pass) ;

/********************************* Implementation *********************************/
static void ADC_Fun (void)
{
	
	static volatile u8 read_flag = 0;
	if (0==read_flag)
	{
		temp = LM35_Read_Temp_No_Block() ;
		read_flag = 1 ;
		ADC_Start_Conversion(SMOKE_SENSOR);
	}
	else if (1==read_flag)
	{
		smoke_val = MPX_Read_Pressure_No_Block();
		smoke_per = (smoke_val*(u32)100) /115 ;
		read_flag = 0 ;
		ADC_Start_Conversion(TEMP_SENSOR);
	}
	
}

void Fire_System_Init (void) 
{
	u8 i ; 
	LCD_Write_String_Cursor(1,3,(u8*)"Fire System");
	DIO_WritePin(ALARM_LED,LOW);
	DIO_WritePin(EMERGENCY_LED,LOW);
	_delay_ms(1500);
	LCD_Clear_Screen();
	ADC_Start_Conversion(TEMP_SENSOR);
	ADC_Set_Call_Back(ADC_Fun);
	ADC_INTERRUPT_ENABLE();	
	
	GLOBAL_INTERRUPT_DISABLE();
	
	First_address = EEPROM_Read_Data(1);
	First_address &= 0x00FF ;
	First_address |= ((u16)EEPROM_Read_Data(0)<<8);
	
	for (i=0;i<PASSWORD_SIZE;i++)
	{
		password[i] = EEPROM_Read_Data(First_address+i);
	}
	GLOBAL_INTERRUPT_ENABLE();
}

void Fire_System_Runnable (void)
{
	static u8 temp_flag = 0 ;
	static u8 init_flag = 0 ;
	static u8 clr_flag = 0 ;
	u8 key;
	
	
	if (smoke_per>SMOKE_PERCENT)
	{
		state = FIRE_STATE ;
		fire_flag = 1 ; 
	}
	
	if ((temp>FINE_TEMP)&&(temp<HEAT_TEMP)&&(init_flag==0))
	{
		state = FINE_STATE ;
		DIO_WritePin(ALARM_LED,LOW);
		DIO_WritePin(EMERGENCY_LED,LOW);
		DIO_WritePin(BUZZER_ALARM,LOW);
		DIO_WritePin(MOTOR_PUMP,LOW);
		
	}
	
	key = KeyPad_Get_Key();
	 
	if (key !=NO_KEY)
	{
		if ((key == '*')&&(FINE_STATE==state)&&((0==fire_flag)))
		{
			new_flag = 1 ;
			if (1==new_flag)
			{
				LCD_Clear_Screen();
				new_flag = 0 ;
			}
			reset_flag = 0 ;
			old_flag = 0 ;
			Set_New_Password(password);
			LCD_Clear_Screen();
		}
	}
	
	if ((temp>=HEAT_TEMP)&&(0==fire_flag))
	{
		state = HEAT_STATE ;
		DIO_WritePin(ALARM_LED,HIGH);
		DIO_WritePin(MOTOR_PUMP,LOW);
		DIO_WritePin(BUZZER_ALARM,LOW);
		
		temp_flag = 0 ;
		init_flag = 1 ;
	}
	
	else if ((temp<=FINE_TEMP)&&(0==fire_flag))
	{
		state = FINE_STATE ;
		DIO_WritePin(ALARM_LED,LOW);
		DIO_WritePin(EMERGENCY_LED,LOW);
		DIO_WritePin(MOTOR_PUMP,LOW);
		DIO_WritePin(BUZZER_ALARM,LOW);
		
		temp_flag = 0 ;
		init_flag = 1 ;
	}
	
	
	else if (FIRE_STATE==state)
	{
		DIO_WritePin(ALARM_LED,LOW);
		DIO_WritePin(EMERGENCY_LED,HIGH);
		DIO_WritePin(MOTOR_PUMP,HIGH);
		DIO_WritePin(BUZZER_ALARM,HIGH);
		if  (0==clr_flag)
		{
			clr_flag = 1 ;
			LCD_Clear_Screen() ;
		}
		LCD_Write_String_Cursor(1,1,(u8*)"Fire");
		LCD_Write_String_Cursor(1,5,(u8*)"/");
		LCD_Write_Number(temp/10);
		LCD_Write_Character('.');
		LCD_Write_Number(temp%10);
		LCD_Write_String((u8*)" ");
		LCD_Write_String_Cursor(1,11,(u8*)"/");
		LCD_Write_Number(smoke_per/10);
		LCD_Write_Character('.');
		LCD_Write_Number(smoke_per%10);
		LCD_Write_Character('%');
		LCD_Write_String_Cursor(2,1,(u8*)"PASSWORD:");
	}
	
	if ((FINE_STATE==state)||(HEAT_STATE==state))
	{
		if ((state==FINE_STATE)&&(0==temp_flag))
		{
			LCD_Write_String_Cursor(1,3,(u8*)"FINE MODE");
			temp_flag = 1 ;
			LCD_Write_String_Cursor(2,8,(u8*)"x>newpass");
		}
		else if ((state==HEAT_STATE)&&(0==temp_flag))
		{
			LCD_Clear_Cursor(2,8,10);
			LCD_Write_String_Cursor(1,3,(u8*)"HEAT MODE");
			temp_flag = 1 ;
		}
		LCD_Write_String_Cursor(2,1,(u8*)"T:");
		LCD_Write_Number(temp/10);
		LCD_Write_Character('.');
		LCD_Write_Number(temp%10);
		LCD_Write_String((u8*)" ");
		
	}
	
	else if ((1==fire_flag)&&(state==FIRE_STATE))
	{
		Pass_Fill(pass_buffer);
		if (Pass_Compare(pass_buffer,password)==WRONG_PASSWORD)
		{
			LCD_Clear_Cursor(2,1,16);
			LCD_Write_String_Cursor(2,1,(u8*)"WRONG PASSWORD!!");
			_delay_ms(1000);
			LCD_Clear_Cursor(2,1,16);
		}
		else  
		{
			fire_flag = 0 ;
			LCD_Clear_Cursor(2,1,16);
			LCD_Write_String_Cursor(2,1,(u8*)"CORRECT PASSWORD");
			_delay_ms(1000);
			LCD_Clear_Cursor(2,1,16);
			DIO_WritePin(EMERGENCY_LED,LOW);
			DIO_WritePin(MOTOR_PUMP,LOW);
			temp_flag = 0 ; 
			clr_flag = 0 ;
			init_flag = 0 ;
			old_flag = 0 ;
			LCD_Clear_Screen();
		}
	}
	
}


static void Pass_Fill (u8 *pass)
{
	u8 i=0 ; 
	u8 key ;
	u8 pos = 10 ;
	LCD_Set_Cursor(2,pos);
	while (i<PASSWORD_SIZE)
	{
		LCD_Write_String_Cursor(1,5,(u8*)"/");
		LCD_Write_Number(temp/10);
		LCD_Write_Character('.');
		LCD_Write_Number(temp%10);
		LCD_Write_String((u8*)" ");
		LCD_Write_String_Cursor(1,11,(u8*)"/");
		LCD_Write_Number(smoke_per/10);
		LCD_Write_Character('.');
		LCD_Write_Number(smoke_per%10);
		LCD_Write_Character('%');
		
		key = KeyPad_Get_Key();
		if (key!=NO_KEY)
		{
			if (((key>='0')&&(key<='9'))||(key=='/'))
			{
				if ((key=='/')&&(i!=0)&&(pos!=10))
				{
					LCD_Clear_Cursor(2,pos-1,10);
					pos-- ;
					i--;
				}
				else 
				{
					if (key!='/')
					{
						LCD_Set_Cursor(2,pos);
						pass[i] = key ;
						LCD_Write_Character('*');
						i++ ;
						pos++;
					}
					
				}
				
			}
		}
	}
}


static password_status_t Pass_Compare (u8 *pass1,u8 *pass2)
{
	password_status_t state = CORRECT_PASSWORD ;
	u8 i ;
	for (i=0 ;i<PASSWORD_SIZE ;i++)
	{
		if (pass1[i]!=pass2[i])
		{
			state = WRONG_PASSWORD ;
			break ;
		}
	}
	
	return state ;
}

static void Set_New_Password (u8 *new)
{
	u8 i ;
	old_flag = 0 ;
	static password_status_t pass_state = WRONG_PASSWORD ;
	LCD_Write_String_Cursor(1,1,(u8*)"OLD:");
	LCD_Write_String_Cursor(2,1,(u8*)"NEW:");
	LCD_Set_Cursor(1,5);
	old_Pass_Fill(pass_buffer);
	u8 key = KeyPad_Get_Key();
	pass_state = Pass_Compare(pass_buffer,password);
	
	while ((old_flag<3)&&(pass_state!=CORRECT_PASSWORD)&&(reset_flag==0))
	{
		key = KeyPad_Get_Key();
		
		if ((smoke_per>SMOKE_PERCENT)||(key=='C'))
		{
			state = FIRE_STATE ;
			fire_flag = 1 ;
			old_flag = 0 ;
			new_flag = 0 ;
			LCD_Clear_Screen();
			reset_flag = 1 ;
			return ;
		}
			if (1==fire_flag)
			{
				LCD_Clear_Screen();
				return ;
			}
			LCD_Clear_Cursor(1,1,16);
			LCD_Write_String_Cursor(1,1,(u8*)"WRONG PASSWORD!!");
			_delay_ms(500);
			LCD_Clear_Cursor(1,1,16);
			LCD_Write_String_Cursor(1,1,(u8*)"OLD:");
			old_Pass_Fill(pass_buffer);
			pass_state = Pass_Compare(pass_buffer,password);
		
	}
	if (CORRECT_PASSWORD==pass_state)
	{
		LCD_Clear_Cursor(1,1,16);
		LCD_Write_String_Cursor(1,1,(u8*)"CORRECT PASSWORD");
		_delay_ms(500);
		LCD_Clear_Cursor(1,1,16);
		LCD_Write_String_Cursor(1,1,(u8*)"ENTER NEW PASS");
		new_Pass_Fill(password);
		GLOBAL_INTERRUPT_DISABLE();
		
		First_address += PASSWORD_SIZE ;
		if (First_address>AVAL_RANGE)
		{
			First_address = 2;
		}
		EEPROM_Write_Data(1,(u8)First_address);
		EEPROM_Write_Data(0,(u8)(First_address>>8));
		for (i=0;i<PASSWORD_SIZE;i++)
		{
			EEPROM_Write_Data(First_address+i,password[i]);
		}
		GLOBAL_INTERRUPT_ENABLE();
		LCD_Clear_Screen();
		LCD_Write_String_Cursor(1,1,(u8*)"PASSWORD SAVED");
		_delay_ms(1000);
		LCD_Clear_Screen();
		old_flag= 0 ; 
	}
	if (old_flag==3)
	{
		LCD_Clear_Cursor(1,1,16);
		LCD_Write_String_Cursor(1,1,(u8*)"WRONG PASSWORD!!");
		_delay_ms(500);
		LCD_Clear_Screen();
		LCD_Write_String_Cursor(1,1,(u8*)"TRY AGAIN LATER");
		_delay_ms(500);
		LCD_Clear_Screen();
		old_flag = 0 ;
	}
}

static void old_Pass_Fill (u8 *pass)
{
	u8 i=0 ;
	u8 key ;
	u8 pos = 5 ;
	
	
	old_flag++ ;
	
	while (i<PASSWORD_SIZE)
	{
		if (smoke_per>=500)
		{
			fire_flag = 1 ;
			old_flag = 0 ;
			new_flag = 0 ;
			state = FIRE_STATE ;
			return ;
		}
		key = KeyPad_Get_Key();
		if (key!=NO_KEY)
		{
			if (key == 'C')
			{
				LCD_Clear_Screen();
				old_flag = 0 ;
				reset_flag = 1 ;
				return ;
			}
			else if (((key>='0')&&(key<='9'))||(key=='/'))
			{
				if ((key=='/')&&(i!=0)&&(pos!=5))
				{
					LCD_Clear_Cursor(1,pos-1,10);
					pos-- ;
					i--;
				}
				else
				{
					if (key!='/')
					{
						LCD_Set_Cursor(1,pos);
						pass[i] = key ;
						LCD_Write_Character('*');
						i++ ;
						pos++;
					}
					
				}
				
			}
		}
	}
	
}

static void new_Pass_Fill (u8 *pass)
{
	u8 i=0 ;
	u8 key ;
	u8 pos = 5 ;
	while (i<PASSWORD_SIZE)
	{
		key = KeyPad_Get_Key();
		if (key!=NO_KEY)
		{
			if (((key>='0')&&(key<='9'))||(key=='/'))
			{
				if ((key=='/')&&(i!=0)&&(pos!=5))
				{
					LCD_Clear_Cursor(2,pos-1,10);
					pos-- ;
					i--;
				}
				else
				{
					if (key!='/')
					{
						LCD_Set_Cursor(2,pos);
						pass[i] = key ;
						LCD_Write_Character('*');
						i++ ;
						pos++;
					}
					
				}
				
			}
		}
	}
}