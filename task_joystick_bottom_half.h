/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef TASK_JOYSTICK_BOTTOM_HALF_H_
#define TASK_JOYSTICK_BOTTOM_HALF_H_

#include "main.h"

#define VOLT_0P85  4220 //, 1056      // 0.85 /(3.3/4096) 16384
#define VOLT_2P50  12412      // 2.50 /(3.3/4096)

extern TaskHandle_t Task_Joystick_Bottom_Half_Handle;
extern uint32_t grid_number;
extern int gameInProgress;

typedef enum {
    JOYSTICK_DIR_CENTER,
    JOYSTICK_DIR_LEFT,
    JOYSTICK_DIR_RIGHT,
    JOYSTICK_DIR_UP,
    JOYSTICK_DIR_DOWN,
} JOYSTICK_DIR_t;


/******************************************************************************
* Examines the ADC data from the joystick on the MKII
******************************************************************************/
void Task_Joystick_Bottom_Half(void *pvParameters);

#endif /* TASK_JOYSTICK_BOTTOM_HALF_H_ */
