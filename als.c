/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include "main.h"

/******************************************************************************
 * Initialize the 3001 ambient light sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/
void als_init(void)
{
    int i;

    // Reset the device using the CONFIG register
    i2c_write_16(OPT3001_SLAVE_ADDRESS, CONFIG_REG, DEFAULT_CONFIG_100);

    // delay
    for(i = 0; i < 50000; i++){};

}

/******************************************************************************
 * Returns the current light exposure in lux.
 ******************************************************************************/
float als_read_light(void)
{
    uint16_t raw;
    uint16_t result;
    uint16_t exponent;

    // Read the ambiant temperature
    raw = i2c_read_16(OPT3001_SLAVE_ADDRESS, RESULT_REG);

    result = raw&0x0FFF;
    exponent = (raw>>12)&0x000F;
        //convert raw readings to LUX
    switch(exponent){
        case 0: //*0.015625
            result = result>>6;
            break;
        case 1: //*0.03125
            result = result>>5;
            break;
        case 2: //*0.0625
            result = result>>4;
            break;
        case 3: //*0.125
            result = result>>3;
            break;
        case 4: //*0.25
            result = result>>2;
            break;
        case 5: //*0.5
            result = result>>1;
            break;
        case 6:
            result = result;
            break;
        case 7: //*2
            result = result<<1;
            break;
        case 8: //*4
            result = result<<2;
            break;
        case 9: //*8
            result = result<<3;
            break;
        case 10: //*16
            result = result<<4;
            break;
        case 11: //*32
            result = result<<5;
            break;
        }

    return result;

}

