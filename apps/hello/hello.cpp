
#include <stdio.h>

#include <CC16/CC16.h>

volatile bool ticked;

void
_tick_callback()
{
    ticked = true;
}

auto tick_callback = CC16::tick_callback_t::create<_tick_callback>();

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

    // register a 2s periodic timer
    auto tick_2s = CC16::tick_timer.register_timer(tick_callback, 2000, etl::timer::mode::REPEATING);
    CC16::tick_timer.start(tick_2s);

    CC16::Interrupt::enable_all();
    puts("starting");

    for (;;) {
        if (ticked) {
            puts("ticked");
            ticked = false;
        }
    }
}