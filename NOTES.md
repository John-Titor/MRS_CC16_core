# Notes on the MRS Electronics CC16WP

SoC:    NXP S32K144 / S32K148 (1.154.302.00)
Tools:  MRS Applics Studio
        NXP S32K Developer Studio
        NXP S32K SDK

Defines:    BOARD_PINOUT_CONFIG=2

## EEPROM

EEPROM range 0-0x7ff is reserved by MRS; user data should only occupy 0x800-0xfff.

## Open issues

 - Function of DI_AI_VARIANTE (no description in IDE)
 - Initial vector table - are stack / entrypoint set?

## Memory Map

Base            Size            Function
-----------------------------------------
0x0000_0000     0x0001_0000     Boot ROM
0x0001_0000     0x0000_1000     Application header
0x0001_1000     0x0000_0400     Interrupt vectors (initial)
0x0001_1400     0x0000_0010     Flash configuration
0x0001_1410     0x0006_bbf0     Application program

### Application header

````
typedef struct
{
    uint32_t header_key;          default 0x12345678
    uint32_t header_crc;          crc32 from 0x10008-0x10fff
    uint32_t app_header_version;  default 1
    uint32_t application_crc;     crc32 from 0x11000 of application_length
    uint32_t application_length;  app length (multiple of 256)
    uint8_t sw_version[32];       default "NO PROG"
    uint8_t reserve[460];         zeros
    uint8_t signature_key[512];   zeros
} struct_hal_sys_app_header_t;
````

### Flash configuration

````
.section .FlashConfig, "a"
.long 0xFFFFFFFF     /* 8 bytes backdoor comparison key           */
.long 0xFFFFFFFF     /*                                           */
.long 0xFFFFFFFF     /* 4 bytes program flash protection bytes    */
.long 0xFFFF7FFE     /* FDPROT:FEPROT:FOPT:FSEC(0xFE = unsecured) */
````

## Bootloader config

### Clocking

See S32K144 reference manual, fig 27-1 for specific clock routing and names.

The bootloader launches the application with clocking configured:

clock           frequency
--------------------------
FIRC_CLK        48MHz
FIRCDIV1_CLK    disabled
FIRCDIV2_CLK    disabled
SIRC_CLK        8MHz
SIRCDIV1_CLK    disabled
SIRCDIV2_CLK    disabled
SOSCK_CLK       16MHz
SOSCDIV1_CLK    8MHz
SOSCDIV2_CLK    8MHz
SPLL_CLK        160MHz
CORE_CLK        80MHz
SYS_CLK         80MHz
BUS_CLK         40MHz
FLASH_CLK       26.6MHz
SCG_SLOW_CLK    26.6MHz
SPLLDIV1_CLK    80MHz
SPLLDIV2_CLK    40MHz
CLKOUT          ?
LPO_CLK         ?
RTC_CLK         ?

### Peripheral configuration

#### Clocking

The bootloader leaves most peripherals off; only the following are clocked on at
app start:

clock           device
-----------------------
FTFC            flash memory
FlexCAN0        CAN0
PORTA           JTAG and CAN PHY control pins
PORTE           CAN and CAN PHY control pins

#### Pin config

Only JTAG and CAN-related pins are configured by the bootloader.

pin         function
---------------------
A_04        SWD_DIO
A_05        RESET_b
A_10        TRACE_SWO
A_11        CAN_EN1

E_01        CAN_STB1
E_04        CAN0_RX
E_05        CAN0_TX

#### CAN config

##### Bootloader CAN register dump

Bootloader configured on CAN0 at 500kbps

MCR             88130803
    MDIS = 1        Module disabled
    NOTRDY = 1      Module not ready
    ...

CTRL1           096d6002
    ignored, see CBT (due to CBT.BTF=1)

TIMER           00008e82
RXMGMASK        1fffffff
RX14MASK        1fffffff
RX15MASK        1fffffff
ECR             00000000
ESR1            00000000
IMASK1          00000007
IFLAG1          00000004
CTRL2           00a01000
ESR2            00036000
CRCR            00026c9a
RXFGMASK        ffffffff
RXFIR           406363bb
CBT             812508a5
    BTF = 1         Using these values
    EPRESDIV = 0x33 /52
    ERJW = 5
    EPROPSEG = 2
    EPSEG1 = 5
    EPSEG2 = 5

CTRL1_PN        00000100
CTRL2_PN        00000000
WU_MTC          00000000
FLT_ID1         00000000
FLT_DLC         00000008
PL1_LO          00000000
PL1_HI          00000000
FLT_ID2_IDMASK  00000000
PL2_PLMASK_LO   00000000
PL2_PLMASK_HI   00000000
FDCTRL          80030100
FDCBT           009604c6
FDCRC           02006c9a

