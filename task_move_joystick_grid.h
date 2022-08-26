/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef TASK_MOVE_JOYSTICK_GRID_H_
#define TASK_MOVE_JOYSTICK_GRID_H_

#include <main.h>

extern QueueHandle_t Queue_GRID;
extern TaskHandle_t Task_Move_Joystick_Grid_Handle;

/******************************************************************************
* Task used to move through the grid using joystick
******************************************************************************/
void Task_Move_Joystick_Grid(void *pvParameters);




#endif /* TASK_MOVE_JOYSTICK_GRID_H_ */
