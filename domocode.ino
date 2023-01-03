#include <Wire.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#define DHTPIN A1
#define DHTTYPE DHT11

#define salon 2
#define ccp 3
#define cca 4
#define hall 5
#define wc 6
#define cuisine 7
#define cdc 8
#define state 0
#define buzzer 12
#define inputPin 11
#define pirState LOW
#define val 0

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();

  
	int t_Outputs[] = { salon, ccp, cca, hall, wc, cuisine, cdc, buzzer };
	for(unsigned char i = 0; i != sizeof(t_outputs)/sizeof(int); i++)
		pinMode(t_Outputs[i], OUTPUT);


 pinMode(inputPin, INPUT);
  

}

void loop() 
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HUMID: ");
  lcd.print((float)dht.readHumidity());
  lcd.print(" %");
  lcd.setCursor (0, 1);
  lcd.print("TEMP: ");
  lcd.print((float)dht.readTemperature());
  lcd.print(" C");
  delay(1000);


  if(Serial.available() > 0) {
    state = Serial.read();
  }
  if (state == '1') {
    digitalWrite(salon, HIGH);
  }
  else if (state == '2') {
    digitalWrite(salon, LOW);
  }
  else if (state == '3') {
    digitalWrite(ccp, HIGH);
  }
  else if (state == '4') {
    digitalWrite(ccp, LOW);
  }
  else if (state == '5') {
    digitalWrite(cca, HIGH);
  }
  else if (state == '6') {
    digitalWrite(cca, LOW);
  }
  else if (state == '7') {
    digitalWrite(hall, HIGH);
    }
  else if (state == '8') {
    digitalWrite(hall, LOW);
    }
  else if (state == '9') {
    digitalWrite(wc, HIGH);
    }
  else if (state == 'A') {
    digitalWrite(wc, LOW);
    }
  else if (state == 'B') {
    digitalWrite(cuisine, HIGH);
    }
  else if (state == 'C') {
    digitalWrite(cuisine, LOW);
    }
  else if (state == 'D') {
    digitalWrite(cdc, HIGH);
    }
  else if (state == 'E') {
    digitalWrite(cdc, LOW);
    }
  else if (state == 'F') {
    digitalWrite(salon, HIGH);
    digitalWrite(ccp, HIGH);
    digitalWrite(cca, HIGH);
    digitalWrite(hall, HIGH);
    digitalWrite(wc, HIGH);
    digitalWrite(cuisine, HIGH);
    digitalWrite(cdc, HIGH);
  }
  else if (state == 'G') {
    digitalWrite(salon, LOW);
    digitalWrite(ccp, LOW);
    digitalWrite(cca, LOW);
    digitalWrite(hall, LOW);
    digitalWrite(wc, LOW);
    digitalWrite(cuisine, LOW);
    digitalWrite(cdc, LOW);
  }
  val = digitalRead(inputPin);
  if (val == HIGH) {
    digitalWrite(buzzer, HIGH);
    if (pirState == LOW) {
      pirState = HIGH;
    }
  } /*else {
    digitalWrite(buzzer, LOW); if ended motion buzzer will go off :) please don't uncomment that just if needed !!
    if (pirState == HIGH) {
      pirState == LOW;
    }}*/
  }
