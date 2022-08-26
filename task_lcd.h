/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef TASK_LCD_H_
#define TASK_LCD_H_

typedef enum {MSP432, MKIIEDU} LED_LOCATION;

typedef struct {
    uint32_t lcd_location;
    uint32_t lcd_color;
    uint32_t isS2; // 1 if S2 is pressed else 0
}LCD_MSG_t;

extern QueueHandle_t Queue_LCD;

/******************************************************************************
* Controls the LCD based on if S1 or S2 was pressed
******************************************************************************/
void Task_LCD(void *pvParameters);

#endif /* TASK_LCD_H_ */
