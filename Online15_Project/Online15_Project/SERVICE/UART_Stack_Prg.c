
#include "StdTypes.h"
#include "UART_Int.h"
#include "UART_Services_Int.h"
#include "UART_Stack_Int.h"

u8 uart_stack_pointer = 0 ;
u8 uart_stack_arr[UART_STACK_SIZE] ;

uart_stack_status_t UART_Stack_Push (u8 data)
{
	uart_stack_status_t ret_val = UART_STACK_OK ;
	if (uart_stack_pointer<UART_STACK_SIZE)
	{
		uart_stack_arr[uart_stack_pointer] = data ;
		uart_stack_pointer++ ;
	}
	else 
	{
		ret_val = UART_STACK_FULL ;
	}
	
	return ret_val ;
}


uart_stack_status_t UART_Stack_Pop (u8 *pdata)
{
	uart_stack_status_t ret_val = UART_STACK_OK ;
	if (uart_stack_pointer>0)
	{
		uart_stack_pointer-- ;
		*pdata = uart_stack_arr[uart_stack_pointer] ;
		
	}
	else
	{
		ret_val = UART_STACK_EMPTY ;
	}
	
	return ret_val ;
	
}