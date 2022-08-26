/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include <main.h>

QueueHandle_t Queue_LCD;

/******************************************************************************
* Controls the LCD based on if S1 or S2 was pressed
******************************************************************************/
void Task_LCD(void *pvParameters)
{
    BaseType_t status;
    LCD_MSG_t msg;

    while(1)
    {
        /*
         * Wait until we receive a message from the Queue_LED
         */
        status = xQueueReceive(Queue_LCD, &msg, portMAX_DELAY);
        if(status != pdTRUE)
        {
            // should never make it here
            printf("\n\r *** Unknown error sending to Queue_LCD ***\n\r");
            while(1){};
        }

        if(gameInProgress == 1) {

            if(msg.isS2 == 0) {
                USR_ANS[msg.lcd_location] = msg.lcd_color;
                xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                lcd_draw_block_grid(msg.lcd_location, COLORS[msg.lcd_color]);
                xSemaphoreGive(Sem_LCD);
            } else {
                gameInProgress = 0;
                xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                ece353_play_tune(lcd_display_result());
                lcd_clear_screen();
                status = xQueueSend(Queue_JOY, &msg, portMAX_DELAY);
            }
        }
    }
}


