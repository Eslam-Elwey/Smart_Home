
#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Int.h"
#include "UART_Int.h"
#include "UART_Services_Int.h"
#include "UART_Stack_Int.h"
#include "Servo_Int.h"
#include "MOTOR_Int.h"
#include "Stepper_Int.h"
#include "LCD_Int.h"
#include "UltraSonic_Int.h"
#include "RGB_Int.h"
#include "ADC_Int.h"
#include "Timers_Int.h"
#include "Timers_Services_Int.h"
#include "SMART_HOME_Int.h"

#define F_CPU		8000000UL
#include <util/delay.h>


/** Other Files Global Variables **/

extern const u8 *color_names[TOTAL_RGB_COLOURS] ;
extern volatile u8 serial_flag ;

/************ Private Function ***************/

static void String_Parsing (void);
static u8 String_Compare (u8 *s1 ,u8 *s2) ;
static s8 Get_string_match_index (void)  ;
static void Get_Match_Color (void)   ;

/**********************************************************/

static void RED_LED_Func (void);
static void GREEN_LED_Func (void);
static void BLUE_LED_Func (void);
static void Servo_Func (void);
static void Stepper_Func (void);
static void Relay1_Func (void);
static void Relay2_Func (void);
static void Buzzer_Func (void);
static void UltraSonic_Func (void);
static void ADC_Func (void);
static void RGB_Func (void);
static void DC_Motor_Func (void);
static void LCD_Func (void);

/********* Global Variables *****************/

static u8 str1[15] ;
static u8 str2[15] ;
static u8 received_string[40] ;
static u8 servo_angle ;
static s16 stepper_angle ;
static s8 stepper_rotate ;
static u8 Rgb_Current;
static u8 Rgb_Pervious;
static u16 ultraSonic_val;
static u16 ADC_volt;
static s8 index = -1; 
static s8 RGB_Index ; 

const serial_uart_t serial_data[TOTAl_SERIAL_DATA]={
		
										{(u8*)"REDLED",RED_LED_Func},
										{(u8*)"GREENLED",GREEN_LED_Func},
										{(u8*)"BLUELED",BLUE_LED_Func},
										{(u8*)"SERVO",Servo_Func},
										{(u8*)"RGB",RGB_Func},
										{(u8*)"STEPPERA",Stepper_Func},
									    {(u8*)"STEPPERR",Stepper_Func},
										{(u8*)"ULTRASONIC",UltraSonic_Func},
										{(u8*)"ADC",ADC_Func},
										{(u8*)"MOTOR",DC_Motor_Func},//CW CCW STOP
										{(u8*)"LCD",LCD_Func},
										{(u8*)"RELAY1",Relay1_Func},
										{(u8*)"RELAY2",Relay2_Func},
										{(u8*)"BUZZER",Buzzer_Func}
	
};

/********************************************************************/


void SMART_HOME_Init (void)
{
	#if SMART_HOME == BLUETOOTH_CHOICE
		UART_Receive_String_Async(received_string);
	#elif SMART_HOME == DOCKLIGHT_CHOICE
		UART_Receive_String_Async_docklight(received_string);
	#endif
	
	Rgb_Pervious = 0 ;
}

void SMART_HOME_Runnable (void)
{
		if (1==serial_flag)
		{
			serial_flag = 0 ;
			LCD_Clear_Screen();
			UART_Send_String((u8*)"PROCESSING  ");
			String_Parsing();
			LCD_Set_Cursor(1,1);
			#if SMART_HOME == BLUETOOTH_CHOICE
			LCD_Write_String(received_string);
			LCD_Write_String((u8*)"        ");
			#endif
			index = Get_string_match_index() ;
			if (index==-1)
			{
				UART_Send_String((u8*)"Command Not Found  ");
			}
			else 
			{
				#if SMART_HOME == DOCKLIGHT_CHOICE
				LCD_Write_String(str1);
				LCD_Write_String((u8*)"        ");
				#endif 
				serial_data[index].pf() ;
				UART_Send_String((u8*)"DONE  ");
			}
		}
		
}


