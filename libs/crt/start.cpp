/*
 * Startup
 */

#include <stdint.h>

extern "C" void main();

extern uint32_t __data_start;
extern uint32_t __data_end;
extern uint32_t __data_load;
extern uint32_t __bss_start;
extern uint32_t __bss_end;
extern uint32_t __heap_start;

typedef void (*func_t)();
extern func_t __preinit_array_start[];
extern func_t __preinit_array_end[];
extern func_t __init_array_start[];
extern func_t __init_array_end[];
extern func_t __fini_array_start[];
extern func_t __fini_array_end[];

static void
copy_data() 
{
    auto src = &__data_load;
    auto dst = &__data_start;

    while(dst < &__data_end) {
        *dst++ = *src++;
    }
}

static void
zero_bss() 
{
    auto dst = &__bss_start;

    while (dst < &__bss_end) {
        *dst++ = 0;
    }
}

static void
call_init_funcs() 
{
    for (auto pfunc = __preinit_array_start;
         pfunc < __preinit_array_end;
         pfunc++) {
        (*pfunc)();
    }

    for (auto pfunc = __init_array_start;
         pfunc < __init_array_end;
         pfunc++) {
        (*pfunc)();
    }
}

static void
call_fini_funcs()
{
    for (auto pfunc = __fini_array_start;
         pfunc < __fini_array_end;
         pfunc++) {
        (*pfunc)();
    }
}


extern "C" void
Reset_Handler(void)
{
    copy_data();
    zero_bss();
    call_init_funcs();
    main();
    call_fini_funcs();
    // stop
    while (true);
}