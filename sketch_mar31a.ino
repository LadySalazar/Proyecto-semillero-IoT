#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
static const uint8_t D4   = 2;
DHT dht(DHTPIN, DHTTYPE);

#include <DallasTemperature.h>
#include <OneWire.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.begin(9600); 
  sensors.begin();
}

void loop() {
  delay(5000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print("DHT11 --- Temperature is: ");
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  sensors.requestTemperatures();                // Send the command to get temperatures  
  Serial.println("DS18B20 --- Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0));   // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  delay(500);
  Serial.println(" \n\n");
  
}
