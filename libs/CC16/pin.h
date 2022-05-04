// Common pin and GPIO functionality.
//

#pragma once

#include <stdint.h>
#include <CMSIS/S32K144.h>

namespace Pin
{

class _Pin
{
public:
    constexpr _Pin(__IO void *cfgbase,
                   uint8_t index) :
        _cfgh   { ((PORTA_Type *)cfgbase)->PORTA_GPCHR },
        _cfgl   { ((PORTA_Type *)cfgbase)->PORTA_GPCLR },
        _mask   { 1U << index }
    {}

protected:
    static const uint8_t    func_analog = 0;
    static const uint8_t    func_gpio = 1;

    __IOM uint32_t  &_cfgh;
    __IOM uint32_t  &_cfgl;
    const uint32_t  _mask;

    void configure(uint8_t function) volatile {
        if (_mask < 0x10000) {
            _cfgl = (_mask << 16) | (function << 8);
        } else {
            _cfgh = _mask | (function << 8);
        }
    }
};

class _GPIO : public _Pin
{
public:
    constexpr _GPIO(__IO void *iobase,
                    __IO void *cfgbase,
                    uint8_t index) :
        _Pin(cfgbase, index),
        _set        { ((PTA_Type *)iobase)->GPIOA_PSOR },
        _clear      { ((PTA_Type *)iobase)->GPIOA_PCOR },
        _toggle     { ((PTA_Type *)iobase)->GPIOA_PTOR },
        _data       { ((PTA_Type *)iobase)->GPIOA_PDOR },
        _direction  { ((PTA_Type *)iobase)->GPIOA_PDDR }
    {}

protected:
    static const bool           mode_output = true;
    static const bool           mode_input = false;

    __IOM uint32_t  &_set;
    __IOM uint32_t  &_clear;
    __IOM uint32_t  &_toggle;
    __IOM uint32_t  &_data;
    __IOM uint32_t  &_direction;

    void configure(bool mode)
    {
        if (mode == mode_output) {
            _direction |= _mask;
        } else {
            _direction &= ~_mask;
        }
        _Pin::configure(func_gpio); 
    }
};

class GPIOOut : public _GPIO
{
public:
    constexpr GPIOOut(__IO void *iobase,
                      __IO void *cfgbase,
                      uint8_t index,
                      bool initial=false) :
        _GPIO(iobase, cfgbase, index),
        _initial { initial }
    {}

    void set(void)              volatile { _set = _mask; }
    void set(bool v)            volatile { if (v) set(); else clear(); }
    void clear(void)            volatile { _clear = _mask; }
    void toggle(void)           volatile { _toggle = _mask; }
    bool get(void)              volatile { return _data & _mask; }
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
    constexpr GPIOIn(__IO void *iobase,
                     __IO void *cfgbase,
                     uint8_t index) :
        _GPIO(iobase, cfgbase, index)
    {}

    bool get(void)              volatile { return _data & _mask; }
    bool operator()(void)       volatile { return get(); }
    void configure()            { _GPIO::configure(mode_input); }
};

class AnalogPin : public _Pin
{
public:
    constexpr AnalogPin(__IO void *cfgbase,
                        uint8_t index) :
        _Pin(cfgbase, index)
    {}

    void configure(void)        { _Pin::configure(func_analog); }
};

class PeripheralPin : public _Pin
{
public:
    constexpr PeripheralPin(__IO void *cfgbase,
                            uint8_t index,
                            uint8_t function) :
        _Pin(cfgbase, index),
        _function               { function }
    {}

