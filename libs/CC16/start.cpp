/*
 * Application framework.
 */

#include <CMSIS/S32K144.h>

#include "pin.h"
#include "pwm.h"

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

    /* run one-time app startup code */
    app_init();

    /* spin running the app loop */
    for (;;) {
        app_loop();
        /* TODO - T15 power-down, deferred events, etc. */
    }
}

void
clock_setup(void)
{
    // The bootloader has already configured the PLL and the 
    // clock tree, so we can leave it alone.

    // GPIO clocks on
    PCC->PCC_PORTB_b.CGC = 1;
    PCC->PCC_PORTC_b.CGC = 1;
    PCC->PCC_PORTD_b.CGC = 1;

    // FTM0-2 on, running from SYS_CLK
    PCC->PCC_FTM0_b.PCS = 1;
    PCC->PCC_FTM0_b.CGC = 1;
    PCC->PCC_FTM1_b.PCS = 1;
    PCC->PCC_FTM1_b.CGC = 1;
    PCC->PCC_FTM2_b.PCS = 1;
    PCC->PCC_FTM2_b.CGC = 1;
}

void
pin_setup(void)
{
    CAN_EN1.configure();
    CAN_EN2.configure();
    CAN_ERR1.configure();
    CAN_ERR2.configure();
    CAN_STB1.configure();
    CAN_STB2.configure();
    CAN_WAKE1.configure();
    CAN_WAKE2.configure();
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
    DO_SHIFT_MR.configure();
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

    ExpanderPins::reset();
}


void
pwm_setup(void)
{
    // XXX
}