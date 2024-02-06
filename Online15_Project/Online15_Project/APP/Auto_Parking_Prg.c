

#include "StdTypes.h"
#include "LCD_Int.h"
#include "DIO_Int.h"
#include "UltraSonic_Int.h"
#include "Servo_Int.h"
#include "Timers_Int.h"
#include "Timers_Services_Int.h"
#include "MOTOR_Int.h"
#include "Auto_Parking_Int.h"
#include "EXI_Int.h"
#define F_CPU		8000000UL
#include <util/delay.h>

/*****************************************************************************************/

static void Auto_park_right_side (void) ;
static void Auto_park_left_side (void) ;
static void Timer2_Func_Cal (void) ;
static void EXI0_func(void);
/*****************************************************************************************/

static u16 read_buffer[TOTAL_ULRASONIC_NUMBER];
static u16 Store_buffer[TOTAL_ULRASONIC_NUMBER];
static ultrasonic_t ultra_sonics[TOTAL_ULRASONIC_NUMBER] = {Ultra_S1,Ultra_S2,Ultra_S3,Ultra_S4};
static u8 current_ultra = 0 ;
static u16 distance ;
static volatile u8 ret_flag = 0 ;
static park_t park_dir = RIGHT_PARK ;
static volatile u8 park_flag_execute = 0 ;
static volatile u8 Running_flag = 0 ; 
static u8 park_flag = 0 ;
static u8 dir_flag = 0 ;

/*****************************************************************************************/

void Auto_Parking_Init (void) 
{
	u8 i ;
	
	Servo_Set_Pos(SERVO_POS_90);
	MOTOR_Rotate_CW(M1);
	MOTOR_Rotate_Counter_CW(M2);
	
	Set_Call_Timer2_Interrupt_Time_ms((u32)FOCUS_TIME_SEC*1000,Timer2_Func_Cal);
	EXT_INT_Set_Call_Back(EXT_INT0,EXI0_func);
	
	
	for (i=0;i<TOTAL_ULRASONIC_NUMBER;i++)
	{
		UltraSonic_Start_Trigger(ultra_sonics[current_ultra]);
		ret_flag = UltraSonic_Get_Distance(ultra_sonics[current_ultra],&distance);
		if (ret_flag==1)
		{
			Store_buffer[i]=distance ;
		}
		current_ultra++ ;
	}
	
	current_ultra = 0 ;

	for(i=0;i<TOTAL_ULRASONIC_NUMBER;i++)
	{
		read_buffer[i] = Store_buffer[i] ;
	}
	
}

