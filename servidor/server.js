const express = require('express');
const mqtt = require('mqtt');
const socketIo = require('socket.io');
const app = express();
const port = 3000;

// Conectar al broker MQTT
const client = mqtt.connect('mqtt://54.162.7.201');

client.on('connect', function () {
  console.log('Conectado al broker MQTT');
  client.subscribe('sensor/estado/#', function (err) {
    if (err) {
      console.error('Error al suscribirse a los temas', err);
    }
  });
});

// Crear un servidor HTTP
const server = app.listen(port, () => {
  console.log(`Servidor corriendo en http://localhost:${port}`);
});
// Inicializar Socket.io
const io = socketIo(server);

// Configurar la carpeta pública
app.use(express.static('public'));

// Escuchar mensajes MQTT y enviarlos a los clientes conectados
client.on('message', (topic, message) => {
  console.log(`Mensaje recibido en el tema ${topic}: ${message.toString()}`);

  // Extraer el ID del sensor del tema MQTT
  const sensorMatch = topic.match(/sensor\/estado\/(\w+)/);
  if (sensorMatch) {
    const sensorId = sensorMatch[1]; // Extraer el ID del sensor (por ejemplo, "Touch")
    const sensorData = JSON.parse(message.toString());

    // Enviar el dato al cliente con el formato adecuado
    io.emit('nuevo_dato', { sensorId, value: sensorData.sensor_estado });
  }
});
