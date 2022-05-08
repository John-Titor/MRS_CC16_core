// CAN interfaces
//

#define NDEBUG
#include <assert.h>

#include <etl/queue_spsc_atomic.h>
#include <etl/atomic.h>

#include "can.h"
#include "pins.h"

namespace CC16 {
    const Pin CAN_EN1    { .port = Pin::PortA, .index = 11, .mux = Pin::GPIO, .direction = Pin::OUT, .initial = 1 };
    const Pin CAN_EN2    { .port = Pin::PortE, .index = 12, .mux = Pin::GPIO, .direction = Pin::OUT, .initial = 1 };
    const Pin CAN_ERR1   { .port = Pin::PortE, .index = 0,  .mux = Pin::GPIO, .direction = Pin::IN };
    const Pin CAN_ERR2   { .port = Pin::PortE, .index = 12, .mux = Pin::GPIO, .direction = Pin::IN };
    const Pin CAN_STB1   { .port = Pin::PortE, .index = 1,  .mux = Pin::GPIO, .direction = Pin::OUT, .initial = 1 };
    const Pin CAN_STB2   { .port = Pin::PortE, .index = 3,  .mux = Pin::GPIO, .direction = Pin::OUT, .initial = 1 };
    const Pin CAN_WAKE1  { .port = Pin::PortA, .index = 14, .mux = Pin::GPIO, .direction = Pin::IN };
    const Pin CAN_WAKE2  { .port = Pin::PortE, .index = 14, .mux = Pin::GPIO, .direction = Pin::IN };
} // namespace CC16

namespace CC16::CAN
{
    // Timing values calculated using http://www.bittiming.can-wiki.info and verified with 
    // S32 Design Studio. Wiki tool and S32DS swap EPROPSEG and EPSEG1; using the S32DS values here.
    //
    // Clock = 80Mhz from SYS_CLK required to achieve 1Mbps.
    //
    const uint32_t rate_table[] = {
        (CAN_CBT_EPRESDIV(0x04) | CAN_CBT_EPROPSEG(0x07) | CAN_CBT_EPSEG1(0x04) | CAN_CBT_EPSEG2(0x01)),    // 1000000
        (CAN_CBT_EPRESDIV(0x09) | CAN_CBT_EPROPSEG(0x07) | CAN_CBT_EPSEG1(0x04) | CAN_CBT_EPSEG2(0x01)),    //  500000
        (CAN_CBT_EPRESDIV(0x13) | CAN_CBT_EPROPSEG(0x07) | CAN_CBT_EPSEG1(0x04) | CAN_CBT_EPSEG2(0x01)),    //  250000
        (CAN_CBT_EPRESDIV(0x27) | CAN_CBT_EPROPSEG(0x07) | CAN_CBT_EPSEG1(0x04) | CAN_CBT_EPSEG2(0x01)),    //  125000
    };

    // RX FIFO access in mailbox 0
    //
    union RxFIFO {
        uint32_t    u32[4];
        struct {
            uint32_t    timestamp:16;
            uint32_t    dlc:4;
            uint32_t    rtr:1;
            uint32_t    ide:1;
            uint32_t    srr:1;
            uint32_t    idhit:9;

            union {
                struct {
                    uint32_t    id_ext:29;
                    uint32_t    :3;
                };
                struct {
                    uint32_t    :18;
                    uint32_t    id:11;
                    uint32_t    :3;
                };
            };
            uint8_t     data[8];
        };
    };
    static_assert(sizeof(RxFIFO) == 0x10);

    // TX buffer in mailboxes 8-up (depending on config)
    //
    union TxBuf {
        uint32_t    u32[4];
        struct {
            uint32_t    timestamp:16;
            uint32_t    dlc:4;
            uint32_t    rtr:1;
            uint32_t    ide:1;
            uint32_t    srr:1;
            uint32_t    :1;
            uint32_t    code:4;
            uint32_t    :1;
            uint32_t    esi:1;
            uint32_t    brs:1;
            uint32_t    edl:1;

