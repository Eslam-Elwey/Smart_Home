
#include "StdTypes.h"
#include "UART_Int.h" 
#include "UART_Services_Int.h"
#include "UART_Stack_Int.h"
#include "MemMap.h"
#include "LCD_Int.h"
#define F_CPU		8000000UL
#include <util/delay.h>

#define TOTAL_STRINGS				10

extern u8 uart_stack_pointer ;
extern u8 uart_stack_arr[UART_STACK_SIZE] ;
static u8* str_tx = NULLPTR ;
static u8* str_rx = NULLPTR ;
static u8* str_tx_arr[TOTAL_STRINGS] ;
static u8 currnt_string = 0 ;
static u8 i = 0 ;
static u8 j = 0 ;
static u8 strings_received = 0 ;
static u8 count = 0 ;
volatile u8 serial_flag = 0 ;


static void Tx_Func (void) ;
static void Rx_Func_using_stack (void) ;
static void Rx_Func (void) ;
static void Rx_Func_docklight (void) ;
static void Rx_Func_using_stack_charcters (void) ;
static void Tx_Func_strings (void) ;


void UART_Send_String (u8* str) 
{
	u8 i ;
	for (i=0;str[i]!='\0';i++)
	{
		UART_Send(str[i]);
	}
	
}

void UART_Receive_String (u8* str) 
{
	u8 i = 0 ;
	str[i] = UART_Receive();
	while (str[i]!=(u8)0x0D)
	{
		i++;
		str[i] = UART_Receive();
	}
	str[i] = '\0' ;
}

void UART_Receive_String_docklight (u8* str)
{
	u8 i = 0 ;
	str[i] = UART_Receive();
	while ((str[i-1]!=(u8)0x0D)&&(str[i]!=(u8)0x0A))
	{
		i++;
		str[i] = UART_Receive();
	}
	str[i-1] = '\0' ;
}

/* Length of Data - Data - Sum Of Data */
void UART_Send_String_CheckSum (u8 *str)
{
	u16 Sum = 0 ;
	u8 i ;
	for (i=0;str[i];i++)
	{
		Sum += str[i] ;
	}
	UART_Send(i) ;
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
	
	UART_Send ((u8)Sum);
	UART_Send ((u8)(Sum>>8));
}

u8 UART_Receive_String_CheckSum (u8 *str)
{
	u16 Sum_Rec = 0  , Sum_Cal = 0 ;
	u8 i , len;
	u8 ret_val = 0 ;
	
	len = UART_Receive();
	
	for (i=0;str[i];i++)
	{
		str[i] = UART_Receive();
		Sum_Cal += str[i] ;
	}
	
	
	Sum_Rec |= (u16)UART_Receive() ;
	Sum_Rec |= (u16)(UART_Receive()<<8) ;
	if (Sum_Rec==Sum_Cal)
	{
		ret_val = 1 ;
	}
	return ret_val ;
}

void UART_Send_Number (u32 num) 
{
	u8 *p = (u8 *)&num ; 
	
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
	
// 	UART_Send((u8)num);
// 	UART_Send((u8)num>>8);
// 	UART_Send((u8)num>>16);
// 	UART_Send((u8)num>>24);
	
}


u32 UART_Receive_Number (void)
{
	u32 num ;
	u8 b0 = UART_Receive() ;
	u8 b1 = UART_Receive() ;
	u8 b2 = UART_Receive() ;
	u8 b3 = UART_Receive() ;

	num = (u32)b0 | (((u32) b1) << 8 ) | (((u32) b2) << 16 ) | (((u32) b3) << 24) ;
	
	return num ;
}

u8 UART_Receive_1byte_Number (void) 
{
	u8 num ;
	num = UART_Receive ();
	return num ;
}

u8 Endian_Test (void)
{
	u32 num = 1 ;
	u8 *ptr = (u8 *)&num ;
	u8 ret_val = 0 ;
	if (*ptr == 1)
	{
		 ret_val = 1 ;
	}
	
	return ret_val ;
}

u32 Endian_Convert_u32 (u32 num) 
{
	u32 num_val = 0 ;
	
	num_val = (num >>24) | (((num&0x00FF0000)>>16)<<8) | (((num&0x0000FF00)>>8)<<16)|(num<<24) ;
	
	return num_val ;
}

u16 Endian_Convert_u16 (u16 num) 
{
	u32 num_val = (num<<8)| (num>>8) ;
	return num_val ;
}


static void Tx_Func (void) 
{
	static u8 i = 1 ;
	if (str_tx[i])
	{
		UART_Send_No_Block(str_tx[i]);
		i++ ;
	}	
}

