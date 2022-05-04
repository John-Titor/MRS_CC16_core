// Pin expander
//

#include "pin.h"

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

