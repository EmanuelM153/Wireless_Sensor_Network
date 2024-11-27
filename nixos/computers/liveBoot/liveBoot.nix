{
  inputs,
  pkgsUnfree,
  unstable-small-pkgs,
  ...
}:

let
  system = pkgsUnfree.system;

  globalVars = {
    userName = "nixos";
    hostName = "ha";
  };
in
{
  inherit system;
  pkgs = pkgsUnfree;

  modules = [
    ../../purposes/server/configs/adhocNet
    ../../purposes/server
    ./hardware
    ./configuration.nix

    inputs.home-manager.nixosModules.home-manager
    {
      home-manager.useGlobalPkgs = true;
      home-manager.useUserPackages = true;
      home-manager.extraSpecialArgs = {
        inherit inputs globalVars unstable-small-pkgs;
      };
    }
  ];

  specialArgs = {
    inherit inputs globalVars unstable-small-pkgs;
  };
}
