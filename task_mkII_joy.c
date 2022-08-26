/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include "main.h"

QueueHandle_t Queue_JOY;
TaskHandle_t Task_mkII_joy_Handle = NULL;

/******************************************************************************
 * De-bounce switch joy.
 *****************************************************************************/
bool debounce_joy(void)
{
    static uint8_t debounce_state = 0x00;

    // Shift the de-bounce variable to the left
    debounce_state = debounce_state << 1;

    // If S1 is being pressed, set the LSBit of debounce_state to a 1;
    if ((P4->IN & BIT1 ) == 0)
    {
        debounce_state |= 0x01;
    }

    // If the de-bounce variable is equal to 0x7F, change the color of the tri-color LED.
    if (debounce_state == 0x7F)
    {
        return true;
    }
    else
    {
        return false;
    }

}

/******************************************************************************
 * Execute all routines to start up a new game
 *****************************************************************************/
void startup_game()
{
    xSemaphoreTake(Sem_LCD, portMAX_DELAY);
    lcd_clear_screen();
    lcd_generate_startup_images();
    lcd_generate_grid();
    ece353_T32_1_wait_3S();
    lcd_clear_grid();
    xSemaphoreGive(Sem_LCD);
    gameInProgress = 1;
}

/******************************************************************************
 * De-bounce switch Joy. If joy has been pressed startup a new game!
 *****************************************************************************/
void task_mkII_joy(void *pvParameters)
{
    BaseType_t status;
    LCD_MSG_t msg;


    while (1)
    {
        status = xQueueReceive(Queue_JOY, &msg, portMAX_DELAY);
        if(status != pdTRUE)
        {
            // should never make it here
            printf("\n\r *** Unknown error sending to Queue_Task2 ***\n\r");
            while(1){};
        }

        while(1)
        {
            if(debounce_joy()) {
                xSemaphoreGive(Sem_LCD);
                startup_game();
                break;
            }
        }

        // Delay for 10mS using vTaskDelay
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