/********************************************************************/

static s8 Get_string_match_index (void) 
{
	u8  i , ret_val;
	s8 index = -1 ;
	
	for (i=0 ;i<TOTAl_SERIAL_DATA;i++)
	{
		ret_val = String_Compare (str1 ,(u8*) serial_data[i].str );
		if (ret_val == 1)
		{
			index = i ;
			break ;
		}
	}
	
	return index ;
}

static void String_Parsing (void)
{
	u8 i = 0 , j =0 , flag = 0  ;
	while (received_string[i]!='\0')
	{
		if ((received_string[i]!=' ')&&(0==flag))
		{
			str1[i] = received_string[i] ;
			i++ ;
		}
		else if (received_string[i]==' ')
		{
			str1[i] = '\0' ;
			flag = 1 ;
			i++;
		}
		else 
		{
			str2[j] = received_string[i] ;
			j++ ;
			i++ ;
		}

	}
	str2[j] = '\0' ;
}


static u8 String_Compare (u8 *s1 , u8 *s2) 
{
	u8 i  , ret_val = 1 ;
	for (i=0;s1[i];i++)
	{
		if (s1[i]!=s2[i])
		{
			ret_val = 0 ;
			break ;
		}
	}
	
	return ret_val ;
}

static void RED_LED_Func (void)
{
	if (String_Compare(str2,(u8*)"ON"))
	{
		DIO_WritePin(RED_LED_PIN,HIGH);
	}
	else if (String_Compare(str2,(u8*)"OFF"))
	{
		DIO_WritePin(RED_LED_PIN,LOW);
	}
	else 
	{
		UART_Send_String((u8*)"Command Not RIGHT  ");
	}
}


static void GREEN_LED_Func (void)
{
	if (String_Compare(str2,(u8*)"ON"))
	{
		DIO_WritePin(GREEN_LED_PIN,HIGH);
	}
	else if (String_Compare(str2,(u8*)"OFF"))
	{
		DIO_WritePin(GREEN_LED_PIN,LOW);
	}
	else
	{
		UART_Send_String((u8*)"Command Not RIGHT ");
	}
}


static void BLUE_LED_Func (void)
{
	if (String_Compare(str2,(u8*)"ON"))
	{
		DIO_WritePin(BLUE_LED_PIN,HIGH);
	}
	else if (String_Compare(str2,(u8*)"OFF"))
	{
		DIO_WritePin(BLUE_LED_PIN,LOW);
	}
	else
	{
		UART_Send_String((u8*)"Command Not RIGHT  ");
	}
}


static void Servo_Func (void)
{
	Timer1_Init(TIMER1_FAST_PWM_OCR1A_TOP,TIMER1_PRESCALER_CLK_8);
	Servo_Init();
	servo_angle = (u8)String_To_Int(str2);
	Servo_Set_angle(servo_angle);
}


static void Stepper_Func (void)
{
	if (index==5)
	{
		stepper_angle = (s16)String_To_Int(str2) ;
		if (stepper_angle>=0)
		{
			Stepper_Rotate_CW_By_Angle(stepper_angle);
		}
		else 
		{
			Stepper_Rotate_Counter_CW_By_Angle(-1*stepper_angle);
		}
	}
	else if (index==6)
	{
		stepper_rotate = (s8)String_To_Int(str2) ;
		if (stepper_rotate>=0)
		{
			Stepper_Rotate_CW_By_nof_Rotations(stepper_rotate);
		}
		else
		{
			Stepper_Rotate_Counter_CW_By_nof_Rotations(-1*stepper_rotate);
		}
	}
}

