
#include "StdTypes.h"
#include "DIO_Int.h"
#include "DIO_Cfg.h"

/* INFREE  -  INPULL   -   OUTPUT  */
const DIO_PinStatus_t pin_arr[TOTAL_PINS] =
{
	INFREE,   /* PORTA  PINA0 / ADC0 */
	OUTPUT,   /* PORTA  PINA1 / ADC1 */
	OUTPUT,   /* PORTA  PINA2 / ADC2 */
	OUTPUT,   /* PORTA  PINA3 / ADC3 */
	OUTPUT,   /* PORTA  PINA4 / ADC4 */
	OUTPUT,   /* PORTA  PINA5 / ADC5 */
	OUTPUT,   /* PORTA  PINA6 / ADC6 */
	OUTPUT,   /* PORTA  PINA7 / ADC7 */
	
	OUTPUT,   /* PORTB  PINB0 / XCK / T0 */
	OUTPUT,   /* PORTB  PINB1 / T1 */
	OUTPUT,   /* PORTB  PINB2 / INT2 / AIN0 */
	OUTPUT,   /* PORTB  PINB3 / OC0 / AIN1 */
	OUTPUT,   /* PORTB  PINB4 / SS' */
	OUTPUT,   /* PORTB  PINB5 / MOSI */
	OUTPUT,   /* PORTB  PINB6 / MISO */
	OUTPUT,   /* PORTB  PINB7 / SCK */
	
	OUTPUT,   /* PORTC  PINC0 / SCL*/
	OUTPUT,   /* PORTC  PINC1 / SDA */
	OUTPUT,   /* PORTC  PINC2 / TCK */
	OUTPUT,   /* PORTC  PINC3 / TMS */
	OUTPUT,   /* PORTC  PINC4 / TD0 */
	OUTPUT,   /* PORTC  PINC5 / TD1 */
	INPULL,   /* PORTC  PINC6 / TOSC1 */
	OUTPUT,   /* PORTC  PINC7 / TOSC2 */
	
	INFREE,   /* PORTD  PIND0 / RXD */
	OUTPUT,   /* PORTD  PIND1 / TXD */
	OUTPUT,   /* PORTD  PIND2 / INT0 */
	OUTPUT,   /* PORTD  PIND3 / INT1 */
	OUTPUT,   /* PORTD  PIND4 / OC1B */
	OUTPUT,   /* PORTD  PIND5 / OC1A */
	INFREE,   /* PORTD  PIND6 / ICP */
	OUTPUT,   /* PORTD  PIND7 / OC2 */
};