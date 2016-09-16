void setup() {
  // put your setup code here, to run once:
  DDRF = 0xff;
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTF = 0xff;
  delay(1000);
  PORTF = 0x00;
}
