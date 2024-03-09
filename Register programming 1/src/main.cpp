#include <Arduino.h>

void setup()
{
  DDRB = 0;
  DDRB |= (1 << 5);
}

void loop()
{
  PORTB |= (1 << 5);
  delay(1000);
  PORTB &= ~(1 << 5);
  delay(1000);
}