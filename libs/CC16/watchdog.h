// Hardware watchdog timer
//

#pragma once

#include <CMSIS/S32K144.h>

namespace Watchdog
{
    void reset(void)
    {
        WDOG_regs.CNT = 0xB480A602;          // reset
    }
    
 void disable(void)
    {
        WDOG_regs.CNT = 0xD928C520;          // unlock
        (void)WDOG_regs.CNT;                 // force ordering
        WDOG_regs.CS &= ~WDOG_CS_EN;        // disable
    }
    
    void enable(void)
    {
        WDOG_regs.CNT = 0xD928C520;          // unlock
        WDOG_regs.TOVAL = 0xffff;            // set maximum period
        (void)WDOG_regs.CNT;                 // force ordering
        WDOG_regs.CS |= WDOG_CS_EN;          // enable
    }
}