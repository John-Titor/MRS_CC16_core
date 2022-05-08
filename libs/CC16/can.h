// CAN interfaces
//

#include <stdint.h>

namespace CAN
{
    enum Port : uint8_t {
        CAN1,
        CAN2,
    };

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
        uint8_t     ide:1;
        uint8_t     port:1;
        uint8_t     :2;

        uint8_t     data[8];
    };
    static_assert(sizeof(Frame) == 0x10);

    void configure(Port port, Rate rate);
    void send_ordered(Port port, const Frame &msg);
    void send_async(Port port, const Frame &msg);
}