    void configure(void)        { _Pin::configure(_function); }

private:
    const uint8_t   _function;
};

//
// Pin indices in port space
//
typedef enum
{
    _DI_AI_OUT1,
    _DI_AI_OUT4,
    _DI_AI_OUT6,
    _DI_AI_OUT7,
    _MC_JTAG_TMS,
    _MC_JTAG_TRST,
    _DI_AI_A_IN3,
    _DI_AI_A_IN2,
    _MC_SCI_RXD,
    _MC_SCI_TXD,
    _MC_JTAG_TDO,
    _CAN_EN1,
    _MC_CAN_RXD2,
    _MC_CAN_TXD2,
    _CAN_WAKE1,
    _DI_AI_OUT2,
    _DI_AI_OUT3,
    _DI_PGD,
} PortA;

typedef enum 
{
    _DI_AI_A_IN1,
    _DI_AI_A_IN0,
    _DI_AI_INA_OUT4,
    _DI_AI_INA_OUT7,
    _DO_HSD1_OUT1,
    _DO_HSD1_OUT3,
    _XTAL,
    _EXTAL,
    _DO_RS2,
    _MC_FREQ_A_IN4,
    _MC_FREQ_A_IN5,
    _DO_RS4,
    _DI_AI_SNS4,
    _DI_AI_SNS1,
    _DI_AI_SNS2,
    _DI_AI_A_IN5,
    _DI_AI_A_IN4,
    _DO_RS5,
} PortB;

typedef enum 
{
    _DI_AI_INA_OUT3,
    _DI_AI_INA_OUT2,
    _DI_AI_KL30_1,
    _DI_AI_KL30_2,
    _MC_JTAG_TCLK,
    _MC_JTAG_TDI,
    _DI_AI_VARIANTE,
    _DI_AI_ID,
    _DO_RS3,
    _DO_RS0,
    _MC_FREQ_A_IN0,
    _MC_FREQ_A_IN1,
    _MC_FREQ_A_IN2,
    _MC_FREQ_A_IN3,
    _DI_AI_INA_OUT5,
    _DI_AI_INA_OUT6,
    _DI_AI_INA_OUT0,
    _DI_AI_INA_OUT1,
} PortC;

typedef enum 
{
    _DO_SHIFT_SH_CP,
    _DO_SHIFT_ST_CP,
    _DI_AI_OUT5,
    _DI_AI_VREF,
    _DI_AI_SNS3,
    _DO_HSD2_OUT4,
    _DO_SHIFT_IN_DS,
    _DI_INTERFACE2_A,
    _DI_INTERFACE2_B,
    _DO_HSD2_OUT6,
    _DO_VREF_EN,
    _DO_CS_HSD2,
    _DO_HSD2_OUT5,
    _DI_KL15,
    _DO_HSD1_OUT0,
    _DO_POWER,
    _DO_HSD2_OUT7,
    _DO_CS_HSD1,
} PortD;

typedef enum
{
    _CAN_ERR1,
    _CAN_STB1,
    _Pin74,
    _CAN_STB2,
    _MC_CAN_RXD1,
    _MC_CAN_TXD1,
    _DI_AI_OUT0,
    _DO_RS1,
    _DO_HSD1_OUT2,
    _LIN_EN,
    _Pin82,
    _WD,
    _CAN_EN2,
    _CAN_ERR2,
    _CAN_WAKE2,
    _DO_SHIFT_OE,
    _DO_SHIFT_MR,
} PortE;

typedef enum
{
    _DCDC_8V5,
    _DCDC_10V,
    _PD_A_IN5,
    _PD_A_IN4,
    _PD_A_IN3,
    _PD_A_IN2,
    _PD_A_IN1,
    _PD_A_IN0,
    _PU_A_IN5,
    _PU_A_IN4,
    _PU_A_IN3,
    _PU_A_IN2,
    _PU_A_IN1,
    _PU_A_IN0,
    _Max,
} PortX;
} // namespace GPIO

namespace ExpanderPins
{
    void reset(void);
    void set(uint8_t index, bool state);
}

class ExpanderPin
{
public:
    constexpr ExpanderPin(uint8_t index) :
        _index { index }
    {}

    void set(bool v)    { ExpanderPins::set(_index, v); }
    void set()          { set(true); }
    void clear()        { set(false); }
    void operator = (bool v) { set(v); }

private:
    const uint8_t   _index;
};

