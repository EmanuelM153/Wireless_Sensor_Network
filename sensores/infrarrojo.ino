#include <IRremote.h>

// Configuración del pin del receptor IR
const int RECV_PIN = 11;

// Variables para el estado actual
int lastState = LOW;
int currentState = LOW;

// Crear un objeto receptor
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  String sensorId = "Infrarrojo";
  Serial.begin(9600);
  delay(5000); // Espera para estabilizar
  Serial.println(sensorId);
  // Iniciar el receptor IR
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    currentState = HIGH; // Cambiar estado si hay señal
    irrecv.resume();     // Preparar para recibir la siguiente señal
  } else {
    currentState = LOW; // Sin señal
  }

  if (lastState != currentState) {
    // Mostrar el estado actual en consola
    if (currentState == HIGH)
      Serial.println("Señal detectada");
    else
      Serial.println("Señal no detectada");

    lastState = currentState;
  }

  delay(500);
}
