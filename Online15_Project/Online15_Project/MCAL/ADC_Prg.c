
#include "StdTypes.h"
#include "MemMap.h"
#include "ADC_Int.h"
#include "ADC_Cfg.h"

static void (*ADC_PF) (void) ;
static u8 adc_flag = 0 ;
void ADC_Init (ADC_vref_t v_ref ,ADC_PreScaler_t scaler )
{
	/******* Prescaler *******/
	scaler &= 0x07 ;
	ADCSRA &= 0xF8 ;
	ADCSRA |= scaler ;
	
	/******* Voltage Reference *******/
	v_ref &= 0x03 ;
	ADMUX &= 0x3F ;
	ADMUX |= (v_ref<<6) ;
	
	/* Right Adjust */
	CLR_BIT(ADMUX,ADLAR);
	
	/* Enable ADC */
	ADC_ENABLE();
}

u16 ADC_Read (ADC_Channel_t channel)
{
	/***** Select Channel ******/
	channel &= 0x1F ;
	ADMUX &= 0xE0 ;
	ADMUX |= channel ;
	adc_flag = 0 ;
	/**Start Conversion **/
	ADC_BEGIN_CONVERSION();
	
	/*** Busy Wait ***/
	while (READ_BIT(ADCSRA,ADSC));
	
	/** Get ADC READ **/
	
	/*
		1.Right Adjust : 
		adcl = ADCL ;
		adch = ADCH ;
		return (((u16)adcl)|((u16)adch<<8));
		
		2.Left Adjust :
		adcl = ADCL ;
		adch = ADCH ;
		return (((u16)adcl>>6)|((u16)adch<<2));
	*/
	return ADC ;
	
}

void ADC_Start_Conversion (ADC_Channel_t channel)
{
	/***** Select Channel ******/
	if (0==adc_flag)
	{
		channel &= 0x1F ;
		ADMUX &= 0xE0 ;
		ADMUX |= channel ;
		
		/**Start Conversion **/
		ADC_BEGIN_CONVERSION();
		
		adc_flag = 1 ;
	}
	
}

u16 ADC_Get_Read (void)
{
	/*** Busy Wait ***/
	while (READ_BIT(ADCSRA,ADSC));
	adc_flag = 0 ;
	/** Get ADC READ **/
	return ADC ;
}

ADC_Status_t ADC_Get_Read_Periodic(u16 *pdata)
{
	ADC_Status_t state = ADC_NOT_READY ;
	if (READ_BIT(ADCSRA,ADSC)==0)
	{
		*pdata = ADC ;
		adc_flag = 0 ;
		state = ADC_READY ; 
	}
	else 
	{
		adc_flag = 1 ;
	}
	
	return state ; 
}

u16 ADC_Get_Read_No_Block (void) 
{
	adc_flag = 0 ;
	return ADC ; 
}

u16 ADC_Read_Volt_No_Block (void)
{
	u16 volt ; 
	adc_flag = 0 ;
	volt = ((u32) ADC * VOLTAGE_REFERENCE) / (ADC_RESOLUTION) ;
	
	return volt ;
}

u16 ADC_Read_Volt (ADC_Channel_t channel)
{
	u16 volt ;
	adc_flag = 0 ;
	u16 ADC_Val = ADC_Read (channel);
	volt = ((u32) ADC_Val * VOLTAGE_REFERENCE) / (ADC_RESOLUTION) ;
	
	return volt ;
}

void ADC_Set_Call_Back ( void (*PF) (void) )
{
	ADC_PF = PF ; 
}


ISR(ADC_vect)
{
	if (ADC_PF!=NULLPTR)
	{
		ADC_PF();
	}
}

