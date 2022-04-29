# stm32_dht-zs05-am-temperature_and_humidity_sensor
<br>Single bus communication.<br>
###Just tested for ZS05 and DHT11
##Pin Diagram
<br>----Sensor----MUC----
<br>---- Vcc ---> 3.3V
<br>---- SDA ---> desired gpio pin (w/pull-up resistor)
<br>---  GND ---> GND
<br>---  SCL ---> GND
<br>
##How To
<br>Before include this you have to 
<br>---->#define DHT_PORT <GPIOX>  
<br>---->#define DHT_PIN  <GPIO_PIN_X>
<br>else it uses GPIOA PIN 1
<br>then 
<br>declare DHT_DataTypedef hdht
<br>initiate sensor with DHT_Init(&hdht,&htim);
<br>&htim for timer that has to be in 1MHZ
  

  