            union {
                struct {
                    uint32_t    id_ext:29;
                    uint32_t    prio:3;
                };
                struct {
                    uint32_t    :18;
                    uint32_t    id:11;
                    uint32_t    :3;
                };
            };

            uint8_t     data[8];
        };
    };
    static_assert(sizeof(TxBuf) == 0x10);

    // TxBuf::code encodings
    //
    enum TxCode {
        TX_INACTIVE = 0x8,
        TX_ABORT    = 0x9,
        TX_DATA     = 0xc,
        TX_TANSWER  = 0xe,
    };

    const unsigned          num_tx_buf = 8;

    etl::queue_spsc_atomic<Frame, 32, etl::memory_model::MEMORY_MODEL_SMALL> rx_queue;

    volatile CAN_regs_t &
    _regs(Port port)
    {
        assert(port <= CAN2);
        return port ? CAN1_regs : CAN0_regs; 
    }

    volatile TxBuf &_txbase0 = *reinterpret_cast<volatile TxBuf *>(&CAN0_regs.RAMn32);
    volatile TxBuf &_txbase1 = *reinterpret_cast<volatile TxBuf *>(&CAN1_regs.RAMn32);

    volatile TxBuf &
    _txBuf(Port port, unsigned index) 
    {
        assert(port <= CAN2);
        assert(index <= num_tx_buf);
        return *((port ? &_txbase1 : &_txbase0) + index);
    }

    volatile RxFIFO &_rxfifo0 = *reinterpret_cast<volatile RxFIFO *>(&CAN0_regs.RAMn0);
    volatile RxFIFO &_rxfifo1 = *reinterpret_cast<volatile RxFIFO *>(&CAN1_regs.RAMn0);

    volatile RxFIFO &
    _rxFIFO(Port port)
    {
        assert(port <= CAN2);
        return port ? _rxfifo1 : _rxfifo0;
    }

    void
    configure(Port port, Rate rate)
    {
        assert(port <= CAN2);
        auto &regs = _regs(port);

        // per-port clock & GPIO configuration
        switch (port) {
        case CAN1:
            PCC_regs.PCC_FlexCAN0 |= PCC_PCC_FlexCAN0_CGC;
            CAN_EN1.configure();
            CAN_ERR1.configure();
            CAN_STB1.configure();
            CAN_WAKE1.configure();
            break;

        case CAN2:
            PCC_regs.PCC_FlexCAN1 |= PCC_PCC_FlexCAN1_CGC;
            CAN_EN2.configure();
            CAN_ERR2.configure();
            CAN_STB2.configure();
            CAN_WAKE2.configure();
        }

        // Select SYS_CLK (80MHz) (table 27-9)
        regs.CTRL1 |= CAN_CTRL1_CLKSRC;

        // enable CAN
        regs.MCR |= CAN_MCR_FRZ;
        regs.MCR &= ~CAN_MCR_MDIS;
        while(regs.MCR & CAN_MCR_LPMACK);
        
        // soft reset
        regs.MCR ^= CAN_MCR_SOFTRST;
        while(regs.MCR & CAN_MCR_SOFTRST);

        // wait for freeze ack
        while(!(regs.MCR & CAN_MCR_FRZACK));

        // MCR.WRNEN? warning interrupts?
        // MCR.LPRIOEN? more confusing tx priority rules?
        // CAN_MCR_AEN has odd TX queueing requirements, XXX check this

        regs.MCR |= CAN_MCR_IRMQ   |    // select 'new' interrupt masking
                    CAN_MCR_SRXDIS |    // disable self-reception
                    CAN_MCR_RFEN   |    // enable RX FIFO
                    0;

        // set bit timing
        assert((rate >= 0) && (rate < CAN::RATE_Max));
        regs.CBT = CAN_CBT_BTF | CAN_CBT_ERJW(1) | rate_table[rate];
        // FDCBT?
        // CTRL1.LBUF?

        // Init control/status words in message buffers
        // Init ID filter table
        // RXIMRn
        // Set interrupt mask bits in IMASK
        // Set error mask bits in CTRL1/2
        // Clear MCR.HALT
        regs.MCR &= ~CAN_MCR_HALT;
        while (regs.MCR & CAN_MCR_NOTRDY);

        // set TX buffers to inactive
        for (auto i = 0U; i < num_tx_buf; i++) {
            _txBuf(port, i).code = TxCode::TX_INACTIVE;
        }

        // enable RX FIFO buffer-available interrupt
        regs.IMASK1 |= CAN_IFLAG1_BUF5I;
    }