void Auto_Parking_Runnable (void) 
{
	
	if (0==Running_flag)
	{
		if (0==park_flag)
		{
			park_flag = 1 ;
			LCD_Clear_Screen();
		}
		LCD_Write_String_Cursor(1,3,(u8*)"DRIVE MODE");
		Servo_Set_Pos(SERVO_POS_90);
		MOTOR_Rotate_CW(M1);
		MOTOR_Rotate_Counter_CW(M2);
		DIO_WritePin(PINB2,LOW);
		DIO_WritePin(PINB3,HIGH);
	}
	
	else if (1==Running_flag)
	{
			park_flag = 0 ;
	
			DIO_WritePin(PINB2,HIGH);
			DIO_WritePin(PINB3,LOW);
			LCD_Write_String_Cursor(1,1,(u8*)"FR:");
			if (read_buffer[0]<1000)
			{
				LCD_Write_Number(read_buffer[0]);
				LCD_Write_String((u8*)"   ");
				
			}
			
			LCD_Write_String_Cursor(1,9,(u8*)"BR:");
			if (read_buffer[1]<1000)
			{
				LCD_Write_Number(read_buffer[1]);
				LCD_Write_String((u8*)"    ");
			}	
			LCD_Write_String_Cursor(2,1,(u8*)"FL:");
			if (read_buffer[2]<1000)
			{
				LCD_Write_Number(read_buffer[2]);
				LCD_Write_String((u8*)"   ");
			}
			
			LCD_Write_String_Cursor(2,9,(u8*)"BL:");
			if (read_buffer[3]<1000)
			{
				LCD_Write_Number(read_buffer[3]);
				LCD_Write_String((u8*)"    ");
			}
			
		if ((Store_buffer[0]>MINIMUM_ACCEPTANCE_WIDTH)&&(0==park_flag_execute)&&(dir_flag==0))
		{
			dir_flag = 1 ;
			
			TIMER2_OVER_FLOW_INTERRUPT_ENABLE();
			
			park_dir = RIGHT_PARK ;
		}
		if ((Store_buffer[2]>MINIMUM_ACCEPTANCE_WIDTH)&&(0==park_flag_execute)&&(dir_flag==0))
		{
			TIMER2_OVER_FLOW_INTERRUPT_ENABLE();
			dir_flag = 1 ;
			park_dir = LEFT_PARK ;
		}
		
		if ((1==park_flag_execute)||(2==park_flag_execute))
		{
			if (RIGHT_PARK==park_dir)
			{
				if (2==park_flag_execute)
				{
					TIMER2_OVER_FLOW_INTERRUPT_DISABLE();
					LCD_Clear_Screen();
					
					LCD_Write_String_Cursor(1,2,(u8*)"RIGHT AUTO PARK");
					LCD_Write_String_Cursor(2,4,(u8*)"PROCESSING");
					
					park_flag_execute = 0 ;
					Auto_park_right_side();
					
					LCD_Clear_Screen() ;
					LCD_Write_String_Cursor(1,3,(u8*)"CAR IS PARKED");
					LCD_Write_String_Cursor(2,3,(u8*)"ON RIGHT SIDE");
					Servo_Set_Pos(SERVO_POS_90);
					MOTOR_Stop(M1);
					MOTOR_Stop(M2);
					DIO_WritePin(PINB2,LOW);
					DIO_WritePin(PINB3,LOW);
					_delay_ms(1500);
					Running_flag = 0 ;
					dir_flag = 0 ;
				}
				else if ((Store_buffer[1]>MINIMUM_ACCEPTANCE_WIDTH)&&(1==park_flag_execute)&&(Store_buffer[0]>MINIMUM_ACCEPTANCE_WIDTH))
				{
					TIMER2_OVER_FLOW_INTERRUPT_ENABLE();
				}
				else
				{
					dir_flag = 0 ;
					park_flag_execute = 0 ;
					TIMER2_OVER_FLOW_INTERRUPT_DISABLE();
				}
			}
			else if (LEFT_PARK==park_dir)
			{
				if (2==park_flag_execute)
				{
					TIMER2_OVER_FLOW_INTERRUPT_DISABLE();
					LCD_Clear_Screen();
					
					LCD_Write_String_Cursor(1,2,(u8*)"LEFT AUTO PARK");
					LCD_Write_String_Cursor(2,4,(u8*)"PROCESSING");
					
					park_flag_execute = 0 ;
					Auto_park_left_side();
					LCD_Clear_Screen() ;
					LCD_Write_String_Cursor(1,3,(u8*)"CAR IS PARKED");
					LCD_Write_String_Cursor(2,3,(u8*)"ON LEFT SIDE");
					Servo_Set_Pos(SERVO_POS_90);
					MOTOR_Stop(M1);
					MOTOR_Stop(M2);
					DIO_WritePin(PINB2,LOW);
					DIO_WritePin(PINB3,LOW);
					_delay_ms(1500);
					Running_flag = 0 ;
					dir_flag = 0 ;
				}
				else if ((Store_buffer[3]>MINIMUM_ACCEPTANCE_WIDTH)&&((1==park_flag_execute))&&(Store_buffer[2]>MINIMUM_ACCEPTANCE_WIDTH))
				{
					TIMER2_OVER_FLOW_INTERRUPT_ENABLE();
				}
				else
				{
					park_flag_execute = 0 ;
					dir_flag = 0 ;
					TIMER2_OVER_FLOW_INTERRUPT_DISABLE();
				}
			}
			
		}
		
		UltraSonic_Start_Trigger(ultra_sonics[current_ultra]);
		ret_flag = UltraSonic_Get_Distance(ultra_sonics[current_ultra],&distance);
		if (ret_flag==1)
		{
			Store_buffer[current_ultra]=distance ;
		}
		current_ultra++ ;
		if (current_ultra==TOTAL_ULRASONIC_NUMBER)
		{
			current_ultra = 0 ;
			for (u8 i=0;i<TOTAL_ULRASONIC_NUMBER;i++)
			{
				read_buffer[i] = Store_buffer[i] ;
			}
		}
	}
	
}


static void Auto_park_right_side (void)
{
	u8 angle = 90 ;
	MOTOR_Rotate_Counter_CW(M1);
	MOTOR_Stop(M2);
	while (angle<=180)
	{
		Servo_Set_angle(angle);
		angle += 9 ;
		_delay_ms(150);
	}
	
	_delay_ms(500);
	MOTOR_Stop(M1);
	while (angle>=90)
	{
		Servo_Set_angle(angle);
		angle -= 9 ;
		_delay_ms(150);
	}
	Servo_Set_Pos(SERVO_POS_90);
	_delay_ms(500);
}


static void Auto_park_left_side (void) 
{
	s8 angle = 90 ;
	MOTOR_Rotate_CW(M2);
	MOTOR_Stop(M1);
	while (angle>=0)
	{
		Servo_Set_angle(angle);
		angle -= 9 ;
		_delay_ms(150);
	}
	while (angle<=90)
	{
		Servo_Set_angle(angle);
		angle += 9 ;
		_delay_ms(150);
	}
	_delay_ms(500);
	MOTOR_Stop(M2);
	Servo_Set_Pos(SERVO_POS_90);
	_delay_ms(500);
	
}


static void Timer2_Func_Cal (void) 
{
	if (0==park_flag_execute)
	{
		park_flag_execute = 1 ;
		TIMER2_OVER_FLOW_INTERRUPT_DISABLE();
	}
	else if (1==park_flag_execute)
	{
		park_flag_execute = 2 ;
		TIMER2_OVER_FLOW_INTERRUPT_DISABLE();
	}
}

static void EXI0_func(void)
{
	if (0==Running_flag)
	{
		Running_flag = 1 ;
	}
	else if (1==Running_flag)
	{
		Running_flag = 0 ;
	}

}
