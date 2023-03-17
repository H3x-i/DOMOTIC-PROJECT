/*#include <Wire.h>
#include <LiquidCrystal_I2C.h>*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include "DHT.h"
#include "uart.h"
#include "liquid_crystal_i2c.h"

#define salon     DDD2
#define ccp       DDD3
#define cca       DDD4
#define hall      DDD5
#define wc        DDD6
#define cuisine   DDD7
#define cdc       DDB0
#define buzzer    DDB4
#define inputPin  DDC1

int main(void){

	uart_init();

  FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL,         _FDEV_SETUP_WRITE);
	FILE uart_input  = FDEV_SETUP_STREAM(NULL,         uart_getchar, _FDEV_SETUP_READ);
	FILE uart_io     = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

	stdout = &uart_output;
	stdin  = &uart_input;

  LiquidCrystalDevice_t ScreenDevice = lq_init(0x27, 16, 2, LCD_5x8DOTS);
  lq_turnOnBacklight(&ScreenDevice);

  int d_outputs[] = { salon, ccp, cca, hall, wc, cuisine };
	for(unsigned char i = 0; i != sizeof(d_outputs)/sizeof(int); i++)
    DDRD |= (1 << d_outputs[i]);

  int b_outputs[] = { cdc, buzzer };
	for(unsigned char i = 0; i != (sizeof(b_outputs)/sizeof(b_outputs[0])); i++)
    DDRB |= (1 << b_outputs[i]);

  DDRC &= ~(1 << inputPin);

  while(true) {
    int8_t temperature = 0;
    int8_t humidity = 0;
    int8_t dbgDHT = dht_GetTempUtil(&temperature, &humidity);

    if(dbgDHT != 0){
      lq_clear(&ScreenDevice);
      lq_setCursor(&ScreenDevice, 0, 0);
      lq_print(&ScreenDevice, "HUMID: ");
      lq_printInt(&ScreenDevice, humidity);
      
      lq_print(&ScreenDevice, " %");
      lq_setCursor(&ScreenDevice, 0, 1);
      lq_print(&ScreenDevice, "TEMP: ");
      lq_printInt(&ScreenDevice, temperature);
      lq_print(&ScreenDevice, " C");
    }else{
      printf("DHT failed with return : %d\n", dbgDHT);
    }

    _delay_ms(1000);

    char state = 0;

    state = getchar();

    if (state == '1') {
      PORTD |= (1 << salon);
    }
    else if (state == '2') {
      PORTD &= ~(1 << salon);
    }
    else if (state == '3') {
      PORTD |= (1 << ccp);
    }
    else if (state == '4') {
      PORTD &= ~(1 << ccp);
    }
    else if (state == '5') {
      PORTD |= (1 << cca);
    }
    else if (state == '6') {
      PORTD &= ~(1 << cca);
    }
    else if (state == '7') {
      PORTD |= (1 << hall);
    }
    else if (state == '8') {
      PORTD &= ~(1 << hall);
    }
    else if (state == '9') {
      PORTD |= (1 << wc);
    }
    else if (state == 'A') {
      PORTD &= ~(1 << wc);
    }
    else if (state == 'B') {
      PORTD |= (1 << cuisine);
    }
    else if (state == 'C') {
      PORTD &= ~(1 << cuisine);
    }
      //PORT B
    else if (state == 'D') {
      PORTB |= (1 << cdc);
    }
    else if (state == 'E') {
      PORTB &= ~(1 << cdc);
    }
    else if (state == 'F') {
      PORTD |= (1 << salon)
            |  (1 << ccp)
            |  (1 << cca)
            |  (1 << hall)
            |  (1 << wc)
            |  (1 << cuisine);
      PORTB |= (1 << cdc);
    }
    else if (state == 'G') {
      PORTD &= ~((1 << salon)
            |    (1 << ccp)
            |    (1 << cca)
            |    (1 << hall)
            |    (1 << wc)
            |    (1 << cuisine));
      PORTB &= ~(1 << cdc);
    }
    bool val = ((PINC & (1 << inputPin)) >> inputPin);
    static bool pirState = false;
    if (val == true) {
      PORTB |= (1 << buzzer);
      if (pirState == false) {
        pirState = true;
      }
    } /*else {
      digitalWrite(buzzer, LOW); if ended motion buzzer will go off :) please don't uncomment that just if needed !!
      if (pirState == HIGH) {
        pirState == LOW;
      }}*/
  }
}
