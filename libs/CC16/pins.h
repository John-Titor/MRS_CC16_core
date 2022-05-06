// Common pin and GPIO functionality.
//

#pragma once

#include <stdint.h>
#include <CMSIS/S32K144.h>

struct ExpanderPin
{
    uint8_t             _index;

    void set(bool v)         const;
    void set()               const { set(true); }
    void clear()             const { set(false); }
    void operator = (bool v) const { set(v); }

    static void         reset();
    static uint16_t     _state;
    static void         update(void);
};

extern const ExpanderPin DCDC_8V5;
extern const ExpanderPin DCDC_10V;
extern const ExpanderPin PD_A_IN5;
extern const ExpanderPin PD_A_IN4;
extern const ExpanderPin PD_A_IN3;
extern const ExpanderPin PD_A_IN2;
extern const ExpanderPin PD_A_IN1;
extern const ExpanderPin PD_A_IN0;
extern const ExpanderPin PU_A_IN5;
extern const ExpanderPin PU_A_IN4;
extern const ExpanderPin PU_A_IN3;
extern const ExpanderPin PU_A_IN2;
extern const ExpanderPin PU_A_IN1;
extern const ExpanderPin PU_A_IN0;

namespace Pins
{
    class _Pin
    {
    public:
        constexpr _Pin(volatile PORT_regs &cfg,
                       uint32_t index) :
            _cfg    { cfg },
            _mask   { 1U << index }
        {}

    protected:
        static const uint8_t    func_analog = 0;
        static const uint8_t    func_gpio = 1;

        volatile PORT_regs  &_cfg;
        const uint32_t      _mask;

        void configure(uint32_t function) volatile {
            if (_mask < 0x10000) {
                _cfg.GPCLR = (_mask << 16) | (function << 8);
            } else {
                _cfg.GPCHR = _mask | function << 8;
            }
        }
    };

    class _GPIO : public _Pin
    {
    public:
        constexpr _GPIO(volatile PT_regs &io,
                        volatile PORT_regs &cfg,
                        uint32_t index) :
            _Pin(cfg, index),
            _io { io }
        {}

    protected:
        static const bool           mode_output = true;
        static const bool           mode_input = false;

