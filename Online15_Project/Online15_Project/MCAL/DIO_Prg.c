
#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Int.h"
#include "DIO_Priv.h"
#include "DIO_Cfg.h"


void DIO_Init(void)
{
	u8 i ; 
	for (i=PINA0 ; i<TOTAL_PINS ; i++)
	{
		DIO_InitPin(i,pin_arr[i]);
	}
}

static void DIO_InitPin(DIO_Pin_t pin, DIO_PinStatus_t status)
{
	DIO_Port_t port = pin / 8 ; 
	u8 pin_num = pin % 8 ; 
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
				SET_BIT(DDRA,pin_num);
				CLR_BIT(PORTA,pin_num);
			break;
			
			case PB:
				SET_BIT(DDRB,pin_num);
				CLR_BIT(PORTB,pin_num);
			break;
			
			case PC:
				SET_BIT(DDRC,pin_num);
				CLR_BIT(PORTC,pin_num);
			break;
			
			case PD:
				SET_BIT(DDRD,pin_num);
				CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
				CLR_BIT(DDRA,pin_num);
				CLR_BIT(PORTA,pin_num);
			break;
			
			case PB:
				CLR_BIT(DDRB,pin_num);
				CLR_BIT(PORTB,pin_num);
			break;
			
			case PC:
				CLR_BIT(DDRC,pin_num);
				CLR_BIT(PORTC,pin_num);
			break;
			
			case PD:
				CLR_BIT(DDRD,pin_num);
				CLR_BIT(PORTD,pin_num);
			break;
		}
		break;
		case INPULL:
		switch(port)
		{
			case PA:
				CLR_BIT(DDRA,pin_num);
				SET_BIT(PORTA,pin_num);
			break;
			
			case PB:
				CLR_BIT(DDRB,pin_num);
				SET_BIT(PORTB,pin_num);
			break;
			
			case PC:
				CLR_BIT(DDRC,pin_num);
				SET_BIT(PORTC,pin_num);
			break;
			
			case PD:
				CLR_BIT(DDRD,pin_num);
				SET_BIT(PORTD,pin_num);
			break;
		}
		break;
	}
}

void DIO_WritePin(DIO_Pin_t pin,DIO_PinVoltage_t volt)
{
	DIO_Port_t port = pin / 8 ;
	u8 pin_num = pin % 8 ;
	
	if (volt==HIGH)
	{
		switch(port)
		{
			case PA:
				SET_BIT(PORTA,pin_num);
			break;
			
			case PB:
				SET_BIT(PORTB,pin_num);
			break;
			
			case PC:
				SET_BIT(PORTC,pin_num);
			break;
			
			case PD:
				SET_BIT(PORTD,pin_num);
			break;
		}
	}
	else
	{
		switch(port)
		{
			case PA:
				CLR_BIT(PORTA,pin_num);
			break;
			
			case PB:
				CLR_BIT(PORTB,pin_num);
			break;
			
			case PC:
				CLR_BIT(PORTC,pin_num);
			break;
			
			case PD:
				CLR_BIT(PORTD,pin_num);
			break;
		}
	}
}

DIO_PinVoltage_t DIO_ReadPin(DIO_Pin_t pin)
{
	DIO_Port_t port = pin / 8 ;
	u8 pin_num = pin % 8 ;
	
	DIO_PinVoltage_t volt=LOW;
	
	switch(port)
	{
		case PA:
			volt=READ_BIT(PINA,pin_num);
		break;
		
		case PB:
			volt=READ_BIT(PINB,pin_num);
		break;
		
		case PC:
			volt=READ_BIT(PINC,pin_num);
		break;
		
		case PD:
			volt=READ_BIT(PIND,pin_num);
		break;
	}
	return volt;
}


void DIO_Toggle_Pin(DIO_Pin_t pin)
{
	DIO_Port_t port = pin / 8 ;
	u8 pin_num = pin % 8 ;
	switch(port)
	{
		case PA:
			TOGGLE_BIT(PORTA,pin_num);
		break;
		
		case PB:
			TOGGLE_BIT(PORTB,pin_num);
		break;
		
		case PC:
			TOGGLE_BIT(PORTC,pin_num);
		break;
		
		case PD:
			TOGGLE_BIT(PORTD,pin_num);
		break;
	}
}



void DIO_Write_Port(DIO_Port_t port , u8 value)
{
	switch(port)
	{
		case PA:
			PORTA = value ;
		break;
		
		case PB:
			PORTB = value ;
		break;
		
		case PC:
			PORTC = value ;
		break;
		
		case PD:
			PORTD = value ;
		break;
	}
}

u8 DIO_Read_Port(DIO_Port_t port)
{
	u8 port_Val = 0 ; 
	switch(port)
	{
		case PA:
			port_Val = PORTA  ;
		break;
		
		case PB:
			port_Val = PORTB ;
		break;
		
		case PC:
			port_Val = PORTC ;
		break;
		
		case PD:
			port_Val = PORTD ;
		break;
	}
	return port_Val ;
}