// CAN interfaces
//

#include "can.h"

// Timing values calculated using http://www.bittiming.can-wiki.info and verified with 
// S32 Design Studio. Wiki tool and S32DS swap EPROPSEG and EPSEG1; using the S32DS values here.
//
// Clock = 80Mhz from SYS_CLK required to achieve 1Mbps.
//
static const uint32_t
rate_table[] = {
	(CAN_CBT_EPRESDIV(0x04) | CAN_CBT_EPROPSEG(0x07) | CAN_CBT_EPSEG1(0x04) | CAN_CBT_EPSEG2(0x01)),	// 1000000
	(CAN_CBT_EPRESDIV(0x09) | CAN_CBT_EPROPSEG(0x07) | CAN_CBT_EPSEG1(0x04) | CAN_CBT_EPSEG2(0x01)),	//  500000
	(CAN_CBT_EPRESDIV(0x13) | CAN_CBT_EPROPSEG(0x07) | CAN_CBT_EPSEG1(0x04) | CAN_CBT_EPSEG2(0x01)),	//  250000
	(CAN_CBT_EPRESDIV(0x27) | CAN_CBT_EPROPSEG(0x07) | CAN_CBT_EPSEG1(0x04) | CAN_CBT_EPSEG2(0x01)),	//  125000
};

void
CAN::configure(Rate rate)
{
	if ((rate < 0) || (rate > RATE_Max)) {
		rate = RATE_500K;
	}

    // CAN clocks on
    PCC_regs.PCC_FlexCAN0 = PCC_PCC_FlexCAN0_CGC;
    PCC_regs.PCC_FlexCAN1 = PCC_PCC_FlexCAN1_CGC;

	// Select SYS_CLK (80MHz) (table 27-9)
	_reg.CTRL1 |= CAN_CTRL1_CLKSRC;

	// enable CAN
	_reg.MCR |= CAN_MCR_FRZ;
	_reg.MCR &= ~CAN_MCR_MDIS;
	while(_reg.MCR & CAN_MCR_LPMACK);
	
	// soft reset
	_reg.MCR ^= CAN_MCR_SOFTRST;
	while(_reg.MCR & CAN_MCR_SOFTRST);

	// wait for freeze ack
	while(!(_reg.MCR & CAN_MCR_FRZACK));

	// MCR.IRMQ?
	// MCR.WRNEN?

	// disable self-reception
	_reg.MCR |= CAN_MCR_SRXDIS;

	// enable RX FIFO
	_reg.MCR |= CAN_MCR_RFEN;

	// MCR.AEN?
	// MCR.LPRIOEN?

	// set bit timing
	_reg.CBT = CAN_CBT_BTF | CAN_CBT_ERJW(1) | rate_table[rate];
	// FDCBT?
	// CTRL1.LBUF?

	// Init control/status words in message buffers
	// Init ID filter table
	// RXIMRn
	// Set interrupt mask bits in IMASK
	// Set error mask bits in CTRL1/2
	// Clear MCR.HALT
	_reg.MCR &= ~CAN_MCR_HALT;
	while (_reg.MCR & CAN_MCR_NOTRDY);

	// set TX buffers to inactive
	for (auto i = 0U; i < num_tx_buf; i++) {
		_txBuf(i).code = MBCode::TX_INACTIVE;
	}
}

void
CAN::send(const CAN::Frame &frm)
{
	auto 		&mb = _txBuf(0);
	TxBuf		tb;

	tb.dlc = frm.dlc;
	tb.ide = frm.ide;
	if (frm.ide) {
		tb.id_ext = frm.id_ext;
	} else {
		tb.id = frm.id;
	}
	tb.code = MBCode::TX_DATA;
	tb.data[3] = frm.data[0];	// hooray, big-endian buffer nonsense
	tb.data[2] = frm.data[1];
	tb.data[1] = frm.data[2];
	tb.data[0] = frm.data[3];
	tb.data[7] = frm.data[4];
	tb.data[6] = frm.data[5];
	tb.data[5] = frm.data[6];
	tb.data[4] = frm.data[7];

	mb.u32[1] = tb.u32[1];
	mb.u32[2] = tb.u32[2];
	mb.u32[3] = tb.u32[3];
	mb.u32[0] = tb.u32[0];
}

volatile CAN::TxBuf &
CAN::_txBuf(unsigned index)
{
	auto bp = (reinterpret_cast<uintptr_t>(&_reg.RAMn32) + index * sizeof(TxBuf));

	return *reinterpret_cast<volatile TxBuf *>(bp);
}

CAN CAN0(CAN0_regs);
