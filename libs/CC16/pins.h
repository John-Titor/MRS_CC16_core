// Common pin and GPIO functionality.
//

#pragma once

#include <stdint.h>
#include <CMSIS/S32K144.h>

class ExpanderPin
{
public:
    constexpr ExpanderPin(uint32_t index) :
        _index { index}
    {}

    void set(bool v)         const;
    void set()               const { set(true); }
    void clear()             const { set(false); }
    void operator = (bool v) const { set(v); }

    enum {
        PortX_DCDC_8V5,
        PortX_DCDC_10V,
        PortX_PD_A_IN5,
        PortX_PD_A_IN4,
        PortX_PD_A_IN3,
        PortX_PD_A_IN2,
        PortX_PD_A_IN1,
        PortX_PD_A_IN0,
        PortX_PU_A_IN5,
        PortX_PU_A_IN4,
        PortX_PU_A_IN3,
        PortX_PU_A_IN2,
        PortX_PU_A_IN1,
        PortX_PU_A_IN0,
    };

    static void         reset();

private:
    uint32_t             _index;

    static uint16_t     _state;
    static void         update(void);
};

#define DCDC_8V5 ::ExpanderPin(::ExpanderPin::PortX_DCDC_8V5)
#define DCDC_10V ::ExpanderPin(::ExpanderPin::PortX_DCDC_10V)
#define PD_A_IN5 ::ExpanderPin(::ExpanderPin::PortX_PD_A_IN5)
#define PD_A_IN4 ::ExpanderPin(::ExpanderPin::PortX_PD_A_IN4)
#define PD_A_IN3 ::ExpanderPin(::ExpanderPin::PortX_PD_A_IN3)
#define PD_A_IN2 ::ExpanderPin(::ExpanderPin::PortX_PD_A_IN2)
#define PD_A_IN1 ::ExpanderPin(::ExpanderPin::PortX_PD_A_IN1)
#define PD_A_IN0 ::ExpanderPin(::ExpanderPin::PortX_PD_A_IN0)
#define PU_A_IN5 ::ExpanderPin(::ExpanderPin::PortX_PU_A_IN5)
#define PU_A_IN4 ::ExpanderPin(::ExpanderPin::PortX_PU_A_IN4)
#define PU_A_IN3 ::ExpanderPin(::ExpanderPin::PortX_PU_A_IN3)
#define PU_A_IN2 ::ExpanderPin(::ExpanderPin::PortX_PU_A_IN2)
#define PU_A_IN1 ::ExpanderPin(::ExpanderPin::PortX_PU_A_IN1)
#define PU_A_IN0 ::ExpanderPin(::ExpanderPin::PortX_PU_A_IN0)

class _Pin
{
public:
    constexpr _Pin(volatile PORT_regs_t &cfg,
                   uint32_t index) :
        _cfg    { cfg },
        _mask   { 1U << index }
    {}

    // Pin indices
    enum
    {
        PortA_DI_AI_OUT1,
        PortA_DI_AI_OUT4,
        PortA_DI_AI_OUT6,
        PortA_DI_AI_OUT7,
        PortA_MC_JTAG_TMS,
        PortA_MC_JTAG_TRST,
        PortA_DI_AI_A_IN3,
        PortA_DI_AI_A_IN2,
        PortA_MC_SCI_RXD,
        PortA_MC_SCI_TXD,
        PortA_MC_JTAG_TDO,
        PortA_CAN_EN1,
        PortA_MC_CAN_RXD2,
        PortA_MC_CAN_TXD2,
        PortA_CAN_WAKE1,
        PortA_DI_AI_OUT2,
        PortA_DI_AI_OUT3,
        PortA_DI_PGD,
    };

    enum 
    {
        PortB_DI_AI_A_IN1,
        PortB_DI_AI_A_IN0,
        PortB_DI_AI_INA_OUT4,
        PortB_DI_AI_INA_OUT7,
        PortB_DO_HSD1_OUT1,
        PortB_DO_HSD1_OUT3,
        PortB_XTAL,
        PortB_EXTAL,
        PortB_DO_RS2,
        PortB_MC_FREQ_A_IN4,
        PortB_MC_FREQ_A_IN5,
        PortB_DO_RS4,
        PortB_DI_AI_SNS4,
        PortB_DI_AI_SNS1,
        PortB_DI_AI_SNS2,
        PortB_DI_AI_A_IN5,
        PortB_DI_AI_A_IN4,
        PortB_DO_RS5,
    };

