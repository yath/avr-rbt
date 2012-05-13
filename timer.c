#include "debug.h"
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void timer_init(void) {
    TCCR0 = (1<<CS02)|(1<<CS00);
//    TIMSK |= (1<<TOIE0);
    sei();
}

ISR (TIMER0_OVF_vect) {
    DEBUG("ISR TIMER0_OVF_vect!");
}
