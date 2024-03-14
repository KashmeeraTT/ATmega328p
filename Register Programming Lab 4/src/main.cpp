#include <Arduino.h>

volatile uint32_t timer1_micros = 0;
volatile uint8_t counter = 0;

ISR(TIMER1_COMPA_vect)
{
  timer1_micros++;
}

void setup()
{
  // Set timer mode to CTC
  TCCR1B |= (1 << WGM12);

  // Set output compare register for 1ms tick
  OCR1A = 15;

  // Enable output compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Start timer with prescaler 64
  TCCR1B |= (1 << CS10);

  // Enable global interrupts
  sei();

  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
}

void delay_us(uint16_t us)
{
  uint32_t start_time = timer1_micros;
  while ((timer1_micros - start_time) < us)
    ;
}

void delay_ms(uint16_t ms)
{
  delay_us((uint32_t)ms * 1000); // 1 millisecond is 1000 microseconds
}

void loop()
{
  if ((timer1_micros / 1000) % 20 == 0)
  {
    counter++;
  }
  if ((timer1_micros / 1000) % 100 == 0)
  {
    Serial.println(counter);
  }
}