    enum 
    {
        PortC_DI_AI_INA_OUT3,
        PortC_DI_AI_INA_OUT2,
        PortC_DI_AI_KL30_1,
        PortC_DI_AI_KL30_2,
        PortC_MC_JTAG_TCLK,
        PortC_MC_JTAG_TDI,
        PortC_DI_AI_VARIANTE,
        PortC_DI_AI_ID,
        PortC_DO_RS3,
        PortC_DO_RS0,
        PortC_MC_FREQ_A_IN0,
        PortC_MC_FREQ_A_IN1,
        PortC_MC_FREQ_A_IN2,
        PortC_MC_FREQ_A_IN3,
        PortC_DI_AI_INA_OUT5,
        PortC_DI_AI_INA_OUT6,
        PortC_DI_AI_INA_OUT0,
        PortC_DI_AI_INA_OUT1,
    };

    enum 
    {
        PortD_DO_SHIFT_SH_CP,
        PortD_DO_SHIFT_ST_CP,
        PortD_DI_AI_OUT5,
        PortD_DI_AI_VREF,
        PortD_DI_AI_SNS3,
        PortD_DO_HSD2_OUT4,
        PortD_DO_SHIFT_IN_DS,
        PortD_DI_INTERFACE2_A,
        PortD_DI_INTERFACE2_B,
        PortD_DO_HSD2_OUT6,
        PortD_DO_VREF_EN,
        PortD_DO_CS_HSD2,
        PortD_DO_HSD2_OUT5,
        PortD_DI_KL15,
        PortD_DO_HSD1_OUT0,
        PortD_DO_POWER,
        PortD_DO_HSD2_OUT7,
        PortD_DO_CS_HSD1,
    };

    enum
    {
        PortE_CAN_ERR1,
        PortE_CAN_STB1,
        PortE_Pin74,
        PortE_CAN_STB2,
        PortE_MC_CAN_RXD1,
        PortE_MC_CAN_TXD1,
        PortE_DI_AI_OUT0,
        PortE_DO_RS1,
        PortE_DO_HSD1_OUT2,
        PortE_LIN_EN,
        PortE_Pin82,
        PortE_WD,
        PortE_CAN_EN2,
        PortE_CAN_ERR2,
        PortE_CAN_WAKE2,
        PortE_DO_SHIFT_OE,
        PortE_DO_SHIFT_MR,
    };


protected:
    static const uint8_t    func_analog = 0;
    static const uint8_t    func_gpio = 1;

    volatile PORT_regs_t    &_cfg;
    const uint32_t          _mask;

    void configure(uint32_t function) volatile {
        auto data = PORT_PCR0_MUX(function);
        if (_mask < 0x10000) {
            _cfg.GPCLR = PORT_GPCLR_GPWE(_mask) | PORT_GPCLR_GPWD(data);
        } else {
            _cfg.GPCHR = PORT_GPCHR_GPWE(_mask >> 16) | PORT_GPCHR_GPWD(data);
        }
    }
};

class _GPIO : public _Pin
{
public:
    constexpr _GPIO(volatile PT_regs_t &io,
                    volatile PORT_regs_t &cfg,
                    uint32_t index) :
        _Pin(cfg, index),
        _io { io }
    {}

protected:
    static const bool           mode_output = true;
    static const bool           mode_input = false;

    volatile PT_regs_t  &_io;

    void configure(bool mode)
    {
        if (mode == mode_output) {
            _io.PDDR |= _mask;
        } else {
            _io.PDDR &= ~_mask;
        }
        _Pin::configure(func_gpio); 
    }
};

class GPIOOut : public _GPIO
{
public:
    constexpr GPIOOut(volatile PT_regs_t &io,
                      volatile PORT_regs_t &cfg,
                      uint32_t index,
                      bool initial=false) :
        _GPIO(io, cfg, index),
        _initial { initial }
    {}

    void set(void)              volatile { _io.PSOR = _mask; }
    void set(bool v)            volatile { if (v) set(); else clear(); }
    void clear(void)            volatile { _io.PCOR = _mask; }
    void toggle(void)           volatile { _io.PTOR = _mask; }
    bool get(void)              volatile { return _io.PDOR & _mask; }
    uint32_t mask(void)         volatile { return _mask; }

    void operator = (bool v)    volatile { set(v); }
    bool operator()(void)       volatile { return get(); }

    void configure()
    {
        set(_initial);
        _GPIO::configure(mode_output);
    }

private:
    const bool      _initial;
};