static void Relay1_Func (void)
{
	if (String_Compare(str2,(u8*)"ON"))
	{
		DIO_WritePin(RELAY1_PIN,HIGH);
	}
	else if (String_Compare(str2,(u8*)"OFF"))
	{
		DIO_WritePin(RELAY1_PIN,LOW);
	}
	else
	{
		UART_Send_String((u8*)"Command Not RIGHT  ");
	}
}


static void Relay2_Func (void)
{
	if (String_Compare(str2,(u8*)"ON"))
	{
		DIO_WritePin(RELAY2_PIN,HIGH);
	}
	else if (String_Compare(str2,(u8*)"OFF"))
	{
		DIO_WritePin(RELAY2_PIN,LOW);
	}
	else
	{
		UART_Send_String((u8*)"Command Not RIGHT  ");
	}
}


static void Buzzer_Func (void)
{
	if (String_Compare(str2,(u8*)"ON"))
	{
		DIO_WritePin(BUZZER_PIN,HIGH);
	}
	else if (String_Compare(str2,(u8*)"OFF"))
	{
		DIO_WritePin(BUZZER_PIN,LOW);
	}
	else
	{
		UART_Send_String((u8*)"Command Not RIGHT  ");
	}
}


static void UltraSonic_Func (void)
{
	UltraSonic_Init();
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_PRESCALER_CLK_8);
	UltraSonic_Start_Trigger(Ultra_S1) ;
	if (1==UltraSonic_Get_Distance(Ultra_S1,&ultraSonic_val) )
	{
		LCD_Clear_Cursor(2,1,16);
		LCD_Write_Number(ultraSonic_val);
		UART_SEND_2_Byte_Number(ultraSonic_val);
	}
	else 
	{
		UART_Send_String_Async((u8*)" TOO FAR  ");
	}
}


static void ADC_Func (void)
{
	ADC_volt = ADC_Read_Volt(ADC_CHANNEL_0) ;
	LCD_Clear_Cursor(2,1,16);
	LCD_Write_Number(ADC_volt);
	UART_SEND_2_Byte_Number(ADC_volt);
}


static void RGB_Func (void)
{
	Timer0_Init(TIMER0_FAST_PWM_MODE,Timer0_PRESCALER_CLK_8);
	Timer1_Init(TIMER1_PWM_PHASE_CR_8_BIT_TOP,TIMER1_PRESCALER_CLK_8);
	Timer2_Init(TIMER2_NORMAL_MODE,TIMER2_PRESCALER_CLK_1024);
	RGB_Init();
	Get_Match_Color();
	
	if (-1==RGB_Index)
	{
		UART_Send_String((u8*)"COLOR Not Found  ");
	}
	else 
	{
		Rgb_Current = RGB_Index ;
		RGB_Convert_Colours((rgb_color_name_t)Rgb_Pervious,(rgb_color_name_t)Rgb_Current);
		Rgb_Pervious = Rgb_Current ;
	}
}


static void DC_Motor_Func (void)
{
	if (String_Compare(str2,(u8*)"CW"))
	{
		MOTOR_Rotate_CW(M1);
	}
	else if (String_Compare(str2,(u8*)"CCW"))
	{
		MOTOR_Rotate_Counter_CW(M1);
	}
	else if (String_Compare(str2,(u8*)"STOP"))
	{
		MOTOR_Stop(M1);
	}
	else
	{
		UART_Send_String((u8*)"Command Not RIGHT  ");
	}
}


static void LCD_Func (void)
{
	LCD_Clear_Cursor(2,1,16);
	LCD_Set_Cursor(2,1);
	LCD_Write_String(str2);
}


static void Get_Match_Color (void)  
{
	u8 i  ,  ret_val = 0 ;
	
	for ( i=0 ; i <TOTAL_RGB_COLOURS ;i++)
	{
		ret_val = String_Compare(str2 ,(u8*) color_names[i]);
		if (ret_val==1)
		{
			break ;
		}
	}
	
	if (ret_val==1)
	{
		RGB_Index = i ;
	}
	else 
	{
		RGB_Index = -1 ;
	}
}