static void Rx_Func_using_stack_charcters (void)
{
	u8 udr_val ;
	uart_stack_status_t ret_val ;
	UART_READ_BUFFER (&udr_val);
	ret_val = UART_Stack_Push (udr_val) ;
	if (ret_val==UART_STACK_FULL)
	{
		LCD_Set_Cursor(2,5);
		LCD_Write_String((u8*)"FULL Buffer");
		_delay_ms(1000);
		LCD_Clear_Cursor(2,5,12);
	}
	
	
}

static void Rx_Func_using_stack (void) 
{
	u8 udr_val ;
	uart_stack_status_t ret_val ;
	UART_READ_BUFFER (&udr_val);
	ret_val = UART_Stack_Push (udr_val) ;
	if(ret_val==UART_STACK_FULL)
	{
		RX_COMPLETE_INTERRUPT_DISABLE();
	}
	if (UDR == 0x0D)
	{
		uart_stack_arr[uart_stack_pointer-1]='\0';
		uart_stack_pointer = 0 ;
	}
}

static void Rx_Func (void)
{
	static u8 i = 0 ;
	str_rx[i] = UART_Receive_No_Block();
		
		
		if (str_rx[i]!='#' )
		{
			i++;
			str_rx[i] = UART_Receive_No_Block();
			
			
		}
		else
		{
			str_rx[i]='\0';
			i = 0 ;
			serial_flag = 1 ;
		}
	
// 	if (str_rx[i] == 0x0D)
// 	{
// 		str_rx[i]='\0';
// 		i = 0 ;
// 		serial_flag = 1 ;
// 	}
	
}




void UART_Send_String_Async (u8* str) 
{
	UART_Send(str[0]);
	str_tx = str ;
	
	TX_Set_Call_Back(Tx_Func);
	
	TX_COMPLETE_INTERRUPT_ENABLE();
	
}

void UART_Receive_String_Async (u8* str) 
{
	RX_Set_Call_Back(Rx_Func);
	str_rx = str ;
	RX_COMPLETE_INTERRUPT_ENABLE();
}

void UART_Receive_String_Async_docklight (u8* str) 
{
	RX_Set_Call_Back(Rx_Func_docklight);
	str_rx = str ;
	RX_COMPLETE_INTERRUPT_ENABLE();
}

static void Rx_Func_docklight (void)
{
	static u8 i = 0 ;
	if (0==serial_flag)
	{
		if ((str_rx[i]==' ')&&(i==0))
		{
			
		}
		else
		{
			str_rx[i] = UART_Receive_No_Block();
			i++ ;
		}
		
		if ((str_rx[i-2]==(u8)0x0D)&&(str_rx[i-1]==(u8)0x0A))
		{
			serial_flag = 1 ;
			str_rx[i-2]='\0';
			i = 0 ;
		}
	}
	
}

void UART_Receive_charcters_Async (void)
{
	RX_Set_Call_Back(Rx_Func_using_stack_charcters);
	RX_COMPLETE_INTERRUPT_ENABLE();
}

void UART_Receive_String_Stack_Async (void) 
{
	RX_Set_Call_Back(Rx_Func_using_stack);
	RX_COMPLETE_INTERRUPT_ENABLE();
}

void UART_Send_String_Async_no_block_Strings (u8* str)
{
	str_tx_arr[currnt_string] = str ;
	strings_received++ ;
	if (str_tx_arr[j][i])
	{
		UART_Send(str_tx_arr[j][i]);
		i++ ;
	}
	else 
	{
		count++ ;
		j++ ;
		i = 0 ;
		UART_Send(str_tx_arr[j][i]);
	}
	currnt_string++ ;
	if (currnt_string==TOTAL_STRINGS)
	{
		currnt_string = 0 ;
	}
	TX_Set_Call_Back(Tx_Func_strings);
	
	TX_COMPLETE_INTERRUPT_ENABLE();
	
}

static void Tx_Func_strings (void)
{
	
	if (str_tx_arr[j][i])
	{
		UART_Send_No_Block(str_tx_arr[j][i]);
		i++ ;
		
	}
	
	else 
	{
		count++ ;
		j++ ;
		if (j==TOTAL_STRINGS)
		{
			j = 0 ;
		}
		i = 0 ;
		UART_Send_No_Block(str_tx_arr[j][i]);
		i++ ;
		if (count==strings_received)
		{
			TX_COMPLETE_INTERRUPT_DISABLE();
		}
	}
	
	
}

void UART_SEND_2_Byte_Number (u16 num)
{
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
}