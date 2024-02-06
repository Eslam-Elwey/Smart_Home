
#ifndef LED_CFG_H_
#define LED_CFG_H_

#define LED_TOTAL_NUMBERS		8	

/*Led Pin No : PINA0 - PINB0 - state : ACTIVE_LOW - ACTIVE_HIGH */
static const led_t led_arr[LED_TOTAL_NUMBERS] = {
										   {PINB0,ACTIVE_HIGH},
										   {PINB1,ACTIVE_HIGH},
										   {PINB2,ACTIVE_HIGH},
										   {PINB3,ACTIVE_HIGH},
										   {PINB4,ACTIVE_HIGH},
										   {PINB5,ACTIVE_HIGH},  
										   {PINB6,ACTIVE_HIGH},
										   {PINB7,ACTIVE_HIGH}
													   
									};


#endif /* LED_CFG_H_ */