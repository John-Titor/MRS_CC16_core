/*
 * Interrupt vectors
 */

#include <stdint.h>

extern "C" void
Unhandled_Interrupt(void)
{
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
    0,                          // 29
    0,                          // 30
    LPUART0_RxTx_Handler,       // 31  LPUART0_RxTx
    0,                          // 32
    LPUART1_RxTx_Handler,       // 33  LPUART1_RxTx
    0,                          // 34
    LPUART2_RxTx_Handler,       // 35  LPUART2_RxTx
    0,                          // 36
    0,                          // 37
    0,                          // 38
    ADC0_Handler,               // 39  ADC0
    ADC1_Handler,               // 40  ADC1
    CMP0_Handler,               // 41  CMP0
    0,                          // 42
    0,                          // 43
    ERM_single_fault_Handler,   // 44  ERM_single_fault
    ERM_double_fault_Handler,   // 45  ERM_double_fault
    RTC_Handler,                // 46  RTC
    RTC_Seconds_Handler,        // 47  RTC_Seconds
    LPIT0_Ch0_Handler,          // 48  LPIT0_Ch0
    LPIT0_Ch1_Handler,          // 49  LPIT0_Ch1
    LPIT0_Ch2_Handler,          // 50  LPIT0_Ch2
    LPIT0_Ch3_Handler,          // 51  LPIT0_Ch3
    PDB0_Handler,               // 52  PDB0
    0,                          // 53
    0,                          // 54
    0,                          // 55
    0,                          // 56
    SCG_Handler,                // 57  SCG
    LPTMR0_Handler,             // 58  LPTMR0
    PORTA_Handler,              // 59  PORTA
    PORTB_Handler,              // 60  PORTB
    PORTC_Handler,              // 61  PORTC
    PORTD_Handler,              // 62  PORTD
    PORTE_Handler,              // 63  PORTE
    SWI_Handler,                // 64  SWI
    0,                          // 65
    0,                          // 66
    0,                          // 67
    PDB1_Handler,               // 68  PDB1
    FLEXIO_Handler,             // 69  FLEXIO
    0,                          // 70
    0,                          // 71
    0,                          // 72
    0,                          // 73
    0,                          // 74
    0,                          // 75
    0,                          // 76
    0,                          // 77
    CAN0_ORed_Handler,          // 78  CAN0_ORed
    CAN0_Error_Handler,         // 79  CAN0_Error
    CAN0_Wake_Up_Handler,       // 80  CAN0_Wake_Up
    CAN0_ORed_0_15_MB_Handler,  // 81  CAN0_ORed_0_15_MB
    CAN0_ORed_16_31_MB_Handler, // 82  CAN0_ORed_16_31_MB
    0,                          // 83
    0,                          // 84
    CAN1_ORed_Handler,          // 85  CAN1_ORed
    CAN1_Error_Handler,         // 86  CAN1_Error
    0,                          // 87
    CAN1_ORed_0_15_MB_Handler,  // 88  CAN1_ORed_0_15_MB
    0,                          // 89
    0,                          // 90
    0,                          // 91
    CAN2_ORed_Handler,          // 92  CAN2_ORed
    CAN2_Error_Handler,         // 93  CAN2_Error
    0,                          // 94
    CAN2_ORed_0_15_MB_Handler,  // 95  CAN2_ORed_0_15_MB
    0,                          // 96
    0,                          // 97
    0,                          // 98
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
    0,                          // 123
    0,                          // 124
    0,                          // 125
    0,                          // 126
    0,                          // 127
    0,                          // 128
    0,                          // 129
    0,                          // 130
    0,                          // 131
    0,                          // 132
    0,                          // 133
    0,                          // 134
    0,                          // 135
    0,                          // 136
    0,                          // 137
    0,                          // 138
    0,                          // 139
    0,                          // 140
    0,                          // 141
    0,                          // 142
    0,                          // 143
    0,                          // 144
    0,                          // 145
    0,                          // 146
    0,                          // 147
    0,                          // 148
    0,                          // 149
    0,                          // 150
    0,                          // 151
    0,                          // 152
    0,                          // 153
    0,                          // 154
    0,                          // 155
    0,                          // 156
    0,                          // 157
    0,                          // 158
    0,                          // 159
    0,                          // 160
    0,                          // 161
    0,                          // 162
    0,                          // 163
    0,                          // 164
    0,                          // 165
    0,                          // 166
    0,                          // 167
    0,                          // 168
    0,                          // 169
    0,                          // 170
    0,                          // 171
    0,                          // 172
    0,                          // 173
    0,                          // 174
    0,                          // 175
    0,                          // 176
    0,                          // 177
    0,                          // 178
    0,                          // 179
    0,                          // 180
    0,                          // 181
    0,                          // 182
    0,                          // 183
    0,                          // 184
    0,                          // 185
    0,                          // 186
    0,                          // 187
    0,                          // 188
    0,                          // 189
    0,                          // 190
    0,                          // 191
    0,                          // 192
    0,                          // 193
    0,                          // 194
    0,                          // 195
    0,                          // 196
    0,                          // 197
    0,                          // 198
    0,                          // 199
    0,                          // 200
    0,                          // 201
    0,                          // 202
    0,                          // 203
    0,                          // 204
    0,                          // 205
    0,                          // 206
    0,                          // 207
    0,                          // 208
    0,                          // 209
    0,                          // 210
    0,                          // 211
    0,                          // 212
    0,                          // 213
    0,                          // 214
    0,                          // 215
    0,                          // 216
    0,                          // 217
    0,                          // 218
    0,                          // 219
    0,                          // 220
    0,                          // 221
    0,                          // 222
    0,                          // 223
    0,                          // 224
    0,                          // 225
    0,                          // 226
    0,                          // 227
    0,                          // 228
    0,                          // 229
    0,                          // 230
    0,                          // 231
    0,                          // 232
    0,                          // 233
    0,                          // 234
    0,                          // 235
    0,                          // 236
    0,                          // 237
    0,                          // 238
    (handler_func_t)0xffffffff, // reserved for user TRIM value
};

static_assert(sizeof(_interrupt_vectors) == (sizeof(handler_func_t) * (256 - 16)), "interrupt vector table size mismatch");
