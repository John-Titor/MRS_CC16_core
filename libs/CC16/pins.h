// Common pin and GPIO functionality.
//

#pragma once

#include <CMSIS/S32K144.h>

struct Pin
{
    const uint16_t  port:3;
    enum {
        PortA,
        PortB,
        PortC,
        PortD,
        PortE,
        PortX
    };
    const uint16_t  index:5;
    const uint16_t  mux:3;
    enum {
        Analog,
        GPIO,
        Function2,
        Function3,
        Function4,
        Function5,
        Function6,
        Function7,
    };
    const uint16_t  direction:1;
    enum {
        IN,
        OUT
    };
    const uint16_t  initial:1;
    const int16_t   :3;

    void        configure() const;
    void        set(bool v) const;
    bool        get(void) const;
    void        set() const { set(true); }
    void        clear() const { set(false); }
    void        toggle() const;
    void operator = (bool v) const { set(v); }
    bool operator ()() const { return get(); }

private:
    static uint16_t _portX_state;
    static void _portX_update(void);
};

static_assert(sizeof(struct Pin) == 2);

//
// Pins on the port expander.
//
static const Pin DCDC_8V5       { .port = Pin::PortX, .index = 0 };
static const Pin DCDC_10V       { .port = Pin::PortX, .index = 1 };
static const Pin PD_A_IN5       { .port = Pin::PortX, .index = 2 };
static const Pin PD_A_IN4       { .port = Pin::PortX, .index = 3 };
static const Pin PD_A_IN3       { .port = Pin::PortX, .index = 4 };
static const Pin PD_A_IN2       { .port = Pin::PortX, .index = 5 };
static const Pin PD_A_IN1       { .port = Pin::PortX, .index = 6 };
static const Pin PD_A_IN0       { .port = Pin::PortX, .index = 7 };
static const Pin PU_A_IN5       { .port = Pin::PortX, .index = 8 };
static const Pin PU_A_IN4       { .port = Pin::PortX, .index = 9 };
static const Pin PU_A_IN3       { .port = Pin::PortX, .index = 10 };
static const Pin PU_A_IN2       { .port = Pin::PortX, .index = 11 };
static const Pin PU_A_IN1       { .port = Pin::PortX, .index = 12 };
static const Pin PU_A_IN0       { .port = Pin::PortX, .index = 13 };

