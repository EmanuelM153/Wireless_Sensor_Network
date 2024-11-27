{
  pkgs,
  globalVars,
  ...
}:

let
  python = "${
    (pkgs.python312.withPackages (python-pkgs: [
      python-pkgs.paho-mqtt
      python-pkgs.pyserial
    ]))
  }/bin/python";
in
{
  home-manager.users.${globalVars.userName}.home.file."/home/${globalVars.userName}/script.py".source = ./arduino_to_mqtt.py;

  systemd.services."sensor-script" = {
    after = [ "network-online.target" ];
    wants = [ "network-online.target" ];
    description = "Script para enviar datos del sensor";
    wantedBy = [ "multi-user.target" ];
    serviceConfig = {
      User = "${globalVars.userName}";
      Type = "simple";
      Restart = "on-failure";
      RestartSec = "5s";
    };

    script = ''
      ${python} /home/${globalVars.userName}/script.py
    '';
  };
}
