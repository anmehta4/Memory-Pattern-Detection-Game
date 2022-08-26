/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include "main.h"

/****************************************************
 * Sets the PWM period of the buzzer. The duty cycle
 * will be set to 50%
 *
 * Parameters
 *      ticks_period: Period of the PWM pulse
 *
 * Returns
 *      None
 ****************************************************/
void ece353_MKII_Buzzer_Init(uint16_t ticks_period) {

    //Set P2.7 to be a GPIO Output Pin
    P2->DIR |= BIT7;

    //The TIMERA PWM controller will control the buzzer on the MKII
    //P2.7 <--> TA0.4
    P2->SEL0 |= BIT7;
    P2->SEL1 &= ~BIT7;

    //Turn Off TA0
    TIMER_A0->CTL = 0;

    //Set the period of the timer (always in CCR[0])
    TIMER_A0->CCR[0] = ticks_period - 1;

    //Configure BUZZER Duty Cycle to 50%
    TIMER_A0->CCR[4] = (ticks_period/2) - 1;

    //Configure TA0.4 for RESET/SET Mode
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;

    //Select the master clock as the timer source
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK;
}

/****************************************************
 * Turns the Buzzer on
 *
 * Parameters
 *      None
 * Returns
 *      None
 ****************************************************/
void ece353_MKII_Buzzer_On(void) {

    // Turn the first TimerA peripheral.  Use SMCLK as the clock source
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK; //Use SMCLK as clock source

    //Clear the current Mode Control Bits
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;

    // Set the Control to UP and Clear the current count
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP| TIMER_A_CTL_CLR;
}

/****************************************************
 * Turns the Buzzer off
 *
 * Parameters
 *      None
 * Returns
 *      None
 ****************************************************/
void ece353_MKII_Buzzer_Off(void) {

    //Turn off the Timer
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;
}

/****************************************************
 * Check Buzzer run status
 *
 * Parameters
 *      None
 * Returns
 *      True if TimerA0 is On
 *      False if TimerA0 is Off
 ****************************************************/
bool ece353_MKII_Buzzer_Run_Status(void) {

    if((TIMER_A0->CTL & TIMER_A_CTL_MC_MASK) == TIMER_A_CTL_MC__STOP) {
        return false;
    } else {
        return true;
    }
}

/****************************************************
 * Play tune if true else constant noise if false
 ****************************************************/
void ece353_play_tune(bool result) {
    if(!result) {
        ece353_MKII_Buzzer_On();
        ece353_T32_1_wait_1S();
        ece353_MKII_Buzzer_Off();
        return;
    }

    int i=0;
    for(i=0;i<12;i++) {
        ece353_MKII_Buzzer_On();
        ece353_T32_1_wait_10ms();
        ece353_T32_1_wait_10ms();
        ece353_T32_1_wait_10ms();
        ece353_MKII_Buzzer_Off();
        ece353_T32_1_wait_10ms();
        ece353_T32_1_wait_10ms();
        ece353_T32_1_wait_10ms();
    }
}
