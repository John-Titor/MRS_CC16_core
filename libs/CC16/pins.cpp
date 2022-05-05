// Pin functionality.
//

#include "pins.h"

namespace ExpanderPins
{
	uint16_t    _state;

	void reset(void)
	{
		DO_SHIFT_MR = 0;	
		DO_SHIFT_MR = 1;	
	}

	void update(void)
	{
		DO_SHIFT_MR = 1;
		DO_SHIFT_ST_CP = 0;
		for (unsigned i = 0; i < ::ExpanderPins::PortX::_Max; i++) {
			DO_SHIFT_IN_DS = _state & (1U << i);
			DO_SHIFT_SH_CP = 0;
			DO_SHIFT_SH_CP = 1;
		}
		DO_SHIFT_ST_CP = 1;
	}

	void set(uint8_t index, bool state) 
	{
	    auto mask = 1U << index;
	    if (state) {
	        _state |= mask;
	    } else {
	        _state &= ~mask;
	    }
		update();
	}
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