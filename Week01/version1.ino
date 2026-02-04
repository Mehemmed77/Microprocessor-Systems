#include <avr/io.h>
#include <util/delay.h>

void setup() {
  // put your setup code here, to run once:
  DDRB |= (1 << DDB5);
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB |= (1 << PORTB5); // Turn the LED On
  _delay_ms(500);
  PORTB &= ~(1 << PORTB5); // Turn the LED Off
  _delay_ms(500);
}
