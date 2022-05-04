// PWM output using FlexTimer 0/1/2
//

#pragma once
#include "pin.h"

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
		_reg.FTM0_MODE = 0;
		_reg.FTM0_SC = 0;
		_reg.FTM0_SC_b.CLKS = 0x1;	// SYS_CLK
		_reg.FTM0_SC_b.PS = 0x7;	// /128 = 625kHz = 1.6µs per count = ~100ms max period
		_reg.FTM0_SC_b.PWMEN0 = 1;
		_reg.FTM0_SC_b.PWMEN1 = 1;
		_reg.FTM0_SC_b.PWMEN2 = 1;
		_reg.FTM0_SC_b.PWMEN3 = 1;
		_reg.FTM0_SC_b.PWMEN4 = 1;
		_reg.FTM0_SC_b.PWMEN5 = 1;
		_reg.FTM0_SC_b.PWMEN6 = 1;
		_reg.FTM0_SC_b.PWMEN7 = 1;
		_reg.FTM0_MOD = 4899;		// ~128Hz period
		_reg.FTM0_CNTIN = 0;		// count from zero

		_reg.FTM0_COMBINE = 0;

		_reg.FTM0_C0SC = 0;			// edge-aligned PWM, high-true
		_reg.FTM0_C0SC_b.MSB = 1;
		_reg.FTM0_C0SC_b.ELSA = 0;
		_reg.FTM0_C0SC_b.ELSB = 1;

		_reg.FTM0_C1SC = _reg.FTM0_C0SC;	// copy channel 0
		_reg.FTM0_C2SC = _reg.FTM0_C0SC;
		_reg.FTM0_C3SC = _reg.FTM0_C0SC;
		_reg.FTM0_C4SC = _reg.FTM0_C0SC;
		_reg.FTM0_C5SC = _reg.FTM0_C0SC;
		_reg.FTM0_C6SC = _reg.FTM0_C0SC;
		_reg.FTM0_C7SC = _reg.FTM0_C0SC;
	}

	void set_duty(uint8_t channel, uint8_t duty_percentage)
	{
		uint32_t cnt = duty_percentage * 49;

		switch (channel) {
		case 0:	_reg.FTM0_C0V = cnt; break;
		case 1:	_reg.FTM0_C1V = cnt; break;
		case 2:	_reg.FTM0_C2V = cnt; break;
		case 3:	_reg.FTM0_C3V = cnt; break;
		case 4:	_reg.FTM0_C4V = cnt; break;
		case 5:	_reg.FTM0_C5V = cnt; break;
		case 6:	_reg.FTM0_C6V = cnt; break;
		case 7:	_reg.FTM0_C7V = cnt; break;
		}
	}

private:
	__IO FTM0_Type	&_reg;
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
		_ftm 	 { ftm },
		_channel { channel }
	{}

	void operator = (unsigned v)	{ set(v <= 100 ? v : 100); }

	void configure(void)
	{
		::Pins::PeripheralPin::configure();
		set(0);
	}

	void set(uint8_t duty_percentage)
	{
		_ftm.set_duty(_channel, duty_percentage);
	}

private:
	_FTM			&_ftm;
	const uint8_t	_channel;
};

#define _FTM0	::PWM::_FTM(FTM0)
#define _FTM1	::PWM::_FTM(FTM1)
#define _FTM2	::PWM::_FTM(FTM2)

#define DO_HSD1_OUT0    ::PWM::Pin(PORTD, ::Pins::PortD::_DO_HSD1_OUT0, 2, _FTM2, 5)
#define DO_HSD1_OUT1    ::PWM::Pin(PORTB, ::Pins::PortB::_DO_HSD1_OUT1, 2, _FTM0, 4)
#define DO_HSD1_OUT2    ::PWM::Pin(PORTE, ::Pins::PortE::_DO_HSD1_OUT2, 2, _FTM0, 6)
#define DO_HSD1_OUT3    ::PWM::Pin(PORTB, ::Pins::PortB::_DO_HSD1_OUT3, 2, _FTM0, 5)
#define DO_HSD2_OUT4    ::PWM::Pin(PORTD, ::Pins::PortD::_DO_HSD2_OUT4, 2, _FTM2, 3)
#define DO_HSD2_OUT5    ::PWM::Pin(PORTD, ::Pins::PortD::_DO_HSD2_OUT5, 2, _FTM2, 2)
#define DO_HSD2_OUT6    ::PWM::Pin(PORTD, ::Pins::PortD::_DO_HSD2_OUT6, 6, _FTM1, 5)
#define DO_HSD2_OUT7    ::PWM::Pin(PORTD, ::Pins::PortD::_DO_HSD2_OUT7, 2, _FTM0, 1)

}
