
#ifndef DOCKLIGH_SERIAL_INT_H_
#define DOCKLIGH_SERIAL_INT_H_

#define TOTAl_SERIAL_DATA			14

#define BLUETOOTH_CHOICE			1
#define DOCKLIGHT_CHOICE			2

/*BLUETOOTH_CHOICE - DOCKLIGHT_CHOICE */
#define SMART_HOME		BLUETOOTH_CHOICE		


#define  RED_LED_PIN				PINC0
#define  GREEN_LED_PIN				PINC1
#define  BLUE_LED_PIN				PINC2
#define  RELAY1_PIN					PINC4
#define  RELAY2_PIN					PINC3
#define  BUZZER_PIN					PINC5

typedef struct 
{
	const u8* str;
	void (*pf) (void) ;
}serial_uart_t;

void SMART_HOME_Init (void);

void SMART_HOME_Runnable (void);


#endif /* DOCKLIGH_SERIAL_INT_H_ */