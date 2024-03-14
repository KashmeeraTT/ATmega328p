#include <Arduino.h>

volatile uint32_t timer1_millis = 0;
volatile uint32_t timer2_micros = 0;
volatile uint8_t counter = 0;

ISR(TIMER1_COMPA_vect)
{
  timer1_millis++;
}

ISR(TIMER2_COMPA_vect)
{
  timer2_micros++;
}

void setup()
{
  // Set up Timer1
  TCCR1B |= (1 << WGM12);              // CTC mode
  OCR1A = 249;                         // Compare value for 1 ms interrupt
  TIMSK1 |= (1 << OCIE1A);             // Enable compare match interrupt
  TCCR1B |= (1 << CS10) | (1 << CS11); // Start timer with prescaler 64

  // Set up Timer2
  TCCR2A = 0;             // Normal mode
  TCCR2B = (1 << CS21);   // Prescaler = 8
  OCR2A = 1;              // Compare value for 1 us interrupt
  TIMSK2 = (1 << OCIE2A); // Enable compare match interrupt

  // Enable global interrupts
  sei();

  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
}

void delay_ms(uint16_t ms)
{
  uint32_t start_time = timer1_millis;
  while ((timer1_millis - start_time) < ms)
    ;
}

void delay_us(uint16_t us)
{
  uint32_t start_time = timer2_micros;
  while ((timer2_micros - start_time) < (us / 2)) // divide by 2 because each tick is 2us
    ;
}

void loop()
{
  counter++;
  delay_ms(5000);
  Serial.println("Delayed 5s");
  delay_us(5000);
  Serial.println(counter);
}
