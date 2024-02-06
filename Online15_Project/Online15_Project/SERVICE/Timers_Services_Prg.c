
#include "StdTypes.h"
#include "Timers_Int.h"
#include "Timers_Services_Int.h"
#include "EXI_Int.h"
#include "DIO_Int.h"
#define F_CPU		8000000UL
#include <util/delay.h>

static void Fun_Call_Interrrupt (void) ;
static void Fun_Timer2_Call_Interrrupt (void) ;
static void measure_timer1_no_interrupts (void) ;
static void EXI0_Measure_Func (void);
static void ICU_Func_PWM(void) ;
static void Timer1_ovf_Func (void) ;


static u32 time_interrupt ;
static void (*pfunc) (void);
static u32 repeat ; 
static u32 reminder ;

static u32 time2_interrupt ;
static void (*pfunc2) (void);
static u32 repeat2 ;
static u32 reminder2 ;

static volatile u16 t1 , t2 , press_counter ; 
static volatile u32   press_time ;
static u8 finish_flag = 0 ;

static volatile u16 t1_pwm , t2_pwm ,t3_pwm , count_pwm , snap_pwm1 ,snap_pwm2 ;
static u8 Pwm_flag = 0 ;


/*Use Timer0 Normal Mode (Over Flow Interrupt)
 Timer0_Init(TIMER0_NORMAL_MODE,Timer0_PRESCALER_CLK_8)  */
void Set_Function_Call_Interrupt_Time_us (u32 time , void (*pf) (void))
{
	pfunc = pf ;
	time_interrupt = time ;
	
	if (time_interrupt <= 255)
	{
		TIMER0_WRITE_VALUE (256-time_interrupt);
	}
	else 
	{
		reminder = time_interrupt % 256 ;
		repeat = (time_interrupt / 256) + 1 ;
		TIMER0_WRITE_VALUE (256-reminder);
	}
	Timer0_SET_OVF_Call_Back(Fun_Call_Interrrupt);
}


static void Fun_Call_Interrrupt (void) 
{
	
	if (time_interrupt <= 255)
	{
		TIMER0_WRITE_VALUE (256-time_interrupt);
		pfunc();
	}
	
	else 
	{
		static u16 counter = 0 ;
		
		counter++ ;
		
		if (counter==repeat)
		{
			counter = 0 ;
			TIMER0_WRITE_VALUE (256-reminder);
			pfunc();
		}
	
	}
}

void Set_Call_Timer2_Interrupt_Time_ms (u32 time , void (*pf) (void))
{
	pfunc2 = pf ;
	time2_interrupt = time*1000 ;
	
	if (time2_interrupt <= 32768)
	{
		TIMER2_WRITE_VALUE (256-(time2_interrupt/128));
	}
	else
	{
		reminder2 = time2_interrupt % 32768 ;
		repeat2 = (time2_interrupt / 32768) + 1 ;
		TIMER2_WRITE_VALUE (256-(reminder2/128));
	}
	Timer2_SET_OVF_Call_Back(Fun_Timer2_Call_Interrrupt);
}


static void Fun_Timer2_Call_Interrrupt (void)
{
	if (time2_interrupt <= 32768)
	{
		TIMER2_WRITE_VALUE (256-(time2_interrupt/128));
		pfunc2();
	}
	
	else
	{
		static u16 counter = 0 ;
		
		counter++ ;
		
		if (counter==repeat2)
		{
			counter = 0 ;
			TIMER2_WRITE_VALUE (256-(reminder2/128));
			pfunc2();
		}
		
	}
}

/*Use Timer1 Normal Mode Scaler 8 */
void Measure_Button_Pressing_Time (void) 
{
	EXI_INT0_ENABLE() ;
	TIMER1_OVER_FLOW_INTERRUPT_ENABLE() ;
	Timer1_Set_OVF_Call_Back(measure_timer1_no_interrupts);
	EXT_INT_Set_Call_Back(EXT_INT0,EXI0_Measure_Func);
	EXT_INT_ENABLE(EXT_INT0,INTERRUPT_FALLING_EDGE);
}

u8 Get_press_time_val (u32 *ptime) 
{
	u8 ret_state = 0 ; 
	if (1==finish_flag)
	{
		press_time = t2 - t1 + ((u32)press_counter*65535) ; 
		press_counter = 0 ;
		*ptime = press_time ;
		finish_flag = 0 ;
		ret_state = 1 ;
	}
	
	return ret_state ;
}

