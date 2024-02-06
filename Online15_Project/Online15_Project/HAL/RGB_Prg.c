
#include "StdTypes.h"
#include "Timers_Int.h"
#include "Timers_Services_Int.h"
#include "RGB_Config.h"
#include "RGB_Int.h"

#define TOTAL_STEPS						10
#define INCREMENT						0
#define DECREMENT						1
#define NO_CHANGE						2

static void rgb_func_call_back (void) ;

static rgb_t current_color ;
static rgb_t next_color ;
static rgb_t total_change;
static rgb_t step_change ; 
static rgb_t inc_dec_flag ; // 0 Increment - 1 DECREMENT - 2 NO_CHANGE
static rgb_t color_val ; 
static u16 conv_time ; 
static u8 color_no ; 

/*
	Timer0 / Timer1 PWM Fast Mode Top 0xFF
	OCR0 Red 
	OC1A Green 
	OC1B Blue
	
	Timer2 To Set Interrupt Time (Normal Mode)
*/

void RGB_Init (void) 
{
	Timer0_OC0_Mode(Timer0_OC0_SET_COMPARE_MATCH);
	Timer1_Set_OC1A_Mode(TIMER1_OC1A_SET);
	Timer1_Set_OC1B_Mode(TIMER1_OC1B_SET);
}

/* Color From 0 TO (TOTAL_RGB_COLOURS - 1) */
rgb_ret_status_t RGB_Colour_array (u8 color)
{
	rgb_ret_status_t status = RGB_OK ;
	if (color>=TOTAL_RGB_COLOURS)
	{
		status = RGB_OUT_RANGE ;
	}
	else 
	{
		WRITE_RED_VALUE (255-rgb_colors[color].red_val);
		WRITE_GREEN_VALUE (255-rgb_colors[color].grn_val);
		WRITE_BLUE_VALUE (255-rgb_colors[color].blu_val);
		current_color = rgb_colors[color] ;
	}
	
	return status ;
}


void RGB_Colour_Data (rgb_t* percent)
{
	if (percent!=NULLPTR)
	{
		WRITE_RED_VALUE (255-percent->red_val);
		WRITE_GREEN_VALUE (255-percent->grn_val);
		WRITE_BLUE_VALUE (255-percent->blu_val);
	}
	
}


rgb_ret_status_t RGB_Convert_Colours (u8 color1 , u8 color2 )
{
	rgb_ret_status_t status = RGB_OK ; 
	RGB_Colour_array(color1);
	if ((color1<TOTAL_RGB_COLOURS)&&(color2<TOTAL_RGB_COLOURS))
	{
		u32 step_time = conv_time / TOTAL_STEPS ;
		color_no = color2 ;
		current_color = rgb_colors[color1] ;
		color_val = current_color ;
		next_color = rgb_colors[color2] ;
		conv_time = CONVERSION_TIME_MS ;
		/* Enable Counter Unit flag */
		TIMER2_OVER_FLOW_INTERRUPT_ENABLE();
		/* Red */
		if (rgb_colors[color1].red_val>rgb_colors[color2].red_val)
		{
			total_change.red_val = rgb_colors[color1].red_val - rgb_colors[color2].red_val ;
			step_change.red_val = total_change.red_val / TOTAL_STEPS ;
			inc_dec_flag.red_val = DECREMENT ;
		}
		else if (rgb_colors[color1].red_val<rgb_colors[color2].red_val)
		{
			total_change.red_val = rgb_colors[color2].red_val - rgb_colors[color1].red_val ;
			step_change.red_val = total_change.red_val / TOTAL_STEPS ;
			inc_dec_flag.red_val = INCREMENT ;
		}
		else
		{
			inc_dec_flag.red_val = NO_CHANGE ;
		}
		/* Green */
		if (rgb_colors[color1].grn_val>rgb_colors[color2].grn_val)
		{
			total_change.grn_val = rgb_colors[color1].grn_val - rgb_colors[color2].grn_val ;
			step_change.grn_val = total_change.grn_val / TOTAL_STEPS ;
			inc_dec_flag.grn_val = DECREMENT ;
			
		}
		else if (rgb_colors[color1].grn_val<rgb_colors[color2].grn_val)
		{
			total_change.grn_val = rgb_colors[color2].grn_val - rgb_colors[color1].grn_val ;
			step_change.grn_val = total_change.grn_val / TOTAL_STEPS ;
			inc_dec_flag.grn_val = INCREMENT ;
		}
		else
		{
			inc_dec_flag.grn_val = NO_CHANGE  ;
		}
		/* Blue */
		if (rgb_colors[color1].blu_val>rgb_colors[color2].blu_val)
		{
			total_change.blu_val = rgb_colors[color1].blu_val - rgb_colors[color2].blu_val ;
			step_change.blu_val = total_change.blu_val / TOTAL_STEPS ;
			inc_dec_flag.blu_val = DECREMENT ;
		}
		else if (rgb_colors[color1].blu_val<rgb_colors[color2].blu_val)
		{
			total_change.blu_val = rgb_colors[color2].blu_val - rgb_colors[color1].grn_val ;
			step_change.blu_val = total_change.blu_val / TOTAL_STEPS ;
			inc_dec_flag.blu_val = INCREMENT ;
		}
		else
		{
			inc_dec_flag.blu_val = NO_CHANGE   ;
		}
		
		
		/** Set Call Back  **/
		Set_Call_Timer2_Interrupt_Time_ms (step_time,rgb_func_call_back);
	}
	
	else 
	{
		status = RGB_OUT_RANGE ;
	}
	return status ;
}

/* time in ms */
rgb_ret_status_t RGB_Convert_Colours_time_request_ms (u8 color1 , u8 color2 , u16 time )
{
	rgb_ret_status_t ret_status = RGB_OK ;
	
	if ((color1<TOTAL_RGB_COLOURS)&&(color2<TOTAL_RGB_COLOURS))
	{
		conv_time = time ;
		RGB_Convert_Colours(color1 , color2) ;
	}
	else 
	{
		ret_status = RGB_OUT_RANGE ; 
	}
	return ret_status ;
}

static void rgb_func_call_back (void)
{
	
	static u8 counter = 0 ;
	if (counter == (TOTAL_STEPS-1))
	{
		current_color = next_color ;
		RGB_Colour_array (color_no);
		TIMER2_OVER_FLOW_INTERRUPT_DISABLE();
		counter = 0 ;
	}
	else 
	{
		/* RED */
		if (inc_dec_flag.red_val==INCREMENT)
		{
			(color_val.red_val) +=  step_change.red_val ;
		}
		else if (inc_dec_flag.red_val==DECREMENT)
		{
			(color_val.red_val) -=  step_change.red_val ;
		}
		/* GREEN */
		if (inc_dec_flag.grn_val==INCREMENT)
		{
			(color_val.grn_val) +=  step_change.grn_val ;
		}
		else if (inc_dec_flag.grn_val==DECREMENT)
		{
			(color_val.grn_val) -=  step_change.grn_val ;
		}
		/* Blue */
		if (inc_dec_flag.blu_val==INCREMENT)
		{
			(color_val.blu_val) +=  step_change.blu_val ;
		}
		else if (inc_dec_flag.blu_val==DECREMENT)
		{
			(color_val.blu_val) -=  step_change.blu_val ;
		}
		RGB_Colour_Data (&color_val);
		counter++ ;
	}
	
}
