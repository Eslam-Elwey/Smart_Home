
#include "StdTypes.h"
#include "MemMap.h"
#include "EXI_Int.h"

 static pf EXT_INT0_call_back = NULLPTR ;
 static pf EXT_INT1_call_back = NULLPTR ;
 static pf EXT_INT2_call_back = NULLPTR ;
 
 void EXI_Init(void)
 {
	 EXT_INT_ENABLE(EXT_INT0,INTERRUPT_FALLING_EDGE);
	 EXT_INT_ENABLE(EXT_INT1,INTERRUPT_FALLING_EDGE);
	 EXT_INT_ENABLE(EXT_INT2,INTERRUPT_FALLING_EDGE);
 }

 void EXT_INT_ENABLE(external_interrupt_t int_no , Interrupt_Sense_Control_t edge_type)
 {
	 switch(int_no)
	 {
		 case EXT_INT0 :
		 EXI_INT0_ENABLE();
		 switch(edge_type)
		 {
			 case INTERRUPT_LOW_LEVEL :
			 CLR_BIT(MCUCR,ISC00);
			 CLR_BIT(MCUCR,ISC01);
			 break ;
			 
			 case INTERRUPT_LOGICAL_CHANGE :
			 SET_BIT(MCUCR,ISC00);
			 CLR_BIT(MCUCR,ISC01);
			 break ;
			 
			 case INTERRUPT_FALLING_EDGE :
			 CLR_BIT(MCUCR,ISC00);
			 SET_BIT(MCUCR,ISC01);
			 break ;
			 
			 case INTERRUPT_RISING_EDGE :
			 SET_BIT(MCUCR,ISC00);
			 SET_BIT(MCUCR,ISC01);
			 break ;
		 }
		 break ;
		 
		 case EXT_INT1 :
		 EXI_INT1_ENABLE();
		 switch(edge_type)
		 {
			 case INTERRUPT_LOW_LEVEL :
			 CLR_BIT(MCUCR,ISC10);
			 CLR_BIT(MCUCR,ISC11);
			 break ;
			 
			 case INTERRUPT_LOGICAL_CHANGE :
			 SET_BIT(MCUCR,ISC10);
			 CLR_BIT(MCUCR,ISC11);
			 break ;
			 
			 case INTERRUPT_FALLING_EDGE :
			 CLR_BIT(MCUCR,ISC10);
			 SET_BIT(MCUCR,ISC11);
			 break ;
			 
			 case INTERRUPT_RISING_EDGE :
			 SET_BIT(MCUCR,ISC10);
			 SET_BIT(MCUCR,ISC11);
			 break ;
		 }
		 break ;
		 
		 case EXT_INT2 :
		 EXI_INT2_ENABLE();
		 switch(edge_type)
		 {
			 case INTERRUPT_FALLING_EDGE :
			 CLR_BIT(MCUCSR,ISC2);
			 break ;
			 
			 case INTERRUPT_RISING_EDGE :
			 SET_BIT(MCUCSR,ISC2);
			 break ;
			 
			 case INTERRUPT_LOW_LEVEL :
				 break ;
			 
			 case INTERRUPT_LOGICAL_CHANGE :
				break ;
		 }
		 break ;
	 }
	 
 }

 void EXT_INT_Disable(external_interrupt_t int_no )
 {
	 switch (int_no)
	 {
		 case EXT_INT0 :
		 EXI_INT0_DISABLE();
		 break;
		 
		 case EXT_INT1 :
		 EXI_INT1_DISABLE();
		 break;
		 
		 case EXT_INT2 :
		 EXI_INT2_DISABLE();
		 break;
	 }
 }

 void EXT_INT_Set_Call_Back(external_interrupt_t int_no,pf p_func)
 {
	 switch (int_no)
	 {
		 case EXT_INT0 :
		 EXT_INT0_call_back = p_func ;
		 break;
		 
		 case EXT_INT1 :
		 EXT_INT1_call_back = p_func ;
		 break;
		 
		 case EXT_INT2 :
		 EXT_INT2_call_back = p_func ;
		 break;
	 }
 }

 ISR(INT0_vect)
 {
	 if (EXT_INT0_call_back!=NULLPTR)
	 {
		 EXT_INT0_call_back();
	 }
 }

 ISR(INT1_vect)
 {
	 if (EXT_INT1_call_back!=NULLPTR)
	 {
		 EXT_INT1_call_back();
	 }
 }

 ISR (INT2_vect)
 {
	 if (EXT_INT2_call_back!=NULLPTR)
	 {
		 EXT_INT2_call_back();
	 }
 }