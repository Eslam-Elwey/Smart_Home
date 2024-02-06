
#include "StdTypes.h"
#include "DIO_Int.h"
#include "Stepper_Int.h"
#include "Stepper_Cfg.h"

#define F_CPU		8000000UL
#include <util/delay.h>


void Stepper_Motor_Init(void)
{
	
}

void Stepper_Motor_Bipolar_CW(void)
{
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	_delay_ms(DELAY);
}

void Stepper_Motor_Bipolar_Counter_CW(void)
{
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
}

void Stepper_Motor_Unipolar_CW(void)
{
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL1B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL1B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	DIO_WritePin(COIL1B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL1B,HIGH);
	_delay_ms(DELAY);
}


void Stepper_Motor_Unipolar_Counter_CW(void)
{
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL2A,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL2A,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	_delay_ms(DELAY);
}

void Stepper_Motor_Unipolar_HS_CW(void)
{
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL1B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL1B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL1B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,HIGH);
	DIO_WritePin(COIL1B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	DIO_WritePin(COIL1B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	DIO_WritePin(COIL1B,HIGH);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL1B,HIGH);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL1B,HIGH);
	_delay_ms(DELAY);
}
void Stepper_Motor_Unipolar_HS_Counter_CW(void)
{
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL2A,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL2A,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL2A,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2B,HIGH);
	DIO_WritePin(COIL2A,HIGH);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	_delay_ms(DELAY);
}


/*Step Angle 0.18*/
void Stepper_Rotate_CW_By_Angle(u16 angle)
{
	u16 Rot = ((u32)angle*TOTAL_1_TURN)/360 ;
	u16 i ;
	for (i=0;i<Rot;i++)
	{
		Stepper_Motor_Unipolar_CW();
	}
}



void Stepper_Rotate_CW_By_nof_Rotations(u8 rot_no)
{
	u32 i ; 
	for (i=0;i<((u32)rot_no*TOTAL_1_TURN);i++)
	{
		Stepper_Motor_Unipolar_CW();
	}
}

void Stepper_Rotate_Counter_CW_By_Angle(u16 angle)
{
	u16 Rot = ((u32)angle*TOTAL_1_TURN)/360 ;
	u16 i ;
	for (i=0;i<Rot;i++)
	{
		Stepper_Motor_Unipolar_Counter_CW();
	}
}

void Stepper_Rotate_Counter_CW_By_nof_Rotations(u8 rot_no)
{
	u32 i ;
	for (i=0;i<((u32)rot_no*TOTAL_1_TURN);i++)
	{
		Stepper_Motor_Unipolar_Counter_CW();
	}
}