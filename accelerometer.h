/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "main.h"

#define OPT3001_SLAVE_ADDRESS 0x44

#define OPT_INTERRUPT_PIN   11
#define RESULT_REG          0x00
#define CONFIG_REG          0x01
#define LOWLIMIT_REG        0x02
#define HIGHLIMIT_REG       0x03
#define MANUFACTUREID_REG   0x7E
#define DEVICEID_REG        0x7F


/* CONFIGURATION REGISTER SETTINGS */

#define DEFAULT_CONFIG 0xCC10 // 800ms
#define DEFAULT_CONFIG_100 0xC410 // 100ms

/******************************************************************************
 * Initialize the tmp006 temperature sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/
void ece353_ADC14_Acceleromter_init(void);


#endif /* ACCELEROMETER_H_ */
