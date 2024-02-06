
#ifndef STEPPER_INT_H_
#define STEPPER_INT_H_


#define	DELAY									5
#define TOTAL_1_TURN							512


void Stepper_Motor_Init(void);
void Stepper_Motor_Bipolar_CW(void);
void Stepper_Motor_Bipolar_Counter_CW(void);
void Stepper_Motor_Unipolar_CW(void);
void Stepper_Motor_Unipolar_Counter_CW(void);
void Stepper_Motor_Unipolar_HS_CW(void);
void Stepper_Motor_Unipolar_HS_Counter_CW(void);

void Stepper_Rotate_CW_By_Angle(u16 angle);
void Stepper_Rotate_Counter_CW_By_Angle(u16 angle);

void Stepper_Rotate_CW_By_nof_Rotations(u8 rot_no);
void Stepper_Rotate_Counter_CW_By_nof_Rotations(u8 rot_no);


#endif /* STEPPER_INT_H_ */