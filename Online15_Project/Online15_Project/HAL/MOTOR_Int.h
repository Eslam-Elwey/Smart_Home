
#ifndef MOTOR_INT_H_
#define MOTOR_INT_H_

#include "DIO_Int.h"

typedef struct 
{
	DIO_Pin_t MOTOR_ENABLE_1;
	DIO_Pin_t MOTOR_ENABLE_2;	
}motor_control_t;

typedef enum 
{
	M1=0,
	M2,
	M3,
	M4,
	M5,
	M6,
	M7,
	M8,
	M9,
	M10
}motor_t;

void MOTOR_Init(void) ;
void MOTOR_Rotate_CW(motor_t motor_no) ;
void MOTOR_Rotate_Counter_CW(motor_t motor_no) ;
void MOTOR_Stop(motor_t motor_no) ;
void MOTOR_Set_Speed(motor_t motor_no , u8 speed_Percentage);


#endif /* MOTOR_INT_H_ */