// Pin functionality.
//

#include "pins.h"

uint16_t    Pin::_portX_state;

void
Pin::configure(void) const 
{
    if (port <= PortE) {
        auto mask = (uint32_t)1 << index;
        auto &cfg = port == PortA ? PORTA_regs :
                    port == PortB ? PORTB_regs :
                    port == PortC ? PORTC_regs :
                    port == PortD ? PORTD_regs :
                    PORTE_regs;
        if (index < 16) {
            cfg.GPCLR = PORT_GPCLR_GPWE(mask) | PORT_GPCLR_GPWD(mux << 8);
        } else {
            cfg.GPCHR = PORT_GPCHR_GPWE(mask >> 16) | PORT_GPCLR_GPWD(mux << 8);
        }
        if (mux == GPIO) {
            auto &io = port == PortA ? PTA_regs :
                       port == PortB ? PTB_regs :
                       port == PortC ? PTC_regs :
                       port == PortD ? PTD_regs :
                       PTE_regs;
            if (direction == OUT) {
                io.PDDR |= mask;
                set(initial);
            } else {
                io.PDDR &= ~mask;
            }
        }
    } else if (port == PortX) {
        set(initial);
    }
}

void
Pin::set(bool v) const
{
    if (port <= PortE) {
        auto mask = (uint32_t)1 << index;
        auto &io = port == PortA ? PTA_regs :
                   port == PortB ? PTB_regs :
                   port == PortC ? PTC_regs :
                   port == PortD ? PTD_regs :
                   PTE_regs;
        if (v) {
            io.PSOR = mask;
        } else {
            io.PCOR = mask;
        }
    } else {
        if (v) {
            _portX_state |= (uint16_t)1 << index;
        } else {
            _portX_state &= ~(uint16_t)1 << index;
        }
        _portX_update();
    }
}

bool
Pin::get(void) const
{
    if (port <= PortE) {
        auto mask = (uint32_t)1 << index;
        auto &io = port == PortA ? PTA_regs :
                   port == PortB ? PTB_regs :
                   port == PortC ? PTC_regs :
                   port == PortD ? PTD_regs :
                   PTE_regs;
        return io.PDIR & mask;
    }
    return false;
}

void
Pin::toggle() const
{
    if (port <= PortE) {
        auto mask = (uint32_t)1 << index;
        auto &io = port == PortA ? PTA_regs :
                   port == PortB ? PTB_regs :
                   port == PortC ? PTC_regs :
                   port == PortD ? PTD_regs :
                   PTE_regs;
        io.PTOR = mask;
    }
}

void
Pin::_portX_update(void)
{
    // ensure register is not in reset
    DO_SHIFT_MR = 1;

    // XXX need to avoid re-entering here - disable interrupts?
    // drop latch pin while shifting
    DO_SHIFT_ST_CP = 0;

    for (unsigned i = 0; i < 14; i++) {
        // clock low
        DO_SHIFT_SH_CP = 0;
        // load data
        DO_SHIFT_IN_DS = _portX_state & (1U << i);
        // clock data on rising edge
        DO_SHIFT_SH_CP = 1;
    }
    // latch on rising edge
    DO_SHIFT_ST_CP = 1;

    // ensure outputs are on - should not be neccessaru
    DO_SHIFT_OE = 0;
}