MCR             88130803 0002100f !
CTRL1           096d6002 01614007 !
TIMER           00008e82 00003648 !
RXMGMASK        1fffffff ffffffff !
RX14MASK        1fffffff ffffffff !
RX15MASK        1fffffff ffffffff !
ECR             00000000 00000000
ESR1            00000000 00040080 !
IMASK1          00000007 00000002 !
IFLAG1          00000004 00000000 !
CTRL2           00a01000 00a00000 !
ESR2            00036000 00026000 !
CRCR            00026c9a 00006d5a !
RXFGMASK        ffffffff ffffffff
RXFIR           406363bb 406363bb
CBT             812508a5 00251c81 !
CTRL1_PN        00000100 00000100
CTRL2_PN        00000000 00000000
WU_MTC          00000000 00000000
FLT_ID1         00000000 00000000
FLT_DLC         00000008 00000008
PL1_LO          00000000 00000000
PL1_HI          00000000 00000000
FLT_ID2_IDMASK  00000000 00000000
PL2_PLMASK_LO   00000000 00000000
PL2_PLMASK_HI   00000000 00000000
FDCTRL          80030100 80030000 !
FDCBT           009604c6 009604c6
FDCRC           02006c9a 000051d5 !

## Pin mapping by function

### "Virtual" output pins

In addition to the SoC pins, 14 additional outputs are attached to a shift register with behaviour similar to the 74595.
Virtual pin V_00 is shifted in first.

Where virtual pins are mentioned elsewhere in this document, they are associated with Port V
(i.e. V_xx).

Assignment              Port_Pin    595 pin         Function
------------------------------------------------------------
DO_SHIFT_MR             E_16        RESET           Active low reset. Must be high to operate.
DO_SHIFT_OE             E_15        OUTPUT ENABLE   Low to enable outputs.
DO_SHIFT_SH_CP          D_00        SHIFT CLOCK     Shifts next bit in on rising edge.
DO_SHIFT_ST_CP          D_01        LATCH_CLOCK     Latches shifted bits to output on rising edge.
DO_SHIFT_IN_DS          D_06        A               Serial data.

Assignment              Port_Pin    Function
--------------------------------------------
DCDC_8V5                V_00        VRef 8V5 select
DCDC_10V                V_01        VRef 10V select
PD_A_IN5                V_02        input pull-down enable
PD_A_IN4                V_03         "
PD_A_IN3                V_04
PD_A_IN2                V_05
PD_A_IN1                V_06
PD_A_IN0                V_07
PU_A_IN5                V_08        input pull-up enable
PU_A_IN4                V_09         "
PU_A_IN3                V_10
PU_A_IN2                V_11
PU_A_IN1                V_12
PU_A_IN0                V_13

### System power control

Assignment              Port_Pin    Function
--------------------------------------------
DO_POWER                D_15        Holds power on in the absence of KL15 and any CAN / LIN transciever wakeup signal.
DI_KL15                 D_13        KL15 input pin
WD                      E_11        external watchdog pin, not used by BOARD_PINOUT_CONFIG=2

#### Sensor reference supply (pin A7)

Up to 500mA may be sourced from pin A7, with various voltage options:

DO_VREF_EN  DCDC_8V5    DCDC_10V    Output
------------------------------------------
0           x           x           off
1           0           0           5V
1           1           0           8V5
1           x           1           10V

Assignment              Port_Pin    Function
--------------------------------------------
DO_VREF_EN              D_10        LM34919 SHUTDOWN
DI_PGD                  A_17        VRef power good signal
DCDC_8V5                V_00        LM34919 FB control
DCDC_10V                V_01        LM34919 FB control
DI_AI_VREF              D_03        ADC1/3, 14444mV full-scale

### CAN/LIN/Serial interfaces and transciever controls

Assignment              Port_Pin    Function
---------------------------------------------
CAN_EN1                 A_11        TJA1043 EN
CAN_ERR1                E_00        TJA1043 ERR_N
CAN_STB1                E_01        TJA1043 STB_N
CAN_WAKE1               A_14        TJA1043 WAKE
MC_CAN_RXD1             E_04        TJA1043 RXD
MC_CAN_TXD1             E_05        TJA1043 TXD
CAN_EN2                 E_12 (1)    TJA1043 EN
CAN_ERR2                E_13 (1)    TJA1043 ERR_N
CAN_STB2                E_03 (1)    TJA1043 STB_N
CAN_WAKE2               E_14 (1)    TJA1043 WAKE
MC_CAN_RXD2             A_12 (1)    TJA1043 RXD
MC_CAN_TXD2             A_13 (1)    TJA1043 TXD
LIN_EN                  E_09 (2)    LIN xcvr EN
MC_SCI_RXD              A_08 (3)    LIN/RS232 xcvr RXD
MC_SCI_TXD              A_09 (3)    LIN/RS232 xcvr TXD

