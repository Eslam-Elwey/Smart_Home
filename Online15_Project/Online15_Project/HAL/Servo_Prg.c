
#include "StdTypes.h"
#include "Timers_Int.h"
#include "Servo_Int.h"

void Servo_Init (void) 
{
	/* Use TIMER1_FAST_PWM_OCR1A_TOP / TIMER1_PRESCALER_CLK_8
	Generate PWM Freq 50 HZ
	Write In OCR1A 19999*/
	TIMER1_OC1A_WRITE_VALUE(TOTAL_TIME_FREQ);
	Timer1_Set_OC1B_Mode(TIMER1_OC1B_CLEAR);
}


void Servo_Set_angle (u8 angle) 
{
	u16 Ton_Val ;
	
	if (angle > 180 )
	{
		angle  = 180 ;
	}
	Ton_Val = (( (u32)ACTAUL_VAL* angle ) / 9) + START_VAL_ANGLE ;
	TIMER1_OC1B_WRITE_VALUE(Ton_Val) ;
}


void Servo_Set_Pos (servo_pos_t angle) 
{
	Servo_Set_angle(angle);
}