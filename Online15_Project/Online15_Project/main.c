
/*********************** Macros *************************************/
#define F_CPU		8000000UL

/************************** Includes *********************************/

#include <util/delay.h>
#include "StdTypes.h"
#include "LED_Int.h"
#include "BUTTON_Int.h"
#include "SEVEN_SEG_Int.h"
#include "STOP_WATCH_Int.h"
#include "MOTOR_Int.h"
#include "CAR_MOVE_Int.h"
#include "Stepper_Int.h"
#include "LCD_Int.h"
#include "KeyPad_Int.h"
#include "Calculator_Int.h"
#include "Number_Converter_Int.h"
#include "StepperAPP_Int.h"
#include "ADC_Int.h"
#include "LCD_Game_Int.h"
#include "SENSORS_Int.h"
#include "EEPROM_Int.h"
#include "Fire_System_Int.h"
#include "TEMP_Filter_Int.h"
#include "EXI_Int.h"
#include "Timers_Int.h"
#include "Timers_Services_Int.h"
#include "RGB_Int.h"
#include "RGB_APP_Int.h"
#include "UltraSonic_Int.h"
#include "Servo_Int.h"
#include "UART_Int.h"
#include "UART_Services_Int.h"
#include "UART_Stack_Int.h"
#include "Auto_Parking_Int.h"
#include "SMART_HOME_Int.h"




int main(void)
{ 
	DIO_Init();
	LCD_Init() ;
	ADC_Init(VREF_AVCC,ADC_SCALER_64);
	UltraSonic_Init();
	UART_Init();	
	Stepper_Motor_Init();
	GLOBAL_INTERRUPT_ENABLE();
	
		SMART_HOME_Init();
	
	
	while (1)
	{		
		SMART_HOME_Runnable();
	}
		
		
}



