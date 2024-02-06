
#include "StdTypes.h"
#include "LCD_Int.h"
#include "SENSORS_Int.h"
#include "TEMP_Filter_Int.h"

static u16 temp_arr[TEMP_SIZE];
static u16 temp_filter ;
static u16 temp_unfilter ;
static u8 flag = 0 ;

void TEMP_Filter_Init(void)
{
	temp_filter = LM35_Read_Temp();
}

void TEMP_Filter_Runnable(void)
{
	static u8 i =0 ;
	u32 sum=0 ; 
	u8 j ;
	temp_arr[i] = LM35_Read_Temp();
	temp_unfilter = temp_arr[i] ;
	i++ ;
	if (i==10)
	{
		i = 0 ;
		flag = 1 ;
	}
	if (1==flag)
	{
		for (j=0;j<TEMP_SIZE;j++)
		{
			sum += temp_arr[j] ;
		}
		temp_filter = sum / TEMP_SIZE ;
	}
	
}


u16 TEMP_GET_Filterd(void)
{
	return temp_filter ;
}

u16 TEMP_GET_Unfiltered(void)
{
	return temp_unfilter ;
}

