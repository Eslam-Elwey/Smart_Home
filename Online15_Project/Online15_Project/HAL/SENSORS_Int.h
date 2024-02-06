
#ifndef SENSORS_INT_H_
#define SENSORS_INT_H_


#define LM35_CHANNEL				ADC_CHANNEL_7
#define MPX_CHANNEL					ADC_CHANNEL_0

/*Temp in celsius *10 */
u16 LM35_Read_Temp (void);
u16 LM35_Read_Temp_No_Block (void) ;


/*Pressure in Kpa *10 */
u16 MPX_Read_Pressure (void);
u16 MPX_Read_Pressure_No_Block (void);


#endif /* SENSORS_INT_H_ */