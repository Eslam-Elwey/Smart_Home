
#ifndef STOP_WATCH_INIT_H_
#define STOP_WATCH_INIT_H_


#define ONE_BUTTON_INCREASE_OTHER_DECREASE						1
#define ONE_BUTTON_INCREASE_10_OTHER_INCREASE_1					2

/*		ONE_BUTTON_INCREASE_OTHER_DECREASE
		ONE_BUTTON_INCREASE_10_OTHER_INCREASE_1		*/

#define ADJUST_METHOD	ONE_BUTTON_INCREASE_10_OTHER_INCREASE_1

#ifndef ADJUST_METHOD
#define ADJUST_METHOD	ONE_BUTTON_INCREASE_OTHER_DECREASE
#endif


#define PRESS_DELAY					5
#define SEG_SHOW_DELAY				500
#define BUZZER_DELAY_TIME			100
#define STOP_TIME					30
#define ADJUST_DELAY				75

#define RESET						1
#define ADJUST_DECREASE				1
#define ADJUST_INCREASE_1			1
#define REUME_PAUSE					0
#define ADJUST_INCREASE				0
#define ADJUST_INCREASE_10			0
#define SET_MODE					2
#define BUZZER_PORT					PORTC		
#define BUZZER						5		

#define BUZZER_TURN_ON()				(SET_BIT(BUZZER_PORT,BUZZER))
#define BUZZER_TURN_OFF()				(CLR_BIT(BUZZER_PORT,BUZZER))


/**************************************************************************/
typedef enum
{
	ADJUST	 = 0x55 ,
	RUNNABLE = 0xAA
}mode_t;

typedef enum
{
	pause  = 0x55 ,
	resume = 0xAA
}state_t;

typedef enum
{
	RESET_ON  = 0x55 ,
	RESET_OFF = 0XAA
}reset_t;

/***********************************************************************************/

void Stop_Watch_Runnable(void) ;



#endif /* STOP_WATCH_INIT_H_ */