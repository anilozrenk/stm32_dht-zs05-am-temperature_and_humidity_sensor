# stm32_dht-zs05-am-temperature_and_humidity_sensor
Single bus communication.
###Just tested for ZS05 and DHT11
##Pin Diagram
----Sensor----MUC----
---- Vcc ---> 3.3V
---- SDA ---> desired gpio pin (w/pull-up resistor)
---  GND ---> GND
---  SCL ---> GND

##How To
Before include this you have to 
---->#define DHT_PORT <GPIOX>  
---->#define DHT_PIN  <GPIO_PIN_X>
else it uses GPIOA PIN 1
then 
declare DHT_DataTypedef hdht
initiate sensor with DHT_Init(&hdht,&htim);
&htim for timer that has to be in 1MHZ
  

  
