
#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_


#include "DIO_Int.h"


#define KEYPAD_ROWS					4
#define KEYPAD_COLS					4

#ifdef	KEYPAD_PROG


static const u8 KeyPad_arr[KEYPAD_ROWS][KEYPAD_COLS] =
{
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'C','0','=','+'}
};

#endif

#define NO_KEY						'T'


typedef struct 
{
	DIO_Pin_t input[4] ;
	DIO_Pin_t output[4] ;
}KeyPad_t;

const static KeyPad_t key_cofig =
{
	/* KIT CFG */
	
	
	{PIND2,PIND3,PIND4,PIND5},
	{PINB4,PINB5,PINB6,PINB7}
		
	/*{PINC0,PINC1,PINC2,PINC3},
	{PINB1,PINB2,PINB3,PINB4}*/
} ;



#endif /* KEYPAD_CFG_H_ */