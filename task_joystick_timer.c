/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include "main.h"

TaskHandle_t Task_Joystick_Timer_Handle;

/******************************************************************************
 * Used to start an ADC14 Conversion
 ******************************************************************************/
void Task_Joystick_Timer(void *pvParameters)
{
    while (1)
    {
        /*
         * Start the ADC conversion
         */
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

        /*
         * Delay 50mS
         */
        vTaskDelay(pdMS_TO_TICKS(50));

    }
}

