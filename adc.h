/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef ADC_H_
#define ADC_H_

#include "main.h"

// Declare any functions found in adc.c that will be used in other files here

/******************************************************************************
 * The X direction should be configured to place the results in MEM[0].
 * The Y direction should be configured to place the results in MEM[1].
 *
 * After BOTH analog signals have finished being converted, a SINGLE interrupt
 * should be generated.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void ece353_ADC14_Init(void);

#endif /* ADC_H_ */