class GPIOIn : public _GPIO
{
public:
    constexpr GPIOIn(volatile PT_regs_t &io,
                     volatile PORT_regs_t &cfg,
                     uint32_t index) :
        _GPIO(io, cfg, index)
    {}

    bool get(void)              volatile { return _io.PDIR & _mask; }
    bool operator()(void)       volatile { return get(); }
    void configure()            { _GPIO::configure(mode_input); }
};

class AnalogPin : public _Pin
{
public:
    constexpr AnalogPin(volatile PORT_regs_t &cfg,
                        uint32_t index) :
        _Pin(cfg, index)
    {}

    void configure(void)        { _Pin::configure(func_analog); }
};

class PeripheralPin : public _Pin
{
public:
    constexpr PeripheralPin(volatile PORT_regs_t &cfg,
                            uint32_t index,
                            uint8_t function) :
        _Pin(cfg, index),
        _function               { function }
    {}

    void configure(void)        { _Pin::configure(_function); }

private:
    const uint8_t   _function;
};

class InputPin : public _Pin
{
public:
    constexpr InputPin(volatile PT_regs_t &io,
                       volatile PORT_regs_t &cfg,
                       uint32_t index,
                       // XXX ADC channel?
                       const ExpanderPin &pull_up,
                       const ExpanderPin &pull_down,
                       GPIOOut range_select) :
        _Pin(cfg, index),
        _gpio { io, cfg, index },
        _pu { pull_up },
        _pd { pull_down },
        _rs { range_select }
    {}

    typedef enum {
        IN_ANALOG_17V,
        IN_ANALOG_32V,
        IN_DIGITAL_PULLUP,
        IN_DIGITAL_PULLDOWN,
        IN_DIGITAL_NOPULL
    } Mode;

    void configure(InputPin::Mode mode=(IN_ANALOG_17V));
    bool get(void)              volatile { return _gpio.get(); }
    bool operator()(void)       volatile { return get(); }

private:
    GPIOIn              _gpio;
    const ExpanderPin   &_pu;
    const ExpanderPin   &_pd;
    GPIOOut             &_rs;
};


//
// Internal GPIO pins.
//
#define CAN_EN1         ::GPIOOut(PTA_regs, PORTA_regs, ::_Pin::PortA_CAN_EN1, 1)
#define CAN_EN2         ::GPIOOut(PTE_regs, PORTE_regs, ::_Pin::PortE_CAN_EN2, 1)
#define CAN_ERR1        ::GPIOIn(PTE_regs, PORTE_regs, ::_Pin::PortE_CAN_ERR1)
#define CAN_ERR2        ::GPIOIn(PTE_regs, PORTE_regs, ::_Pin::PortE_CAN_ERR2)
#define CAN_STB1        ::GPIOOut(PTE_regs, PORTE_regs, ::_Pin::PortE_CAN_STB1, 1)
#define CAN_STB2        ::GPIOOut(PTE_regs, PORTE_regs, ::_Pin::PortE_CAN_STB2, 1)
#define CAN_WAKE1       ::GPIOOut(PTA_regs, PORTA_regs, ::_Pin::PortA_CAN_WAKE1, 1)
#define CAN_WAKE2       ::GPIOOut(PTE_regs, PORTE_regs, ::_Pin::PortE_CAN_WAKE2, 1)
#define DI_KL15         ::GPIOIn(PTD_regs, PORTD_regs, ::_Pin::PortD_DI_KL15)
#define DI_PGD          ::GPIOIn(PTA_regs, PORTA_regs, ::_Pin::PortA_DI_PGD)
#define DO_CS_HSD1      ::GPIOOut(PTD_regs, PORTD_regs, ::_Pin::PortD_DO_CS_HSD1, 1)
#define DO_CS_HSD2      ::GPIOOut(PTD_regs, PORTD_regs, ::_Pin::PortD_DO_CS_HSD2, 1)
#define DO_POWER        ::GPIOOut(PTD_regs, PORTD_regs, ::_Pin::PortD_DO_POWER, 1)
#define DO_RS0          ::GPIOOut(PTC_regs, PORTC_regs, ::_Pin::PortC_DO_RS0)
#define DO_RS1          ::GPIOOut(PTE_regs, PORTE_regs, ::_Pin::PortE_DO_RS1)
#define DO_RS2          ::GPIOOut(PTB_regs, PORTB_regs, ::_Pin::PortB_DO_RS2)
#define DO_RS3          ::GPIOOut(PTC_regs, PORTC_regs, ::_Pin::PortC_DO_RS3)
#define DO_RS4          ::GPIOOut(PTB_regs, PORTB_regs, ::_Pin::PortB_DO_RS4)
#define DO_RS5          ::GPIOOut(PTB_regs, PORTB_regs, ::_Pin::PortB_DO_RS5)
#define DO_SHIFT_IN_DS  ::GPIOOut(PTD_regs, PORTD_regs, ::_Pin::PortD_DO_SHIFT_IN_DS)
#define DO_SHIFT_MR     ::GPIOOut(PTE_regs, PORTE_regs, ::_Pin::PortE_DO_SHIFT_MR)
#define DO_SHIFT_OE     ::GPIOOut(PTE_regs, PORTE_regs, ::_Pin::PortE_DO_SHIFT_OE)
#define DO_SHIFT_SH_CP  ::GPIOOut(PTD_regs, PORTD_regs, ::_Pin::PortD_DO_SHIFT_SH_CP)
#define DO_SHIFT_ST_CP  ::GPIOOut(PTD_regs, PORTD_regs, ::_Pin::PortD_DO_SHIFT_ST_CP)
#define DO_VREF_EN      ::GPIOOut(PTD_regs, PORTD_regs, ::_Pin::PortD_DO_VREF_EN)
#define LIN_EN          ::GPIOOut(PTE_regs, PORTE_regs, ::_Pin::PortE_LIN_EN)

