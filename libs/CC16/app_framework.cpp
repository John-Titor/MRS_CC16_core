/*
 * Application framework.
 */

extern "C" void main(void);

extern "C" void _app_no_init(void) {}
extern "C" void _app_no_loop(void) {}

extern "C" void app_init(void) __attribute__((weak, alias("_app_no_init")));
extern "C" void app_loop(void) __attribute__((weak, alias("_app_no_loop")));

void
main(void)
{
    /* do system hardware init */
    // pins
    // ADC
    // CAN
    // PWM
    // capture
    // UART (if appropriate)
    // LIN (if appropriate)

    /* run one-time app startup code */
    app_init();

    /* spin running the app loop */
    for (;;) {
        app_loop();
        /* TODO - T15 power-down, deferred events, etc. */
    }
}