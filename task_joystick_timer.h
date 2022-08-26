/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef TASK_JOYSTICK_TIMER_H_
#define TASK_JOYSTICK_TIMER_H_

#include "main.h"

extern TaskHandle_t Task_Joystick_Timer_Handle;

/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Joystick_Timer(void *pvParameters);

#endif /* TASK_JOYSTICK_TIMER_H_ */
