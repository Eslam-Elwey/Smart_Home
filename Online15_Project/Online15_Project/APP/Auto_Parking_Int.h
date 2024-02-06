
#ifndef AUTO_PARKING_INT_H_
#define AUTO_PARKING_INT_H_

/*****************************************************************************************/

#define CAR_LENGTH_CM									70
#define CAR_WIDTH_CM									50
#define CAR_SPEED_CM_PER_SEC							40
#define FOCUS_TIME_SEC									((CAR_LENGTH_CM + 10)/CAR_SPEED_CM_PER_SEC)

#define MINIMUM_ACCEPTANCE_WIDTH						(CAR_WIDTH_CM + 10)

#define TOTAL_ULRASONIC_NUMBER							4

typedef enum 
{
	RIGHT_PARK = 0 ,
	LEFT_PARK
}park_t;

/*****************************************************************************************/

void Auto_Parking_Init (void) ;

void Auto_Parking_Runnable (void) ;


#endif /* AUTO_PARKING_INT_H_ */