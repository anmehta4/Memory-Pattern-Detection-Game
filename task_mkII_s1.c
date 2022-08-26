/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include "task_mkII_s1.h"

TaskHandle_t Task_mkII_s1_Handle = NULL;
uint8_t lcd_color;

/******************************************************************************
 * De-bounce switch S1.
 *****************************************************************************/
bool debounce_s1(void)
{
    static uint8_t debounce_state = 0x00;

    // Shift the de-bounce variable to the left
    debounce_state = debounce_state << 1;

    // If S1 is being pressed, set the LSBit of debounce_state to a 1;
    if(ece353_MKII_S1())
    {
        debounce_state |= 0x01;
    }

    // If the de-bounce variable is equal to 0x7F, change the color of the tri-color LED.
    if(debounce_state == 0x7F)
    {
        return true;
    }
    else
    {
        return false;
    }

}

/******************************************************************************
 * De-bounce switch S1.  If is has been pressed, change the color of the grid
 * in order RED->GREEN->BLUE
 *****************************************************************************/
void task_mkII_s1(void *pvParameters)
{
    BaseType_t status;
    LCD_MSG_t msg;
    lcd_color = 0;

    while(1)
    {

        if(debounce_s1())
        {
            lcd_color = (lcd_color + 1) % 3;

            msg.lcd_location = grid_number;
            msg.lcd_color = lcd_color + 1;
            msg.isS2 = 0;

            status = xQueueSend(Queue_LCD, &msg, portMAX_DELAY);
            if(status != pdTRUE)
            {
                // should never make it here
                printf("\n\r *** Unknown error sending to Queue_LCD ***\n\r");
                while(1){};
            }
        }

        // Delay for 10mS using vTaskDelay
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
