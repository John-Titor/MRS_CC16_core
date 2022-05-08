//
// Standard Cortex M4F exception vectors.
//

#include <stdint.h>

#include <CMSIS/S32K144.h>

#include "CC16.h"

extern uint32_t __stacktop;
extern "C" void Reset_Handler(void);

extern "C" void
Unhandled_Exception(void)
{
    for (;;) {}
}

void NonMaskableInt_Handler(void) __attribute__((weak, alias("Unhandled_Exception")));
void HardFault_Handler(void) __attribute__((weak, alias("Unhandled_Exception")));
void MemoryManagement_Handler(void) __attribute__((weak, alias("Unhandled_Exception")));
void BusFault_Handler(void) __attribute__((weak, alias("Unhandled_Exception")));
void UsageFault_Handler(void) __attribute__((weak, alias("Unhandled_Exception")));
void SVCall_Handler(void) __attribute__((weak, alias("Unhandled_Exception")));
void DebugMonitor_Handler(void) __attribute__((weak, alias("Unhandled_Exception")));
void PendSV_Handler(void) __attribute__((weak, alias("Unhandled_Exception")));

CC16::timer_controller_t CC16::timer_controller;
void SysTick_Handler(void)
{
    static uint32_t ticks;

    if (CC16::timer_controller.tick(++ticks)) {
        ticks = 0;
    } else {
        ticks++;
    }
};

typedef void (*handler_func_t)(void);

static const __attribute__((used, section(".exception_vectors")))
handler_func_t _exception_vectors[] =
{
    (handler_func_t)&__stacktop,
    Reset_Handler,              // -15
    NonMaskableInt_Handler,     // -14
    HardFault_Handler,          // -13
    MemoryManagement_Handler,   // -12
    BusFault_Handler,           // -11
    UsageFault_Handler,         // -10
    0,                          // -9
    0,                          // -8
    0,                          // -7
    0,                          // -6
    SVCall_Handler,             // -5 
    DebugMonitor_Handler,       // -4 
    0,                          // -3
    PendSV_Handler,             // -2 
    SysTick_Handler,            // -1 
};

static_assert(sizeof(_exception_vectors) == (sizeof(handler_func_t) * 16), "exception vector table size mismatch");
