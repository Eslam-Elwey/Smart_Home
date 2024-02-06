
#ifndef EXI_INT_H_
#define EXI_INT_H_

/* Macro Funcs */
/*INTO Enable - disable */
#define EXI_INT0_ENABLE()			(SET_BIT(GICR,INT0))
#define EXI_INT0_DISABLE()			(CLR_BIT(GICR,INT0))
/*INT1 Enable - disable */
#define EXI_INT1_ENABLE()			(SET_BIT(GICR,INT1))
#define EXI_INT1_DISABLE()			(CLR_BIT(GICR,INT1))
/*INT2 Enable - disable */
#define EXI_INT2_ENABLE()			(SET_BIT(GICR,INT2))
#define EXI_INT2_DISABLE()			(CLR_BIT(GICR,INT2))

/*user defined data types */
typedef enum
{
	INTERRUPT_LOW_LEVEL = 0 ,
	INTERRUPT_LOGICAL_CHANGE ,
	INTERRUPT_FALLING_EDGE ,
	INTERRUPT_RISING_EDGE
}Interrupt_Sense_Control_t;

typedef enum
{
	EXT_INT0 = 0 ,
	EXT_INT1 ,
	EXT_INT2
}external_interrupt_t;

typedef void (*pf) (void) ;

void EXI_Init(void);
void EXT_INT_ENABLE(external_interrupt_t int_no , Interrupt_Sense_Control_t edge_type) ;
void EXT_INT_Disable(external_interrupt_t int_no );
void EXT_INT_Set_Call_Back(external_interrupt_t int_no,pf p_func);



#endif /* EXI_INT_H_ */