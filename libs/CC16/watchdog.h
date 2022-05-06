// Hardware watchdog timer
//

#pragma once

#include <CMSIS/S32K144.h>

namespace Watchdog
{
    void reset(void)
    {
        WDOG.CNT = 0xB480A602;          // reset
    }
    
 void disable(void)
    {
        WDOG.CNT = 0xD928C520;          // unlock
        (void)WDOG.CNT;                 // force ordering
        WDOG.CS &= ~WDOG_CS_EN;        // disable
    }
    
    void enable(void)
    {
        WDOG.CNT = 0xD928C520;          // unlock
        WDOG.TOVAL = 0xffff;            // set maximum period
        (void)WDOG.CNT;                 // force ordering
        WDOG.CS |= WDOG_CS_EN;          // enable
    }
}