//
// GPIO pins.
//
#define CAN_EN1         ::Pin::GPIOOut(PTA, PORTA, ::Pin::PortA::_CAN_EN1, 1)
#define CAN_EN2         ::Pin::GPIOOut(PTE, PORTE, ::Pin::PortE::_CAN_EN2, 1)
#define CAN_ERR1        ::Pin::GPIOIn(PTE, PORTE, ::Pin::PortE::_CAN_ERR1)
#define CAN_ERR2        ::Pin::GPIOIn(PTE, PORTE, ::Pin::PortE::_CAN_ERR2)
#define CAN_STB1        ::Pin::GPIOOut(PTE, PORTE, ::Pin::PortE::_CAN_STB1, 1)
#define CAN_STB2        ::Pin::GPIOOut(PTE, PORTE, ::Pin::PortE::_CAN_STB2, 1)
#define CAN_WAKE1       ::Pin::GPIOOut(PTA, PORTA, ::Pin::PortA::_CAN_WAKE1, 1)
#define CAN_WAKE2       ::Pin::GPIOOut(PTE, PORTE, ::Pin::PortE::_CAN_WAKE2, 1)
#define DI_INTERFACE2_A ::Pin::GPIOIn(PTD, PORTD, ::Pin::PortD::_DI_INTERFACE2_A)
#define DI_INTERFACE2_B ::Pin::GPIOIn(PTD, PORTD, ::Pin::PortD::_DI_INTERFACE2_B)
#define DI_KL15         ::Pin::GPIOIn(PTD, PORTD, ::Pin::PortD::_DI_KL15)
#define DI_PGD          ::Pin::GPIOIn(PTA, PORTA, ::Pin::PortA::_DI_PGD)
#define DO_CS_HSD1      ::Pin::GPIOOut(PTD, PORTD, ::Pin::PortD::_DO_CS_HSD1)
#define DO_CS_HSD2      ::Pin::GPIOOut(PTD, PORTD, ::Pin::PortD::_DO_CS_HSD2)
#define DO_POWER        ::Pin::GPIOOut(PTD, PORTD, ::Pin::PortD::_DO_POWER, 1)
#define DO_RS0          ::Pin::GPIOOut(PTC, PORTC, ::Pin::PortC::_DO_RS0)
#define DO_RS1          ::Pin::GPIOOut(PTE, PORTE, ::Pin::PortE::_DO_RS1)
#define DO_RS2          ::Pin::GPIOOut(PTB, PORTB, ::Pin::PortB::_DO_RS2)
#define DO_RS3          ::Pin::GPIOOut(PTC, PORTC, ::Pin::PortC::_DO_RS3)
#define DO_RS4          ::Pin::GPIOOut(PTB, PORTB, ::Pin::PortB::_DO_RS4)
#define DO_RS5          ::Pin::GPIOOut(PTB, PORTB, ::Pin::PortB::_DO_RS5)
#define DO_SHIFT_IN_DS  ::Pin::GPIOOut(PTD, PORTD, ::Pin::PortD::_DO_SHIFT_IN_DS)
#define DO_SHIFT_MR     ::Pin::GPIOOut(PTE, PORTE, ::Pin::PortE::_DO_SHIFT_MR)
#define DO_SHIFT_OE     ::Pin::GPIOOut(PTE, PORTE, ::Pin::PortE::_DO_SHIFT_OE)
#define DO_SHIFT_SH_CP  ::Pin::GPIOOut(PTD, PORTD, ::Pin::PortD::_DO_SHIFT_SH_CP)
#define DO_SHIFT_ST_CP  ::Pin::GPIOOut(PTD, PORTD, ::Pin::PortD::_DO_SHIFT_ST_CP)
#define DO_VREF_EN      ::Pin::GPIOOut(PTD, PORTD, ::Pin::PortD::_DO_VREF_EN)
#define LIN_EN          ::Pin::GPIOOut(PTE, PORTE, ::Pin::PortE::_LIN_EN)

