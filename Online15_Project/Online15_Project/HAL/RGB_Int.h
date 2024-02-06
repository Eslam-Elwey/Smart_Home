

#ifndef RGB_INIT_H_
#define RGB_INIT_H_

/*
#define RGB_RED									0
#define RGB_GREEN								1
#define RGB_BLUE								2
#define RGB_WHITE								3
#define RGB_YELLOW								4
#define RGB_CYAN								5
#define RGB_ORANGE								6
#define RGB_PURPLE								7
#define RGB_LIGHT_BLUE							8
#define RGB_BROWN							    9
#define RGB_LIGHT_GREEN							10
#define RGB_LIGHT_RED							11
#define RGB_GRAY								12
#define RGB_BLACK								13
#define RGB_PINK								14
*/

#define CONVERSION_TIME_MS							1000

#define WRITE_RED_VALUE(val)				TIMER0_OC0_WRITE_VALUE(val)	
#define WRITE_GREEN_VALUE(val)				TIMER1_OC1A_WRITE_VALUE(val)	
#define WRITE_BLUE_VALUE(val)				TIMER1_OC1B_WRITE_VALUE(val)				

typedef enum 
{
	RGB_RED = 0 ,
	RGB_GREEN,
	RGB_BLUE,
	RGB_WHITE,
	RGB_YELLOW,
	RGB_CYAN,
	RGB_ORANGE,
	RGB_PURPLE,
	RGB_LIGHT_BLUE,
	RGB_BROWN,
	RGB_LIGHT_GREEN,
	RGB_LIGHT_RED,
	RGB_GRAY,
	RGB_BLACK,
	RGB_PINK,
	TOTAL_RGB_COLOURS
	
}rgb_color_name_t;

typedef struct 
{
	u8 red_val ;
	u8 grn_val ;
	u8 blu_val ;	
}rgb_t;

typedef enum 
{
	RGB_OK = 0 ,
	RGB_OUT_RANGE	
}rgb_ret_status_t;


void RGB_Init (void) ;
rgb_ret_status_t RGB_Colour_array (rgb_color_name_t color);
void RGB_Colour_Data (rgb_t* percent);
rgb_ret_status_t RGB_Convert_Colours (u8 color1 , u8 color2 );
rgb_ret_status_t RGB_Convert_Colours_time_request_ms (u8 color1 , u8 color2 , u16 time );

#endif /* RGB_INIT_H_ */