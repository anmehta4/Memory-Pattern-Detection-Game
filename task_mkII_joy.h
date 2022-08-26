/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef TASK_MKII_JOY_H_
#define TASK_MKII_JOY_H_

#include "main.h"

extern TaskHandle_t Task_mkII_joy_Handle;
extern QueueHandle_t Queue_JOY;

/****************************************************
 * Initialize hardware resources used to control PS2 Joy on the MKII
 ****************************************************/
void ece353_PS2_Button_Init(void);

/******************************************************************************
 * De-bounce switch joy.
 *****************************************************************************/
bool debounce_joy(void);

/******************************************************************************
 * Execute all routines to start up a new game
 *****************************************************************************/
void startup_game();

/******************************************************************************
 * De-bounce switch Joy. If joy has been pressed startup a new game!
 *****************************************************************************/
void task_mkII_joy(void *pvParameters);


#endif /* TASK_MKII_JOY_H_ */
