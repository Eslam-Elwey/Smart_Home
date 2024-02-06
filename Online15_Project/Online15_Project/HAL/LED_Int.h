
#ifndef LED_INT_H_
#define LED_INT_H_
#include "DIO_Int.h"

typedef enum 
{
	ACTIVE_LOW=0,
	ACTIVE_HIGH 
}volt_status_t;

typedef struct 
{
	DIO_Pin_t led_pin_no : 6 ;
	volt_status_t volt : 1 ; 
}led_t;

void LED_Init(void);

void LED_Turn_On (u8 led_no);

void LED_Turn_Off (u8 led_no);

void LED_Toggle_state (u8 led_no);

void LED_Count_turn_on (u8 led_count);


#endif /* LED_INT_H_ */