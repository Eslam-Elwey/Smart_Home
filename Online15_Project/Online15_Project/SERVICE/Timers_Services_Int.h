
#ifndef TIMERS_SERVICES_INT_H_
#define TIMERS_SERVICES_INT_H_

#define MEASURE_TIMEOUT_uS						1000	

/* Timer1 PWM Mode ( ICR1 Top) Output OCR1A Pin - Prescaler 8*/
void PWM_Generate_Frq_KHZ (u16 Freq , u8 duty) ;
void PWM_Generate_Frq_HZ (u16 Freq , u8 duty) ;				

/* Set Timer0 Normal Mode Prescaler 8*/
void Set_Function_Call_Interrupt_Time_us (u32 time , void (*pf) (void));


/* Set Timer2 Normal Mode Prescaler 1024*/
void Set_Call_Timer2_Interrupt_Time_ms (u32 time , void (*pf) (void));

/*Using Input Capture Unit
busy Wait Till TimeOut */
void PWM_Measure_Init(void);
void PWM_Measure(u32 *Freq , u8 *duty );


/*Timer 1
Set EXI On Any Change 
Take 2 Reads From Timer 
on Falling Edge And Rising Edge 
time = t2 - t1 + c * I.T*/
void Measure_Button_Pressing_Time (void) ;
u8 Get_press_time_val (u32 *ptime) ;

#endif /* TIMERS_SERVICES_INT_H_ */