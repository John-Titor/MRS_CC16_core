/*
 * Interrupt vectors
 */

#include <stdint.h>

#include "CC16.h"

extern "C" void
Unhandled_Interrupt(void)
{
    puts("???");
    for (;;) {}
}

void DMA0_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA1_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA2_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA3_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA4_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA5_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA6_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA7_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA8_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA9_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA10_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA11_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA12_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA13_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA14_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA15_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void DMA_Error_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void MCM_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTFC_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void Read_Collision_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LVD_LVW_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTFC_Fault_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void WDOG_EWM_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void RCM_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPI2C0_Master_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPI2C0_Slave_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPSPI0_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPSPI1_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPSPI2_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPUART0_RxTx_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPUART1_RxTx_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPUART2_RxTx_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void ADC0_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void ADC1_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CMP0_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void ERM_single_fault_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void ERM_double_fault_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void RTC_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void RTC_Seconds_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPIT0_Ch0_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPIT0_Ch1_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPIT0_Ch2_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPIT0_Ch3_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void PDB0_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void SCG_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void LPTMR0_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void PORTA_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void PORTB_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void PORTC_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void PORTD_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void PORTE_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void SWI_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void PDB1_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FLEXIO_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN0_ORed_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN0_Error_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN0_Wake_Up_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN0_ORed_0_15_MB_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN0_ORed_16_31_MB_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN1_ORed_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN1_Error_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN1_ORed_0_15_MB_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN2_ORed_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN2_Error_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void CAN2_ORed_0_15_MB_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM0_Ch0_Ch1_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM0_Ch2_Ch3_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM0_Ch4_Ch5_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM0_Ch6_Ch7_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM0_Fault_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM0_Ovf_Reload_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM1_Ch0_Ch1_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM1_Ch2_Ch3_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM1_Ch4_Ch5_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM1_Ch6_Ch7_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM1_Fault_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM1_Ovf_Reload_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM2_Ch0_Ch1_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM2_Ch2_Ch3_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM2_Ch4_Ch5_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM2_Ch6_Ch7_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM2_Fault_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM2_Ovf_Reload_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM3_Ch0_Ch1_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM3_Ch2_Ch3_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM3_Ch4_Ch5_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM3_Ch6_Ch7_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM3_Fault_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));
void FTM3_Ovf_Reload_Handler(void) __attribute__((weak, alias("Unhandled_Interrupt")));

typedef void (*handler_func_t)(void);

