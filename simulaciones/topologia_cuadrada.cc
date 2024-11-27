#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SquareTopologyExample");

int main(int argc, char *argv[])
{
    CommandLine cmd;
    cmd.Parse(argc, argv);

    // Crear 4 nodos
    NodeContainer nodes;
    nodes.Create(4);

    // Configurar el dispositivo Wi-Fi
    WifiHelper wifi;
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager");

    // Crear y configurar el canal Wi-Fi
    YansWifiChannelHelper wifiChannel;
    wifiChannel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
    wifiChannel.AddPropagationLoss("ns3::FriisPropagationLossModel");

    Ptr<YansWifiChannel> channel = wifiChannel.Create();

    YansWifiPhyHelper wifiPhy;
    wifiPhy.SetChannel(channel);

    WifiMacHelper wifiMac;
    wifiMac.SetType("ns3::AdhocWifiMac");

    // Instalar Wi-Fi en los nodos
    NetDeviceContainer devices = wifi.Install(wifiPhy, wifiMac, nodes);

    // Configurar la movilidad en forma de cuadrado
    MobilityHelper mobility;
    Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
    positionAlloc->Add(Vector(0.0, 0.0, 0.0));   // Nodo 0
    positionAlloc->Add(Vector(0.0, 50.0, 0.0));  // Nodo 1
    positionAlloc->Add(Vector(50.0, 0.0, 0.0));  // Nodo 2
    positionAlloc->Add(Vector(50.0, 50.0, 0.0)); // Nodo 3
    mobility.SetPositionAllocator(positionAlloc);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(nodes);

    // Instalar la pila de Internet
    InternetStackHelper internet;
    internet.Install(nodes);

    // Asignar direcciones IP
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);

    // Configurar aplicaciones
    // Servidor en el Nodo 0
    uint16_t port = 9;
    UdpEchoServerHelper server(port);
    ApplicationContainer serverApps = server.Install(nodes.Get(0));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    // Clientes en los Nodos 1, 2 y 3 que envÃ­an datos al Nodo 0
    for (uint32_t i = 1; i < nodes.GetN(); ++i)
    {
        UdpEchoClientHelper client(interfaces.GetAddress(0), port);
        client.SetAttribute("MaxPackets", UintegerValue(5));
        client.SetAttribute("Interval", TimeValue(Seconds(1.0)));
        client.SetAttribute("PacketSize", UintegerValue(1024));
        ApplicationContainer clientApps = client.Install(nodes.Get(i));
        clientApps.Start(Seconds(2.0 + i)); // Escalonar el inicio de cada cliente
        clientApps.Stop(Seconds(10.0));
    }

    // Habilitar trazas pcap
    wifiPhy.EnablePcapAll("square-topology");

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
