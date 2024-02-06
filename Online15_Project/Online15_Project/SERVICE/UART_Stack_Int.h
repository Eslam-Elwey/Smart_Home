
#ifndef UART_STACK_INT_H_
#define UART_STACK_INT_H_

#define UART_STACK_SIZE					20

typedef enum 
{
	UART_STACK_OK = 0 ,
	UART_STACK_EMPTY ,
	UART_STACK_FULL	
}uart_stack_status_t;




uart_stack_status_t UART_Stack_Push (u8 data);
uart_stack_status_t UART_Stack_Pop (u8 *pdata);

#endif /* UART_STACK_INT_H_ */