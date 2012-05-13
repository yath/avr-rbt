#include <util/delay.h>
#include "uart.h"
#include "debug.h"
#include "timer.h"
#include "bits.h"

void init(void) {
    uart_init();
    debug_init();
    timer_init();
    DEBUG("initialization finished");
}

int main(void) {
    init();

    SET_BIT(DDRB, DDB0);
    CLR_BIT(DDRB, DDB1);

    DEBUG("BEFORE:");
    DUMPBYTE(DDRD);
    DUMPBYTE(PORTD);
    CLR_BITS(DDRD, DDD6, DDD7);
    CLR_BITS(PORTD, PD6, PD7);
    DEBUG("AFTER:");
    DUMPBYTE(DDRD);
    DUMPBYTE(PORTD);

#define bitchar(x, y) (GET_BIT(x, y) ? '1' : '0')
    uint8_t old = 0;
    while (1) {
        uint8_t new = GET_BITS(PIND, PIND6, PIND7);
        if (old != new) {
            DUMPBYTE(PIND);
            DEBUG("changed: %c%c -> %c%c",
                bitchar(old, PIND6), bitchar(old, PIND7),
                bitchar(new, PIND6), bitchar(new, PIND7));
            old = new;
        }
    }
}
