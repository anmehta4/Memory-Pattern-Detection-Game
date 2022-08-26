/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */
#include <main.h>


void ece353_ADC14_Acceleromter_init(void)
{
    // Configure the X direction as an analog input pin.
    P6->SEL0 |= BIT0;
    P6->SEL1 |= BIT0;

    // Configure the Y direction as an analog input pin.
    P4->SEL0 |= BIT4;
    P4->SEL1 |= BIT4;

    // Configure the X direction as an analog input pin.
    P4->SEL0 |= BIT0;
    P4->SEL1 |= BIT0;

    // Configure the Y direction as an analog input pin.
    P4->SEL0 |= BIT2;
    P4->SEL1 |= BIT2;

    // Configure the Z direction as an analog input pin.
    P6->SEL0 |= BIT1;
    P6->SEL1 |= BIT1;

    // Configure CTL0 to sample 16-times in pulsed sample mode.
    // NEW -- Indicate that this is a sequence-of-channels.
    ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02 | ADC14_CTL0_CONSEQ_1;

    // Configure ADC to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_3;

    // Associate the X direction analog signal with MEM[0]
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_15;

    // Associate the Y direction analog signal with MEM[1]
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_9;

    // Associate the X direction analog signal with MEM[0]
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_14 | ADC14_MCTLN_EOS;

    // Associate the Y direction analog signal with MEM[1]
    // NEW -- Make sure to indicate this is the end of a sequence.
//    ADC14->MCTL[3] = ADC14_MCTLN_INCH_13;
//
//
//    ADC14->MCTL[4] = ADC14_MCTLN_INCH_11 | ADC14_MCTLN_EOS;

    // Enable interrupts in the ADC AFTER a value is written into MEM[1].
    //
    // NEW: This is not the same as what is demonstrated in the example
    // coding video.
    ADC14->IER0 = ADC14_IER0_IE2;

    // Enable ADC Interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);
    NVIC_SetPriority(ADC14_IRQn, 2);

    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON; //|= so doesn't overwrite line 2 code
}


