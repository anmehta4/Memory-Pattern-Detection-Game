/*
 * gpio.h
 *
 *      Author: Arnav Mehta
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <stdbool.h>
#include "msp.h"

/****************************************************
 * Initialize hardware resources used to control S1 on the MKII
 ****************************************************/
void ece353_MKII_S1_Init(void);

/****************************************************
 * Initialize hardware resources used to control S2 on the MKII
 ****************************************************/
void ece353_MKII_S2_Init(void);

/****************************************************
 * Initialize hardware resources used to control PS2 Joy on the MKII
 ****************************************************/
void ece353_PS2_Button_Init(void);

/******************************************************************************
 * Configure the IO pins for BOTH the X and Y directions of the analog.
 *
 * After BOTH analog signals have finished being converted, a SINGLE interrupt
 * should be generated.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void ece353_PS2_XY_Init(void);

/****************************************************
 * Initialize hardware resources used to initialize RGB LED
 ****************************************************/
void ece353_RGB_led_Init(void);

/****************************************************
 * Returns if MKII.S1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true  :  MKII.S1 is pressed
 *      false :  MKII.S1 is NOT pressed
 ****************************************************/
bool ece353_MKII_S1(void);

/****************************************************
 * Returns if MKII.S2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true  :  MKII.S2 is pressed
 *      false :  MKII.S2 is NOT pressed
 ****************************************************/
bool ece353_MKII_S2(void);

#endif /* GPIO_H_ */
