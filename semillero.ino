#include "Ubidots.h"
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
OneWire ourWire1(14);                //Se establece el pin 2  como bus OneWire
OneWire ourWire2(13);                //Se establece el pin 3  como bus OneWire
DallasTemperature sensors1(&ourWire1); //Se declara una variable u objeto para nuestro sensor1
DallasTemperature sensors2(&ourWire2); //Se declara una variable u objeto para nuestro sensor2
const char* UBIDOTS_TOKEN = "BBFF-GTgKUhzu7n6qkfKMqsFYfgIZPzyy1Z";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "santiagoniñov";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "juanpalo";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  sensors1.begin();   //Se inicia el sensor 1
  sensors2.begin();   //Se inicia el sensor 2
}
void loop() {
 sensors1.requestTemperatures();   //Se envía el comando para leer la temperatura
float temp1= sensors1.getTempCByIndex(0); //Se obtiene la temperatura en ºC del sensor 1
sensors2.requestTemperatures();   //Se envía el comando para leer la temperatura
float temp2= sensors2.getTempCByIndex(0); //Se obtiene la temperatura en ºC del sensor 2
  ubidots.add("TEMPERATURA.1", temp1);  // Change for your variable name
  ubidots.add("TEMPERATURA.2", temp2);
  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id
  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
    Serial.print("Temperatura 1 = ");
    Serial.print(temp1);
    Serial.print(" C");
    Serial.print("   Temperatura 2 = ");
    Serial.print(temp2);
    Serial.println(" C");
  }
  delay(5000);
}
