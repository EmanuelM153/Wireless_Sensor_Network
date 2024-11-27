# Red de Sensores Inalámbricos
Este proyecto es una Red de Sensores Inalámbricos (WSN), con 4 nodos y 4 sensores, que utiliza B.A.T.M.A.N como protocolo de enrutamiento.
Los nodos están configurados para enviar los datos de los sensores a un servidor mediante el protocolo MQTT.

> Los sensores están conectados a través de 3 placas Arduino y 1 placa ESP8266.

En este repositorio se puede encontrar el código en Nix para configurar la instalación y personalización de NixOS para cada nodo en la red. Esto incluye:
* Un servicio systemd para configurar automáticamente el nodo con el módulo _batman-adv_, establecer la tarjeta Wi-Fi en modo ibss y unirse a la red.
* La instalación y personalización de algunos paquetes necesarios, como **iw**, **alfred** y **batctl**.
* Una especialización que activa el modo gateway de B.A.T.M.A.N, habilita NAT y lanza un servidor DHCP.
* Un script en Python para leer y enviar los datos de los sensores al servidor.
* Un servicio systemd para ejecutar automáticamente el script de Python.

> Esta configuración está integrada en un flake que genera una imagen personalizada de instalación de NixOS, permitiendo crear una imagen ISO que se puede grabar en una memoria USB, facilitando el arranque y la copia de contenidos en la memoria RAM.

Finalmente, también se puede encontrar el código fuente de los programas ejecutados por los microcontroladores de las placas, dos simulaciones de una **MANET** (Red Móvil Ad-hoc) escritas en C++ para ser ejecutadas con las bibliotecas de **ns-3**, y los códigos para el procesamiento y muestra de los datos en el servidor.
