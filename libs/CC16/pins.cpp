// Pin functionality.
//

#include "pins.h"

uint16_t ExpanderPin::_state;

const ExpanderPin DCDC_8V5 = { ._index = 0 };
const ExpanderPin DCDC_10V = { ._index = 1 };
const ExpanderPin PD_A_IN5 = { ._index = 2 };
const ExpanderPin PD_A_IN4 = { ._index = 3 };
const ExpanderPin PD_A_IN3 = { ._index = 4 };
const ExpanderPin PD_A_IN2 = { ._index = 5 };
const ExpanderPin PD_A_IN1 = { ._index = 6 };
const ExpanderPin PD_A_IN0 = { ._index = 7 };
const ExpanderPin PU_A_IN5 = { ._index = 8 };
const ExpanderPin PU_A_IN4 = { ._index = 9 };
const ExpanderPin PU_A_IN3 = { ._index = 10 };
const ExpanderPin PU_A_IN2 = { ._index = 11 };
const ExpanderPin PU_A_IN1 = { ._index = 12 };
const ExpanderPin PU_A_IN0 = { ._index = 13 };

void
ExpanderPin::reset(void)
{
	_state = 0;
	DO_SHIFT_MR = 0;	
	DO_SHIFT_MR = 1;	
}

void
ExpanderPin::set(bool v) const
{
    if (v) {
        _state |= (1U << v);
    } else {
        _state &= ~(1U << v);
    }
    update();
}

void
ExpanderPin::update(void)
{
	// ensure register is not in reset
	DO_SHIFT_MR = 1;

	// XXX need to avoid re-entering here - disable interrupts?
	// drop latch pin while shifting
	DO_SHIFT_ST_CP = 0;

	for (unsigned i = 0; i < 14; i++) {
		// clock low
		DO_SHIFT_SH_CP = 0;
		// load data
		DO_SHIFT_IN_DS = _state & (1U << i);
		// clock data on rising edge
		DO_SHIFT_SH_CP = 1;
	}
	// latch on rising edge
	DO_SHIFT_ST_CP = 1;

	// ensure outputs are on - should not be neccessaru
	DO_SHIFT_OE = 0;
}


namespace Pins
{
	void InputPin::configure(InputPin::Mode mode)
	{
		switch (mode) {
		case IN_ANALOG_17V:
		    _Pin::configure(0);
		    _rs.clear();
		    break;
		case IN_ANALOG_32V:
		    _Pin::configure(0);
		    _rs.set();
		    break;
		case IN_DIGITAL_PULLUP:
		    _Pin::configure(1);
		    _rs.clear();
		    _pu.set();
		    _pd.clear();
		    break;
		case IN_DIGITAL_PULLDOWN:
		    _Pin::configure(1);
		    _rs.clear();
		    _pu.clear();
		    _pd.set();
		    break;
		case IN_DIGITAL_NOPULL:
		    _Pin::configure(1);
		    _rs.clear();
		    _pu.clear();
		    _pd.clear();
		    break;        
		}
	}
}