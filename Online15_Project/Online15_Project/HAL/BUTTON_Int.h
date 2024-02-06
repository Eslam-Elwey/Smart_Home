
#ifndef BUTTON_INT_H_
#define BUTTON_INT_H_

#include "DIO_Int.h"

typedef enum 
{
	SIG_LOW,
	SIG_HIGH  
}signal_t;

typedef struct 
{
	DIO_Pin_t button_pin : 6 ; 
	signal_t button_press_sig : 1 ; 
}button_t;

typedef enum 
{
	BUTTON_PRESSED ,
	BUTTON_RELEASED 
}button_status_t;

void BUTTON_Init (void) ;
button_status_t BUTTON_Get_status (u8 but_no);

#endif /* BUTTON_INT_H_ */