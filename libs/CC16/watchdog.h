// Hardware watchdog timer
//

#pragma once

#include <CMSIS/S32K144.h>

namespace Watchdog
{

void reset(void)
{
	WDOG->WDOG_CNT = 0xB480A602;
}

void disable(void)
{
	WDOG->WDOG_CNT = 0xD928C520;			// unlock
	(void)WDOG->WDOG_CNT;					// force ordering
	WDOG->WDOG_CS_b.EN = 0;					// disable
}

void enable(void)
{
	WDOG->WDOG_CNT = 0xD928C520;			// unlock
	WDOG->WDOG_TOVAL = (uint32_t )0xFFFF;	// set maximum period
	(void)WDOG->WDOG_CNT;					// force ordering
	WDOG->WDOG_CS_b.EN = 1;					// enable
}

}