/*
 * Assorted CAN functions.
 */

#include "sdk_project_config.h"

#define TX_MAILBOX  0
#define RX_MAILBOX  1

#define ID_PUTC     0x1ffffffe
#define ID_GETC     0x1ffffffd

static flexcan_msgbuff_t getc_buf;

int
CAN_init(void)
{
    FLEXCAN_DRV_Init(INST_FLEXCAN_CONFIG_1, &flexcanState0, &flexcanInitConfig0);

    // CAN transceiver enable
    PINS_DRV_WritePin(CAN_STB1_PORT, CAN_STB1_PIN, 1);
    PINS_DRV_WritePin(CAN_EN1_PORT, CAN_EN1_PIN, 1);

    // receive init
    flexcan_data_info_t dataInfo =
    {
            .data_length = 1U,
            .msg_id_type = FLEXCAN_MSG_ID_EXT,
            .fd_enable   = false,
    };

    /* Configure RX message buffer with index ID_GETC and RX_MAILBOX */
    FLEXCAN_DRV_ConfigRxMb(INST_FLEXCAN_CONFIG_1, RX_MAILBOX, &dataInfo, ID_GETC);

    /* Start receiving data in RX_MAILBOX. */
    FLEXCAN_DRV_Receive(INST_FLEXCAN_CONFIG_1, RX_MAILBOX, &getc_buf);

    return 0;
}

int
CAN_send_blocking(uint32_t id, bool extended, uint8_t dlc, uint8_t *buf)
{
    flexcan_data_info_t dataInfo =
    {
            .msg_id_type = extended ? FLEXCAN_MSG_ID_EXT : FLEXCAN_MSG_ID_STD,
            .data_length = dlc,
            .fd_enable   = false,
            .is_remote   = false,
    };
    FLEXCAN_DRV_ConfigTxMb(INST_FLEXCAN_CONFIG_1, TX_MAILBOX, &dataInfo, id);
    return FLEXCAN_DRV_SendBlocking(INST_FLEXCAN_CONFIG_1, TX_MAILBOX, &dataInfo, id, buf, 1000);    
}

void 
CAN_putchar(uint8_t c)
{
    static uint8_t buf[8];
    static uint8_t buflen;

    if (c == '\n') {
        c = '\0';
    }
    buf[buflen++] = c;
    if ((buflen == sizeof(buf)) || (c == '\0')) {
        CAN_send_blocking(ID_PUTC, true, buflen, buf);
        buflen = 0;
    }
}

int
CAN_getchar() 
{
    int ret = -1;

    // has receive completed?
    if (FLEXCAN_DRV_GetTransferStatus(INST_FLEXCAN_CONFIG_1, RX_MAILBOX) != STATUS_BUSY) {
        // did we get a character?
        if (getc_buf.msgId == ID_GETC) {
            ret = getc_buf.data[0];
        }
        // start a new receive
        FLEXCAN_DRV_Receive(INST_FLEXCAN_CONFIG_1, RX_MAILBOX, &getc_buf);
    }

    return ret;
}

void
CAN_puts(const char *s)
{
    while (*s) {
        CAN_putchar(*s++);
    } 
    CAN_putchar('\n');
}

