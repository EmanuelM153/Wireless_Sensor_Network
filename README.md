# Wireless Sensor Network
This project is a Wireless Sensor Network (WSN), with 4 nodes and 4 sensors, that uses B.A.T.M.A.N as the routing protocol. 
The nodes are configured to send the sensor's data to a server through the MQTT protocol.

> The sensors are connected through 3 Arduino boards and 1 ESP8266 board

In this repository you can found the Nix code for configuring the NixOS installation and customization for each node in the network. It includes:
* A systemd service for automatically configuring the node to use the batman-adv module, to set the wifi card in ibss mode, and to join the network
* The installation and customization of some needed packages, such as **iw**, **alfred** and **batctl**
* A specialisation for the gateway node that activates B.A.T.M.A.N gateway mode, enables NAT, and starts a DHCP server
* A python script for reading and sending sensor data to the server
* A systemd service for automatically executing the python script

> This configuration is embedded in a flake that outputs a custom NixOS installer image, so that an iso image can be created and written in a usb stick, letting you boot and copy the contents to the RAM memory.

Finally, you can also found the source code for the programs run by the microcontrollers of the boards, and two simulations of a **MANET** (Mobile Ad-hoc Network) written in C++ to be executed with the **ns-3** libraries.