//
// Peripheral and unused pins not requiring other setup.
//
#define MC_CAN_RXD1     ::PeripheralPin(PORTE_regs, ::_Pin::PortE_MC_CAN_RXD1, 5)
#define MC_CAN_RXD2     ::PeripheralPin(PORTA_regs, ::_Pin::PortA_MC_CAN_RXD2, 3)
#define MC_CAN_TXD1     ::PeripheralPin(PORTE_regs, ::_Pin::PortE_MC_CAN_TXD1, 5)
#define MC_CAN_TXD2     ::PeripheralPin(PORTA_regs, ::_Pin::PortA_MC_CAN_TXD2, 3)
#define MC_SCI_RXD      ::PeripheralPin(PORTA_regs, ::_Pin::PortA_MC_SCI_RXD, 2)
#define MC_SCI_TXD      ::PeripheralPin(PORTA_regs, ::_Pin::PortA_MC_SCI_TXD, 2)
#define Pin74           ::PeripheralPin(PORTE_regs, ::_Pin::PortE_Pin74, 0)
#define Pin82           ::PeripheralPin(PORTE_regs, ::_Pin::PortE_Pin82, 0)
#define WD              ::PeripheralPin(PORTE_regs, ::_Pin::PortE_WD, 0)

//
// Internal analog pins.
//
#define DI_AI_INA_OUT0  ::AnalogPin(PORTC_regs, ::_Pin::PortC_DI_AI_INA_OUT0)
#define DI_AI_INA_OUT1  ::AnalogPin(PORTC_regs, ::_Pin::PortC_DI_AI_INA_OUT1)
#define DI_AI_INA_OUT2  ::AnalogPin(PORTC_regs, ::_Pin::PortC_DI_AI_INA_OUT2)
#define DI_AI_INA_OUT3  ::AnalogPin(PORTC_regs, ::_Pin::PortC_DI_AI_INA_OUT3)
#define DI_AI_INA_OUT4  ::AnalogPin(PORTB_regs, ::_Pin::PortB_DI_AI_INA_OUT4)
#define DI_AI_INA_OUT5  ::AnalogPin(PORTC_regs, ::_Pin::PortC_DI_AI_INA_OUT5)
#define DI_AI_INA_OUT6  ::AnalogPin(PORTC_regs, ::_Pin::PortC_DI_AI_INA_OUT6)
#define DI_AI_INA_OUT7  ::AnalogPin(PORTB_regs, ::_Pin::PortB_DI_AI_INA_OUT7)
#define DI_AI_KL30_1    ::AnalogPin(PORTC_regs, ::_Pin::PortC_DI_AI_KL30_1)
#define DI_AI_KL30_2    ::AnalogPin(PORTC_regs, ::_Pin::PortC_DI_AI_KL30_2)
#define DI_AI_OUT0      ::AnalogPin(PORTE_regs, ::_Pin::PortE_DI_AI_OUT0)
#define DI_AI_OUT1      ::AnalogPin(PORTA_regs, ::_Pin::PortA_DI_AI_OUT1)
#define DI_AI_OUT2      ::AnalogPin(PORTA_regs, ::_Pin::PortA_DI_AI_OUT2)
#define DI_AI_OUT3      ::AnalogPin(PORTA_regs, ::_Pin::PortA_DI_AI_OUT3)
#define DI_AI_OUT4      ::AnalogPin(PORTA_regs, ::_Pin::PortA_DI_AI_OUT4)
#define DI_AI_OUT5      ::AnalogPin(PORTD_regs, ::_Pin::PortD_DI_AI_OUT5)
#define DI_AI_OUT6      ::AnalogPin(PORTA_regs, ::_Pin::PortA_DI_AI_OUT6)
#define DI_AI_OUT7      ::AnalogPin(PORTA_regs, ::_Pin::PortA_DI_AI_OUT7)
#define DI_AI_SNS1      ::AnalogPin(PORTB_regs, ::_Pin::PortB_DI_AI_SNS1)
#define DI_AI_SNS2      ::AnalogPin(PORTB_regs, ::_Pin::PortB_DI_AI_SNS2)
#define DI_AI_SNS3      ::AnalogPin(PORTD_regs, ::_Pin::PortD_DI_AI_SNS3)
#define DI_AI_SNS4      ::AnalogPin(PORTB_regs, ::_Pin::PortB_DI_AI_SNS4)
#define DI_AI_VARIANTE  ::AnalogPin(PORTC_regs, ::_Pin::PortC_DI_AI_VARIANTE)
#define DI_AI_VREF      ::AnalogPin(PORTD_regs, ::_Pin::PortD_DI_AI_VREF)

