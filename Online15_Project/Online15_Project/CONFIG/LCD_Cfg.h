
#ifndef LCD_CFG_H_
#define LCD_CFG_H_


#define LCD_4_BIT				1
#define LCD_8_BIT				2

/* LCD_4_BIT -  LCD_8_BIT  */
#define LCD_MODE	LCD_4_BIT

		


#ifndef LCD_MODE
#define LCD_MODE		LCD_8_BIT
#endif 


#define LCD_DATA_PINS			4


typedef struct
{
	DIO_Pin_t Enable_pin ;
	DIO_Pin_t Reigster_Sel ;
	DIO_Pin_t DataPins[LCD_DATA_PINS];
}lcd_t;


static const lcd_t LCD_Pin_control =
{
	.Enable_pin  = PINA2 ,
	.Reigster_Sel = PINA1 ,
	{PINA3 , PINA4 , PINA5 , PINA6}
};


#endif /* LCD_CFG_H_ */