
#ifndef EEPROM_INT_H_
#define EEPROM_INT_H_


#define EEPROM_READY_INTERRUPT_ENABLE()				(SET_BIT(EECR,EERIE))
#define EEPROM_READY_INTERRUPT_DISABLE()			(CLR_BIT(EECR,EERIE))

void EEPROM_Init (void);
void EEPROM_Write_Data (u16 address , u8 data);
u8 EEPROM_Read_Data(u16 address);
void EEPROM_Set_Call_Back (void (*pf)(void));


#endif /* EEPROM_INT_H_ */