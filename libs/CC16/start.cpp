/*
 * Application framework.
 */

#include <CMSIS/S32K144.h>

#include "can.h"
#include "pins.h"
#include "pwm.h"
#include "watchdog.h"

void
die(int count) {
    for (;;) {
        int n;

        for (n = 0; n < count; n++) {
            DO_HSD1_OUT0.set();
            for (volatile int x = 0; x < 1000000; x++) {}
            DO_HSD1_OUT0.clear();
            for (volatile int x = 0; x < 1000000; x++) {}
        }
        for (volatile int x = 0; x < 5000000; x++) {}
    }
}

extern "C" void main(void);

extern "C" void _app_no_init(void) {}
extern "C" void _app_no_loop(void) {}

extern "C" void app_init(void) __attribute__((weak, alias("_app_no_init")));
extern "C" void app_loop(void) __attribute__((weak, alias("_app_no_loop")));

static void clock_setup(void);
static void pin_setup(void);
static void pwm_setup(void);

void
main(void)
{
    //Watchdog::reset();
    Watchdog::disable();

    /* do system hardware init */
    clock_setup();
    pin_setup();
    pwm_setup();
    // CAN
    // ADC
    // PWM
    // capture
    // UART (if appropriate)
    // LIN (if appropriate)

    CAN1.configure(CAN::RATE_500K);
    CAN::Frame f = {
        .id_ext = 0x1ffffffe,
        .dlc = 6,
        .ide = 1,
        .data = { 'h', 'e', 'l', 'l', 'o', 0, 0, 0 }
    };
    CAN1.send(f);

    /* run one-time app startup code */
    app_init();

    /* spin running the app loop */
    for (;;) {
        //Watchdog::reset();
        app_loop();
        die(3);
        /* TODO - T15 power-down, deferred events, etc. */
    }
}

void
clock_setup(void)
{
    // The bootloader has already configured the PLL and the 
    // clock tree, so we can leave it alone.

    // GPIO clocks on
    PCC_regs.PCC_PORTB = PCC_PCC_PORTB_CGC;
    PCC_regs.PCC_PORTC = PCC_PCC_PORTB_CGC;
    PCC_regs.PCC_PORTD = PCC_PCC_PORTB_CGC;

}

void
pin_setup(void)
{
    // Reset the port expander pins before they get configured.
    //
    DO_SHIFT_MR.configure();
    DO_SHIFT_MR = 0;
    DO_SHIFT_MR = 1;

    DI_AI_A_IN0.configure();
    DI_AI_A_IN1.configure();
    DI_AI_A_IN2.configure();
    DI_AI_A_IN3.configure();
    DI_AI_A_IN4.configure();
    DI_AI_A_IN5.configure();
    DI_AI_ID.configure();
    DI_AI_INA_OUT0.configure();
    DI_AI_INA_OUT1.configure();
    DI_AI_INA_OUT2.configure();
    DI_AI_INA_OUT3.configure();
    DI_AI_INA_OUT4.configure();
    DI_AI_INA_OUT5.configure();
    DI_AI_INA_OUT6.configure();
    DI_AI_INA_OUT7.configure();
    DI_AI_KL30_1.configure();
    DI_AI_KL30_2.configure();
    DI_AI_OUT0.configure();
    DI_AI_OUT1.configure();
    DI_AI_OUT2.configure();
    DI_AI_OUT3.configure();
    DI_AI_OUT4.configure();
    DI_AI_OUT5.configure();
    DI_AI_OUT6.configure();
    DI_AI_OUT7.configure();
    DI_AI_SNS1.configure();
    DI_AI_SNS2.configure();
    DI_AI_SNS3.configure();
    DI_AI_SNS4.configure();
    DI_AI_VARIANTE.configure();
    DI_AI_VREF.configure();
    DI_INTERFACE2_A.configure();
    DI_INTERFACE2_B.configure();
    DI_KL15.configure();
    DI_PGD.configure();
    DO_CS_HSD1.configure();
    DO_CS_HSD2.configure();
    DO_HSD1_OUT0.configure();
    DO_HSD1_OUT1.configure();
    DO_HSD1_OUT2.configure();
    DO_HSD1_OUT3.configure();
    DO_HSD2_OUT4.configure();
    DO_HSD2_OUT5.configure();
    DO_HSD2_OUT6.configure();
    DO_HSD2_OUT7.configure();
    DO_POWER.configure();
    DO_RS0.configure();
    DO_RS1.configure();
    DO_RS2.configure();
    DO_RS3.configure();
    DO_RS4.configure();
    DO_RS5.configure();
    DO_SHIFT_IN_DS.configure();
    DO_SHIFT_OE.configure();
    DO_SHIFT_SH_CP.configure();
    DO_SHIFT_ST_CP.configure();
    DO_VREF_EN.configure();
    LIN_EN.configure();
    MC_CAN_RXD1.configure();
    MC_CAN_RXD2.configure();
    MC_CAN_TXD1.configure();
    MC_CAN_TXD2.configure();
    MC_FREQ_A_IN0.configure();
    MC_FREQ_A_IN1.configure();
    MC_FREQ_A_IN2.configure();
    MC_FREQ_A_IN3.configure();
    MC_FREQ_A_IN4.configure();
    MC_FREQ_A_IN5.configure();
    MC_SCI_RXD.configure();
    MC_SCI_TXD.configure();
    Pin74.configure();
    Pin82.configure();
    WD.configure();

}


void
pwm_setup(void)
{
    //::PWM::configure();
}