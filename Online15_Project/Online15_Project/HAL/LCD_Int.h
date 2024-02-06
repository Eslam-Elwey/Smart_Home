
#ifndef LCD_INT_H_
#define LCD_INT_H_



#define LCD_8_BIT_MODE					0X38
#define LCD_4_BIT_MODE					0X28
#define LCD_DIS_ON_CUR_OFF_BLI_OFF		0X0C
#define LCD_DIS_OFF_CUR_OFF_BLI_OFF		0X08
#define LCD_DIS_ON_CUR_ON_BLI_OFF		0X0E
#define LCD_DIS_ON_CUR_ON_BLI_ON		0X0F
#define LCD_CLEAR_DISPALY				0X01
#define LCD_RETURN_HOME					0X02
#define LCD_INCREASE_ADD_NO_SHIFT		0X06
#define LCD_DECREASE_ADD_NO_SHIFT		0X04
#define LCD_INCREASE_ADD_SHIFT_LEFT		0X07
#define LCD_DECREASE_ADD_SHIFT_RIGHT	0X05
#define LCD_CURSOR_SHIFT_LEFT			0X10
#define LCD_CURSOR_SHIFT_RIGHT			0X14
#define LCD_DISPLAY_SHIFT_LEFT			0X18
#define LCD_DISPLAY_SHIFT_RIGHT			0X1C



void LCD_Init(void);
void LCD_Write_Character(u8 chr);
void LCD_Write_String(u8 *str);
void LCD_Write_Number(s32 num);

/* Line 1-2 / Cell 1 - 16 */
void LCD_Set_Cursor(u8 line , u8 cell);

void LCD_Custom_Char(u8 address , u8 *Pattern);
void LCD_Clear_Screen(void);
void LCD_Write_String_Cursor(u8 line , u8 cell , u8 *str);
void LCD_Write_Number_Cursor(u8 line , u8 cell , s32 num);

void LCD_Clear_Cursor(u8 line , u8 cell , u8 num);

void LCD_Print_Binary(u16 num);
void LCD_Print_Hexa(u8 num);
void LCD_Snake_Word(u8 *str);
void LCD_Write_Number_4_Digits (u32 num);
s32 String_To_Int (u8 *str);

#endif /* LCD_INT_H_ */