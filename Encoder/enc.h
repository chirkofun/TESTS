/*
 * enc.h
 *
 *  Created on: 21 ����. 2019 �.
 *      Author: cyirkofun
 */

#ifndef ENC_H_
#define ENC_H_

/*
 * @brief       Starts EXT module
 */
void lld_Encoder_Init(void);

/*
 * @brief       Return encoder ticks
 * @return      Encoder ticks
 */
uint32_t get_ticks(void);

/*
 * @brief       Counts encoder turnovers
 * @return      Number of turnovers
 */
float get_turnover(void);


#endif /* ENC_H_ */
