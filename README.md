# ADC_MAX1167
ADC_MAX1167 for stm32 using HAL

for using this lib redefine some lines like this

#define CS_ON()													HAL_GPIO_WritePin(SPI4_CS_GPIO_Port, SPI4_CS_Pin, GPIO_PIN_RESET)
#define CS_OFF()												HAL_GPIO_WritePin(SPI4_CS_GPIO_Port, SPI4_CS_Pin, GPIO_PIN_SET)
#define IS_CS_ON()												(HAL_GPIO_ReadPin(SPI4_CS_GPIO_Port, SPI4_CS_Pin) == RESET)

and redifine your spi port like this

extern SPI_HandleTypeDef hspi4;