(1) CAN CAN model only
(2) CAN LIN model only
(3) CAN RS232 model only

### Analog/Digital inputs and controls

#### Inputs IN0-IN5

Assignment              Port_Pin  ADC       Full-scale           
-------------------------------------------------------
DI_AI_A_IN0             B_01      0/5       16920mV / 32250mV
DI_AI_A_IN1             B_00      0/4       16920mV / 32250mV
DI_AI_A_IN2             A_07      0/3       16920mV / 32250mV
DI_AI_A_IN3             A_06      0/2       16920mV / 32250mV
DI_AI_A_IN4             B_16      1/15      16920mV / 32250mV
DI_AI_A_IN5             B_15      1/14      16920mV / 32250mV

#### Controls IN0-IN5

Assignment              Port_Pin    Function
----------------------------------------------
PU_A_IN0                V_13        1k0 pull-up enable
PU_A_IN1                V_12         "
PU_A_IN2                V_11         "
PU_A_IN3                V_10         "
PU_A_IN4                V_09         "
PU_A_IN5                V_08         "
PD_A_IN0                V_07        330R pull-down enable
PD_A_IN1                V_06         "
PD_A_IN2                V_05         "
PD_A_IN3                V_04         "
PD_A_IN4                V_03         "
PD_A_IN5                V_02         "
DO_RS0                  C_09        16920mV / 32250mV range select
DO_RS1                  E_07         "
DO_RS2                  B_08         "
DO_RS3                  C_08         "
DO_RS4                  B_11         "
DO_RS5                  B_17         "

#### Misc analog inputs

Assignment              Port_Pin    ADC       Full-scale  Function
-------------------------------------------------------------------
DI_AI_ID                C_07        1/5       16920mV     analog input or ID pin
DI_AI_KL30_1            C_02 (1)    0/10      39000mv     pin A1 KL30 sense
DI_AI_KL30_2            C_03 (1)    0/11      39000mv     pin A8 KL30 sense
DI_AI_VARIANTE          C_06        1/4       5000mV      ???

(1) Only connected when DO_POWER is 1.

#### Misc digital inputs

Assignment              Port_Pin    Function
--------------------------------------------
MC_FREQ_A_IN0           C_10        input frequency measurement
MC_FREQ_A_IN1           C_11         "
MC_FREQ_A_IN2           C_12         "
MC_FREQ_A_IN3           C_13         "
MC_FREQ_A_IN4           B_09         "
MC_FREQ_A_IN5           B_10         "
DI_INTERFACE2_A         D_07 (1)
DI_INTERFACE2_B         D_08 (1)

(1) CAN GPIO model only.

### High-side outputs, controls and feedback

Outputs are driven by two VNQ5050AK-E high-side drivers, HSD1 and HSD2.

#### Output controls

Assignment              Port_Pin    Function
----------------------------------------------
DO_HSD1_OUT0            D_14        HSD1 INPUT1
DO_HSD1_OUT1            B_04        HSD1 INPUT2
DO_HSD1_OUT2            E_08        HSD1 INPUT3
DO_HSD1_OUT3            B_05        HSD1 INPUT4
DO_HSD2_OUT4            D_05        HSD2 INPUT1
DO_HSD2_OUT5            D_12        HSD2 INPUT2
DO_HSD2_OUT6            D_09        HSD2 INPUT3
DO_HSD2_OUT7            D_16        HSD2 INPUT4
DO_CS_HSD1              D_17 (1)    HSD1 CS_DIS
DO_CS_HSD2              D_11 (1)    HSD2 CS_DIS

(1) At most one of DO_CS_HSDx should be set low at a time to select
    either HSD1 or HSD2 OUTPUT CURRENTx sensing on DI_AI_SNSx.

#### Feedback signals

DI_AI_INA_OUTx and DI_AI_SNSx have EEPROM calibration data, formatted as 3-point
1D linear interpolation tables. Each table is 3 16-bit X values followed by 3 16-bit
Y values, with input being on the X axis. Values outside of the table are interpolated
using the slope of the closest segment, with output constrained to -32768...32767.

