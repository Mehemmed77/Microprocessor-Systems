#include <avr/io.h>
#include <avr/interrupt.h>

#define EEPROM_ADDR 0x00

volatile uint8_t counter = 0;

uint8_t eeprom_read_byte_avr(uint16_t addr) {
  while (EECR & (1 << EEPE));
  EEAR = addr;
  EECR |= (1 << EERE);
  return EEDR;
}

void eeprom_write_byte_avr(uint16_t addr, uint8_t data) {
  while (EECR & (1 << EEPE));
  EEAR = addr;
  EEDR = data;
  EECR |= (1 << EEMPE);
  EECR |= (1 << EEPE);
}

ISR(TIMER1_OVF_vect) {
  Serial.print("Counter: ");
  Serial.println(counter);

  TCNT1 = 49991;
  counter++;
}

void setup() {
  Serial.begin(9600);

  counter = eeprom_read_byte_avr(EEPROM_ADDR);

  TCCR1A = 0x00;
  TCCR1B = (1 << CS12) | (1 << CS10);
  TCNT1 = 49991;

  TIMSK1 = (1 << TOIE1);

  sei();
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 's') {
      eeprom_write_byte_avr(EEPROM_ADDR, counter);
    }

    if (cmd == 'r') {
      counter = 0;
      eeprom_write_byte_avr(EEPROM_ADDR, 0);
    }
  }
}
