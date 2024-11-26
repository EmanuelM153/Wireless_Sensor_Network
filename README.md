# Wireless Sensor Network
This project is a Wireless Sensor Network (WSN), with _4_ nodes and _4_ sensors, that uses B.A.T.M.A.N as the routing protocol. 
The nodes are configured to send the sensor's data to a server, that formats and displays the information, through the MQTT protocol.

> The sensors are connected through _3_ Arduino boards and _1_ ESP8266 board

In this repository it can be found the Nix code for configuring the NixOS installation for each node in the network. It includes:
* A systemd service for automatically configuring the node to use the batman-adv module, to set the wifi card in ibss mode, and to join the network
* The installation and customization of some needed packages, such as **iw**, **alfred** and **batctl**
* A specialisation for the gateway node that activates B.A.T.M.A.N gateway mode, enables NAT, and starts a DHCP server
* A python script for reading and sending sensor data to the server
* A systemd service for automatically executing the python script

> Additionally this configuration is installed in a liveBoot "computer" (within a flake), so that an iso image can be created and written in a usb stick, letting you boot and copy the contents to the RAM memory

Finally, it can also be found the source code for the programs run by the microcontrollers of the boards