DI_AI_INA_OUTx have 3-point source/sink tables @ 24B each, starting at 0x222.
DI_AI_SNSx have 3-point source tables @ 12B each, starting at 0x2e2, with two
sets of tables, one for HSD1 followed by one for HSD2.

Despite the differing table types, only the first 3 points in either table type
is used. Presumably this design would support an H-bridge driver arrangement, but
for the CC16 at least it appears that output current sensing is duplicated.

Assignment              Port_Pin    ADC       Full-scale  Function                    
-------------------------------------------------------------------
DI_AI_OUT0              E_06        1/11      39340mV     HSD1 OUTPUT1
DI_AI_OUT1              A_00        0/0       39340mV     HSD1 OUTPUT2
DI_AI_OUT2              A_15        1/12      39340mV     HSD1 OUTPUT3
DI_AI_OUT3              A_16        1/13      39340mV     HSD1 OUTPUT4
DI_AI_OUT4              A_01        0/1       39340mV     HSD2 OUTPUT1
DI_AI_OUT5              D_02        1/2       39340mV     HSD2 OUTPUT2
DI_AI_OUT6              A_02        1/0       39340mV     HSD2 OUTPUT3
DI_AI_OUT7              A_03        1/1       39340mV     HSD2 OUTPUT4
DI_AI_INA_OUT0          C_16        0/14      5000mV      ???
DI_AI_INA_OUT1          C_17        0/15      5000mV      ???
DI_AI_INA_OUT2          C_01        0/9       5000mV      ???
DI_AI_INA_OUT3          C_00        0/8       5000mV      ???
DI_AI_INA_OUT4          B_02        0/6       5000mV      ???
DI_AI_INA_OUT5          C_14        0/12      5000mV      ???
DI_AI_INA_OUT6          C_15        0/13      5000mV      ???
DI_AI_INA_OUT7          B_03        0/7       5000mV      ???
DI_AI_SNS1              B_13 (1)    1/8       32000mV     HSD1/HSD2 CURRENT SENSE1
DI_AI_SNS2              B_14 (1)    1/9       32000mV     HSD1/HSD2 CURRENT SENSE2
DI_AI_SNS3              D_04 (1)    1/6       32000mV     HSD1/HSD2 CURRENT SENSE3
DI_AI_SNS4              B_12 (1)    1/7       32000mV     HSD1/HSD2 CURRENT SENSE4

(1) Pins are shared, only one of DO_CS_HSDx may be low at a time to ensure
    correct measurement.

### Misc system / unexposed pins

Assignment              Port_Pin    
--------------------------------
MC_JTAG_TCLK            C_04
MC_JTAG_TDI             C_05
MC_JTAG_TDO             A_10
MC_JTAG_TMS             A_04
MC_JTAG_TRST            A_05
Pin74                   E_02
Pin82                   E_10
EXTAL                   B_07
XTAL                    B_06


## External pin mapping

Pin         Associated Function
-------------------------------
A1          KL30_1
A2          LIN Data, CAN1_H, RS232-?X, DI_INTERFACE2_A
A3          IN5
A4          IN4
A5          IN2
A6          IN1
A7          VRefOut
A8          KL30_2
B1          OUT3
B2          CAN1_L, RS232-?X, DI_INTERFACES2_B
B3          AI_ID
B4          CAN0_H
B5          KL15
B6          IN0
B7          Ground
B8          OUT4
C1          OUT2
C2          OUT1
C3          OUT0
C4          IN3
C5          CAN0_L
C6          OUT7
C7          OUT6
C8          OUT5


## Pin mapping by port/pin

Port_Pin    Assignment
----------------------
A_00        DI_AI_OUT1
A_01        DI_AI_OUT4
A_02        DI_AI_OUT6
A_03        DI_AI_OUT7
A_04        MC_JTAG_TMS
A_05        MC_JTAG_TRST
A_06        DI_AI_A_IN3
A_07        DI_AI_A_IN2
A_08        MC_SCI_RXD
A_09        MC_SCI_TXD
A_10        MC_JTAG_TDO
A_11        CAN_EN1
A_12        MC_CAN_RXD2
A_13        MC_CAN_TXD2
A_14        CAN_WAKE1
A_15        DI_AI_OUT2
A_16        DI_AI_OUT3
A_17        DI_PGD

