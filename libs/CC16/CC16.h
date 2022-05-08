//
// CC16 library header.
//

#pragma once

#include <stdint.h>
#include <etl/callback_timer_atomic.h>

#include "can.h"
#include "pins.h"
//#include "pwm.h"

namespace CC16
{
    enum Clocks : uint32_t {
        FIRC_CLK        =  48000000,
        SIRC_CLK        =   8000000,
        SOSCK_CLK       =  16000000,
        SOSCDIV1_CLK    =   8000000,
        SOSCDIV2_CLK    =   8000000,
        SPLL_CLK        = 160000000,
        CORE_CLK        =  80000000,
        SYS_CLK         =  80000000,
        BUS_CLK         =  40000000,
        FLASH_CLK       =  26600000,
        SCG_SLOW_CLK    =  26600000,
        SPLLDIV1_CLK    =  80000000,
        SPLLDIV2_CLK    =  40000000,      
    };

    // system tick callback controller - max 8 registered callbacks
    using timer_controller_t = etl::callback_timer_atomic<8, std::atomic_int32_t>;
    extern timer_controller_t timer_controller;

    // console I/O
    void cons_putc(char c);
    int cons_getc(void);
}

namespace CC16::Watchdog
{
    void reset(void);
    void disable(void);
    void enable(void);
}
