//
// Standard Cortex M4F exception vectors.
//

#include <stdint.h>
#include <stdio.h>

#include <CMSIS/S32K144.h>

#include "CC16.h"

typedef void (*func_t)();

extern uint32_t __stacktop;

extern "C" void main(void);

extern "C" void
Unhandled_Exception(void)
{
    puts("!!!");
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


void SysTick_Handler(void)
{
    static uint32_t ticks;
    if (CC16::tick_timer.tick(++ticks)) {
        ticks = 0;
    } else {
        ticks++;
    }
};


// Tick callback controller.
//
CC16::tick_timer_t CC16::tick_timer;

//
// Entrypoint from reset.
//
// Naked to avoid pushing LR, since %sp is garbage from the bootloader.
//
extern "C" void
__attribute__((naked))
Reset_Handler(void)
{
    // fix the stack pointer
    register void *sp  __asm__("%sp");
    sp = &__stacktop;
    (void)sp;

    // point VTOR back at our vector table
    extern uint32_t __vector_table;
    SCB->VTOR = (uint32_t)&__vector_table;

    // disable interrupts
    CC16::Interrupt::disable_all();

    // early init, required for C/C++ to work correctly
    extern uint32_t __data_start;
    extern uint32_t __data_end;
    extern uint32_t __data_load;
    auto data_src = &__data_load;
    auto data_dst = &__data_start;
    while(data_dst < &__data_end) {
        *data_dst++ = *data_src++;
    }

    extern uint32_t __bss_start;
    extern uint32_t __bss_end;
    auto zero_dst = &__bss_start;
    while (zero_dst < &__bss_end) {
        *zero_dst++ = 0;
    }

    // run global constructors
    extern func_t __preinit_array_start[];
    extern func_t __preinit_array_end[];
    for (auto pfunc = __preinit_array_start;
         pfunc < __preinit_array_end;
         pfunc++) {
        (*pfunc)();
    }

    extern func_t __init_array_start[];
    extern func_t __init_array_end[];
    for (auto pfunc = __init_array_start;
         pfunc < __init_array_end;
         pfunc++) {
        (*pfunc)();
    }

    // start 1kHz timer tick 
    SysTick_Config((CC16::Clocks::CORE_CLK) / 1000);
    CC16::tick_timer.enable(true);

    // run application
    main();

    // run global destructors
    extern func_t __fini_array_start[];
    extern func_t __fini_array_end[];
    for (auto pfunc = __fini_array_start;
         pfunc < __fini_array_end;
         pfunc++) {
        (*pfunc)();
    }

    // stop (should reset here?)
    while (true);
}

static const __attribute__((used, section(".exception_vectors")))
func_t _exception_vectors[] =
{
    (func_t)&__stacktop,
    Reset_Handler,              // -15
    NonMaskableInt_Handler,     // -14
    HardFault_Handler,          // -13
    MemoryManagement_Handler,   // -12
    BusFault_Handler,           // -11
    UsageFault_Handler,         // -10
    Unhandled_Exception,        // -9
    Unhandled_Exception,        // -8
    Unhandled_Exception,        // -7
    Unhandled_Exception,        // -6
    SVCall_Handler,             // -5 
    DebugMonitor_Handler,       // -4 
    Unhandled_Exception,        // -3
    PendSV_Handler,             // -2 
    SysTick_Handler,            // -1 
};

static_assert(sizeof(_exception_vectors) == (sizeof(func_t) * 16), "exception vector table size mismatch");
