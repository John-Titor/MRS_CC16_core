#include <stdbool.h>
#include <stdint.h>

extern int  CAN_init(void);
extern int  CAN_send_blocking(uint32_t id, bool extended, uint8_t dlc, uint8_t *buf);
extern void CAN_putchar(uint8_t c);
extern int  CAN_getchar();
extern void CAN_puts(const char *s);
