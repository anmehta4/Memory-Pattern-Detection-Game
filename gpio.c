/*
 * gpio.c
 *
 *      Author: Arnav Mehta
 */

#include "main.h"

/****************************************************
 * Initialize hardware resources used to control S1 on the MKII
 ****************************************************/
void ece353_MKII_S1_Init(void) {

    //configure as input
    P5->DIR &= ~BIT1;
}

/****************************************************
 * Initialize hardware resources used to control S2 on the MKII
 ****************************************************/
void ece353_MKII_S2_Init(void) {

    //configure as input
    P3->DIR &= ~BIT5;
}

/****************************************************
 * Initialize hardware resources used to control PS2 Joy on the MKII
 ****************************************************/
void ece353_PS2_Button_Init(void) {

    //configure as input
    P4->DIR &= ~BIT1;
}

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
void ece353_PS2_XY_Init(void)
{
    // Configure the X direction as an analog input pin.
    P6->SEL0 |= BIT0;
    P6->SEL1 |= BIT0;

    // Configure the Y direction as an analog input pin.
    P4->SEL0 |= BIT4;
    P4->SEL1 |= BIT4;

    //Configure the Joy button as an input pin.
    P4->DIR &= ~BIT1;
}

/****************************************************
 * Initialize hardware resources used to initialize RGB LED
 ****************************************************/
void ece353_RGB_led_Init(void) {

    //Set direction as an output for red
    P2->DIR |= BIT0;

    //Turn off LED for red
    P2->OUT &= ~BIT0;

    //Set direction as an output for green
    P2->DIR |= BIT1;

    //Turn off LED for green
    P2->OUT &= ~BIT1;

    //Set direction as an output for blue
    P2->DIR |= BIT2;

    //Turn off LED for blue
    P2->OUT &= ~BIT2;
}

/****************************************************
 * Returns if MKII.S1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true  :  MKII.S1 is pressed
 *      false :  MKII.S1 is NOT pressed
 ****************************************************/
bool ece353_MKII_S1(void) {

    if((P5->IN & BIT1) == 0) {
        return true;
    } else {
        return false;
    }
}

/****************************************************
 * Returns if MKII.S2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true  :  MKII.S2 is pressed
 *      false :  MKII.S2 is NOT pressed
 ****************************************************/
bool ece353_MKII_S2(void) {

    if((P3->IN & BIT5) == 0) {
            return true;
    } else {
        return false;
    }
}