//
// Peripheral and unused pins not requiring other setup.
//
#define MC_CAN_RXD1     ::Pin::PeripheralPin(PORTE, ::Pin::PortE::_MC_CAN_RXD1, 5)
#define MC_CAN_RXD2     ::Pin::PeripheralPin(PORTA, ::Pin::PortA::_MC_CAN_RXD2, 3)
#define MC_CAN_TXD1     ::Pin::PeripheralPin(PORTE, ::Pin::PortE::_MC_CAN_TXD1, 5)
#define MC_CAN_TXD2     ::Pin::PeripheralPin(PORTA, ::Pin::PortA::_MC_CAN_TXD2, 3)
#define MC_SCI_RXD      ::Pin::PeripheralPin(PORTA, ::Pin::PortA::_MC_SCI_RXD, 2)
#define MC_SCI_TXD      ::Pin::PeripheralPin(PORTA, ::Pin::PortA::_MC_SCI_TXD, 2)
#define Pin74           ::Pin::PeripheralPin(PORTE, ::Pin::PortE::_Pin74, 0)
#define Pin82           ::Pin::PeripheralPin(PORTE, ::Pin::PortE::_Pin82, 0)
#define WD              ::Pin::PeripheralPin(PORTE, ::Pin::PortE::_WD, 0)

//
// Analog input pins.
//
#define DI_AI_A_IN0     ::Pin::AnalogPin(PORTB, ::Pin::PortB::_DI_AI_A_IN0)
#define DI_AI_A_IN1     ::Pin::AnalogPin(PORTB, ::Pin::PortB::_DI_AI_A_IN1)
#define DI_AI_A_IN2     ::Pin::AnalogPin(PORTA, ::Pin::PortA::_DI_AI_A_IN2)
#define DI_AI_A_IN3     ::Pin::AnalogPin(PORTA, ::Pin::PortA::_DI_AI_A_IN3)
#define DI_AI_A_IN4     ::Pin::AnalogPin(PORTB, ::Pin::PortB::_DI_AI_A_IN4)
#define DI_AI_A_IN5     ::Pin::AnalogPin(PORTB, ::Pin::PortB::_DI_AI_A_IN5)
#define DI_AI_ID        ::Pin::AnalogPin(PORTC, ::Pin::PortC::_DI_AI_ID)
#define DI_AI_INA_OUT0  ::Pin::AnalogPin(PORTC, ::Pin::PortC::_DI_AI_INA_OUT0)
#define DI_AI_INA_OUT1  ::Pin::AnalogPin(PORTC, ::Pin::PortC::_DI_AI_INA_OUT1)
#define DI_AI_INA_OUT2  ::Pin::AnalogPin(PORTC, ::Pin::PortC::_DI_AI_INA_OUT2)
#define DI_AI_INA_OUT3  ::Pin::AnalogPin(PORTC, ::Pin::PortC::_DI_AI_INA_OUT3)
#define DI_AI_INA_OUT4  ::Pin::AnalogPin(PORTB, ::Pin::PortB::_DI_AI_INA_OUT4)
#define DI_AI_INA_OUT5  ::Pin::AnalogPin(PORTC, ::Pin::PortC::_DI_AI_INA_OUT5)
#define DI_AI_INA_OUT6  ::Pin::AnalogPin(PORTC, ::Pin::PortC::_DI_AI_INA_OUT6)
#define DI_AI_INA_OUT7  ::Pin::AnalogPin(PORTB, ::Pin::PortB::_DI_AI_INA_OUT7)
#define DI_AI_KL30_1    ::Pin::AnalogPin(PORTC, ::Pin::PortC::_DI_AI_KL30_1)
#define DI_AI_KL30_2    ::Pin::AnalogPin(PORTC, ::Pin::PortC::_DI_AI_KL30_2)
#define DI_AI_OUT0      ::Pin::AnalogPin(PORTE, ::Pin::PortE::_DI_AI_OUT0)
#define DI_AI_OUT1      ::Pin::AnalogPin(PORTA, ::Pin::PortA::_DI_AI_OUT1)
#define DI_AI_OUT2      ::Pin::AnalogPin(PORTA, ::Pin::PortA::_DI_AI_OUT2)
#define DI_AI_OUT3      ::Pin::AnalogPin(PORTA, ::Pin::PortA::_DI_AI_OUT3)
#define DI_AI_OUT4      ::Pin::AnalogPin(PORTA, ::Pin::PortA::_DI_AI_OUT4)
#define DI_AI_OUT5      ::Pin::AnalogPin(PORTD, ::Pin::PortD::_DI_AI_OUT5)
#define DI_AI_OUT6      ::Pin::AnalogPin(PORTA, ::Pin::PortA::_DI_AI_OUT6)
#define DI_AI_OUT7      ::Pin::AnalogPin(PORTA, ::Pin::PortA::_DI_AI_OUT7)
#define DI_AI_SNS1      ::Pin::AnalogPin(PORTB, ::Pin::PortB::_DI_AI_SNS1)
#define DI_AI_SNS2      ::Pin::AnalogPin(PORTB, ::Pin::PortB::_DI_AI_SNS2)
#define DI_AI_SNS3      ::Pin::AnalogPin(PORTD, ::Pin::PortD::_DI_AI_SNS3)
#define DI_AI_SNS4      ::Pin::AnalogPin(PORTB, ::Pin::PortB::_DI_AI_SNS4)
#define DI_AI_VARIANTE  ::Pin::AnalogPin(PORTC, ::Pin::PortC::_DI_AI_VARIANTE)
#define DI_AI_VREF      ::Pin::AnalogPin(PORTD, ::Pin::PortD::_DI_AI_VREF)

