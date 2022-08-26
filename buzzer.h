/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef BUZZER_H_
#define BUZZER_H_

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
void ece353_MKII_Buzzer_Init(uint16_t ticks_period);

/****************************************************
 * Turns the Buzzer on
 *
 * Parameters
 *      None
 * Returns
 *      None
 ****************************************************/
void ece353_MKII_Buzzer_On(void);

/****************************************************
 * Turns the Buzzer off
 *
 * Parameters
 *      None
 * Returns
 *      None
 ****************************************************/
void ece353_MKII_Buzzer_Off(void);

/****************************************************
 * Check Buzzer run status
 *
 * Parameters
 *      None
 * Returns
 *      True if TimerA0 is On
 *      False if TimerA0 is Off
 ****************************************************/
bool ece353_MKII_Buzzer_Run_Status(void);

/****************************************************
 * Play tune if true else constant noise if false
 ****************************************************/
void ece353_play_tune(bool result);

#endif /* BUZZER_H_ */