    void
    send_ordered(Port port, const Frame &frm)
    {
        auto        &mb = _txBuf(port, 0);
        TxBuf       tb;

        // spin waiting for previous message to be sent
        while (mb.code != TX_INACTIVE);

        // copy frame into local message buffer copy
        tb.dlc = frm.dlc;
        tb.ide = frm.ide;
        if (frm.ide) {
            tb.id_ext = frm.id_ext;
        } else {
            tb.id = frm.id;
        }
        tb.code = TxCode::TX_DATA;
        tb.data[3] = frm.data[0];   // hooray, big-endian buffer nonsense
        tb.data[2] = frm.data[1];
        tb.data[1] = frm.data[2];
        tb.data[0] = frm.data[3];
        tb.data[7] = frm.data[4];
        tb.data[6] = frm.data[5];
        tb.data[5] = frm.data[6];
        tb.data[4] = frm.data[7];

        // bulk copy to mailbox
        mb.u32[1] = tb.u32[1];
        mb.u32[2] = tb.u32[2];
        mb.u32[3] = tb.u32[3];
        mb.u32[0] = tb.u32[0];      // this updates .code and thus starts transmission
    }


    void
    rx_interrupt(Port port)
    {
        auto &regs = _regs(port);
        auto &fifo = _rxFIFO(port);

        while (regs.IFLAG1 & CAN_IFLAG1_BUF5I) {
            RxFIFO  rb;

            // copy message into local buffer
            rb.u32[0] = fifo.u32[0];
            rb.u32[1] = fifo.u32[1];
            rb.u32[2] = fifo.u32[2];
            rb.u32[3] = fifo.u32[3];

            // acknowledge reception, next message pops to the top
            regs.IFLAG1 |= CAN_IFLAG1_BUF5I;

            // unpack the message buffer
            Frame frm;
            frm.dlc = rb.dlc;
            frm.ide = rb.ide;
            if (rb.ide) {
                frm.id_ext = rb.id_ext;
            } else {
                frm.id = rb.id;
            }
            frm.data[0] = rb.data[3];
            frm.data[1] = rb.data[2];
            frm.data[2] = rb.data[1];
            frm.data[3] = rb.data[0];
            frm.data[4] = rb.data[7];
            frm.data[5] = rb.data[6];
            frm.data[6] = rb.data[5];
            frm.data[7] = rb.data[4];

            rx_queue.push(frm);
        }

    }

}

void
CAN0_ORed_0_15_MB_Handler(void)
{
    CC16::CAN::rx_interrupt(CC16::CAN::CAN1);
}

void
CAN1_ORed_0_15_MB_Handler(void)
{
    CC16::CAN::rx_interrupt(CC16::CAN::CAN2);
}

namespace CC16
{
    void
    cons_putc(char c)
    {
        static CC16::CAN::Frame   f { {{.id_ext = 0x1ffffffe}}, .ide = 1 };

        if (c == '\n') {
            c = '\0';
        }
        f.data[f.dlc++] = c;
        if ((f.dlc == 8) || c == '\0') {
            CC16::CAN::send_ordered(CC16::CAN::CAN1, f);
            f.dlc = 0;
        }
    }

    int
    cons_getc()
    {
        return -1;
    }

} // namespace CC16