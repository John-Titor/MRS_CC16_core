//
// Interrupt management
//

#pragma once

#include <CMSIS/S32K144.h>

namespace CC16
{
    class Interrupt
    {
    public:
        constexpr Interrupt(IRQn_Type vector) :
            _vector(vector)
        {}

        __always_inline void                enable()  const { __atomic_thread_fence(__ATOMIC_RELEASE); NVIC_EnableIRQ(_vector); }
        __always_inline void                disable() const { NVIC_DisableIRQ(_vector); }
        __always_inline void                set_priority(unsigned priority) const { NVIC_SetPriority(_vector, priority); }

        __always_inline static void         enable_all() { __atomic_thread_fence(__ATOMIC_RELEASE); __enable_irq(); }
        __always_inline static void         disable_all() { __disable_irq(); __atomic_thread_fence(__ATOMIC_ACQUIRE); }
        __always_inline static void         wait() { __WFI(); }

    private:
        const IRQn_Type      _vector;
    };

    class CriticalSection
    {
    public:
        CriticalSection() :
            _enabled(__get_PRIMASK() == 0)
        {
            if (_enabled) {
                Interrupt::disable_all();
            }
        }
        ~CriticalSection()
        {
            if (_enabled) {
                Interrupt::enable_all();
            }
        }

    private:
        const bool           _enabled = false;
    };

    static const Interrupt CAN0_ORed_0_15_MB(CAN0_ORed_0_15_MB_IRQn);
    static const Interrupt CAN0_ORed_1_15_MB(CAN1_ORed_0_15_MB_IRQn);
    

} // namespace CC16

#define BEGIN_CRITICAL_SECTION  do { CC16::CriticalSection _crit
#define END_CRITICAL_SECTION    } while(0)
