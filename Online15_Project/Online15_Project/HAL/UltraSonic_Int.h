

#ifndef ULTRASONIC_INT_H_
#define ULTRASONIC_INT_H_

#define  US1_PIN			PINA7
#define  US2_PIN			PINC2
#define  US3_PIN			PINC3
#define  US4_PIN			PINC4

#define US_TIMEOUT				23000
#define TOP_VAL					65536

typedef enum 
{
	Ultra_S1 = US1_PIN ,
	Ultra_S2 = US2_PIN ,
	Ultra_S3 = US3_PIN ,
	Ultra_S4 = US4_PIN,
}ultrasonic_t;



void UltraSonic_Init (void) ;

void UltraSonic_Start_Trigger (ultrasonic_t ultra_no ) ;

u8 UltraSonic_Get_Distance (ultrasonic_t ultra_no , u16* p_distance );



#endif /* ULTRASONIC_INT_H_ */