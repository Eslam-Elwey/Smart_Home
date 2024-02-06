
#ifndef TEMP_FILTER_INT_H_
#define TEMP_FILTER_INT_H_

#define TEMP_SIZE				10

/* Mean Filter */

void TEMP_Filter_Init(void);

void TEMP_Filter_Runnable(void);

u16 TEMP_GET_Filterd(void);

u16 TEMP_GET_Unfiltered(void);



#endif /* TEMP_FILTER_INT_H_ */