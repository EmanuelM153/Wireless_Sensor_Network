#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-static-routing-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("TopologiaLinealExample");

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

    // Configurar la movilidad en línea
    MobilityHelper mobility;
    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "MinX", DoubleValue(0.0),
                                  "MinY", DoubleValue(0.0),
                                  "DeltaX", DoubleValue(50.0),
                                  "DeltaY", DoubleValue(0.0),
                                  "GridWidth", UintegerValue(4),
                                  "LayoutType", StringValue("RowFirst"));
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(nodes);

    // Instalar la pila de Internet
    InternetStackHelper internet;
    internet.Install(nodes);

    // Asignar direcciones IP
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);

    // Configurar aplicaciones
    uint16_t port = 9;

    // Servidor en el Nodo 3
    UdpEchoServerHelper server(port);
    ApplicationContainer serverApps = server.Install(nodes.Get(3));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    // Cliente en el Nodo 0 que envía datos al Nodo 3
    UdpEchoClientHelper client(interfaces.GetAddress(3), port);
    client.SetAttribute("MaxPackets", UintegerValue(10));
    client.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    client.SetAttribute("PacketSize", UintegerValue(1024));
    ApplicationContainer clientApps = client.Install(nodes.Get(0));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    // Habilitar trazas pcap
    wifiPhy.EnablePcapAll("topologia_lineal");

    // Habilitar trazas ASCII
    AsciiTraceHelper ascii;
    wifiPhy.EnableAsciiAll(ascii.CreateFileStream("topologia_lineal.tr"));

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
