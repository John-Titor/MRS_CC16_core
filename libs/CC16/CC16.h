//
// CC16 library header.
//

#pragma once

#include <stdint.h>
#include <etl/callback_timer_atomic.h>

#include "can.h"
#include "interrupts.h"
#include "pins.h"
//#include "pwm.h"

namespace CC16
{
    enum Clocks : uint32_t {
        FIRC_CLK        =  48000000U,
        SIRC_CLK        =   8000000U,
        SOSCK_CLK       =  16000000U,
        SOSCDIV1_CLK    =   8000000U,
        SOSCDIV2_CLK    =   8000000U,
        SPLL_CLK        = 160000000U,
        CORE_CLK        =  80000000U,
        SYS_CLK         =  80000000U,
        BUS_CLK         =  40000000U,
        FLASH_CLK       =  26600000U,
        SCG_SLOW_CLK    =  26600000U,
        SPLLDIV1_CLK    =  80000000U,
        SPLLDIV2_CLK    =  40000000U,      
    };

    // 1kHz tick timer - max 8 callbacks
    using tick_timer_t = etl::callback_timer_atomic<8, std::atomic_int32_t>;
    using tick_callback_t = etl::icallback_timer_atomic<std::atomic_int32_t>::callback_type;
    extern tick_timer_t tick_timer;

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
