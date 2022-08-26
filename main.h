/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "ece353_staff.h"
#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/* ECE353 Includes */
#include <timer32_1.h>
#include <buzzer.h>

/* Task Includes */
#include <task_lcd.h>
#include <task_mkII_s1.h>
#include <task_mkII_s2.h>
#include <task_mkII_joy.h>
#include <task_joystick_timer.h>
#include <task_move_joystick_grid.h>
#include <task_joystick_bottom_half.h>

/*Light_sensor Includes*/
#include "i2c.h"
#include "als.h"
#include "accelerometer.h"
#include "adc.h"
#include "gpio.h"
#include "circular_buffer.h"

/* Semaphore for LCD */
extern SemaphoreHandle_t Sem_LCD;

/*Other relevent Includes */
#include <lcd.h>
#include <image.h>

#endif /* MAIN_H_ */
