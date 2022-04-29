/*
 * zs05.h
 *
 *  Created on: Apr 29, 2022
 *      Author: Anil
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_
#include "stm32f0xx_hal.h"

#ifndef DHT_PORT
#define DHT_PORT GPIOA
#endif
#ifndef DHT_PIN
#define DHT_PIN GPIO_PIN_1
#endif

typedef struct{
	TIM_HandleTypeDef *htim;
	float Temperature;
	float Humidity;
	uint8_t Rh_byte1;
	uint8_t Rh_byte2;
	uint8_t Temp_byte1;
	uint8_t Temp_byte2;
	uint16_t SUM;
	uint8_t Response;
}DHT_DataTypedef;

uint8_t DHT_GetData (DHT_DataTypedef *DHT_Data);
void DHT_Init (DHT_DataTypedef *DHT_Data,TIM_HandleTypeDef *htim);




#endif /* INC_DHT11_H_ */
