#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "pins_driver.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/*! @brief Definitions/Declarations for BOARD_InitPins Functional Group */
/*! @brief User definition pins */
#define DI_AI_OUT1_PORT    PTA
#define DI_AI_OUT1_PIN     0U
#define DI_AI_OUT4_PORT    PTA
#define DI_AI_OUT4_PIN     1U
#define DI_AI_OUT6_PORT    PTA
#define DI_AI_OUT6_PIN     2U
#define DI_AI_OUT7_PORT    PTA
#define DI_AI_OUT7_PIN     3U
#define DI_AI_A_IN3_PORT    PTA
#define DI_AI_A_IN3_PIN     6U
#define DI_AI_A_IN2_PORT    PTA
#define DI_AI_A_IN2_PIN     7U
#define CAN_EN1_PORT    PTA
#define CAN_EN1_PIN     11U
#define CAN_WAKE1_PORT    PTA
#define CAN_WAKE1_PIN     14U
#define DI_PGD_PORT    PTA
#define DI_PGD_PIN     17U
#define DI_AI_A_IN1_PORT    PTB
#define DI_AI_A_IN1_PIN     0U
#define DI_AI_A_IN0_PORT    PTB
#define DI_AI_A_IN0_PIN     1U
#define DI_AI_INA_OUT4_PORT    PTB
#define DI_AI_INA_OUT4_PIN     2U
#define DI_AI_INA_OUT7_PORT    PTB
#define DI_AI_INA_OUT7_PIN     3U
#define DO_HSD1_OUT1_PORT    PTB
#define DO_HSD1_OUT1_PIN     4U
#define DO_HSD1_OUT3_PORT    PTB
#define DO_HSD1_OUT3_PIN     5U
#define DO_RS2_PORT    PTB
#define DO_RS2_PIN     8U
#define MC_FREQ_A_IN4_PORT    PTB
#define MC_FREQ_A_IN4_PIN     9U
#define MC_FREQ_A_IN5_PORT    PTB
#define MC_FREQ_A_IN5_PIN     10U
#define DO_RS4_PORT    PTB
#define DO_RS4_PIN     11U
#define DI_AI_SNS4_PORT    PTB
#define DI_AI_SNS4_PIN     12U
#define DI_AI_SNS1_PORT    PTB
#define DI_AI_SNS1_PIN     13U
#define DI_AI_SNS_2_PORT    PTB
#define DI_AI_SNS_2_PIN     14U
#define DI_AI_OUT2_PORT    PTA
#define DI_AI_OUT2_PIN     15U
#define DI_AI_OUT3_PORT    PTA
#define DI_AI_OUT3_PIN     16U
#define DO_RS5_PORT    PTB
#define DO_RS5_PIN     17U
#define DI_AI_INA_OUT3_PORT    PTC
#define DI_AI_INA_OUT3_PIN     0U
#define DI_AI_INA_OUT2_PORT    PTC
#define DI_AI_INA_OUT2_PIN     1U
#define DI_AI_KL30_1_PORT    PTC
#define DI_AI_KL30_1_PIN     2U
#define DI_AI_KL30_2_PORT    PTC
#define DI_AI_KL30_2_PIN     3U
#define DI_AI_VARIANTE_PORT    PTC
#define DI_AI_VARIANTE_PIN     6U
#define DO_AI_ID_PORT    PTC
#define DO_AI_ID_PIN     7U
#define DO_RS3_PORT    PTC
#define DO_RS3_PIN     8U
#define DO_RS0_PORT    PTC
#define DO_RS0_PIN     9U
#define MC_FREQ_A_IN0_PORT    PTC
#define MC_FREQ_A_IN0_PIN     10U
#define MC_FREQ_A_IN1_PORT    PTC
#define MC_FREQ_A_IN1_PIN     11U
#define MC_FREQ_A_IN2_PORT    PTC
#define MC_FREQ_A_IN2_PIN     12U
#define MC_FREQ_A_IN3_PORT    PTC
#define MC_FREQ_A_IN3_PIN     13U
#define DI_AI_INA_OUT5_PORT    PTC
#define DI_AI_INA_OUT5_PIN     14U
#define DI_AI_INA_OUT6_PORT    PTC
#define DI_AI_INA_OUT6_PIN     15U
#define DI_AI_INA_OUT0_PORT    PTC
#define DI_AI_INA_OUT0_PIN     17U
#define DI_AI_INA_OUT1_PORT    PTC
#define DI_AI_INA_OUT1_PIN     16U
#define DO_SHIFT_SH_CP_PORT    PTD
#define DO_SHIFT_SH_CP_PIN     0U
#define DO_SHIFT_ST_CP_PORT    PTD
#define DO_SHIFT_ST_CP_PIN     1U
#define DI_AI_OUT5_PORT    PTD
#define DI_AI_OUT5_PIN     2U
#define DI_AI_VREF_PORT    PTD
#define DI_AI_VREF_PIN     3U
#define DO_HSD2_OUT4_PORT    PTD
#define DO_HSD2_OUT4_PIN     5U
#define DOX_SHIFT_IN_DS_PORT    PTD
#define DOX_SHIFT_IN_DS_PIN     6U
#define DI_INTERFACE2_A_PORT    PTD
#define DI_INTERFACE2_A_PIN     7U
#define DI_INTERFAC2_B_PORT    PTD
#define DI_INTERFAC2_B_PIN     8U
#define DI_HSD2_OUT6_PORT    PTD
#define DI_HSD2_OUT6_PIN     9U
#define DO_VREF_EN_PORT    PTD
#define DO_VREF_EN_PIN     10U
#define DO_CS_HSD2_PORT    PTD
#define DO_CS_HSD2_PIN     11U
#define DO_HSD2_OUT5_PORT    PTD
#define DO_HSD2_OUT5_PIN     12U
#define DI_KL15_PORT    PTD
#define DI_KL15_PIN     13U
#define DO_HSD1_OUT0_PORT    PTD
#define DO_HSD1_OUT0_PIN     14U
#define DO_POWER_PORT    PTD
#define DO_POWER_PIN     15U
#define DO_HSD2_OUT7_PORT    PTD
#define DO_HSD2_OUT7_PIN     16U
#define DO_CS_HSD1_PORT    PTD
#define DO_CS_HSD1_PIN     17U
#define CAN_ERR1_PORT    PTE
#define CAN_ERR1_PIN     0U
#define CAN_STB1_PORT    PTE
#define CAN_STB1_PIN     1U
#define CAN_STB2_PORT    PTE
#define CAN_STB2_PIN     3U
#define DI_AI_OUT0_PORT    PTE
#define DI_AI_OUT0_PIN     6U
#define DO_RS1_PORT    PTE
#define DO_RS1_PIN     7U
#define DO_HSD1_OUT2_PORT    PTE
#define DO_HSD1_OUT2_PIN     8U
#define LIN_EN_PORT    PTE
#define LIN_EN_PIN     9U
#define DO_SHIFT_OE_PORT    PTE
#define DO_SHIFT_OE_PIN     15U
#define DO_SHIFT_MR_PORT    PTE
#define DO_SHIFT_MR_PIN     16U
#define CAN_WAKE2_PORT    PTE
#define CAN_WAKE2_PIN     14U
#define CAN_ERR2_PORT    PTE
#define CAN_ERR2_PIN     13U
#define CAN_EN2_PORT    PTE
#define CAN_EN2_PIN     12U
#define DI_AI_A_IN5_PORT    PTB
#define DI_AI_A_IN5_PIN     15U
#define DI_AI_A_IN4_PORT    PTB
#define DI_AI_A_IN4_PIN     16U
#define DI_AI_SNS3_PORT    PTD
#define DI_AI_SNS3_PIN     4U
/*! @brief User number of configured pins */
#define NUM_OF_CONFIGURED_PINS0 86
/*! @brief User configuration structure */
extern pin_settings_config_t g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0];


#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

