
#include "StdTypes.h"
#include "MemMap.h"
#include "UART_Int.h"


static void (*TX_Func)(void) ;
static void (*RX_Func)(void) ;
static void (*Empty_Reg_Func)(void) ;

// static uart_t uart_obj =
// {
// 	UART_ASYNCHRONOUS ,
// 	PARITY_DISABLED ,
// 	STOP_1_BIT ,
// 	UART_CHARCTER_SIZE
// };

void UART_Init(void)
{
	//frame 1 STOP 8 DATA NO PARITY
	//baud rate  9600
	UBRRL=BAUD_RATE_9600_NORMAL_SPEED_8MHZ_OSC;//9615
	CLR_BIT(UCSRA,U2X);// NORMAL SPEED

	UART_RECEIVER_ENABLE();
	UART_TRANSMITTER_ENABLE();
}

// void UART_Init (void) 
// {
// 	//Frame 
// 	SET_BIT(UCSRC,URSEL);
// 	/* Parity mode */
// 	switch (uart_obj.parity)
// 	{
// 		case PARITY_DISABLED :
// 			CLR_BIT(UCSRC,UPM0);
// 			CLR_BIT(UCSRC,UPM1);
// 		break ;
// 		
// 		case PARITY_EVEN :
// 			CLR_BIT(UCSRC,UPM0);
// 			SET_BIT(UCSRC,UPM1);
// 		break ;
// 		
// 		case PARITY_ODD :
// 			SET_BIT(UCSRC,UPM0);
// 			SET_BIT(UCSRC,UPM1);
// 		break ;
// 	}
// 	/* Stop bit mode */
// 	if ((uart_obj.stop_bit) == STOP_1_BIT)
// 	{
// 		CLR_BIT (UCSRC,USBS);
// 	}
// 	else
// 	{
// 		SET_BIT (UCSRC,USBS);
// 	}
// 	
// 	/* Data size mode */
// 	switch (uart_obj.data_size)
// 	{
// 		case UART_CHARCTER_SIZE_5_BIT :
// 			CLR_BIT(UCSRC,UCSZ0);
// 			CLR_BIT(UCSRC,UCSZ1);
// 			CLR_BIT(UCSRB,UCSZ2);
// 		break ;
// 		
// 		case UART_CHARCTER_SIZE_6_BIT :
// 			SET_BIT(UCSRC,UCSZ0);
// 			CLR_BIT(UCSRC,UCSZ1);
// 			CLR_BIT(UCSRB,UCSZ2);
// 		break ;
// 		
// 		case UART_CHARCTER_SIZE_7_BIT :
// 			CLR_BIT(UCSRC,UCSZ0);
// 			SET_BIT(UCSRC,UCSZ1);
// 			CLR_BIT(UCSRB,UCSZ2);
// 		break ;
// 		
// 		case UART_CHARCTER_SIZE_8_BIT :
// 			SET_BIT(UCSRC,UCSZ0);
// 			SET_BIT(UCSRC,UCSZ1);
// 			CLR_BIT(UCSRB,UCSZ2);
// 		break ;
// 		
// 		case UART_CHARCTER_SIZE_9_BIT :
// 			SET_BIT(UCSRC,UCSZ0);
// 			SET_BIT(UCSRC,UCSZ1);
// 			SET_BIT(UCSRB,UCSZ2);
// 		break ;
// 	}
// 	
// 	//Baud Rate

// 	 //UART SPEED (Normal/Double) (Asynchronous Mode)
// #if UART_SPEED == NORMAL_SPEED
// 	CLR_BIT (UCSRA,U2X);
// #else
// 	SET_BIT (UCSRA,U2X);
// #endif
// 	
// 	/* UART mode */
// 	if ((uart_obj.mode) == UART_ASYNCHRONOUS)
// 	{
// 		CLR_BIT (UCSRC,UMSEL);
// 		/* Baud Rate */
// 		UBRRH = (UART_ASYNC_BAUD_RATE>>8) ;
// 		UBRRL = /*UART_ASYNC_BAUD_RATE*/25 ;
// 		
//
// 
// 
// 	}
// 	else
// 	{
// 		CLR_BIT(UCSRA,U2X);
// 		SET_BIT (UCSRC,UMSEL);
// 		
// #if XCK_SYNC_MODE == XCK_RISING_TRANSMIT_FALLING_RECEIVE
// 		CLR_BIT(UCSRC,UCPOL);
// #else
// 		SET_BIT(UCSRC,UCPOL);
// #endif
// 
// 	}
// 	
// 	UART_RECEIVER_ENABLE();
// 	UART_TRANSMITTER_ENABLE();
// 	
// }



