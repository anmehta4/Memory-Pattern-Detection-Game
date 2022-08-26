/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef TASK_MKII_S1_H_
#define TASK_MKII_S1_H_

#include "main.h"

extern TaskHandle_t Task_mkII_s1_Handle;
extern uint8_t lcd_color;

/******************************************************************************
 * De-bounce switch S1.
 *****************************************************************************/
bool debounce_s1(void);

/******************************************************************************
 * De-bounce switch S1.  If is has been pressed, change the color of the grid
 * in order RED->GREEN->BLUE
 *****************************************************************************/
void task_mkII_s1(void *pvParameters);

#endif /* TASK_MKII_S1_H_ */
