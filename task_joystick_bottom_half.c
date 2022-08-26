/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include <main.h>

 TaskHandle_t Task_Joystick_Bottom_Half_Handle;

 volatile uint32_t JOYSTICK_X_DIR = 0;
 volatile uint32_t JOYSTICK_Y_DIR = 0;
 volatile uint32_t resultsBuffer[3];
 int gameInProgress = 0;


 uint32_t grid_number = 0;
 uint32_t prev_grid_number = 0;


/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the joystick on the MKII
* Also checks status of accelerometer
******************************************************************************/
void Task_Joystick_Bottom_Half(void *pvParameters)
{
    JOYSTICK_DIR_t dir;
    JOYSTICK_DIR_t prev_dir = JOYSTICK_DIR_CENTER;

    BaseType_t status;

    while(1)
    {
        /* ADD CODE
         * Wait until we get a task notification from the ADC14 ISR
         */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        /*
         * Set the dir variable to one of the following values based
         * on the values of JOYSTICK_X_DIR and JOYSTIC_Y_DIR
         */
        if (JOYSTICK_X_DIR < VOLT_0P85)
        {
            dir = JOYSTICK_DIR_LEFT;
            if(dir != prev_dir) {
                if (grid_number == 0 || grid_number == 3 || grid_number == 6)
                {
                    grid_number += 2;
                }
                else
                {
                    grid_number--;
                }
            }
        }
        else if (JOYSTICK_X_DIR > VOLT_2P50)
        {
            dir = JOYSTICK_DIR_RIGHT;
            if(dir != prev_dir) {
                if (grid_number == 2 || grid_number == 5 || grid_number == 8)
                {
                    grid_number -= 2;
                }
                else
                {
                    grid_number++;
                }
            }
        }
        else if (JOYSTICK_Y_DIR < VOLT_0P85)
        {
            dir = JOYSTICK_DIR_DOWN;
            if(dir != prev_dir) {
                if (grid_number == 6 || grid_number == 7 || grid_number == 8)
                {
                    grid_number -= 6;
                }
                else
                {
                    grid_number += 3;
                }
            }
        }
        else if (JOYSTICK_Y_DIR > VOLT_2P50)
        {
            dir = JOYSTICK_DIR_UP;
            if(dir != prev_dir) {
                if (grid_number == 0 || grid_number == 1 || grid_number == 2)
                {
                    grid_number += 6;
                }
                else
                {
                    grid_number -= 3;
                }
            }
        }
        else
        {
            dir = JOYSTICK_DIR_CENTER;
        }


        char s[256];
        sprintf(s, "x %d\r\n", resultsBuffer[0]);
        printf(s);
        sprintf(s, "y %d\r\n", resultsBuffer[1]);
        printf(s);
        sprintf(s, "z %d\r\n", resultsBuffer[2]);
        printf(s);
        sprintf(s, "x_dir %d\r\n", JOYSTICK_X_DIR);
        printf(s);
        sprintf(s, "y_dir %d\r\n", JOYSTICK_Y_DIR);
        printf(s);

        /*
         * Draw accelerometer data on display and determine if orientation
         * change thresholds are reached and redraw as necessary
         */
        if(resultsBuffer[0] > 11300) {
            if(gameInProgress) {
                xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                lcd_clear_grid();
                xSemaphoreGive(Sem_LCD);
                uint32_t i = 0;
                for(i=0; i<9; i++) {
                    USR_ANS[i] = 0;
                }
            }
        } else if(resultsBuffer[0] < 5000) {
            if(gameInProgress) {
                startup_game();
            }
        }
        /* ADD CODE
         * Send dir to Queue_Console if the the current direction
         * of the joystick does not match the previous direction of the joystick
         */

        if((dir!=prev_dir) && (grid_number!=prev_grid_number)) {
            status = xQueueSend(Queue_GRID, &grid_number, portMAX_DELAY);
            if(status != pdTRUE)
            {
                // should never make it here
                printf("\n\r *** Unknown error sending to Queue_GRID ***\n\r");
                while(1){};
            }
        }

        /* ADD CODE
         * Update the prev_dir of the joystick
         */
        prev_dir = dir;
        prev_grid_number = grid_number;
    }
}


/******************************************************************************
* Top Half of ADC14 Handler.
******************************************************************************/
void ADC14_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    JOYSTICK_X_DIR = ADC14->MEM[0]; // Read the value and clear the interrupt
    JOYSTICK_Y_DIR = ADC14->MEM[1]; // Read the value and clear the interrupt

    resultsBuffer[0] = ADC14->MEM[2];
//    resultsBuffer[1] = ADC14->MEM[3];
//    resultsBuffer[2] = ADC14->MEM[4];

    /* ADD CODE
     * Send a task notification to Task_Joystick_Bottom_Half
     */
    vTaskNotifyGiveFromISR(
                    Task_Joystick_Bottom_Half_Handle,
                    &xHigherPriorityTaskWoken
            );
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}



