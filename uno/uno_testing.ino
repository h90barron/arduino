void setup() {
  // put your setup code here, to run once:

  
  DDRD = 0xff;
  DDRB = 0xff;
  DDRC = 0xff;

  TCCR2A = 0x00;
  TCCR2B = 0x00;

  TCCR2A |= (0x01 << WGM21); // CTC mode. clear counter on TCNT2 == OCR2A
  OCR2A = 10; // Interrupt every 25600th cpu cycle (256*100)
  TCNT2 = 0x00; // start counting at 0
  TCCR2B |= (0x01 << CS22) | (0x01 << CS21); // Start the clock with a 256 prescaler

  TIMSK2 |= (0x01 << OCIE2A);
}
//ISR(TIMER2_COMPA_vect)
//{
//  PORTC = 0xff;
//  PORTC = 0x00;
//}
void loop() {
  // put your main code here, to run repeatedly:
  PORTD = 0xff;
  PORTB = 0x0f;
  PORTC = 0x0f;
  
}
