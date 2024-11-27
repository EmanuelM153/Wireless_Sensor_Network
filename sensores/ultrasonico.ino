const int trigPin = 6;
const int echoPin = 7;

// Variables para las mediciones
long duration;
float lastDistance = -500.0;
float distance;

void setup() {
  String sensorId = "ultrasonico";
  Serial.begin(9600);
  delay(5000); // Espera para estabilizar
  Serial.println(sensorId);

  // Configuración de los pines
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Realizar la primera medición
  distance = measureDistance();
  delay(100); // Esperar antes de la siguiente medición

  // Imprimir una medición solo si los valores son diferentes
  String text = "Distancia en cm: ";
  if (distance != lastDistance) {
    Serial.print(text);          // Imprimir el texto
    Serial.println(distance, 0); // Imprimir el número sin decimales

    lastDistance = distance;
  };
}

// Función para medir la distancia
float measureDistance() {
  // Enviar pulso de 10 µs
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer duración del pulso
  duration = pulseIn(echoPin, HIGH);

  // Convertir duración a distancia (en cm)
  float distance = (duration * 0.034 / 2);

  return distance;
}
