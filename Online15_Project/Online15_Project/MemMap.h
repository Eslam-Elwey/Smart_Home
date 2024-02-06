
#ifndef MEMMAP_H_
#define MEMMAP_H_


/************************************************ macros **************************************************************/
/* DIO_Port_Registers*/
#define PORTA (*(volatile unsigned char *)0x3B)
#define DDRA  (*(volatile unsigned char *)0x3A)
#define PINA  (*(volatile unsigned char *)0x39)

#define PORTB (*(volatile unsigned char *)0x38)
#define DDRB  (*(volatile unsigned char *)0x37)
#define PINB  (*(volatile unsigned char *)0x36)

#define PORTC (*(volatile unsigned char *)0x35)
#define DDRC  (*(volatile unsigned char *)0x34)
#define PINC  (*(volatile unsigned char *)0x33)

#define PORTD (*(volatile unsigned char *)0x32)
#define DDRD  (*(volatile unsigned char *)0x31)
#define PIND  (*(volatile unsigned char *)0x30)

/*ADC_Rgisters */

#define ADCL	(*(volatile unsigned char *)0x24)
#define ADCH	(*(volatile unsigned char *)0x25)
#define ADC		(*(volatile unsigned short *)0x24)

#define ADMUX   (*(volatile unsigned char *)0x27)
/*ADMUX Bits*/
#define MUX0				0
#define MUX1				1
#define MUX2				2
#define MUX3				3
#define MUX4				4
#define ADLAR				5
#define REFS0				6
#define REFS1				7

#define ADCSRA  (*(volatile unsigned char *)0x26)
/*ADCSRA Bits*/
#define ADPS0				0
#define ADPS1				1
#define ADPS2				2
#define ADIE				3
#define ADIF				4
#define ADATE				5
#define ADSC				6
#define ADEN				7

/* General Interrupt Control Register */

#define GICR	(*(volatile unsigned char *)0x5B)
/* GICR Bits */
#define IVCE		0
#define IVSEL		1
#define INT2		5
#define INT0		6
#define INT1		7

/*SERG Special Register */
#define SREG			(*(volatile unsigned char *)0x5F)
#define GLO_INT_EN		7

/*********************** Interrupt vector Table **********************/

/* External Interrupt Request 0 */
#define INT0_vect								__vector_1
/* External Interrupt Request 1 */
#define INT1_vect								__vector_2
/* External Interrupt Request 2 */
#define INT2_vect								__vector_3
/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect						__vector_4
/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect							__vector_5
/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect						__vector_6
/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect						__vector_7
/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_vect						__vector_8
/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect							__vector_9
/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect						__vector_10
/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect							__vector_11
/* Serial Transfer Complete */
#define SPI_STC_vect							__vector_12
/* USART, Rx Complete */
#define USART_RXC_vect							__vector_13
/* USART Data Register Empty */
#define USART_UDRE_vect							__vector_14
/* USART, Tx Complete */
#define USART_TXC_vect							__vector_15
/* ADC Conversion Complete */
#define ADC_vect								__vector_16
/* EEPROM Ready */
#define EE_RDY_vect								__vector_17
/* Analog Comparator */
#define ANA_COMP_vect							__vector_18
/* Two-wire Serial Interface */
#define TWI_vect								__vector_19
/* Store Program Memory Ready */
#define SPM_RDY_vect							__vector_20

#define BAD_vect								__vector_default

/* Enable Global Interrupt Assembly */
#define GLOBAL_INTERRUPT_ENABLE()		sei()
#define sei()	 __asm__ __volatile__ ("sei"::)
# define cli()   __asm__ __volatile__ ("cli" ::)
# define reti()  __asm__ __volatile__ ("reti" ::)
# define ret()   __asm__ __volatile__ ("ret" ::)
#define GLOBAL_INTERRUPT_DISABLE()		cli()

/* ISR Def*/
#define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)

#define ISR_NOBLOCK    __attribute__((interrupt))
#define ISR_NAKED      __attribute__((naked))

/******************************************************************************************/
/* Special Function Register*/
#define SFIOR	(*(volatile unsigned char *)0x50)

