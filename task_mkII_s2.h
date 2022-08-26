/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef TASK_MKII_S2_H_
#define TASK_MKII_S2_H_
#include "main.h"

extern TaskHandle_t Task_mkII_s2_Handle;

/******************************************************************************
 * De-bounce switch S2.
 *****************************************************************************/
bool debounce_s2(void);


/******************************************************************************
 * De-bounce switch S2.  If s2 has has been pressed, complete the game and
 * execute neccessary functions.
 *****************************************************************************/
void task_mkII_s2(void *pvParameters);

#endif /* TASK_MKII_S2_H_ */
