/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include "main.h"

/*****************************************************
 * Busy waits for 100mS and then returns.
 *
 * Timer32_1 MUST be configured as a 16-bit timer.
 * Assume that the MCU clock runs at 3MHz.  You will
 * need to use a pre-scalar in order to achieve a delay
 * of 100mS.
 *
 * Parameters:
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_T32_1_wait_10ms(void) {
    //Stop the timer
    TIMER32_1->CONTROL = 0;

    //Set the timer to be a 16-bit, not one-shot with prescale of 16
    TIMER32_1->CONTROL = TIMER32_CONTROL_PRESCALE_1;

    //Set the load register
    TIMER32_1->LOAD = 18750;

    //Start the timer
    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE;

    //Wait until timer reaches 0
    while(TIMER32_1->VALUE != 0) {
        //timer is still counting so wait
    }
}

/*****************************************************
 * Busy waits for 3S and then returns.
 * Parameters:
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_T32_1_wait_3S(void) {
    int i = 0;
    for(i=0;i<400;i++) {
        ece353_T32_1_wait_10ms();
    }
}

/*****************************************************
 * Busy waits for 1S and then returns.
 * Parameters:
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_T32_1_wait_1S(void) {
    int i = 0;
    for(i=0;i<75;i++) {
        ece353_T32_1_wait_10ms();
    }
}
