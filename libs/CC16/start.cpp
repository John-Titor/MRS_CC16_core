/*
 * Application framework.
 */

#include <CMSIS/S32K144.h>

#include "_pin_names.h"

extern "C" void main(void);

extern "C" void _app_no_init(void) {}
extern "C" void _app_no_loop(void) {}

extern "C" void app_init(void) __attribute__((weak, alias("_app_no_init")));
extern "C" void app_loop(void) __attribute__((weak, alias("_app_no_loop")));

static void clock_setup(void);
static void pin_setup(void);

void
main(void)
{
    /* do system hardware init */
    clock_setup();
    pin_setup();

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

    //
    // Turn on missing peripheral clocks.
    //
    PCC->PCC_ADC0_b.CGC = 1;
    PCC->PCC_ADC1_b.CGC = 1;
    PCC->PCC_FlexCAN1_b.CGC = 1;
    PCC->PCC_PORTB_b.CGC = 1;
    PCC->PCC_PORTC_b.CGC = 1;
    PCC->PCC_PORTD_b.CGC = 1;
}

void
pin_setup(void)
{
    //
    // bulk-configure analog input pins
    // mux disable, no pulls
    //
#define PORTA_ANALOG_PINS    \
    ((1U << DI_AI_OUT1)     |\
     (1U << DI_AI_OUT4)     |\
     (1U << DI_AI_OUT6)     |\
     (1U << DI_AI_OUT7)     |\
     (1U << DI_AI_A_IN3)    |\
     (1U << DI_AI_A_IN2)    |\
     (1U << DI_AI_OUT2)     |\
     (1U << DI_AI_OUT3))

    PORTA->PORTA_GPCLR = ((PORTA_ANALOG_PINS & 0xFFFF) << 16) | (0U << 8);
    PORTA->PORTA_GPCHR = ((PORTA_ANALOG_PINS & 0xFFFF0000))   | (0U << 8);

#define PORTB_ANALOG_PINS    \
    ((1U << DI_AI_A_IN1)    |\
     (1U << DI_AI_A_IN0)    |\
     (1U << DI_AI_INA_OUT4) |\
     (1U << DI_AI_INA_OUT7) |\
     (1U << DI_AI_SNS4)     |\
     (1U << DI_AI_SNS1)     |\
     (1U << DI_AI_SNS2)     |\
     (1U << DI_AI_A_IN5)    |\
     (1U << DI_AI_A_IN4))

    PORTB->PORTB_GPCLR = ((PORTB_ANALOG_PINS & 0xFFFF) << 16) | (0U << 8);
    PORTB->PORTB_GPCHR = ((PORTB_ANALOG_PINS & 0xFFFF0000))   | (0U << 8);

#define PORTC_ANALOG_PINS    \
    ((1U << DI_AI_INA_OUT3) |\
     (1U << DI_AI_INA_OUT2) |\
     (1U << DI_AI_KL30_1)   |\
     (1U << DI_AI_KL30_2)   |\
     (1U << DI_AI_VARIANTE) |\
     (1U << DI_AI_ID)       |\
     (1U << DI_AI_INA_OUT5) |\
     (1U << DI_AI_INA_OUT6) |\
     (1U << DI_AI_INA_OUT0) |\
     (1U << DI_AI_INA_OUT1))

    PORTC->PORTC_GPCLR = ((PORTC_ANALOG_PINS & 0xFFFF) << 16) | (0U << 8);
    PORTC->PORTC_GPCHR = ((PORTC_ANALOG_PINS & 0xFFFF0000))   | (0U << 8);

#define PORTD_ANALOG_PINS    \
    ((1U << DI_AI_OUT5)     |\
     (1U << DI_AI_VREF)     |\
     (1U << DI_AI_SNS3))

    PORTD->PORTD_GPCLR = ((PORTD_ANALOG_PINS & 0xFFFF) << 16) | (0U << 8);
    PORTD->PORTD_GPCHR = ((PORTD_ANALOG_PINS & 0xFFFF0000))   | (0U << 8);

#define PORTE_ANALOG_PINS    \
    ((1U << Pin74)          |\
     (1U << DI_AI_OUT0)     |\
     (1U << Pin82)          |\
     (1U << WD))

    PORTE->PORTE_GPCLR = ((PORTE_ANALOG_PINS & 0xFFFF) << 16) | (0U << 8);
    PORTE->PORTE_GPCHR = ((PORTE_ANALOG_PINS & 0xFFFF0000))   | (0U << 8);

    //
    // bulk-configure special functions
    //
#define PORTA_ALT2_PINS      \
    ((1U << MC_SCI_RXD)     |\
     (1U << MC_SCI_TXD))
#define PORTA_ALT3_PINS      \
    ((1U << MC_CAN_RXD2)    |\
     (1U << MC_CAN_TXD2))

    PORTA->PORTA_GPCLR = ((PORTA_ALT2_PINS & 0xFFFF) << 16) | (2U << 8);
    PORTA->PORTA_GPCHR = ((PORTA_ALT2_PINS & 0xFFFF0000))   | (2U << 8);
    PORTA->PORTA_GPCLR = ((PORTA_ALT3_PINS & 0xFFFF) << 16) | (3U << 8);
    PORTA->PORTA_GPCHR = ((PORTA_ALT3_PINS & 0xFFFF0000))   | (3U << 8);

#define PORTB_ALT2_PINS      \
    ((1U << DO_HSD1_OUT1)   |\
     (1U << DO_HSD1_OUT3)   |\
     (1U << MC_FREQ_A_IN4)  |\
     (1U << MC_FREQ_A_IN5))

    PORTB->PORTB_GPCLR = ((PORTB_ALT2_PINS & 0xFFFF) << 16) | (2U << 8);
    PORTB->PORTB_GPCHR = ((PORTB_ALT2_PINS & 0xFFFF0000))   | (2U << 8);

#define PORTC_ALT2_PINS      \
    ((1U << MC_FREQ_A_IN0)  |\
     (1U << MC_FREQ_A_IN1)  |\
     (1U << MC_FREQ_A_IN2)  |\
     (1U << MC_FREQ_A_IN3))

    PORTC->PORTC_GPCLR = ((PORTC_ALT2_PINS & 0xFFFF) << 16) | (2U << 8);
    PORTC->PORTC_GPCHR = ((PORTC_ALT2_PINS & 0xFFFF0000))   | (2U << 8);

#define PORTD_ALT2_PINS      \
    ((1U << DO_HSD2_OUT4)   |\
     (1U << DO_HSD2_OUT5)   |\
     (1U << DO_HSD1_OUT0)   |\
     (1U << DO_HSD2_OUT7))
#define PORTD_ALT6_PINS      \
    (1U << DO_HSD2_OUT6)

    PORTD->PORTD_GPCLR = ((PORTD_ALT2_PINS & 0xFFFF) << 16) | (2U << 8);
    PORTD->PORTD_GPCHR = ((PORTD_ALT2_PINS & 0xFFFF0000))   | (2U << 8);
    PORTD->PORTD_GPCLR = ((PORTD_ALT6_PINS & 0xFFFF) << 16) | (6U << 8);
    PORTD->PORTD_GPCHR = ((PORTD_ALT6_PINS & 0xFFFF0000))   | (6U << 8);

#define PORTE_ALT2_PINS      \
    (1U << DO_HSD1_OUT2)
#define PORTE_ALT5_PINS      \
    ((1U << MC_CAN_RXD1)    |\
     (1U << MC_CAN_TXD1))

    PORTE->PORTE_GPCLR = ((PORTE_ALT2_PINS & 0xFFFF) << 16) | (2U << 8);
    PORTE->PORTE_GPCHR = ((PORTE_ALT2_PINS & 0xFFFF0000))   | (2U << 8);
    PORTE->PORTE_GPCLR = ((PORTE_ALT5_PINS & 0xFFFF) << 16) | (5U << 8);
    PORTE->PORTE_GPCHR = ((PORTE_ALT5_PINS & 0xFFFF0000))   | (5U << 8);

    //
    // bulk-configure GPIOs
    // all have low drive strength, no pulls
    //

#define PORTA_GPIO_PINS      \
    ((1U << CAN_EN1)        |\
     (1U << CAN_WAKE1)      |\
     (1U << DI_PGD))
#define PORTA_GPIO_OUTPUTS   \
    ((1U << CAN_EN1)        |\
     (1U << CAN_WAKE1))
#define PORTA_GPIO_DEFAULTS  \
    ((1U << CAN_EN1)        |\
     (1U << CAN_WAKE1))

    PORTA->PORTA_GPCLR = ((PORTA_GPIO_PINS & 0xFFFF) << 16) | (1U << 8);
    PORTA->PORTA_GPCHR = ((PORTA_GPIO_PINS & 0xFFFF0000))   | (1U << 8);
    PTA->GPIOA_PDOR = PORTA_GPIO_DEFAULTS;
    PTA->GPIOA_PDDR = PORTA_GPIO_OUTPUTS;

#define PORTB_GPIO_PINS      \
    ((1U << DO_RS2)         |\
     (1U << DO_RS4)         |\
     (1U << DO_RS5))
#define PORTB_GPIO_OUTPUTS   \
    ((1U << DO_RS2)         |\
     (1U << DO_RS4)         |\
     (1U << DO_RS5))
#define PORTB_GPIO_DEFAULTS  \
    ((1U << DO_RS2)         |\
     (1U << DO_RS4)         |\
     (1U << DO_RS5))

    PORTB->PORTB_GPCLR = ((PORTB_GPIO_PINS & 0xFFFF) << 16) | (1U << 8);
    PORTB->PORTB_GPCHR = ((PORTB_GPIO_PINS & 0xFFFF0000))   | (1U << 8);
    PTB->GPIOB_PDOR = PORTB_GPIO_DEFAULTS;
    PTB->GPIOB_PDDR = PORTB_GPIO_OUTPUTS;

#define PORTC_GPIO_PINS      \
    ((1U << DO_RS3)         |\
     (1U << DO_RS0))
#define PORTC_GPIO_OUTPUTS   \
    ((1U << DO_RS3)         |\
     (1U << DO_RS0))
#define PORTC_GPIO_DEFAULTS  \
    ((1U << DO_RS3)         |\
     (1U << DO_RS0))

    PORTC->PORTC_GPCLR = ((PORTC_GPIO_PINS & 0xFFFF) << 16) | (1U << 8);
    PORTC->PORTC_GPCHR = ((PORTC_GPIO_PINS & 0xFFFF0000))   | (1U << 8);
    PTC->GPIOC_PDOR = PORTC_GPIO_DEFAULTS;
    PTC->GPIOC_PDDR = PORTC_GPIO_OUTPUTS;

#define PORTD_GPIO_PINS      \
    ((1U << DO_SHIFT_SH_CP) |\
     (1U << DO_SHIFT_ST_CP) |\
     (1U << DOX_SHIFT_IN_DS)|\
     (1U << DI_INTERFACE2_A)|\
     (1U << DI_INTERFACE2_B)|\
     (1U << DO_VREF_EN)     |\
     (1U << DO_CS_HSD2)     |\
     (1U << DI_KL15)        |\
     (1U << DO_POWER)       |\
     (1U << DO_CS_HSD1))
#define PORTD_GPIO_OUTPUTS   \
    ((1U << DO_SHIFT_SH_CP) |\
     (1U << DO_SHIFT_ST_CP) |\
     (1U << DOX_SHIFT_IN_DS)|\
     (1U << DO_VREF_EN)     |\
     (1U << DO_CS_HSD2)     |\
     (1U << DO_POWER)       |\
     (1U << DO_CS_HSD1))
#define PORTD_GPIO_DEFAULTS  \
    ((1U << DO_POWER))

    PORTD->PORTD_GPCLR = ((PORTD_GPIO_PINS & 0xFFFF) << 16) | (1U << 8);
    PORTD->PORTD_GPCHR = ((PORTD_GPIO_PINS & 0xFFFF0000))   | (1U << 8);
    PTD->GPIOD_PDOR = PORTD_GPIO_DEFAULTS;
    PTD->GPIOD_PDDR = PORTD_GPIO_OUTPUTS;

#define PORTE_GPIO_PINS      \
    ((1U << CAN_ERR1)       |\
     (1U << CAN_STB1)       |\
     (1U << CAN_STB2)       |\
     (1U << DO_RS1)         |\
     (1U << LIN_EN)         |\
     (1U << CAN_EN2)        |\
     (1U << CAN_ERR2)       |\
     (1U << CAN_WAKE2)      |\
     (1U << DO_SHIFT_OE)    |\
     (1U << DO_SHIFT_MR))
#define PORTE_GPIO_OUTPUTS   \
    ((1U << CAN_STB1)       |\
     (1U << CAN_STB2)       |\
     (1U << DO_RS1)         |\
     (1U << LIN_EN)         |\
     (1U << CAN_EN2)        |\
     (1U << CAN_WAKE2)      |\
     (1U << DO_SHIFT_OE)    |\
     (1U << DO_SHIFT_MR))
#define PORTE_GPIO_DEFAULTS  \
    ((1U << CAN_STB1)       |\
     (1U << CAN_STB2)       |\
     (1U << DO_RS1)         |\
     (1U << CAN_EN2)        |\
     (1U << CAN_WAKE2))

    PORTE->PORTE_GPCLR = ((PORTE_GPIO_PINS & 0xFFFF) << 16) | (1U << 8);
    PORTE->PORTE_GPCHR = ((PORTE_GPIO_PINS & 0xFFFF0000))   | (1U << 8);
    PTE->GPIOE_PDOR = PORTE_GPIO_DEFAULTS;
    PTE->GPIOE_PDDR = PORTE_GPIO_OUTPUTS;
}