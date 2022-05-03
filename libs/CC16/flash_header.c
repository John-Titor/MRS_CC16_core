// MRS bootloader-required application header.
//

#include <stdint.h>

const struct
{
    uint32_t    header_key;            
    uint32_t    header_crc;            
    uint32_t    app_header_version;    
    uint32_t    application_crc;       
    uint32_t    application_length;    
    uint8_t     sw_version[32];         
} flash_header __attribute__((used, section(".APP_HEADER"))) = { 
    .header_key = 0x12345678,
    .app_header_version = 1
};
