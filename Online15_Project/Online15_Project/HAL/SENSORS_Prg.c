
#include "StdTypes.h"
#include "ADC_Int.h"
#include "SENSORS_Int.h"

u16 LM35_Read_Temp (void)
{
	u16 temp ; 
	temp = ADC_Read_Volt(LM35_CHANNEL);
	return temp ;
}

u16 LM35_Read_Temp_No_Block (void)
{
	u16 temp ;
	temp = ADC_Read_Volt_No_Block();
	return temp ;
}


/*Pressure in Kpa *10 */
u16 MPX_Read_Pressure (void)
{
	u16 Pres ; 
	u16 adc_val = ADC_Read(MPX_CHANNEL);
	
	Pres = (((u32)1000*(adc_val-55))/921)+150 ;
	return Pres ;
}

/*Pressure in Kpa *10 */
u16 MPX_Read_Pressure_No_Block (void)
{
	u16 press ;
	u16 adc_val = ADC_Get_Read_No_Block();
	press = (((u32)1000*(adc_val-55))/921)+150 ;
	return press ;
}