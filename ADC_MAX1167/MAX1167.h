/*
 * MAX1167.h
 *
 *  Created on: Feb 27, 2020
 *      Author: i.mishustin
 */

#ifndef MAX1167_H_
#define MAX1167_H_

#include <stdint.h>
#include "spi.h"

#define MAX1167_INTERNAL_CLOCK									(0x01)
#define MAX1167_POWER_DOWN_MODE_NORMAL_1mA_REF_INTERNAL			((0x00) << 1)
#define MAX1167_POWER_DOWN_MODE_SHUTDOWN_0_6uA_REF_INTERNAL		((0x01) << 1)
#define MAX1167_POWER_DOWN_MODE_SLEEP_0_43mA_REF_INTERNAL		((0x02) << 1)
#define MAX1167_POWER_DOWN_MODE_NORMAL_0_6uA_REF_EXTERNAL		((0x03) << 1)
#define MAX1167_SCAN_MODE_SINGLE_CHANNEL_NO_SCAN				((0x00) << 3)
#define MAX1167_SCAN_MODE_SEQ_SCAN_FROM_0_TO_3_CHANNEL			((0x01) << 3)
#define MAX1167_SCAN_MODE_SEQ_SCAN_FROM_2_TO_3_CHANNEL			((0x02) << 3)
#define MAX1167_SCAN_MODE_SCAN_ONE_CHANNEL_FOUR_TIMES			((0x03) << 3)
#define MAX1167_CHANNEL_SELECT_CNANNEL_AIN_0					((0x00) << 5)
#define MAX1167_CHANNEL_SELECT_CNANNEL_AIN_1					((0x01) << 5)
#define MAX1167_CHANNEL_SELECT_CNANNEL_AIN_2					((0x02) << 5)
#define MAX1167_CHANNEL_SELECT_CNANNEL_AIN_3					((0x03) << 5)
#define MAX1167_CHANNEL_SELECT_CNANNEL_AIN_4					((0x04) << 5)
#define MAX1167_CHANNEL_SELECT_CNANNEL_AIN_5					((0x05) << 5)
#define MAX1167_CHANNEL_SELECT_CNANNEL_AIN_6					((0x06) << 5)
#define MAX1167_CHANNEL_SELECT_CNANNEL_AIN_7					((0x07) << 5)

//if you choose MAX1167_SCAN_MODE_SEQ_SCAN_FROM_0_TO_3_CHANNEL
// choosing  MAX1167_CHANNEL_SELECT_CNANNEL_AIN_3 means you are scanning from 0 to 3 channel

#define MAX1167_EOC_PIN											(GPIO_PIN_5)	//change your external interrupt pin

#define CS_ON()													HAL_GPIO_WritePin(SPI4_CS_GPIO_Port, SPI4_CS_Pin, GPIO_PIN_RESET)
#define CS_OFF()												HAL_GPIO_WritePin(SPI4_CS_GPIO_Port, SPI4_CS_Pin, GPIO_PIN_SET)
#define IS_CS_ON()												(HAL_GPIO_ReadPin(SPI4_CS_GPIO_Port, SPI4_CS_Pin) == RESET)

typedef struct SpiErrors
{
	uint16_t txError;
	uint16_t rxError;
}SpiErrors;


typedef struct AnalogInputs
{
	uint16_t analogInput0;
	uint16_t analogInput1;
	uint16_t analogInput2;
	uint16_t analogInput3;
} AnalogInputs;

void MAX1167_configureCCCRegister(void);
void MAX1167_initiateConversionAndReadProccess(void);
void MAX1167_parseAdcData(void);

#endif /* MAX1167_H_ */
