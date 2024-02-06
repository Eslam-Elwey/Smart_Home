
#ifndef LCD_GAME_INT_H_
#define LCD_GAME_INT_H_

#define POT_CHANNEL					ADC_CHANNEL_0
#define TOTAL_STEPS					16

void LCD_Game_Init (void);

void LCD_Game_Runnable (void) ;

void LDR_Init (void) ;

void LDR_Runnable (void) ;

void Radio_Signal_Init(void);

void Radio_Signal_Runnable(void);

void UART_Button_print_Last_Data_Init(void);

void UART_Button_print_Last_Data_Runnable(void);

#endif /* LCD_GAME_INT_H_ */