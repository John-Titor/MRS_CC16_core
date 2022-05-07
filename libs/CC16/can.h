// CAN interfaces
//

#include <CMSIS/S32K144.h>
#include "pins.h"

class CAN
{
public:
    CAN(volatile CAN_regs_t &regs,
        Pin en_gpio,
        Pin stb_gpio,
        Pin wake_gpio,
        Pin err_gpio) :
        _reg   { regs },
        _en { en_gpio },
        _stb { stb_gpio },
        _wake { wake_gpio },
        _err { err_gpio }
    {}

    enum Rate {
        RATE_1M,
        RATE_500K,
        RATE_250K,
        RATE_125K,
        RATE_Max
    };

    struct Frame
    {
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

        uint8_t     dlc:4;
        uint32_t    ide:1;
        uint8_t     :3;

        uint8_t     data[8];
    };
    static_assert(sizeof(Frame) == 0x10);

    void configure(Rate rate);
    void send(const Frame &msg);
    bool recv(Frame &buf);

private:
    const unsigned      num_tx_buf = 8;

    union RxBuf {
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
    static_assert(sizeof(RxBuf) == 0x10);

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

    enum MBCode {
        RX_INACTIVE = 0x0,
        RX_BUSY     = 0x1,
        RX_FULL     = 0x2,
        RX_EMPTY    = 0x4,
        RX_OVERRUN  = 0x6,
        RX_RANSWER  = 0xa,

        TX_INACTIVE = 0x8,
        TX_ABORT    = 0x9,
        TX_DATA     = 0xc,
        TX_TANSWER  = 0xe,
    };

    volatile CAN_regs_t     &_reg;
    volatile TxBuf          &_txBuf(unsigned index);

    const Pin               _en;
    const Pin               _stb;
    const Pin               _wake;
    const Pin               _err;
};

extern CAN CAN1;
extern CAN CAN2;
