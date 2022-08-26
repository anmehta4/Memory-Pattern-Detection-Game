/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#ifndef ALS_H_
#define ALS_H_

#include "main.h"

#define OPT3001_SLAVE_ADDRESS 0x44

#define OPT_INTERRUPT_PIN   11
#define RESULT_REG          0x00
#define CONFIG_REG          0x01
#define LOWLIMIT_REG        0x02
#define HIGHLIMIT_REG       0x03
#define MANUFACTUREID_REG   0x7E
#define DEVICEID_REG        0x7F

#define LUX_MIN             200
#define LUX_MAX             3000

/* CONFIGURATION REGISTER SETTINGS */

#define DEFAULT_CONFIG 0xCC10 // 800ms
#define DEFAULT_CONFIG_100 0xC410 // 100ms


/******************************************************************************
 * Initialize the 3001 ambient light sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/
void als_init(void);

/******************************************************************************
 * Returns the current light exposure in lux.
 ******************************************************************************/
float als_read_light(void);

#endif /* ALS_H_ */
