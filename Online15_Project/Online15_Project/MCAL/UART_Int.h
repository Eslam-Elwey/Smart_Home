
#ifndef UART_INT_H_
#define UART_INT_H_

/****************** MACROs  *********************/
#define ODD_PARITY				1
#define EVEN_PARITY				2
#define NO_PARITY				3
/* ODD_PARITY - EVEN_PARITY - NO_PARITY */
#define PARITY_CHOICE			NO_PARITY

/*******************************************************/
#define XCK_RISING_TRANSMIT_FALLING_RECEIVE					0
#define XCK_FALLING_TRANSMIT_RISING_RECEIVE					1

#define XCK_SYNC_MODE				XCK_RISING_TRANSMIT_FALLING_RECEIVE

/*******************************************************/

#define UART_CHARCTER_SIZE_5_BIT				0
#define UART_CHARCTER_SIZE_6_BIT				1
#define UART_CHARCTER_SIZE_7_BIT				2
#define UART_CHARCTER_SIZE_8_BIT				3
#define UART_CHARCTER_SIZE_9_BIT				7

#define UART_CHARCTER_SIZE				UART_CHARCTER_SIZE_8_BIT

#define NORMAL_SPEED			0
#define DOUBLE_SPEED			1
#define UART_SPEED				NORMAL_SPEED

/*********************************************************/
#define BAUD_RATE_9600_NORMAL_SPEED_8MHZ_OSC				(u8)51
#define BAUD_RATE_9600_DOUBLE_SPEED_8MHZ_OSC				(u8)103

#define BAUD_RATE_19200_NORMAL_SPEED_8MHZ_OSC				(u8)25
#define BAUD_RATE_19200_DOUBLE_SPEED_8MHZ_OSC				(u8)51

#define UART_ASYNC_BAUD_RATE			BAUD_RATE_9600_NORMAL_SPEED_8MHZ_OSC

/****************** MACRO Functions ***************/

#define RX_COMPLETE_INTERRUPT_ENABLE()		(SET_BIT(UCSRB,RXCIE))
#define RX_COMPLETE_INTERRUPT_DISABLE()		(CLR_BIT(UCSRB,RXCIE))

#define TX_COMPLETE_INTERRUPT_ENABLE()		(SET_BIT(UCSRB,TXCIE))
#define TX_COMPLETE_INTERRUPT_DISABLE()		(CLR_BIT(UCSRB,TXCIE))

#define DATA_EMPTY_INTERRUPT_ENABLE()		(SET_BIT(UCSRB,UDRIE))
#define DATA_EMPTY_INTERRUPT_DISABLE()		(CLR_BIT(UCSRB,UDRIE))

#define UART_RECEIVER_ENABLE()				(SET_BIT(UCSRB,RXEN))
#define UART_RECEIVER_DISABLE()				(CLR_BIT(UCSRB,RXEN))

#define UART_TRANSMITTER_ENABLE()			(SET_BIT(UCSRB,TXEN))
#define UART_TRANSMITTER_DISABLE()			(CLR_BIT(UCSRB,TXEN))

#define UART_READ_BUFFER(pval)				(*pval=UDR)
#define UART_WRITE_BUFFER(val)				(UDR=val)


/****************** defined Data Types ******************/
typedef enum
{
	UART_ASYNCHRONOUS = 0 ,
	UART_SYNCHRONOUS
}uart_oper_mode_t;

typedef enum
{
	PARITY_DISABLED = 0 ,
	PARITY_EVEN = 2,
	PARITY_ODD = 3
}uart_parity_t;

typedef enum
{
	STOP_1_BIT = 0,
	STOP_2_BIT = 1
}uart_stop_bit_t;

typedef enum
{
	RECEIVE_EMPTY = 0 ,
	RECEIVE_OK
}receive_state_t;


typedef struct
{
	uart_oper_mode_t mode  ;
	uart_stop_bit_t stop_bit ;
	uart_parity_t parity ;
	u8 data_size  ;
}uart_t;


/*********************************************************************/

void UART_Init (void) ;

#if UART_CHARCTER_SIZE == UART_CHARCTER_SIZE_9_BIT
	void UART_Send (u16 data) ;

	u16 UART_Receive (void) ;
	
	u8 UART_Receive_Periodic (u16*pdata);
	
	void UART_Send_No_Block (u16 data) ;
	
	u16 UART_Receive_No_Block (void) ;
	
#else 
	void UART_Send (u8 data) ;

	u8 UART_Receive (void) ;
	
	u8 UART_Receive_Periodic (u8*pdata);
	
	void UART_Send_No_Block (u8 data) ;
	
	u8 UART_Receive_No_Block (void) ;
	
#endif

void TX_Set_Call_Back(void(*pf)(void));
void RX_Set_Call_Back(void(*pf)(void));
void Data_Empty_Set_Call_Back(void(*pf)(void));
u16 UART_Prepare_Frame (u8 data) ;


#endif /* UART_INT_H_ */