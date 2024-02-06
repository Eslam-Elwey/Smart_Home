
#include "StdTypes.h"
#include "DIO_Int.h"
#include "MOTOR_Cfg.h"
#include "MOTOR_Int.h"
#include "Timers_Int.h"

/*Timer0 PWM Mode */
void MOTOR_Init(void) 
{
	Timer0_OC0_Mode(Timer0_OC0_SET_COMPARE_MATCH);
}


void MOTOR_Rotate_CW(motor_t motor_no) 
{
	DIO_WritePin(motor_arr[motor_no].MOTOR_ENABLE_1,HIGH);
	DIO_WritePin(motor_arr[motor_no].MOTOR_ENABLE_2,LOW);
}

void MOTOR_Rotate_Counter_CW(motor_t motor_no) 
{
	DIO_WritePin(motor_arr[motor_no].MOTOR_ENABLE_1,LOW);
	DIO_WritePin(motor_arr[motor_no].MOTOR_ENABLE_2,HIGH);
}

void MOTOR_Stop(motor_t motor_no) 
{
	DIO_WritePin(motor_arr[motor_no].MOTOR_ENABLE_1,LOW);
	DIO_WritePin(motor_arr[motor_no].MOTOR_ENABLE_2,LOW);
}

void MOTOR_Set_Speed(motor_t motor_no , u8 speed_Percentage)
{
	u8 ocr_val ; 
	if (speed_Percentage>100)
	{
		return ; 
	}
	ocr_val = ((u16)speed_Percentage * 255 )/100 ;
	if ((ocr_val>1)&&(ocr_val<255))
	{
		TIMER0_OC0_WRITE_VALUE(255-(ocr_val-1));
	}
	else if (ocr_val==255)
	{
		DIO_WritePin(PINB3,HIGH);
	}
	else 
	{
		DIO_WritePin(PINB3,LOW);
	}
}