/*Use Timer 0*/
static void EXI0_Measure_Func (void)
{
	static u8 flag = 0 ;
	if (0==flag)
	{
		press_counter = 0 ;
		TIMER1_READ_VALUE(&t1) ;
		EXT_INT_ENABLE(EXT_INT0,INTERRUPT_RISING_EDGE);
		flag = 1 ;
	}
	else if (1==flag)
	{
		TIMER1_READ_VALUE(&t2) ;
		EXT_INT_ENABLE(EXT_INT0,INTERRUPT_FALLING_EDGE);
		finish_flag = 1 ;
		flag = 0 ;
	}
}
static void measure_timer1_no_interrupts (void)
{
	press_counter++ ; 
}


void PWM_Measure_Init(void)
{
	TIMER1_WRITE_VALUE (0) ;
	Timer1_ICU_Edge_Mode(ICES1_RISING) ;
	Timer1_Set_OVF_Call_Back(Timer1_ovf_Func);
	Timer1_Set_ICU_Call_Back(ICU_Func_PWM);
	TIMER1_ICU_INTERRUPT_ENABLE() ;
	TIMER1_OVER_FLOW_INTERRUPT_ENABLE() ;
	
}

void PWM_Measure(u32 *Freq , u8 *duty )
{
	u32 count = 0 ; 
	u32 ton , toff ; 
	while ((count<MEASURE_TIMEOUT_uS)&&(Pwm_flag!=3))
	{
		_delay_us(1);
		count++;
	}
	if (Pwm_flag==3)
	{
		ton = t2_pwm - t1_pwm + (u32)snap_pwm1 * 65535 ;
		toff = t3_pwm - t2_pwm + (u32)snap_pwm2 * 65535 ;
		Pwm_flag = 1 ;
		count_pwm = 0 ;
		*Freq = (u32)1000000/(ton+toff) ;
		*duty = ((u32)ton*100)/(ton+toff) ;
		t1_pwm = t3_pwm ;
	}
	else
	{
		u8 signal_val = DIO_ReadPin(PIND6);
		*Freq = 0 ;
		*duty = signal_val * 100 ;  
	}
	
}

static void ICU_Func_PWM(void)
{
	
	if (0==Pwm_flag)
	{
		count_pwm = 0 ;
		TIMER1_ICU_READ_VALUE(&t1_pwm) ;
		Timer1_ICU_Edge_Mode(ICES1_FALLING) ;
		Pwm_flag = 1 ;
	}
	else if (1==Pwm_flag)
	{
		TIMER1_ICU_READ_VALUE(&t2_pwm) ;
		snap_pwm1 = count_pwm ;
		count_pwm = 0 ;
		Timer1_ICU_Edge_Mode(ICES1_RISING) ;
		Pwm_flag = 2 ;
	}
	else if (2==Pwm_flag)
	{
		TIMER1_ICU_READ_VALUE(&t3_pwm) ;
		snap_pwm2 = count_pwm ;
		count_pwm = 0 ;
		Timer1_ICU_Edge_Mode(ICES1_FALLING) ;
		Pwm_flag = 3 ;
	}
}

static void Timer1_ovf_Func (void) 
{
	count_pwm++;
}

/*TIMER1_PWM_PHASE_CR_ICR1_TOP Or
TIMER1_PWM_PHASE_CR_OCR1A_TOP */
void PWM_Generate_Frq_KHZ (u16 Freq , u8 duty)
{
	u16 total_time  , ton ;
	u16 val ;
	if ((Freq==0)||(duty>=100))
	{
		return ;
	}
	Timer1_Set_OC1A_Mode(TIMER1_OC1A_CLEAR);
	total_time = (1000/Freq);
	if (total_time>=1)
	{
		TIMER1_ICU_WRITE_VALUE(total_time-1); 
	}
	else 
	{
		TIMER1_ICU_WRITE_VALUE(0); 
	}
	ton = ((u32)duty*(TIMER1_ICU_READ_VALUE(&val)+1))/100;
	if (ton>=1)
	{
		TIMER1_OC1A_WRITE_VALUE(ton-1);
	}
	else
	{
		TIMER1_OC1A_WRITE_VALUE(0);
	}
	
}


void PWM_Generate_Frq_HZ (u16 Freq , u8 duty) 
{
	u16 total_time  , ton ;
	u16 val ;
	if ((Freq==0)||(duty>=100))
	{
		return ;
	}
	Timer1_Set_OC1A_Mode(TIMER1_OC1A_CLEAR);
	total_time = ((u32)1000000/Freq);
	if (total_time>=1)
	{
		TIMER1_ICU_WRITE_VALUE(total_time-1);
	}
	else
	{
		TIMER1_ICU_WRITE_VALUE(0);
	}
	ton = ((u32)duty*(TIMER1_ICU_READ_VALUE(&val)+1))/100;
	if (ton>=1)
	{
		TIMER1_OC1A_WRITE_VALUE(ton-1);
	}
	else
	{
		TIMER1_OC1A_WRITE_VALUE(0);
	}
}