//
// Internal GPIO pins.
//
static const Pin DI_KL15        { .port = Pin::PortD, .index = 13, .mux = Pin::GPIO, .direction = Pin::IN };
static const Pin DI_PGD         { .port = Pin::PortA, .index = 17, .mux = Pin::GPIO, .direction = Pin::IN };
static const Pin DO_CS_HSD1     { .port = Pin::PortD, .index = 17, .mux = Pin::GPIO, .direction = Pin::OUT, .initial = 1 };
static const Pin DO_CS_HSD2     { .port = Pin::PortD, .index = 11, .mux = Pin::GPIO, .direction = Pin::OUT, .initial = 1 };
static const Pin DO_POWER       { .port = Pin::PortD, .index = 15, .mux = Pin::GPIO, .direction = Pin::OUT, .initial = 1 };
static const Pin DO_RS0         { .port = Pin::PortC, .index = 9,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_RS1         { .port = Pin::PortE, .index = 7,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_RS2         { .port = Pin::PortB, .index = 8,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_RS3         { .port = Pin::PortC, .index = 8,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_RS4         { .port = Pin::PortB, .index = 11, .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_RS5         { .port = Pin::PortB, .index = 17, .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_SHIFT_IN_DS { .port = Pin::PortD, .index = 6,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_SHIFT_MR    { .port = Pin::PortE, .index = 16, .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_SHIFT_OE    { .port = Pin::PortE, .index = 15, .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_SHIFT_SH_CP { .port = Pin::PortD, .index = 0,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_SHIFT_ST_CP { .port = Pin::PortD, .index = 1,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_VREF_EN     { .port = Pin::PortD, .index = 10, .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin LIN_EN         { .port = Pin::PortE, .index = 9,  .mux = Pin::GPIO, .direction = Pin::OUT };

//
// Peripheral and unused pins not requiring other setup.
//
static const Pin MC_CAN_RXD1    { .port = Pin::PortE, .index = 4,  .mux = Pin::Function5 };
static const Pin MC_CAN_RXD2    { .port = Pin::PortA, .index = 12, .mux = Pin::Function3 };
static const Pin MC_CAN_TXD1    { .port = Pin::PortE, .index = 5,  .mux = Pin::Function5 };
static const Pin MC_CAN_TXD2    { .port = Pin::PortA, .index = 13, .mux = Pin::Function3 };
static const Pin MC_SCI_RXD     { .port = Pin::PortA, .index = 8,  .mux = Pin::Function2 };
static const Pin MC_SCI_TXD     { .port = Pin::PortA, .index = 9,  .mux = Pin::Function2 };
static const Pin Pin74          { .port = Pin::PortE, .index = 2,  .mux = Pin::Analog };
static const Pin Pin82          { .port = Pin::PortE, .index = 10, .mux = Pin::Analog };
static const Pin WD             { .port = Pin::PortE, .index = 11, .mux = Pin::Analog };

//
// Internal analog pins.
//
static const Pin DI_AI_INA_OUT0 { .port = Pin::PortC, .index = 16, .mux = Pin::Analog };
static const Pin DI_AI_INA_OUT1 { .port = Pin::PortC, .index = 17, .mux = Pin::Analog };
static const Pin DI_AI_INA_OUT2 { .port = Pin::PortC, .index = 1,  .mux = Pin::Analog };
static const Pin DI_AI_INA_OUT3 { .port = Pin::PortC, .index = 0,  .mux = Pin::Analog };
static const Pin DI_AI_INA_OUT4 { .port = Pin::PortB, .index = 2,  .mux = Pin::Analog };
static const Pin DI_AI_INA_OUT5 { .port = Pin::PortC, .index = 14, .mux = Pin::Analog };
static const Pin DI_AI_INA_OUT6 { .port = Pin::PortC, .index = 15, .mux = Pin::Analog };
static const Pin DI_AI_INA_OUT7 { .port = Pin::PortB, .index = 3,  .mux = Pin::Analog };
static const Pin DI_AI_KL30_1   { .port = Pin::PortC, .index = 2,  .mux = Pin::Analog };
static const Pin DI_AI_KL30_2   { .port = Pin::PortC, .index = 3,  .mux = Pin::Analog };
static const Pin DI_AI_OUT0     { .port = Pin::PortE, .index = 6,  .mux = Pin::Analog };
static const Pin DI_AI_OUT1     { .port = Pin::PortA, .index = 0,  .mux = Pin::Analog };
static const Pin DI_AI_OUT2     { .port = Pin::PortA, .index = 15, .mux = Pin::Analog };
static const Pin DI_AI_OUT3     { .port = Pin::PortA, .index = 16, .mux = Pin::Analog };
static const Pin DI_AI_OUT4     { .port = Pin::PortA, .index = 1,  .mux = Pin::Analog };
static const Pin DI_AI_OUT5     { .port = Pin::PortD, .index = 2,  .mux = Pin::Analog };
static const Pin DI_AI_OUT6     { .port = Pin::PortA, .index = 2,  .mux = Pin::Analog };
static const Pin DI_AI_OUT7     { .port = Pin::PortA, .index = 3,  .mux = Pin::Analog };
static const Pin DI_AI_SNS1     { .port = Pin::PortB, .index = 13, .mux = Pin::Analog };
static const Pin DI_AI_SNS2     { .port = Pin::PortB, .index = 14, .mux = Pin::Analog };
static const Pin DI_AI_SNS3     { .port = Pin::PortD, .index = 4,  .mux = Pin::Analog };
static const Pin DI_AI_SNS4     { .port = Pin::PortB, .index = 12, .mux = Pin::Analog };
static const Pin DI_AI_VARIANTE { .port = Pin::PortC, .index = 6,  .mux = Pin::Analog };
static const Pin DI_AI_VREF     { .port = Pin::PortD, .index = 3,  .mux = Pin::Analog };

//
// Peripheral pins on hold waiting for function implementation.
//
static const Pin MC_FREQ_A_IN0   { .port = Pin::PortC, .index = 10, .mux = Pin::Function2 };
static const Pin MC_FREQ_A_IN1   { .port = Pin::PortC, .index = 11, .mux = Pin::Function2 };
static const Pin MC_FREQ_A_IN2   { .port = Pin::PortC, .index = 12, .mux = Pin::Function2 };
static const Pin MC_FREQ_A_IN3   { .port = Pin::PortC, .index = 13, .mux = Pin::Function2 };
static const Pin MC_FREQ_A_IN4   { .port = Pin::PortB, .index = 9,  .mux = Pin::Function2 };
static const Pin MC_FREQ_A_IN5   { .port = Pin::PortB, .index = 10, .mux = Pin::Function2 };

//
// External input pins.
//
static const Pin DI_AI_A_IN0     { .port = Pin::PortB, .index = 1,  .mux = Pin::Analog };
static const Pin DI_AI_A_IN1     { .port = Pin::PortB, .index = 0,  .mux = Pin::Analog };
static const Pin DI_AI_A_IN2     { .port = Pin::PortA, .index = 7,  .mux = Pin::Analog };
static const Pin DI_AI_A_IN3     { .port = Pin::PortA, .index = 6,  .mux = Pin::Analog };
static const Pin DI_AI_A_IN4     { .port = Pin::PortB, .index = 16, .mux = Pin::Analog };
static const Pin DI_AI_A_IN5     { .port = Pin::PortB, .index = 15, .mux = Pin::Analog };
static const Pin DI_AI_ID        { .port = Pin::PortC, .index = 7,  .mux = Pin::Analog };
static const Pin DI_INTERFACE2_A { .port = Pin::PortD, .index = 7, .mux = Pin::GPIO, .direction = Pin::IN };
static const Pin DI_INTERFACE2_B { .port = Pin::PortD, .index = 8, .mux = Pin::GPIO, .direction = Pin::IN };

//
// High-side driver output pins.
//
// TODO: these need PWM support
//
static const Pin DO_HSD1_OUT0   { .port = Pin::PortD, .index = 14, .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_HSD1_OUT1   { .port = Pin::PortB, .index = 4,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_HSD1_OUT2   { .port = Pin::PortE, .index = 8,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_HSD1_OUT3   { .port = Pin::PortB, .index = 5,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_HSD2_OUT4   { .port = Pin::PortD, .index = 5,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_HSD2_OUT5   { .port = Pin::PortD, .index = 12, .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_HSD2_OUT6   { .port = Pin::PortD, .index = 9,  .mux = Pin::GPIO, .direction = Pin::OUT };
static const Pin DO_HSD2_OUT7   { .port = Pin::PortD, .index = 16, .mux = Pin::GPIO, .direction = Pin::OUT };
