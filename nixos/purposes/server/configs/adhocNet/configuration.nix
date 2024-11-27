{
  lib,
  pkgs,
  config,
  globalVars,
  ...
}:

let
  cfg = config.adhocConfiguration;
in
{
  imports = [
    ./adhoc.service.nix
  ];

  options.adhocConfiguration = {
    servidorIp = lib.mkOption {
      type = lib.types.str;
      default = "3.92.26.134";
    };
    isServer = lib.mkEnableOption "Is a server";
  };

  config = {
    users.users."${globalVars.userName}".extraGroups = [ "dialout" ];

    adhocNet.isServer = cfg.isServer;

    networking = {
      hosts."${cfg.servidorIp}" = [ "cinco.en.el.proyecto" ];
      wireless.enable = lib.mkForce false;
      dhcpcd.extraConfig = ''
        timeout 300
        denyinterfaces wlan0
        leasetime 80
      '';
    };

    boot = {
      kernelParams = [ "net.ifnames=0" ];
      extraModulePackages = with config.boot.kernelPackages; [ batman_adv ];
      initrd.kernelModules = [ "batman-adv" ];
    };

    environment.defaultPackages = with pkgs; [
      (python312.withPackages (python-pkgs: [
        python-pkgs.paho-mqtt
        python-pkgs.pyserial
      ]))
      iw
      alfred
      batctl
    ];

    services.openssh.settings.PasswordAuthentication = true;
  };
}
