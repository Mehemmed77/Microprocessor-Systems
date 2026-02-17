#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t countdown = 0;

void setup()
{
    cli();

    DDRB |= (1 << DDB5);
    PORTB &= ~(1 << PORTB5);

    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PORTD2);

    EICRA &= ~(1 << ISC00);
    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);

    TCCR1A = 0;
    TCCR1B = 0;

    TCCR1B |= (1 << WGM12);
    OCR1A = 249;

    TCCR1B |= (1 << CS11) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);

    sei();
}

void loop()
{

}

/* ---------- Button Interrupt ---------- */
ISR(INT0_vect)
{
    PORTB |= (1 << PORTB5);  // Set output HIGH immediately
    countdown = 10;          // 10 ms pulse
}

/* ---------- 1 ms Timer Interrupt ---------- */
ISR(TIMER1_COMPA_vect)
{
    if (countdown > 0)
    {
        countdown--;

        if (countdown == 0)
        {
            PORTB &= ~(1 << PORTB5);  // Set LOW after 10 ms
        }
    }
}