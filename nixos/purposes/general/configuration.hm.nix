{ globalVars, ... }:

{
  home-manager.users.${globalVars.userName} = {
    home = {
      username = globalVars.userName;
      homeDirectory = "/home/${globalVars.userName}";
      stateVersion = "24.05";
    };

    programs.home-manager.enable = true;
  };
}
