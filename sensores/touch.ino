#define LED 3
#define TTP223B 4

String estadoGlobal = "APAGADO";

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(TTP223B, INPUT);
  String sensorId = "Touch";

  Serial.begin(9600); // Inicializa la comunicación serial
  delay(5000);
  Serial.println(sensorId);
}

void loop() {
  String estadoSensor;

  // Leer el estado del sensor táctil
  if (digitalRead(TTP223B) == HIGH) {
    digitalWrite(LED, HIGH);
    estadoSensor = "HIGH";
  } else {
    digitalWrite(LED, LOW);
    estadoSensor = "LOW";
  }

  if (estadoSensor != estadoGlobal ){
      Serial.println(estadoSensor);
      estadoGlobal = estadoSensor;
  }

  delay(100);
}
