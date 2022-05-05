// PWM output using FlexTimer 0/1/2
//

#pragma once
#include "pins.h"

#if 1
#define DO_HSD1_OUT0    ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_HSD1_OUT0, 1)
#define DO_HSD1_OUT1    ::Pins::GPIOOut(PTB, PORTB, ::Pins::PortB::_DO_HSD1_OUT1, 0)
#define DO_HSD1_OUT2    ::Pins::GPIOOut(PTE, PORTE, ::Pins::PortE::_DO_HSD1_OUT2, 0)
#define DO_HSD1_OUT3    ::Pins::GPIOOut(PTB, PORTB, ::Pins::PortB::_DO_HSD1_OUT3, 0)
#define DO_HSD2_OUT4    ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_HSD2_OUT4, 0)
#define DO_HSD2_OUT5    ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_HSD2_OUT5, 0)
#define DO_HSD2_OUT6    ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_HSD2_OUT6, 0)
#define DO_HSD2_OUT7    ::Pins::GPIOOut(PTD, PORTD, ::Pins::PortD::_DO_HSD2_OUT7, 0)
#else

namespace PWM
{
    class _FTM
    {
    public:
        constexpr _FTM(__IO void *regbase) :
            _reg { *(__IO FTM0_Type *)regbase }
        {}

        void configure()
        {
            _reg.FTM0_SC = 0x00ff0007;  // set CLKS=0, /128 prescale, all outputs
            _reg.FTM0_MODE = 0x04;      // set WPDIS
            _reg.FTM0_POL = 0;          // all natural polarity

            _reg.FTM0_MOD = 4899;       // ~128Hz period
            _reg.FTM0_CNTIN = 0;        // count from zero

            _reg.FTM0_C0SC = 0x28;      // Set ELSB and MSB
            _reg.FTM0_C1SC = 0x28;
            _reg.FTM0_C2SC = 0x28;
            _reg.FTM0_C3SC = 0x28;
            _reg.FTM0_C4SC = 0x28;
            _reg.FTM0_C5SC = 0x28;
            _reg.FTM0_C6SC = 0x28;
            _reg.FTM0_C7SC = 0x28;

            _reg.FTM0_C0V = 200;
            _reg.FTM0_C1V = 200;
            _reg.FTM0_C2V = 200;
            _reg.FTM0_C3V = 200;
            _reg.FTM0_C4V = 2000;
            _reg.FTM0_C5V = 200;
            _reg.FTM0_C6V = 200;
            _reg.FTM0_C7V = 200;

            _reg.FTM0_CNT = 0;

            _reg.FTM0_MODE |= 0x01;     // FTMEN=1
            _reg.FTM0_SYNCONF = 0xa0;   // SYNCMODE=1, SWWRBUF=1
            _reg.FTM0_MODE |= 0x08;     // PWMSYNC=1
            _reg.FTM0_SC = 0x00ff000f;  // Set PWMENn, CLKS=1, PS=7
        }

        void set_duty(uint8_t channel, uint8_t duty_percentage)
        {
            //uint32_t cnt = duty_percentage * 49;
            uint32_t cnt = 200;

            switch (channel) {
            case 0: _reg.FTM0_C0V = cnt; break;
            case 1: _reg.FTM0_C1V = cnt; break;
            case 2: _reg.FTM0_C2V = cnt; break;
            case 3: _reg.FTM0_C3V = cnt; break;
            case 4: _reg.FTM0_C4V = cnt; break;
            case 5: _reg.FTM0_C5V = cnt; break;
            case 6: _reg.FTM0_C6V = cnt; break;
            case 7: _reg.FTM0_C7V = cnt; break;
            }
    //        _reg.FTM0_SYNC = 0x80;      // SWSYNC=1
        }

    private:
        __IO FTM0_Type  &_reg;
    };

    class Pin : public ::Pins::PeripheralPin
    {
    public:
        constexpr Pin(__IO void *cfgbase, 
                      uint8_t index,
                      uint8_t function,
                      _FTM ftm,
                      uint8_t channel) :
            ::Pins::PeripheralPin(cfgbase, index, function),
            _ftm     { ftm },
            _channel { channel }
        {}

        void operator = (unsigned v)    { set(v <= 100 ? v : 100); }

        void configure(void)
        {
            ::Pins::PeripheralPin::configure();
        }

        void set(uint8_t duty_percentage)
        {
            _ftm.set_duty(_channel, duty_percentage);
        }

    private:
        _FTM            &_ftm;
        const uint8_t   _channel;
    };

    void configure(void)
    {
        ::PWM::_FTM(FTM0).configure();
        ::PWM::_FTM(FTM1).configure();
        ::PWM::_FTM(FTM2).configure();
    }
} // namespace PWM

#define DO_HSD1_OUT0    ::PWM::Pin(PORTD, ::Pins::PortD::_DO_HSD1_OUT0, 2, ::PWM::_FTM(FTM2), 5)
#define DO_HSD1_OUT1    ::PWM::Pin(PORTB, ::Pins::PortB::_DO_HSD1_OUT1, 2, ::PWM::_FTM(FTM0), 4)
#define DO_HSD1_OUT2    ::PWM::Pin(PORTE, ::Pins::PortE::_DO_HSD1_OUT2, 2, ::PWM::_FTM(FTM0), 6)
#define DO_HSD1_OUT3    ::PWM::Pin(PORTB, ::Pins::PortB::_DO_HSD1_OUT3, 2, ::PWM::_FTM(FTM0), 5)
#define DO_HSD2_OUT4    ::PWM::Pin(PORTD, ::Pins::PortD::_DO_HSD2_OUT4, 2, ::PWM::_FTM(FTM2), 3)
#define DO_HSD2_OUT5    ::PWM::Pin(PORTD, ::Pins::PortD::_DO_HSD2_OUT5, 2, ::PWM::_FTM(FTM2), 2)
#define DO_HSD2_OUT6    ::PWM::Pin(PORTD, ::Pins::PortD::_DO_HSD2_OUT6, 6, ::PWM::_FTM(FTM1), 5)
#define DO_HSD2_OUT7    ::PWM::Pin(PORTD, ::Pins::PortD::_DO_HSD2_OUT7, 2, ::PWM::_FTM(FTM0), 1)

#endif // if 1