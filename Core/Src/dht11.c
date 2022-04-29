/*
 * zs05.c
 *
 *  Created on: Apr 29, 2022
 *      Author: Anil
 */
#include <dht11.h>



void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void delay_us (uint16_t us,TIM_HandleTypeDef *htim)
{
	__HAL_TIM_SET_COUNTER(htim,0);
	while (__HAL_TIM_GET_COUNTER(htim) < us);
}
void DHT_Init (DHT_DataTypedef *DHT_Data, TIM_HandleTypeDef *_htim){
	DHT_Data->htim = _htim;
	DHT_Data->Temperature = 25;
	DHT_Data->Humidity = 55;
	DHT_Data->Response = 0;

}
void DHT_Start (TIM_HandleTypeDef *htim)
{
	Set_Pin_Output (DHT_PORT, DHT_PIN);  // set the pin as output
	HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 0);   // pull the pin low


	delay_us(18000,htim);   // wait for 18ms
    HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 1);   // pull the pin high
    delay_us(20,htim);   // wait for 30us
	Set_Pin_Input(DHT_PORT, DHT_PIN);    // set as input
}
uint8_t DHT_Check_Response (TIM_HandleTypeDef *htim)
{
	uint8_t _Response = 0;
	delay_us(40,htim);
	if (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))
	{
		delay_us(80,htim);
		if ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))) _Response = 1;
		else _Response = -1;
	}
	while ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));   // wait for the pin to go low

	return _Response;
}
uint8_t DHT_Read (TIM_HandleTypeDef *htim)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));   // wait for the pin to go high
		delay_us(40,htim);   // wait for 40 us
		if (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))   // if the pin is low
		{
			i&= ~(1<<(7-j));   // write 0
		}
		else i|= (1<<(7-j));  // if the pin is high, write 1
		while ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));  // wait for the pin to go low
	}
	return i;
}

uint8_t DHT_GetData (DHT_DataTypedef *DHT_Data)
{
    DHT_Start (DHT_Data->htim);
	DHT_Data->Response = DHT_Check_Response (DHT_Data->htim);
	DHT_Data->Rh_byte1 = DHT_Read (DHT_Data->htim);
	DHT_Data->Rh_byte2 = DHT_Read (DHT_Data->htim);
	DHT_Data->Temp_byte1 = DHT_Read (DHT_Data->htim);
	DHT_Data->Temp_byte2 = DHT_Read (DHT_Data->htim);
	DHT_Data->SUM = DHT_Read(DHT_Data->htim);

	if (DHT_Data->SUM == (DHT_Data->Rh_byte1+DHT_Data->Rh_byte2+DHT_Data->Temp_byte1+DHT_Data->Temp_byte2))
	{
	//	#if defined(TYPE_DHT11)
			DHT_Data->Temperature = DHT_Data->Temp_byte1;
			DHT_Data->Humidity = DHT_Data->Rh_byte1;
	//	#endif

//		#if defined(TYPE_DHT22)
//			DHT_Data->Temperature = ((Temp_byte1<<8)|Temp_byte2);
//			DHT_Data->Humidity = ((Rh_byte1<<8)|Rh_byte2);
//		#endif

		return 0;
	}
	else return 1;
}

