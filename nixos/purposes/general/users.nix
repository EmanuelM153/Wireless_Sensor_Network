{
  globalVars,
  pkgs,
  lib,
  ...
}:

{
  users = {
    users.root.hashedPassword = lib.mkForce "!";

    users."${globalVars.userName}" = {
      initialPassword = lib.mkDefault "buenos";
      isNormalUser = true;
      extraGroups = [ "wheel" ];
      home = "/home/${globalVars.userName}";
      shell = pkgs.zsh;
    };
  };
}
