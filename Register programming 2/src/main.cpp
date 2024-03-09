#include <Arduino.h>

void setup()
{
  // Setup timer 1 for toggling led 13 every 1 second
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15624;                       // Channel 1 compare value
  TCCR1B |= (1 << WGM12);              // CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set pre scaler
  TIMSK1 |= (1 << OCIE1A);             // match A interrupt enable
  sei();                               // enable global interrupt

  // Set pin 13 as output
  DDRB |= (1 << DDB5);
}

ISR(TIMER1_COMPA_vect)
{
  // toggle led 13
  PORTB ^= (1 << PORTB5);
}

void loop()
{
}