/* Handle 9bit data length */
#if UART_CHARCTER_SIZE == UART_CHARCTER_SIZE_9_BIT

void UART_Send (u16 data) 
{
	data &= 0x01FF ;
	while (!READ_BIT(UCSRA,UDRE)); 
	UDR = (u8)data ; 
	WRITE_BIT_VAL(UCSRB,TXB8,READ_BIT(data,8));
	
}

u16 UART_Receive (void)
{
	u16 data = 0 ;
	while (!READ_BIT(UCSRA,RXC));
	data |= (READ_BIT(UCSRB,RXB8)<<8);
	data |= UDR ;
	return data ;
	
}

u8 UART_Receive_Periodic (u16 *pdata)
{
	u8 ret_val = 0 ;
	u16 UDR_VAl ; 
	if(READ_BIT(UCSRA,RXC))
	{
		UDR_VAl |= (READ_BIT(UCSRB,RXB8)<<8);
		UDR_VAl |= UDR;
		
		*pdata = UDR_VAl ;
		
		ret_val = 1 ;
	}
	
	return ret_val ;
}

void UART_Send_No_Block (u16 data)
{
	data &= 0x01FF ;
	WRITE_BIT_VAL(UCSRB,TXB8,READ_BIT(data,8));
	UDR = (u8)data ; 
}
u16 UART_Receive_No_Block (void) 
{
	u16 data = 0 ;
	data |= (READ_BIT(UCSRB,RXB8)<<8);
	data |= UDR ;
	return data ;
}

#else 

void UART_Send (u8 data)
{
	while (!READ_BIT(UCSRA,UDRE)); 
	UDR = data ;
	
}

u8 UART_Receive (void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
	
}

u8 UART_Receive_Periodic (u8 *pdata)
{
	u8 ret_val = 0 ;
	
	if(READ_BIT(UCSRA,RXC))
	{
		*pdata = UDR ;
		ret_val = 1 ;
	}
	
	return ret_val ;
}

void UART_Send_No_Block (u8 data)
{
	UART_WRITE_BUFFER(data);
}

u8 UART_Receive_No_Block (void)
{
	u8 udr_val ;
	UART_READ_BUFFER(&udr_val);
	return udr_val ;
}

#endif





/**** Prepare UART Frame Manual 
Data Length= 8 
No Parity 
1 Stop Bit *****/
static u8 Count_Ones (u8 data)
{
	u8 counter = 0  ;
	s8 i = 7 ;
	while (i >=0 )
	{
		counter += READ_BIT (data,i);
		i-- ;
	}
	return counter ;
}

u16 UART_Prepare_Frame (u8 data) 
{
	u16 frame = 0  ;
	u8 count ;
	frame |= ((u16)data << 1) ;
	
	count = Count_Ones (data) ;
	
#if PARITY_CHOICE == ODD_PARITY
	if (count & 1)
	{
		CLR_BIT(frame,9) ;
	}
	else
	{
		SET_BIT(frame,9);
	}
	SET_BIT(frame,10);
	
#elif PARITY_CHOICE == EVEN_PARITY
	if (count & 1)
	{
		SET_BIT(frame,9) ;
	}
	else
	{
		CLR_BIT(frame,9);
	}
	SET_BIT(frame,10);
	
#else
	SET_BIT(frame,9);

#endif
	
	return frame ;
}


void TX_Set_Call_Back(void(*pf)(void))
{
	TX_Func = pf ;
}


void RX_Set_Call_Back(void(*pf)(void))
{
	RX_Func = pf ;
}


void Data_Empty_Set_Call_Back(void(*pf)(void))
{
	Empty_Reg_Func = pf ;
}


ISR (USART_TXC_vect)
{
	if (TX_Func!=NULLPTR)
	{
		TX_Func() ;
	}
}

ISR (USART_RXC_vect)
{
	if (RX_Func!=NULLPTR)
	{
		RX_Func() ;
	}
}

ISR (USART_UDRE_vect)
{
	if (Empty_Reg_Func!=NULLPTR)
	{
		Empty_Reg_Func() ;
	}
}