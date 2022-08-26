/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */
#include <main.h>

QueueHandle_t Queue_GRID;
TaskHandle_t Task_Move_Joystick_Grid_Handle;

/******************************************************************************
* Task used to move through the grid using joystick
******************************************************************************/
void Task_Move_Joystick_Grid(void *pvParameters)
{
    BaseType_t status;
    uint32_t grid_number = 0;
    uint32_t prev_grid_number = 0;

    while(1)
    {
        status = xQueueReceive(Queue_GRID, &grid_number, portMAX_DELAY);
        if(status != pdTRUE)
        {
            // should never make it here
            printf("\n\r *** Unknown error receiving from Queue_GRID ***\n\r");
            while(1){};
        }

        xSemaphoreTake(Sem_LCD, portMAX_DELAY);
        lcd_draw_block_outline_grid(prev_grid_number, COLORS[USR_ANS[prev_grid_number]]);
        lcd_draw_block_outline_grid(grid_number, WHITE);
        xSemaphoreGive(Sem_LCD);
        prev_grid_number = grid_number;
    }
}


