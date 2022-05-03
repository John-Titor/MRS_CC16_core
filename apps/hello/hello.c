
#include <can.h>
#include <sdk_project_config.h>

void
main()
{
    // Hardware init
    CLOCK_DRV_Init(&clockMan1_InitConfig0);
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    CAN_init();
    CAN_puts("hello");

    for (;;) {}
}
