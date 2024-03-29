#include <DHT.h>
#include "System.h"

#define DHTTYPE DHT11   // DHT 11

// Prototypes
DHT dht(PIN_DHT11, DHTTYPE);

float HeatIndex = 0.0;

extern float GetHeatIndex(void)
{
	return HeatIndex;
}

extern void ReadTemperature(void)
{
  float Temp;
  float Humidity;

  Humidity = dht.readHumidity();
  Temp = dht.readTemperature();
  HeatIndex = dht.computeHeatIndex(Temp, Humidity, false);
}

extern void InitTemperature(void)
{
  dht.begin();
}
