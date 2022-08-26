/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include "task_mkII_s2.h"

TaskHandle_t Task_mkII_s2_Handle = NULL;

/******************************************************************************
 * De-bounce switch S2.
 *****************************************************************************/
bool debounce_s2(void)
{
    static uint8_t debounce_state = 0x00;

    // Shift the de-bounce variable to the left
    debounce_state = debounce_state << 1;

    // If S1 is being pressed, set the LSBit of debounce_state to a 1;
    if(ece353_MKII_S2())
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
 * De-bounce switch S2.  If s2 has has been pressed, complete the game and
 * execute neccessary functions.
 *****************************************************************************/
void task_mkII_s2(void *pvParameters)
{
    BaseType_t status;
    LCD_MSG_t msg;


    while(1)
    {
        if(debounce_s2())
        {
            msg.lcd_location = 10;
            msg.lcd_color = 10;
            msg.isS2 = 1;

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