B_00        DI_AI_A_IN1
B_01        DI_AI_A_IN0
B_02        DI_AI_INA_OUT4
B_03        DI_AI_INA_OUT7
B_04        DO_HSD1_OUT1
B_05        DO_HSD1_OUT3
B_06        XTAL
B_07        EXTAL
B_08        DO_RS2
B_09        MC_FREQ_A_IN4
B_10        MC_FREQ_A_IN5
B_11        DO_RS4
B_12        DI_AI_SNS4
B_13        DI_AI_SNS1
B_14        DI_AI_SNS2
B_15        DI_AI_A_IN5
B_16        DI_AI_A_IN4
B_17        DO_RS5

C_00        DI_AI_INA_OUT3
C_01        DI_AI_INA_OUT2
C_02        DI_AI_KL30_1
C_03        DI_AI_KL30_2
C_04        MC_JTAG_TCLK
C_05        MC_JTAG_TDI
C_06        DI_AI_VARIANTE
C_07        DI_AI_ID
C_08        DO_RS3
C_09        DO_RS0
C_10        MC_FREQ_A_IN0
C_11        MC_FREQ_A_IN1
C_12        MC_FREQ_A_IN2
C_13        MC_FREQ_A_IN3
C_14        DI_AI_INA_OUT5
C_15        DI_AI_INA_OUT6
C_16        DI_AI_INA_OUT0
C_17        DI_AI_INA_OUT1

D_00        DO_SHIFT_SH_CP
D_01        DO_SHIFT_ST_CP
D_02        DI_AI_OUT5
D_03        DI_AI_VREF
D_04        DI_AI_SNS3
D_05        DO_HSD2_OUT4
D_06        DOX_SHIFT_IN_DS
D_07        DI_INTERFACE2_A
D_08        DI_INTERFACE2_B
D_09        DO_HSD2_OUT6
D_10        DO_VREF_EN
D_11        DO_CS_HSD2
D_12        DO_HSD2_OUT5
D_13        DI_KL15
D_14        DO_HSD1_OUT0
D_15        DO_POWER
D_16        DO_HSD2_OUT7
D_17        DO_CS_HSD1

E_00        CAN_ERR1
E_01        CAN_STB1
E_02        Pin74
E_03        CAN_STB2
E_04        MC_CAN_RXD1
E_05        MC_CAN_TXD1
E_06        DI_AI_OUT0
E_07        DO_RS1
E_08        DO_HSD1_OUT2
E_09        LIN_EN
E_10        Pin82
E_11        WD
E_12        CAN_EN2
E_13        CAN_ERR2
E_14        CAN_WAKE2
E_15        DO_SHIFT_OE
E_16        DO_SHIFT_MR

## ADC channel mapping

Channel     Signal          Function
-------------------------------------
0/0         DI_AI_OUT1      HSD1 OUTPUT2
0/1         DI_AI_OUT4      HSD2 OUTPUT1
0/2         DI_AI_A_IN3     IN3
0/3         DI_AI_A_IN2     IN2
0/4         DI_AI_A_IN1     IN1
0/5         DI_AI_A_IN0     IN0
0/6         DI_AI_INA_OUT4  ???
0/7         DI_AI_INA_OUT7  ???
0/8         DI_AI_INA_OUT3  ???
0/9         DI_AI_INA_OUT2  ???
0/10        DI_AI_KL30_1    pin A1 KL30 sense
0/11        DI_AI_KL30_2    pin A8 KL30 sense
0/12        DI_AI_INA_OUT5  ???
0/13        DI_AI_INA_OUT6  ???
0/14        DI_AI_INA_OUT0  ???
0/15        DI_AI_INA_OUT1  ???
1/0         DI_AI_OUT6      HSD2 OUTPUT3
1/1         DI_AI_OUT7      HSD2 OUTPUT4
1/2         DI_AI_OUT5      HSD2 OUTPUT2
1/3         DI_AI_VREF      Sensor reference supply readback
1/4         DI_AI_VARIANTE  ???
1/5         DI_AI_ID        analog input or ID pin
1/6         DI_AI_SNS3      HSD1/HSD2 CURRENT SENSE3
1/7         DI_AI_SNS4      HSD1/HSD2 CURRENT SENSE4
1/8         DI_AI_SNS1      HSD1/HSD2 CURRENT SENSE1
1/9         DI_AI_SNS2      HSD1/HSD2 CURRENT SENSE2
1/10        Pin74           nc
1/11        DI_AI_OUT0      HSD1 OUTPUT1
1/12        DI_AI_OUT2      HSD1 OUTPUT3
1/13        DI_AI_OUT3      HSD1 OUTPUT4
1/14        DI_AI_A_IN5     IN5
1/15        DI_AI_A_IN4     IN4
