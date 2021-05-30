/*
 * MAX1167.c
 *
 *  Created on: Feb 27, 2020
 *      Author: i.mish
 */

#include "MAX1167.h"


#define DATA_SIZE		(8)

extern SPI_HandleTypeDef hspi4; //implement your spi handler

static uint8_t _commandConfigurationControlRegister[2];
static uint8_t _spiReceiveBuffer[DATA_SIZE];

static SpiErrors _spiErrors; //prototype (reserved)

AnalogInputs analogInputs;

void MAX1167_configureCCCRegister(void)
{
	_commandConfigurationControlRegister[0] = 0;
	_commandConfigurationControlRegister[0] |= MAX1167_INTERNAL_CLOCK | MAX1167_POWER_DOWN_MODE_NORMAL_1mA_REF_INTERNAL | MAX1167_SCAN_MODE_SEQ_SCAN_FROM_0_TO_3_CHANNEL | MAX1167_CHANNEL_SELECT_CNANNEL_AIN_3;
}

void MAX1167_initiateConversionAndReadProccess(void)
{
	if(IS_CS_ON()){
		return;
	}

	CS_ON();
	HAL_SPI_Transmit_DMA(&hspi4, _commandConfigurationControlRegister, 1);
}

//---------------------------------------------------------------
// implement adcDataCompleteCallback in usercode
//---------------------------------------------------------------

__weak void adcDataCompleteCallback(AnalogInputs* analogInputs)
{

}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi == &hspi4){

	}
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi == &hspi4){
		CS_OFF();
			//parse data here
		MAX1167_parseAdcData();
		adcDataCompleteCallback(&analogInputs);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == MAX1167_EOC_PIN){
		HAL_SPI_Receive_DMA(&hspi4, _spiReceiveBuffer, DATA_SIZE);
	}
}

void MAX1167_parseAdcData(void)
{
	analogInputs.analogInput0 = (uint16_t)_spiReceiveBuffer[1];
	analogInputs.analogInput0 |= ((uint16_t)_spiReceiveBuffer[0] << 8);
	analogInputs.analogInput1 = (uint16_t)_spiReceiveBuffer[3];
	analogInputs.analogInput1 |= ((uint16_t)_spiReceiveBuffer[2] << 8);
	analogInputs.analogInput2 = (uint16_t)_spiReceiveBuffer[5];
	analogInputs.analogInput2 |= ((uint16_t)_spiReceiveBuffer[4] << 8);
	analogInputs.analogInput3 = (uint16_t)_spiReceiveBuffer[7];
	analogInputs.analogInput3 |= ((uint16_t)_spiReceiveBuffer[6] << 8);
}

