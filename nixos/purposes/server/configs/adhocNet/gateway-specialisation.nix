{ pkgs, ... }:

{
  imports = [
    ./configuration.nix
  ];

  specialisation.gateway.configuration = {
    system.nixos.tags = [ "gateway" ];

    environment.systemPackages = with pkgs; [
      cowsay
      kea
    ];

    adhocConfiguration.isServer = true;

    networking = {
      nat = {
        enable = true;
        externalInterface = "eth0";
        internalIPs = [ "192.168.0.0/24" ];
        internalInterfaces = [ "bat0" ];
      };

      dhcpcd.extraConfig = ''
        denyinterfaces bat0 wlan0
      '';
    };

    boot.kernel.sysctl = {
      "net.ipv4.ip_forward" = 1;
      "net.ipv4.conf.all.forwarding" = 1;
    };

    services.kea.dhcp4 = {
      enable = true;
      settings = {
        interfaces-config.interfaces = [ "bat0" ];
        lease-database = {
          name = "/var/lib/kea/dhcp4.leases";
          persist = true;
          type = "memfile";
        };
        subnet4 = [
          {
            id = 1;
            pools = [ { pool = "192.168.0.100 - 192.168.0.240"; } ];
            subnet = "192.168.0.0/24";
            option-data = [
              {
                name = "routers";
                data = "192.168.0.1";
              }
            ];
          }
        ];
      };
    };
  };
}
