/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */
#include "main.h"

/*
 *  ======== main ========
 */
 SemaphoreHandle_t Sem_LCD;
 SemaphoreHandle_t Sem_Task;

#define PWM_FREQ    200

int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    uint16_t pwm_count = (uint16_t)(SystemCoreClock/PWM_FREQ) - 1; //PWM_FREQ Hz, resonant:2K Hz

    ece353_staff_init(true);
    ece353_ADC14_Acceleromter_init();
    ece353_MKII_S1_Init();
    ece353_MKII_S2_Init();
    ece353_PS2_XY_Init();
    ece353_MKII_Buzzer_Init(pwm_count);
    i2c_init();
    als_init();

    __enable_irq();

    Crystalfontz128x128_Init();

    Queue_GRID = xQueueCreate(10,sizeof(uint32_t));
    Queue_JOY = xQueueCreate(2, sizeof(uint32_t));
    Queue_LCD = xQueueCreate(2,sizeof(LCD_MSG_t));

    Sem_LCD = xSemaphoreCreateBinary();

    xTaskCreate
    (   task_mkII_s1,
        "task_mkII_s1",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
    (   task_mkII_s2,
        "task_mkII_s2",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
    (   task_mkII_joy,
        "task_mkII_joy",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
    (   Task_LCD,
        "Task_LCD",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    xTaskCreate
    (   Task_Move_Joystick_Grid,
        "Task_Move_Joystick_Grid",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_Move_Joystick_Grid_Handle
    );

    xTaskCreate
    (   Task_Joystick_Timer,
        "Task_Joystick_Timer",
        configMINIMAL_STACK_SIZE,
        NULL,
        2,
        &Task_Joystick_Timer_Handle
    );

    xTaskCreate
    (   Task_Joystick_Bottom_Half,
        "Task_Joystick",
        configMINIMAL_STACK_SIZE,
        NULL,
        3,
        &Task_Joystick_Bottom_Half_Handle
    );

    xSemaphoreGive(Sem_LCD);

    while(!debounce_joy()) {};

    startup_game();

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    while(1){};
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