#define PSR10				0
#define PSR2				1
/* Bit 2 – PUD: Pull-up disable write 1 */
#define PUD					2
#define ACME				3
/*ADC TRIGGER Source */
#define ADTS0				5
#define ADTS1				6
#define ADTS2				7

/******************************************************************************************/
/* The MCU Control Register contains control bits for power management */
/*Bit 7 – SE: Sleep Enable / Bits 6...4 – SM2..0: Sleep Mode  */
#define MCUCR		(*(volatile unsigned char *)0x55)
/*MCUCR Bits*/
#define ISC00						0
#define ISC01						1
#define ISC10						2
#define ISC11						3
#define SM0							4
#define SM1							5
#define SM2							6
#define SE							7
/******************************************************************************************/
/*GIFR Interrupt flag Register */
#define GIFR		(*(volatile unsigned char *)0x55)
/*GIFR Bits*/
#define INT0			6
#define INT1			7
#define INT2			5

/******************************************************************************************/
/*Power Modes*/
#define POWER_Idle									0
#define POWER_ADC_Noise_Reduction					1
#define Power_DOWN									2
#define POWER_SAVE									3
/*Standby mode and Extended Standby mode are only available with external crystals
or resonators */
#define POWER_STANDBY								6
#define POWER_EXTENDED_STANDBY						7

/* External Interrupt Registers */
#define MCUCSR		(*(volatile unsigned char *)0x54)
/*MCUCSR Bits*/
#define PORF								0
#define EXTRF								1
#define BORF								2
#define WDRF								3
#define JTRF								4
#define ISC2								6  // INT2 Sense Control
#define JTD									7
/******************************************************************************************/
/*Timer0 Registers */
/*Timer/Counter Control Register – TCCR0*/
#define TCCR0						(*(volatile unsigned char* )0x53)
/*TCCR0 Bits */
#define CS00						0
#define CS01						1
#define CS02						2
#define WGM01						3
#define COM00						4
#define COM01						5
#define WGM00						6
#define FOC0						7

#define TCNT0						(*(volatile unsigned char* )0x52)
#define OCR0						(*(volatile unsigned char* )0x5C)
#define TIFR						(*(volatile unsigned char* )0x58)

/*Timer/Counter Interrupt Mask Register – TIMSK*/
#define TIMSK						(*(volatile unsigned char* )0x59)
/*TIMSK Bits*/
#define TOIE0						0
#define OCIE0						1
#define TOIE1						2
#define OCIE1B						3
#define OCIE1A						4
#define TICIE1						5
#define TOIE2						6
#define OCIE2						7
/******************************************************************************************/
/*Timer1 Registers */
/*Timer/Counter Control Register – TCCR1A*/
#define TCCR1A						(*(volatile unsigned char* )0x4F)
/*TCCR1A Bits*/
#define WGM10						0
#define WGM11						1
#define FOC1B						2
#define FOC1A						3
#define COM1B0						4
#define COM1B1						5
#define COM1A0						6
#define COM1A1						7


/*Timer/Counter Control Register – TCCR1B*/
#define TCCR1B						(*(volatile unsigned char* )0x4E)
/*TCCR1A Bits*/
#define CS10						0
#define CS11						1
#define CS12						2
#define WGM12						3
#define WGM13						4
#define ICES1						6
#define ICNC1						7

#define TCNT1H						(*(volatile unsigned char* )0x4D)
#define TCNT1L						(*(volatile unsigned char* )0x4C)
#define TCNT1						(*(volatile unsigned short* )0x4C)

#define OCR1AH						(*(volatile unsigned char* )0x4B)
#define OCR1AL						(*(volatile unsigned char* )0x4A)
#define OCR1A						(*(volatile unsigned short* )0x4A)


#define OCR1BH						(*(volatile unsigned char* )0x49)
#define OCR1BL						(*(volatile unsigned char* )0x48)
#define OCR1B						(*(volatile unsigned short* )0x48)

#define ICR1H						(*(volatile unsigned char* )0x47)
#define ICR1L						(*(volatile unsigned char* )0x46)
#define ICR1						(*(volatile unsigned short* )0x46)