//
// Peripheral pins on hold waiting for function implementation.
//
#define MC_FREQ_A_IN0   ::PeripheralPin(PORTC_regs, ::_Pin::PortC_MC_FREQ_A_IN0, 2)
#define MC_FREQ_A_IN1   ::PeripheralPin(PORTC_regs, ::_Pin::PortC_MC_FREQ_A_IN1, 2)
#define MC_FREQ_A_IN2   ::PeripheralPin(PORTC_regs, ::_Pin::PortC_MC_FREQ_A_IN2, 2)
#define MC_FREQ_A_IN3   ::PeripheralPin(PORTC_regs, ::_Pin::PortC_MC_FREQ_A_IN3, 2)
#define MC_FREQ_A_IN4   ::PeripheralPin(PORTB_regs, ::_Pin::PortB_MC_FREQ_A_IN4, 2)
#define MC_FREQ_A_IN5   ::PeripheralPin(PORTB_regs, ::_Pin::PortB_MC_FREQ_A_IN5, 2)

//
// External input pins.
//
#define DI_AI_A_IN0     ::InputPin(PTB_regs, PORTB_regs, ::_Pin::PortB_DI_AI_A_IN0, PU_A_IN0, PD_A_IN0, DO_RS0)
#define DI_AI_A_IN1     ::InputPin(PTB_regs, PORTB_regs, ::_Pin::PortB_DI_AI_A_IN1, PU_A_IN1, PD_A_IN1, DO_RS1)
#define DI_AI_A_IN2     ::InputPin(PTA_regs, PORTA_regs, ::_Pin::PortA_DI_AI_A_IN2, PU_A_IN2, PD_A_IN2, DO_RS2)
#define DI_AI_A_IN3     ::InputPin(PTA_regs, PORTA_regs, ::_Pin::PortA_DI_AI_A_IN3, PU_A_IN3, PD_A_IN3, DO_RS3)
#define DI_AI_A_IN4     ::InputPin(PTB_regs, PORTB_regs, ::_Pin::PortB_DI_AI_A_IN4, PU_A_IN4, PD_A_IN4, DO_RS4)
#define DI_AI_A_IN5     ::InputPin(PTB_regs, PORTB_regs, ::_Pin::PortB_DI_AI_A_IN5, PU_A_IN5, PD_A_IN5, DO_RS5)
#define DI_AI_ID        ::AnalogPin(PORTC_regs, ::_Pin::PortC_DI_AI_ID)
#define DI_INTERFACE2_A ::GPIOIn(PTD_regs, PORTD_regs, ::_Pin::PortD_DI_INTERFACE2_A)
#define DI_INTERFACE2_B ::GPIOIn(PTD_regs, PORTD_regs, ::_Pin::PortD_DI_INTERFACE2_B)
