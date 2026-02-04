uint8_t a, b;
uint8_t result;
uint8_t sreg;
int newData = 0;

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Enter two numbers separated by a space or comma (e.g., 10 20): ");
}

void loop() {
  if (Serial.available() > 0) {
    a = Serial.parseInt();
    b = Serial.parseInt();

    if (Serial.read() == '\n') {
      newData = 1;
    }
  }

  if (newData == 1) {
    asm volatile (
      "mov r16, %2        \n" // r16 = a
      "mov r17, %3        \n" // r17 = b
      "sub r16, r17       \n" // r16 -= r17
      "in r18, _SREG_   \n" // r18 = SREG
      "mov %0, r16        \n" // save result
      "mov %1, r18        \n" // save SREG
      : "=r"(result), "=r"(sreg)
      : "r"(a), "r"(b)
      : "r16", "r17", "r18"
    );

    Serial.print("Result (R16): ");
    Serial.println(result);

    Serial.print("SREG: ");
    Serial.println(sreg, BIN);

    Serial.print("Zero Flag (Z): ");
    Serial.println((sreg & (1 << 1)) ? "SET" : "CLEAR");

    Serial.print("Carry Flag (C): ");
    Serial.println((sreg & (1 << 0)) ? "SET" : "CLEAR");

    newData = 0;
    Serial.println("Enter two numbers separated by a space or comma (e.g., 10 20): ");
  }
}