/******************************************************************************************/
/*Timer2 Registers */
/*Timer2/Counter Control Register – TCCR2 */
#define TCCR2						(*(volatile unsigned char* )0x45)
/*TCCR2 Bits*/
#define CS20						0
#define CS21						1
#define CS22						2
#define WGM21						3
#define COM20						4
#define COM21						5
#define WGM20						6
#define FOC2						7

#define TCNT2						(*(volatile unsigned char* )0x44)

#define OCR2						(*(volatile unsigned char* )0x43)

/******************************************************************************************/
/*USART Registers*/
#define UDR						(*(volatile unsigned char* )0x2C)
/*********************************************************/

/* USART Control Reg A */
#define UCSRA					(*(volatile unsigned char* )0x2B)

#define MPCM						0
#define U2X							1
#define PE							2
#define DOR							3
#define FE							4
#define UDRE						5
#define TXC							6
#define RXC							7

/*********************************************************/
/* USART Control Reg B */
#define UCSRB					(*(volatile unsigned char* )0x2A)

#define TXB8						0
#define RXB8						1
#define UCSZ2						2
#define TXEN						3
#define RXEN						4
#define UDRIE						5
#define TXCIE						6
#define RXCIE						7

/*********************************************************/
/* USART Control Reg C */
#define UCSRC					(*(volatile unsigned char* )0x40)

#define UCPOL						0
#define UCSZ0						1
#define UCSZ1						2
#define USBS						3
#define UPM0						4
#define UPM1						5
#define UMSEL						6
#define URSEL						7

/*********************************************************/

#define UBRRL					(*(volatile unsigned char* )0x29)

/*********************************************************/

#define UBRRH					(*(volatile unsigned char* )0x40)


/*********************************************************/
/*EEPROM Registers */
#define EEARH					(*(volatile unsigned char* )0x3F)
#define EEARL					(*(volatile unsigned char* )0x3E)
#define EEAR					(*(volatile unsigned short* )0x3E)

#define EEDR					(*(volatile unsigned char* )0x3D)

#define EECR					(*(volatile unsigned char* )0x3C)
/* EECR BITS */
#define EERE					0
#define EEWE					1
#define EEMWE					2
#define EERIE					3

/****************************************************************************/

/* Watch Dog Timer WDT Register */
#define WDTCR					(*(volatile unsigned char* )0x41)
/* WDT Bits */
#define WDP0					0
#define WDP1					1
#define WDP2					2
#define WDE						3
#define WDTOE					4

/*******************************************************************************/
/** SPI Registers **/
/* SPI Data Register */
#define SPDR					(*(volatile unsigned char* )0x2F)
 
/** SPSR **/
#define SPSR					(*(volatile unsigned char* )0x2E)
/** SPSR Bits **/
#define SPI2X						0
#define WCOL						6
#define SPIF						7

/** SPCR **/
#define SPCR					(*(volatile unsigned char* )0x2E)
/** SPCR Bits **/
#define SPR0						0
#define SPR1						1
#define CPHA						2
#define CPOL						3
#define MSTR						4
#define DORD						5
#define SPE							6
#define SPIE						7

/************************************************************************************/

/** I2C **/
/** Two-wire Serial Interface Data Register **/
#define TWDR					(*(volatile unsigned char* )0x23)

/** TWAR **/
#define TWAR					(*(volatile unsigned char* )0x22)
/** TWAR Bits **/
#define TWGCE						0
#define TWA0						1
#define TWA1						2
#define TWA2						3
#define TWA3						4
#define TWA4						5
#define TWA5						6
#define TWA6						7

/** TWAR **/
#define TWSR					(*(volatile unsigned char* )0x21)
/** TWAR Bits **/
#define TWPS0						0
#define TWPS1						1
#define TWS3						3
#define TWS4						4
#define TWS5						5
#define TWS6						6
#define TWS7						7

/** Two-wire Serial Interface Bit Rate Register **/
#define TWBR					(*(volatile unsigned char* )0x23)



#endif /* MEMMAP_H_ */