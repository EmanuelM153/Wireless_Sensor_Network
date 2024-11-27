#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT11

// Inicialización del sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Variables para almacenar el estado anterior
float humedadAnterior = -1;      // Inicializado a un valor imposible para el sensor
float temperaturaAnterior = -1;

void setup() {
  String sensorId = "humedad-temperatura";
  Serial.begin(9600);
  dht.begin();
  delay(5000);
  Serial.println(sensorId);
}

void loop() {
  delay(100);

  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error al leer del sensor DHT11.");
    return;
  }

  if (humedad == humedadAnterior && temperatura == temperaturaAnterior)
    return;

  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");

  humedadAnterior = humedad;
  temperaturaAnterior = temperatura;
}
