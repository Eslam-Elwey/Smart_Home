
#ifndef SERVO_INT_H_
#define SERVO_INT_H_

#define WIDE_RANGE					499
#define NARROW_RANGE				999

#define VAL1						50
#define VAL2						100

#define START_VAL_ANGLE			WIDE_RANGE

#if START_VAL_ANGLE == WIDE_RANGE 
#define ACTAUL_VAL				VAL2
#else
#define ACTAUL_VAL				VAL1
#endif	

#define TOTAL_TIME_FREQ			19999


typedef enum 
{
	SERVO_POS_0 = 0 , 
	SERVO_POS_90 = 90,
	SERVO_POS_180 = 180
}servo_pos_t;


/* Use TIMER1_FAST_PWM_OCR1A_TOP / TIMER1_PRESCALER_CLK_8
	Generate PWM Freq 50 HZ
	Write In OCR1A 19999*/
void Servo_Init (void) ;
void Servo_Set_angle (u8 angle) ;
void Servo_Set_Pos (servo_pos_t angle) ;

#endif /* SERVO_INT_H_ */