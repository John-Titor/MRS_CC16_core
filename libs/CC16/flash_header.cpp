// MRS bootloader-required application header.
//

#include <stdint.h>

extern uint32_t __application_size;

static const struct
{
    uint32_t    header_key;            
    uint32_t    header_crc;            
    uint32_t    app_header_version;    
    uint32_t    application_crc;       
    uint32_t    application_length;    
    uint8_t     sw_version[32];         
} flash_header __attribute__((used, section(".application_header"))) = { 
    .header_key = 0x12345678,
    .app_header_version = 1,
};

static const uint32_t flash_configuration[] __attribute__((used, section(".flash_config"))) = {
    0xffffffff,    // backdoor comparison key 1/2
    0xffffffff,    // backdoor comparison key 2/2
    0xffffffff,    // program flash protection bytes
    0xffff7ffe,    // FDPROT:FEPROT:FOPT:FSEC(0xFE = unsecured)
};
