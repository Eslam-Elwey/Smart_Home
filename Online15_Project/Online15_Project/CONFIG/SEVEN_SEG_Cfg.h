
#ifndef SEVEN_SEG_CFG_H_
#define SEVEN_SEG_CFG_H_



#define TOTAL_BASE_SEGMENTS						1

#define TOTAL_MUX_SEGMENTS						1

#define TOTAL_BCD_SEGMENTS						1

/*segment 8 pins arr
common connection : COMMON_CATHODE - COOMMON_ANODE
 */
static const seven_seg_basic_t seg_base_arr[TOTAL_BASE_SEGMENTS] = {
															{
																{PINA0,PINA1,PINA2,PINB1,PINB2,PINB3,PINB5},
																COOMMON_ANODE
															}
															};
/*segment 8 pins arr
enable pins arr -
common connection : COMMON_CATHODE - COOMMON_ANODE
  */														
static const seven_seg_mux_t seg_mux2d_arr[TOTAL_MUX_SEGMENTS] = {
															{
																{PINA1,PINA2,PINA3,PINA4,PINA5,PINA6,PINA7},
																{PINC6,PINC7},
																COMMON_CATHODE
																
															}
														};	
/*segment 4 pins arr
common connection : COMMON_CATHODE - COOMMON_ANODE	 */														
static const seven_seg_bcd_t seg_bcd_arr[TOTAL_BCD_SEGMENTS] = {
															{
																{PINA0,PINA1,PINA2,PINA3},
																COMMON_CATHODE
															},
															{
																{PINB0,PINB1,PINB2,PINB3},
																COMMON_CATHODE
															}
														};													


#endif /* SEVEN_SEG_CFG_H_ */