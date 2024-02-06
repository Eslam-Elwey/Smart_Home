
#ifndef FIRE_SYSTEM_INT_H_
#define FIRE_SYSTEM_INT_H_

typedef enum 
{
	CORRECT_PASSWORD = 0 ,
	WRONG_PASSWORD
}password_status_t;


#define TEMP_SENSOR					ADC_CHANNEL_7
#define SMOKE_SENSOR				ADC_CHANNEL_0
#define PASSWORD_SIZE				5
#define FINE_TEMP					480
#define HEAT_TEMP					500
#define SMOKE_PERCENT				500
#define MOTOR_PUMP					PINC5
#define BUZZER_ALARM				PIND3
#define ALARM_LED					PINB6
#define EMERGENCY_LED				PINB7
#define AVAL_RANGE					1123-PASSWORD_SIZE

typedef enum 
{
	FINE_STATE = 0 ,
	HEAT_STATE  ,
	FIRE_STATE	
}system_state_t;



void Fire_System_Init (void) ;

void Fire_System_Runnable (void) ;


#endif /* FIRE_SYSTEM_INT_H_ */