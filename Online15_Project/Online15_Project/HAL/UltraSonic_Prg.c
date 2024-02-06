
#include "StdTypes.h"
#include "Timers_Int.h"
#include "DIO_Int.h"
#include "UltraSonic_Int.h"

#define F_CPU		8000000UL
#include <util/delay.h>

static void ICU_Func(void) ;
static void Timer1_ovf_Func(void) ;

static volatile u16  t1 , t2 , counter , snap_count ; 
static volatile u8 flag = 0 ;
void UltraSonic_Init (void)
{
	TIMER1_ICU_INTERRUPT_ENABLE() ;
	TIMER1_OVER_FLOW_INTERRUPT_ENABLE() ;
	Timer1_Set_OVF_Call_Back(Timer1_ovf_Func);
	Timer1_Set_ICU_Call_Back(ICU_Func);
	Timer1_ICU_Edge_Mode(ICES1_RISING) ;
}

void UltraSonic_Start_Trigger (ultrasonic_t ultra_no ) 
{
	_delay_ms(10);
	DIO_WritePin(ultra_no,HIGH);
	_delay_us(10);
	DIO_WritePin(ultra_no,LOW);
	
}


u8 UltraSonic_Get_Distance (ultrasonic_t ultra_no , u16* p_distance )
{
	u8 ret_state =0 ;
	u16 count = 0 ;
	while ((flag!=2)&&(count<US_TIMEOUT))
	{
		count++;
		_delay_us(1);
	}
	if (2==flag)
	{
		* p_distance = (t2-t1+((u32)snap_count*TOP_VAL))/58 ;
		flag = 0 ;
		ret_state = 1 ;
		
	}
	return ret_state ;
}


static void ICU_Func(void)
{
	
	if (0==flag)
	{
		counter = 0 ;
		TIMER1_ICU_READ_VALUE(&t1) ;
		Timer1_ICU_Edge_Mode(ICES1_FALLING) ;
		flag = 1 ;
	}
	else if (1==flag)
	{
		TIMER1_ICU_READ_VALUE(&t2) ;
		snap_count = counter ;
		Timer1_ICU_Edge_Mode(ICES1_RISING) ;
		flag = 2 ;
	}
	
}

static void Timer1_ovf_Func(void)
{
	counter++ ;
}