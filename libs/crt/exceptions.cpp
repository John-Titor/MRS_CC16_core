/*
 * Exception vectors
 */

#include <stdint.h>

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
void SysTick_Handler(void) __attribute__((weak, alias("Unhandled_Exception")));

typedef void (*handler_func_t)(void);

static const __attribute__((used, section(".exception_vectors")))
handler_func_t _exception_vectors[] =
{
    (handler_func_t)&__stacktop,
    Reset_Handler,              // -15 Reset Vector, invoked on Power up and warm reset
    NonMaskableInt_Handler,     // -14 Non maskable Interrupt, cannot be stopped or preempted
    HardFault_Handler,          // -13 Hard Fault, all classes of Fault
    MemoryManagement_Handler,   // -12 Memory Management, MPU mismatch, including Access Violation and No Match
    BusFault_Handler,           // -11 Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory related Fault
    UsageFault_Handler,         // -10 Usage Fault, i.e. Undef Instruction, Illegal State Transition
    0,                          // -9
    0,                          // -8
    0,                          // -7
    0,                          // -6
    SVCall_Handler,             // -5  System Service Call via SVC instruction
    DebugMonitor_Handler,       // -4  Debug Monitor
    0,                          // -3
    PendSV_Handler,             // -2  Pendable request for system service
    SysTick_Handler,            // -1  System Tick Timer
};

static_assert(sizeof(_exception_vectors) == (sizeof(handler_func_t) * 16), "exception vector table size mismatch");
