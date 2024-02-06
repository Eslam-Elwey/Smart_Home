
#include "StdTypes.h"
#include "MemMap.h"
#include "EEPROM_Int.h"

static void (*EEPROM_Func) (void) ;

void EEPROM_Init (void)
{
	
}

void EEPROM_Write_Data (u16 address , u8 data)
{
	/** Wait until EEWE becomes zero **/
	while (READ_BIT(EECR,EEWE));
	
	/** Set Address **/ 
	address &=0x03FF ;
	EEAR = address ;
	
	/** Write Data **/
	EEDR = data ;
	
	/** Write a logical one to the EEMWE **/
	SET_BIT(EECR,EEMWE);
	
	/** Start Writing **/
	SET_BIT(EECR,EEWE);
	
}


u8 EEPROM_Read_Data(u16 address)
{
	/** Wait until EEWE becomes zero **/
	while (READ_BIT(EECR,EEWE));
	
	/** Set Address **/
	address &=0x03FF ;
	EEAR = address ;
	
	/** Start Read **/
	SET_BIT(EECR,EERE);
	
	/** Get Data **/
	return EEDR ;
}


void EEPROM_Set_Call_Back (void (*pf)(void))
{
	EEPROM_Func = pf ; 
}

ISR (SPM_RDY_vect)
{
	if (EEPROM_Func!=NULLPTR)
	{
		EEPROM_Func();
	}
}