        volatile PT_regs    &_io;

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
        constexpr GPIOOut(volatile PT_regs &io,
                          volatile PORT_regs &cfg,
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
        constexpr GPIOIn(volatile PT_regs &io,
                         volatile PORT_regs &cfg,
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
        constexpr AnalogPin(volatile PORT_regs &cfg,
                            uint32_t index) :
            _Pin(cfg, index)
        {}

        void configure(void)        { _Pin::configure(func_analog); }
    };

    class PeripheralPin : public _Pin
    {
    public:
        constexpr PeripheralPin(volatile PORT_regs &cfg,
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
        constexpr InputPin(volatile PT_regs &io,
                           volatile PORT_regs &cfg,
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
} // namespace Pin


//
// Internal GPIO pins.
//
#define CAN_EN1         ::Pins::GPIOOut(PTA, PORTA, ::Pins::PortA::_CAN_EN1, 1)
#define CAN_EN2         ::Pins::GPIOOut(PTE, PORTE, ::Pins::PortE::_CAN_EN2, 1)
#define CAN_ERR1        ::Pins::GPIOIn(PTE, PORTE, ::Pins::PortE::_CAN_ERR1)
#define CAN_ERR2        ::Pins::GPIOIn(PTE, PORTE, ::Pins::PortE::_CAN_ERR2)
#define CAN_STB1        ::Pins::GPIOOut(PTE, PORTE, ::Pins::PortE::_CAN_STB1, 1)
#define CAN_STB2        ::Pins::GPIOOut(PTE, PORTE, ::Pins::PortE::_CAN_STB2, 1)
#define CAN_WAKE1       ::Pins::GPIOOut(PTA, PORTA, ::Pins::PortA::_CAN_WAKE1, 1)
#define CAN_WAKE2       ::Pins::GPIOOut(PTE, PORTE, ::Pins::PortE::_CAN_WAKE2, 1)
#define DI_KL15         ::Pins::GPIOIn(PTD, PORTD, ::Pins::PortD::_DI_KL15)
#define DI_PGD          ::Pins::GPIOIn(PTA, PORTA, ::Pins::PortA::_DI_PGD)
#define DO_CS_HSD1      ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_CS_HSD1, 1)
#define DO_CS_HSD2      ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_CS_HSD2, 1)
#define DO_POWER        ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_POWER, 1)
#define DO_RS0          ::Pins::GPIOOut(PTC, PORTC, ::Pins::PortC::_DO_RS0)
#define DO_RS1          ::Pins::GPIOOut(PTE, PORTE, ::Pins::PortE::_DO_RS1)
#define DO_RS2          ::Pins::GPIOOut(PTB, PORTB, ::Pins::PortB::_DO_RS2)
#define DO_RS3          ::Pins::GPIOOut(PTC, PORTC, ::Pins::PortC::_DO_RS3)
#define DO_RS4          ::Pins::GPIOOut(PTB, PORTB, ::Pins::PortB::_DO_RS4)
#define DO_RS5          ::Pins::GPIOOut(PTB, PORTB, ::Pins::PortB::_DO_RS5)
#define DO_SHIFT_IN_DS  ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_SHIFT_IN_DS)
#define DO_SHIFT_MR     ::Pins::GPIOOut(PTE, PORTE, ::Pins::PortE::_DO_SHIFT_MR)
#define DO_SHIFT_OE     ::Pins::GPIOOut(PTE, PORTE, ::Pins::PortE::_DO_SHIFT_OE)
#define DO_SHIFT_SH_CP  ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_SHIFT_SH_CP)
#define DO_SHIFT_ST_CP  ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_SHIFT_ST_CP)
#define DO_VREF_EN      ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_VREF_EN)
#define LIN_EN          ::Pins::GPIOOut(PTE, PORTE, ::Pins::PortE::_LIN_EN)

//
// Peripheral and unused pins not requiring other setup.
//
#define MC_CAN_RXD1     ::Pins::PeripheralPin(PORTE, ::Pins::PortE::_MC_CAN_RXD1, 5)
#define MC_CAN_RXD2     ::Pins::PeripheralPin(PORTA, ::Pins::PortA::_MC_CAN_RXD2, 3)
#define MC_CAN_TXD1     ::Pins::PeripheralPin(PORTE, ::Pins::PortE::_MC_CAN_TXD1, 5)
#define MC_CAN_TXD2     ::Pins::PeripheralPin(PORTA, ::Pins::PortA::_MC_CAN_TXD2, 3)
#define MC_SCI_RXD      ::Pins::PeripheralPin(PORTA, ::Pins::PortA::_MC_SCI_RXD, 2)
#define MC_SCI_TXD      ::Pins::PeripheralPin(PORTA, ::Pins::PortA::_MC_SCI_TXD, 2)
#define Pin74           ::Pins::PeripheralPin(PORTE, ::Pins::PortE::_Pin74, 0)
#define Pin82           ::Pins::PeripheralPin(PORTE, ::Pins::PortE::_Pin82, 0)
#define WD              ::Pins::PeripheralPin(PORTE, ::Pins::PortE::_WD, 0)

//
// Internal analog pins.
//
#define DI_AI_INA_OUT0  ::Pins::AnalogPin(PORTC, ::Pins::PortC::_DI_AI_INA_OUT0)
#define DI_AI_INA_OUT1  ::Pins::AnalogPin(PORTC, ::Pins::PortC::_DI_AI_INA_OUT1)
#define DI_AI_INA_OUT2  ::Pins::AnalogPin(PORTC, ::Pins::PortC::_DI_AI_INA_OUT2)
#define DI_AI_INA_OUT3  ::Pins::AnalogPin(PORTC, ::Pins::PortC::_DI_AI_INA_OUT3)
#define DI_AI_INA_OUT4  ::Pins::AnalogPin(PORTB, ::Pins::PortB::_DI_AI_INA_OUT4)
#define DI_AI_INA_OUT5  ::Pins::AnalogPin(PORTC, ::Pins::PortC::_DI_AI_INA_OUT5)
#define DI_AI_INA_OUT6  ::Pins::AnalogPin(PORTC, ::Pins::PortC::_DI_AI_INA_OUT6)
#define DI_AI_INA_OUT7  ::Pins::AnalogPin(PORTB, ::Pins::PortB::_DI_AI_INA_OUT7)
#define DI_AI_KL30_1    ::Pins::AnalogPin(PORTC, ::Pins::PortC::_DI_AI_KL30_1)
#define DI_AI_KL30_2    ::Pins::AnalogPin(PORTC, ::Pins::PortC::_DI_AI_KL30_2)
#define DI_AI_OUT0      ::Pins::AnalogPin(PORTE, ::Pins::PortE::_DI_AI_OUT0)
#define DI_AI_OUT1      ::Pins::AnalogPin(PORTA, ::Pins::PortA::_DI_AI_OUT1)
#define DI_AI_OUT2      ::Pins::AnalogPin(PORTA, ::Pins::PortA::_DI_AI_OUT2)
#define DI_AI_OUT3      ::Pins::AnalogPin(PORTA, ::Pins::PortA::_DI_AI_OUT3)
#define DI_AI_OUT4      ::Pins::AnalogPin(PORTA, ::Pins::PortA::_DI_AI_OUT4)
#define DI_AI_OUT5      ::Pins::AnalogPin(PORTD, ::Pins::PortD::_DI_AI_OUT5)
#define DI_AI_OUT6      ::Pins::AnalogPin(PORTA, ::Pins::PortA::_DI_AI_OUT6)
#define DI_AI_OUT7      ::Pins::AnalogPin(PORTA, ::Pins::PortA::_DI_AI_OUT7)
#define DI_AI_SNS1      ::Pins::AnalogPin(PORTB, ::Pins::PortB::_DI_AI_SNS1)
#define DI_AI_SNS2      ::Pins::AnalogPin(PORTB, ::Pins::PortB::_DI_AI_SNS2)
#define DI_AI_SNS3      ::Pins::AnalogPin(PORTD, ::Pins::PortD::_DI_AI_SNS3)
#define DI_AI_SNS4      ::Pins::AnalogPin(PORTB, ::Pins::PortB::_DI_AI_SNS4)
#define DI_AI_VARIANTE  ::Pins::AnalogPin(PORTC, ::Pins::PortC::_DI_AI_VARIANTE)
#define DI_AI_VREF      ::Pins::AnalogPin(PORTD, ::Pins::PortD::_DI_AI_VREF)

//
// Peripheral pins on hold waiting for function implementation.
//
#define MC_FREQ_A_IN0   ::Pins::PeripheralPin(PORTC, ::Pins::PortC::_MC_FREQ_A_IN0, 2)
#define MC_FREQ_A_IN1   ::Pins::PeripheralPin(PORTC, ::Pins::PortC::_MC_FREQ_A_IN1, 2)
#define MC_FREQ_A_IN2   ::Pins::PeripheralPin(PORTC, ::Pins::PortC::_MC_FREQ_A_IN2, 2)
#define MC_FREQ_A_IN3   ::Pins::PeripheralPin(PORTC, ::Pins::PortC::_MC_FREQ_A_IN3, 2)
#define MC_FREQ_A_IN4   ::Pins::PeripheralPin(PORTB, ::Pins::PortB::_MC_FREQ_A_IN4, 2)
#define MC_FREQ_A_IN5   ::Pins::PeripheralPin(PORTB, ::Pins::PortB::_MC_FREQ_A_IN5, 2)

//
// External input pins.
//
#define DI_AI_A_IN0     ::Pins::InputPin(PTB, PORTB, ::Pins::PortB::_DI_AI_A_IN0, PU_A_IN0, PD_A_IN0, DO_RS0)
#define DI_AI_A_IN1     ::Pins::InputPin(PTB, PORTB, ::Pins::PortB::_DI_AI_A_IN1, PU_A_IN1, PD_A_IN1, DO_RS1)
#define DI_AI_A_IN2     ::Pins::InputPin(PTA, PORTA, ::Pins::PortA::_DI_AI_A_IN2, PU_A_IN2, PD_A_IN2, DO_RS2)
#define DI_AI_A_IN3     ::Pins::InputPin(PTA, PORTA, ::Pins::PortA::_DI_AI_A_IN3, PU_A_IN3, PD_A_IN3, DO_RS3)
#define DI_AI_A_IN4     ::Pins::InputPin(PTB, PORTB, ::Pins::PortB::_DI_AI_A_IN4, PU_A_IN4, PD_A_IN4, DO_RS4)
#define DI_AI_A_IN5     ::Pins::InputPin(PTB, PORTB, ::Pins::PortB::_DI_AI_A_IN5, PU_A_IN5, PD_A_IN5, DO_RS5)
#define DI_AI_ID        ::Pins::AnalogPin(PORTC, ::Pins::PortC::_DI_AI_ID)
#define DI_INTERFACE2_A ::Pins::GPIOIn(PTD, PORTD, ::Pins::PortD::_DI_INTERFACE2_A)
#define DI_INTERFACE2_B ::Pins::GPIOIn(PTD, PORTD, ::Pins::PortD::_DI_INTERFACE2_B)
