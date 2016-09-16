#include <avr/interrupt.h>
#include <string.h>
#define AXIS_X 1
#define AXIS_Y 2
#define AXIS_Z 3

volatile unsigned char cube[8][8];
volatile int current_layer = 0;

void setup() {
  
      // pinMode(A0, OUTPUT) as specified in the arduino reference didn't work. So I accessed the registers directly.
  //DDRC = 0xff;
  //PORTC = 0x00;

  // Reset any PWM configuration that the arduino may have set up automagically!
  TCCR2A = 0x00;
  TCCR2B = 0x00;

  TCCR2A |= (0x01 << WGM21); // CTC mode. clear counter on TCNT2 == OCR2A
  OCR2A = 10; // Interrupt every 25600th cpu cycle (256*100)
  TCNT2 = 0x00; // start counting at 0
  TCCR2B |= (0x01 << CS22) | (0x01 << CS21); // Start the clock with a 256 prescaler

  TIMSK2 |= (0x01 << OCIE2A);
    DDRA = 0xff;
    DDRF = 0xff;
    DDRK = 0xff;
}

ISR (TIMER2_COMPA_vect)
{
  int i;

  // all layer selects off
  PORTK = 0x00;
  PORTF &= 0x0f;

  PORTB |= 0x08; // output enable off.

  for (i=0; i<8; i++)
  {
    PORTA = cube[current_layer][i];
    PORTF = (PORTB & 0xF8) | (0x07 & (i+1));
  }

  PORTF &= 0b00110111; // Output enable on.

  if (current_layer < 6)
  {
    PORTK = (0x01 << current_layer);
  } 
  else if (current_layer == 6)
  {
    digitalWrite(12, HIGH);
  } 
  else
  {
    digitalWrite(13, HIGH);
  }

  current_layer++;

  if (current_layer == 8)
    current_layer = 0;
}

void loop() {
   PORTA = 0xff;
   //delay(10000);
   //PORTA = 0x00;
   PORTF = 0xff;
   //PORTC &= 0x0f;
   //PORTC |= 0x08;
   //delay(10000);
   //PORTC = 0x00;
   PORTK = 0xff;
   
   
   
  // put your main code here, to run repeatedly:
//  PORTA = B11111111;
//  delay(500);
//  PORTA = B00000000;
//  delay(500);

}
