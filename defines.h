/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * General stdiodemo defines
 *
 * $Id: defines.h 2186 2010-09-22 10:25:15Z aboyapati $
 */

/* CPU frequency */
#define F_CPU 16000000

/* UART baud rate */
#define BAUD 9600
#define BUAD_RATE_CALC ((F_CPU/16/BUAD) - 1)

//Port where DHT sensor is connected
#define DHT_DDR      DDRC
#define DHT_PORT     PORTC
#define DHT_PIN      PINC
#define DHT_INPUTPIN DDC1

//Define sensor type
#define DHT_DHT11 0
#define DHT_DHT22 1
#define DHT_TYPE  DHT_DHT11

//timeout retries
#define DHT_TIMEOUT 200

//functions
#if DHT_TYPE == DHT_DHT22
#	define datatype uint16_t
#elif DHT_TYPE == DHT_DHT11
#	define datatype int8_t
#endif

/* Whether to read the busy flag, or fall back to
   worst-time delays. */
#define USE_BUSY_BIT 1