static const __attribute__((used, section(".interrupt_vectors")))
handler_func_t _interrupt_vectors[] =
{
    DMA0_Handler,               // 0   DMA0
    DMA1_Handler,               // 1   DMA1
    DMA2_Handler,               // 2   DMA2
    DMA3_Handler,               // 3   DMA3
    DMA4_Handler,               // 4   DMA4
    DMA5_Handler,               // 5   DMA5
    DMA6_Handler,               // 6   DMA6
    DMA7_Handler,               // 7   DMA7
    DMA8_Handler,               // 8   DMA8
    DMA9_Handler,               // 9   DMA9
    DMA10_Handler,              // 10  DMA10
    DMA11_Handler,              // 11  DMA11
    DMA12_Handler,              // 12  DMA12
    DMA13_Handler,              // 13  DMA13
    DMA14_Handler,              // 14  DMA14
    DMA15_Handler,              // 15  DMA15
    DMA_Error_Handler,          // 16  DMA_Error
    MCM_Handler,                // 17  MCM
    FTFC_Handler,               // 18  FTFC
    Read_Collision_Handler,     // 19  Read_Collision
    LVD_LVW_Handler,            // 20  LVD_LVW
    FTFC_Fault_Handler,         // 21  FTFC_Fault
    WDOG_EWM_Handler,           // 22  WDOG_EWM
    RCM_Handler,                // 23  RCM
    LPI2C0_Master_Handler,      // 24  LPI2C0_Master
    LPI2C0_Slave_Handler,       // 25  LPI2C0_Slave
    LPSPI0_Handler,             // 26  LPSPI0
    LPSPI1_Handler,             // 27  LPSPI1
    LPSPI2_Handler,             // 28  LPSPI2
    Unhandled_Interrupt,        // 29
    Unhandled_Interrupt,        // 30
    LPUART0_RxTx_Handler,       // 31  LPUART0_RxTx
    Unhandled_Interrupt,        // 32
    LPUART1_RxTx_Handler,       // 33  LPUART1_RxTx
    Unhandled_Interrupt,        // 34
    LPUART2_RxTx_Handler,       // 35  LPUART2_RxTx
    Unhandled_Interrupt,        // 36
    Unhandled_Interrupt,        // 37
    Unhandled_Interrupt,        // 38
    ADC0_Handler,               // 39  ADC0
    ADC1_Handler,               // 40  ADC1
    CMP0_Handler,               // 41  CMP0
    Unhandled_Interrupt,        // 42
    Unhandled_Interrupt,        // 43
    ERM_single_fault_Handler,   // 44  ERM_single_fault
    ERM_double_fault_Handler,   // 45  ERM_double_fault
    RTC_Handler,                // 46  RTC
    RTC_Seconds_Handler,        // 47  RTC_Seconds
    LPIT0_Ch0_Handler,          // 48  LPIT0_Ch0
    LPIT0_Ch1_Handler,          // 49  LPIT0_Ch1
    LPIT0_Ch2_Handler,          // 50  LPIT0_Ch2
    LPIT0_Ch3_Handler,          // 51  LPIT0_Ch3
    PDB0_Handler,               // 52  PDB0
    Unhandled_Interrupt,        // 53
    Unhandled_Interrupt,        // 54
    Unhandled_Interrupt,        // 55
    Unhandled_Interrupt,        // 56
    SCG_Handler,                // 57  SCG
    LPTMR0_Handler,             // 58  LPTMR0
    PORTA_Handler,              // 59  PORTA
    PORTB_Handler,              // 60  PORTB
    PORTC_Handler,              // 61  PORTC
    PORTD_Handler,              // 62  PORTD
    PORTE_Handler,              // 63  PORTE
    SWI_Handler,                // 64  SWI
    Unhandled_Interrupt,        // 65
    Unhandled_Interrupt,        // 66
    Unhandled_Interrupt,        // 67
    PDB1_Handler,               // 68  PDB1
    FLEXIO_Handler,             // 69  FLEXIO
    Unhandled_Interrupt,        // 70
    Unhandled_Interrupt,        // 71
    Unhandled_Interrupt,        // 72
    Unhandled_Interrupt,        // 73
    Unhandled_Interrupt,        // 74
    Unhandled_Interrupt,        // 75
    Unhandled_Interrupt,        // 76
    Unhandled_Interrupt,        // 77
    CAN0_ORed_Handler,          // 78  CAN0_ORed
    CAN0_Error_Handler,         // 79  CAN0_Error
    CAN0_Wake_Up_Handler,       // 80  CAN0_Wake_Up
    CAN0_ORed_0_15_MB_Handler,  // 81  CAN0_ORed_0_15_MB
    CAN0_ORed_16_31_MB_Handler, // 82  CAN0_ORed_16_31_MB
    Unhandled_Interrupt,        // 83
    Unhandled_Interrupt,        // 84
    CAN1_ORed_Handler,          // 85  CAN1_ORed
    CAN1_Error_Handler,         // 86  CAN1_Error
    Unhandled_Interrupt,        // 87
    CAN1_ORed_0_15_MB_Handler,  // 88  CAN1_ORed_0_15_MB
    Unhandled_Interrupt,        // 89
    Unhandled_Interrupt,        // 90
    Unhandled_Interrupt,        // 91
    CAN2_ORed_Handler,          // 92  CAN2_ORed
    CAN2_Error_Handler,         // 93  CAN2_Error
    Unhandled_Interrupt,        // 94
    CAN2_ORed_0_15_MB_Handler,  // 95  CAN2_ORed_0_15_MB
    Unhandled_Interrupt,        // 96
    Unhandled_Interrupt,        // 97
    Unhandled_Interrupt,        // 98
    FTM0_Ch0_Ch1_Handler,       // 99  FTM0_Ch0_Ch1
    FTM0_Ch2_Ch3_Handler,       // 100 FTM0_Ch2_Ch3
    FTM0_Ch4_Ch5_Handler,       // 101 FTM0_Ch4_Ch5
    FTM0_Ch6_Ch7_Handler,       // 102 FTM0_Ch6_Ch7
    FTM0_Fault_Handler,         // 103 FTM0_Fault
    FTM0_Ovf_Reload_Handler,    // 104 FTM0_Ovf_Reload
    FTM1_Ch0_Ch1_Handler,       // 105 FTM1_Ch0_Ch1
    FTM1_Ch2_Ch3_Handler,       // 106 FTM1_Ch2_Ch3
    FTM1_Ch4_Ch5_Handler,       // 107 FTM1_Ch4_Ch5
    FTM1_Ch6_Ch7_Handler,       // 108 FTM1_Ch6_Ch7
    FTM1_Fault_Handler,         // 109 FTM1_Fault
    FTM1_Ovf_Reload_Handler,    // 110 FTM1_Ovf_Reload
    FTM2_Ch0_Ch1_Handler,       // 111 FTM2_Ch0_Ch1
    FTM2_Ch2_Ch3_Handler,       // 112 FTM2_Ch2_Ch3
    FTM2_Ch4_Ch5_Handler,       // 113 FTM2_Ch4_Ch5
    FTM2_Ch6_Ch7_Handler,       // 114 FTM2_Ch6_Ch7
    FTM2_Fault_Handler,         // 115 FTM2_Fault
    FTM2_Ovf_Reload_Handler,    // 116 FTM2_Ovf_Reload
    FTM3_Ch0_Ch1_Handler,       // 117 FTM3_Ch0_Ch1
    FTM3_Ch2_Ch3_Handler,       // 118 FTM3_Ch2_Ch3
    FTM3_Ch4_Ch5_Handler,       // 119 FTM3_Ch4_Ch5
    FTM3_Ch6_Ch7_Handler,       // 120 FTM3_Ch6_Ch7
    FTM3_Fault_Handler,         // 121 FTM3_Fault
    FTM3_Ovf_Reload_Handler,    // 122 FTM3_Ovf_Reload
    Unhandled_Interrupt,        // 123
    Unhandled_Interrupt,        // 124
    Unhandled_Interrupt,        // 125
    Unhandled_Interrupt,        // 126
    Unhandled_Interrupt,        // 127
    Unhandled_Interrupt,        // 128
    Unhandled_Interrupt,        // 129
    Unhandled_Interrupt,        // 130
    Unhandled_Interrupt,        // 131
    Unhandled_Interrupt,        // 132
    Unhandled_Interrupt,        // 133
    Unhandled_Interrupt,        // 134
    Unhandled_Interrupt,        // 135
    Unhandled_Interrupt,        // 136
    Unhandled_Interrupt,        // 137
    Unhandled_Interrupt,        // 138
    Unhandled_Interrupt,        // 139
    Unhandled_Interrupt,        // 140
    Unhandled_Interrupt,        // 141
    Unhandled_Interrupt,        // 142
    Unhandled_Interrupt,        // 143
    Unhandled_Interrupt,        // 144
    Unhandled_Interrupt,        // 145
    Unhandled_Interrupt,        // 146
    Unhandled_Interrupt,        // 147
    Unhandled_Interrupt,        // 148
    Unhandled_Interrupt,        // 149
    Unhandled_Interrupt,        // 150
    Unhandled_Interrupt,        // 151
    Unhandled_Interrupt,        // 152
    Unhandled_Interrupt,        // 153
    Unhandled_Interrupt,        // 154
    Unhandled_Interrupt,        // 155
    Unhandled_Interrupt,        // 156
    Unhandled_Interrupt,        // 157
    Unhandled_Interrupt,        // 158
    Unhandled_Interrupt,        // 159
    Unhandled_Interrupt,        // 160
    Unhandled_Interrupt,        // 161
    Unhandled_Interrupt,        // 162
    Unhandled_Interrupt,        // 163
    Unhandled_Interrupt,        // 164
    Unhandled_Interrupt,        // 165
    Unhandled_Interrupt,        // 166
    Unhandled_Interrupt,        // 167
    Unhandled_Interrupt,        // 168
    Unhandled_Interrupt,        // 169
    Unhandled_Interrupt,        // 170
    Unhandled_Interrupt,        // 171
    Unhandled_Interrupt,        // 172
    Unhandled_Interrupt,        // 173
    Unhandled_Interrupt,        // 174
    Unhandled_Interrupt,        // 175
    Unhandled_Interrupt,        // 176
    Unhandled_Interrupt,        // 177
    Unhandled_Interrupt,        // 178
    Unhandled_Interrupt,        // 179
    Unhandled_Interrupt,        // 180
    Unhandled_Interrupt,        // 181
    Unhandled_Interrupt,        // 182
    Unhandled_Interrupt,        // 183
    Unhandled_Interrupt,        // 184
    Unhandled_Interrupt,        // 185
    Unhandled_Interrupt,        // 186
    Unhandled_Interrupt,        // 187
    Unhandled_Interrupt,        // 188
    Unhandled_Interrupt,        // 189
    Unhandled_Interrupt,        // 190
    Unhandled_Interrupt,        // 191
    Unhandled_Interrupt,        // 192
    Unhandled_Interrupt,        // 193
    Unhandled_Interrupt,        // 194
    Unhandled_Interrupt,        // 195
    Unhandled_Interrupt,        // 196
    Unhandled_Interrupt,        // 197
    Unhandled_Interrupt,        // 198
    Unhandled_Interrupt,        // 199
    Unhandled_Interrupt,        // 200
    Unhandled_Interrupt,        // 201
    Unhandled_Interrupt,        // 202
    Unhandled_Interrupt,        // 203
    Unhandled_Interrupt,        // 204
    Unhandled_Interrupt,        // 205
    Unhandled_Interrupt,        // 206
    Unhandled_Interrupt,        // 207
    Unhandled_Interrupt,        // 208
    Unhandled_Interrupt,        // 209
    Unhandled_Interrupt,        // 210
    Unhandled_Interrupt,        // 211
    Unhandled_Interrupt,        // 212
    Unhandled_Interrupt,        // 213
    Unhandled_Interrupt,        // 214
    Unhandled_Interrupt,        // 215
    Unhandled_Interrupt,        // 216
    Unhandled_Interrupt,        // 217
    Unhandled_Interrupt,        // 218
    Unhandled_Interrupt,        // 219
    Unhandled_Interrupt,        // 220
    Unhandled_Interrupt,        // 221
    Unhandled_Interrupt,        // 222
    Unhandled_Interrupt,        // 223
    Unhandled_Interrupt,        // 224
    Unhandled_Interrupt,        // 225
    Unhandled_Interrupt,        // 226
    Unhandled_Interrupt,        // 227
    Unhandled_Interrupt,        // 228
    Unhandled_Interrupt,        // 229
    Unhandled_Interrupt,        // 230
    Unhandled_Interrupt,        // 231
    Unhandled_Interrupt,        // 232
    Unhandled_Interrupt,        // 233
    Unhandled_Interrupt,        // 234
    Unhandled_Interrupt,        // 235
    Unhandled_Interrupt,        // 236
    Unhandled_Interrupt,        // 237
    Unhandled_Interrupt,        // 238
    (handler_func_t)0xffffffff, // reserved for user TRIM value
};

static_assert(sizeof(_interrupt_vectors) == (sizeof(handler_func_t) * (256 - 16)), "interrupt vector table size mismatch");
