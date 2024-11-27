import paho.mqtt.client as mqtt
import serial
import json

BROKER = "cinco.en.el.proyecto"
PORT = 1883
TOPIC = "sensor/estado/"

arduino = serial.Serial('/dev/ttyACM0', 9600)

def on_connect(client, userdata, flags, rc):
    print("Conectado con resultado: " + str(rc))

client = mqtt.Client()
client.on_connect = on_connect

client.connect(BROKER, PORT, 60)

while True:
    if arduino.in_waiting > 0:
        data = arduino.readline().decode('utf-8').strip()
        message = {
            "sensor_estado": data
        }

        if (TOPIC == "sensor/estado/"):
            message = {
                "nombre_sensor": data
            }
            TOPIC += data


        client.publish(TOPIC, json.dumps(message))
        print(f"Mensaje enviado: {message}")
    client.loop()

