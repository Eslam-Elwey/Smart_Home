

#ifndef SEVEN_SEG_INT_H_
#define SEVEN_SEG_INT_H_
#include "DIO_Int.h"
#include "MemMap.h"

#define SEGEMENT_MUX_ENABLE_PINS				2


typedef enum 
{
	COMMON_CATHODE ,
	COOMMON_ANODE 
}sev_seg_com_t;

typedef struct 
{
	DIO_Pin_t seg_pin[7] ; 
	sev_seg_com_t common : 1 ;
}seven_seg_basic_t;

typedef struct
{
	DIO_Pin_t seg_pin[7] ;
	DIO_Pin_t enable_pin_arr[SEGEMENT_MUX_ENABLE_PINS];
	sev_seg_com_t common : 1 ;
	
	
}seven_seg_mux_t;

typedef struct
{
	DIO_Pin_t seg_pin[4]    ;
	sev_seg_com_t common : 1 ;
}seven_seg_bcd_t;



void SEVEN_SEG_Init (void) ;

void SEVEN_SEG_base_Write(u8 seg_no,u8 num);

void SEVEN_SEG_MUX2D_Write (u8 seg_no,u8 num);

void SEVEN_SEG_MUX2D_Write_HEX (u8 seg_no,u8 num);

void SEVEN_SEG_BCD_Write (u8 seg_no,u8 num);



#endif /* SEVEN_SEG_INT_H_ */