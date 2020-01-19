/**************************************************************
   USBspazo is a library for the Arduino platform
   inspired by:
   http://
   Built by Polupraneeth https://github.com/polupraneeth
   Licensed under MIT license
 **************************************************************/

#include "Arduino.h"
#include "USDspazo.h"

USDspazo::USDspazo(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void USDspazo::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void USDspazo::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}