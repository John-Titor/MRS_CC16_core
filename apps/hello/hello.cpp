
#include <stdio.h>

#include <CC16/CC16.h>

void
main(void)
{
    // Turn off the watchdog for now
    CC16::Watchdog::disable();

    // turn on an LED    
    CC16::DO_HSD1_OUT0.configure();
    CC16::DO_HSD1_OUT0.set();

    // configure CAN
    CC16::CAN::configure(CC16::CAN::CAN1, CC16::CAN::RATE_500K);
    puts("hello");


    for (;;);
}