
#ifndef STEPPERAPP_INT_H_
#define STEPPERAPP_INT_H_

typedef enum
{
	ANGLE= 0 ,
	ROTATE ,
}stepper_state_t ;



void Stepper_APP_Init(void);

void Stepper_APP_Runnable(void);



#endif /* STEPPERAPP_INT_H_ */