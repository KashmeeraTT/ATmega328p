#include <Arduino.h>

volatile uint32_t counter = 0;

ISR(TIMER1_COMPA_vect)
{
  Serial.println(counter);
}

ISR(TIMER2_COMPA_vect)
{
  counter++;
}

void setup()
{
  // Set up Timer1
  TCCR1B |= (1 << WGM12);              // CTC mode
  OCR1A = 24900;                       // Compare value for 100 ms interrupt
  TIMSK1 |= (1 << OCIE1A);             // Enable compare match interrupt
  TCCR1B |= (1 << CS10) | (1 << CS11); // Start timer with prescaler 64

  // Set up Timer2
  TCCR2A |= (1 << WGM21);  // CTC mode
  TCCR2B |= (1 << CS22);   // Prescaler = 64
  OCR2A = 249;             // Compare value for 20 ms interrupt
  TIMSK2 |= (1 << OCIE2A); // Enable compare match interrupt

  // Enable global interrupts
  sei();

  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
}

void loop()
{
}
