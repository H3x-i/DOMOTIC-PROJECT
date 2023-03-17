#ifndef __DHT_H__
#define __DHT_H__

/*
 * DHT Sensor for AVR-GCC Family
 *
 * Author      : David Feng
 * Updated     : June 26th, 2018
 * Description : DHT Sensor Library for AVR-GCC compiler
 * Usage       : Use library with AVR-GCC for Atmega family of microcontrollers (tested with Atmega 1284)
 * Edited by Hamza Fouad Martch 17th, 2023 
 */

#include <stdint.h>
#include "defines.h"

extern datatype dht_GetTempUtil(datatype *temperature, datatype *humidity);


#endif /* __DHT_H_ */