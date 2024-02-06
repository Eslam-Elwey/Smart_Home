
#ifndef ADC_INT_H_
#define ADC_INT_H_


/******************************************************************/
#define ADC_INTERRUPT_ENABLE()				(SET_BIT(ADCSRA,ADIE))
#define ADC_INTERRUPT_DISABLE()				(CLR_BIT(ADCSRA,ADIE))
#define ADC_ENABLE()						(SET_BIT(ADCSRA,ADEN))
#define ADC_DISABLE()						(CLR_BIT(ADCSRA,ADEN))
#define ADC_BEGIN_CONVERSION()				(SET_BIT(ADCSRA,ADSC))
#define ADC_STOP_CONVERSION()				(CLR_BIT(ADCSRA,ADSC))

#define VOLTAGE_REFERENCE					(u16)5000
#define ADC_RESOLUTION						(u16)1024


/******************************************************************/

typedef enum 
{
	VREF_AREF_Internal = 0 ,
	VREF_AVCC = 1 ,
	VREF_Internal_256V = 3 
}ADC_vref_t;

typedef enum 
{
	ADC_SCALER_2 = 1 ,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_PreScaler_t;

typedef enum 
{
	ADC_NOT_READY,
	ADC_READY	
}ADC_Status_t;

typedef enum 
{
	/* Single Ended */
	ADC_CHANNEL_0 = 0 ,
	ADC_CHANNEL_1 ,
	ADC_CHANNEL_2 ,
	ADC_CHANNEL_3 ,
	ADC_CHANNEL_4 ,
	ADC_CHANNEL_5 ,
	ADC_CHANNEL_6 ,
	ADC_CHANNEL_7 ,
	
	/* Differential */
	ADC_CH0_CH0_GAIN_10X = 8 ,
	ADC_CH1_CH0_GAIN_10X ,
	ADC_CH0_CH0_GAIN_200X ,
	ADC_CH1_CH0_GAIN_200X ,
	ADC_CH2_CH2_GAIN_10X ,
	ADC_CH3_CH2_GAIN_10X ,
	ADC_CH2_CH2_GAIN_200X ,
	ADC_CH3_CH2_GAIN_200X ,
	
	
	ADC_CH0_CH1_GAIN_X = 16 ,
	ADC_CH1_CH1_GAIN_X ,
	ADC_CH2_CH1_GAIN_X ,
	ADC_CH3_CH1_GAIN_X ,
	ADC_CH4_CH1_GAIN_X ,
	ADC_CH5_CH1_GAIN_X ,
	ADC_CH6_CH1_GAIN_X ,
	ADC_CH7_CH1_GAIN_X ,
	
	ADC_CH0_CH2_GAIN_X = 24 ,
	ADC_CH1_CH2_GAIN_X ,
	ADC_CH2_CH2_GAIN_X,
	ADC_CH3_CH2_GAIN_X ,
	ADC_CH4_CH2_GAIN_X ,
	ADC_CH5_CH2_GAIN_X ,
	/*****/
	ADC_122_VBG ,
	ADC_0V_GND 
}ADC_Channel_t;

typedef enum 
{
	ADC_FREE_RUNNING_MODE=0 ,
	ADC_ANALOG_COMPERATOR,
	ADC_EXI_INT0 ,
	ADC_TIMER0_COM_MATCH ,
	ADC_TIMER0_OVER_FLOW ,
	ADC_TIMER1_COM_MATCH_B,
	ADC_TIMER1_OVER_FLOW,
	ADC_TIMER1_CAPTURE
}ADC_Trigger_t;

void ADC_Init (ADC_vref_t v_ref ,ADC_PreScaler_t scaler );
u16 ADC_Read (ADC_Channel_t channel);
void ADC_Start_Conversion (ADC_Channel_t channel);
u16 ADC_Get_Read (void) ;
ADC_Status_t ADC_Get_Read_Periodic(u16 *pdata);
u16 ADC_Get_Read_No_Block (void) ;
void ADC_Set_Call_Back ( void (*PF) (void) ) ;

/* VOLT IN mv */
u16 ADC_Read_Volt_No_Block (void);
u16 ADC_Read_Volt (ADC_Channel_t channel);

#endif /* ADC_INT_H_ */