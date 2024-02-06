
#ifndef DIO_INT_H_
#define DIO_INT_H_

typedef enum{
	OUTPUT,
	INFREE,
	INPULL
}DIO_PinStatus_t;

typedef enum{
	PA,
	PB,
	PC,
	PD
}DIO_Port_t;


typedef enum{
	LOW,
	HIGH
}DIO_PinVoltage_t;


typedef enum{
	PINA0=0,
	PINA1=1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
}DIO_Pin_t;

void DIO_Init(void);

void DIO_WritePin(DIO_Pin_t pin,DIO_PinVoltage_t volt);

void DIO_Toggle_Pin(DIO_Pin_t pin);

DIO_PinVoltage_t DIO_ReadPin(DIO_Pin_t pin);

void DIO_Write_Port(DIO_Port_t port , u8 value);

u8 DIO_Read_Port(DIO_Port_t port);

#endif /* DIO_INT_H_ */