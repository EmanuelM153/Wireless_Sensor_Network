{
  config,
  modulesPath,
  lib,
  ...
}:
{

  imports = [
    "${modulesPath}/installer/cd-dvd/installation-cd-minimal.nix"
    ./iso-image.nix
  ];

  disabledModules = [
    "${modulesPath}/installer/cd-dvd/iso-image.nix"
  ];

  nixpkgs.hostPlatform = config.system;

  boot.loader.grub.enable = lib.mkForce false;

  isoImage.squashfsCompression = "gzip -Xcompression-level 1";
}
