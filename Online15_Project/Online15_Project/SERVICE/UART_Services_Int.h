
#ifndef UART_SERVICES_INT_H_
#define UART_SERVICES_INT_H_


void UART_Send_String (u8* str) ;

void UART_Receive_String (u8* str) ;

void UART_Send_String_Async (u8* str) ;

void UART_Send_String_Async_no_block_Strings (u8* str) ;

void UART_Receive_String_Async (u8* str) ;

void UART_Receive_String_Stack_Async (void) ;

void UART_Receive_charcters_Async (void) ;

void UART_Receive_String_Async_docklight (u8* str) ;

void UART_Receive_String_docklight (u8* str) ;

void UART_Send_String_CheckSum (u8 *str);

u8 UART_Receive_String_CheckSum (u8 *str);

void UART_Send_Number (u32 num) ;

void UART_SEND_2_Byte_Number (u16 num); 

u32 UART_Receive_Number (void) ;

u8 UART_Receive_1byte_Number (void) ;

u8 Endian_Test (void) ;

u32 Endian_Convert_u32 (u32 num) ;

u16 Endian_Convert_u16 (u16 num) ;


#endif /* UART_SERVICES_INT_H_ */