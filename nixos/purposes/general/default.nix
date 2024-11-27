{ ... }:

{
  imports = [
    ./defaultPkgs.nix
    ./networking.nix
    ./users.nix
    ./configuration.nix
    ../../modules/programs
  ];
}
