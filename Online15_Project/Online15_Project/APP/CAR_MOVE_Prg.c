
#include "StdTypes.h"
#include "MOTOR_Int.h"
#include "BUTTON_Int.h"
#include "LED_Int.h"
#include "CAR_MOVE_Int.h"


static void CAR_MOVE_Forward (void);
static void CAR_MOVE_Backward (void);
static void CAR_MOVE_Right (void);
static void CAR_MOVE_Left (void);


void CAR_MOVE_Init (void)
{
	
}

void CAR_MOVE_RUNNABLE (void) 
{
	if (BUTTON_PRESSED == BUTTON_Get_status(MOVE_FWD_BUTTON))
	{
		CAR_MOVE_Forward();
		while(BUTTON_PRESSED == BUTTON_Get_status(MOVE_FWD_BUTTON));
	}
	
	if (BUTTON_PRESSED == BUTTON_Get_status(MOVE_BACK_BUTTON))
	{
		CAR_MOVE_Backward();
		while(BUTTON_PRESSED == BUTTON_Get_status(MOVE_BACK_BUTTON));
	}
	
	if (BUTTON_PRESSED == BUTTON_Get_status(MOVE_RIGHT_BUTTON))
	{
		CAR_MOVE_Right();
		while(BUTTON_PRESSED == BUTTON_Get_status(MOVE_RIGHT_BUTTON));
	}
	
	if (BUTTON_PRESSED == BUTTON_Get_status(MOVE_LEFT_BUTTON))
	{
		CAR_MOVE_Left();
		while(BUTTON_PRESSED == BUTTON_Get_status(MOVE_LEFT_BUTTON));
	}
}


static void CAR_MOVE_Forward (void)
{
	MOTOR_Rotate_CW(FWD_RIGHT_WHEEL);
	MOTOR_Rotate_Counter_CW(FWD_LEFT_WHEEL);
	MOTOR_Rotate_CW(BWD_RIGHT_WHEEL);
	MOTOR_Rotate_Counter_CW(BWD_LEFT_WHEEL);
	LED_Turn_Off(1);
	LED_Turn_Off(2);
	LED_Turn_Off(3);
	LED_Turn_On(0);
}

static void CAR_MOVE_Backward (void)
{
	MOTOR_Rotate_Counter_CW(FWD_RIGHT_WHEEL);
	MOTOR_Rotate_CW(FWD_LEFT_WHEEL);
	MOTOR_Rotate_Counter_CW(BWD_RIGHT_WHEEL);
	MOTOR_Rotate_CW(BWD_LEFT_WHEEL);
	LED_Turn_Off(0);
	LED_Turn_Off(2);
	LED_Turn_Off(3);
	LED_Turn_On(1);
}

static void CAR_MOVE_Right (void)
{
	MOTOR_Stop (FWD_RIGHT_WHEEL);
	MOTOR_Stop (BWD_RIGHT_WHEEL);
	MOTOR_Rotate_CW(FWD_LEFT_WHEEL);
	MOTOR_Rotate_CW(BWD_LEFT_WHEEL);
	LED_Turn_Off(0);
	LED_Turn_Off(1);
	LED_Turn_Off(3);
	LED_Turn_On(2);
	
}

static void CAR_MOVE_Left (void)
{
	MOTOR_Stop (FWD_LEFT_WHEEL);
	MOTOR_Stop (BWD_LEFT_WHEEL);
	MOTOR_Rotate_Counter_CW(FWD_RIGHT_WHEEL);
	MOTOR_Rotate_Counter_CW(BWD_RIGHT_WHEEL);
	LED_Turn_Off(0);
	LED_Turn_Off(1);
	LED_Turn_Off(2);
	LED_Turn_On(3);
	
}