//
// Peripheral pins on hold waiting for function implementation.
//
#define MC_FREQ_A_IN0   ::Pin::PeripheralPin(PORTC, ::Pin::PortC::_MC_FREQ_A_IN0, 2)
#define MC_FREQ_A_IN1   ::Pin::PeripheralPin(PORTC, ::Pin::PortC::_MC_FREQ_A_IN1, 2)
#define MC_FREQ_A_IN2   ::Pin::PeripheralPin(PORTC, ::Pin::PortC::_MC_FREQ_A_IN2, 2)
#define MC_FREQ_A_IN3   ::Pin::PeripheralPin(PORTC, ::Pin::PortC::_MC_FREQ_A_IN3, 2)
#define MC_FREQ_A_IN4   ::Pin::PeripheralPin(PORTB, ::Pin::PortB::_MC_FREQ_A_IN4, 2)
#define MC_FREQ_A_IN5   ::Pin::PeripheralPin(PORTB, ::Pin::PortB::_MC_FREQ_A_IN5, 2)

//
// Virtual pins
//
#define DCDC_8V5        ::ExpanderPin::Pin(::Pin::PortX::DCDC_8V5)
#define DCDC_10V        ::ExpanderPin::Pin(::Pin::PortX::DCDC_10V)
#define PD_A_IN5        ::ExpanderPin::Pin(::Pin::PortX::PD_A_IN5)
#define PD_A_IN4        ::ExpanderPin::Pin(::Pin::PortX::PD_A_IN4)
#define PD_A_IN3        ::ExpanderPin::Pin(::Pin::PortX::PD_A_IN3)
#define PD_A_IN2        ::ExpanderPin::Pin(::Pin::PortX::PD_A_IN2)
#define PD_A_IN1        ::ExpanderPin::Pin(::Pin::PortX::PD_A_IN1)
#define PD_A_IN0        ::ExpanderPin::Pin(::Pin::PortX::PD_A_IN0)
#define PU_A_IN5        ::ExpanderPin::Pin(::Pin::PortX::PU_A_IN5)
#define PU_A_IN4        ::ExpanderPin::Pin(::Pin::PortX::PU_A_IN4)
#define PU_A_IN3        ::ExpanderPin::Pin(::Pin::PortX::PU_A_IN3)
#define PU_A_IN2        ::ExpanderPin::Pin(::Pin::PortX::PU_A_IN2)
#define PU_A_IN1        ::ExpanderPin::Pin(::Pin::PortX::PU_A_IN1)
#define PU_A_IN0        ::ExpanderPin::Pin(::Pin::PortX::PU_A_IN0)
