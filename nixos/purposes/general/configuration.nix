{ lib, inputs, ... }:

{
  imports = [
    ./configuration.hm.nix
  ];

  boot.loader = {
    efi = {
      canTouchEfiVariables = true;
      efiSysMountPoint = "/boot/efi";
    };

    grub = {
      enable = true;
      efiSupport = true;
    };
  };

  fonts.fontDir.enable = true;

  services = {
    libinput.enable = true;
    xserver.xkb.options = "ctrl:swapcaps";
  };

  security = {
    sudo.extraConfig = "Defaults   timestamp_timeout = 10";
    tpm2.enable = true;
  };

  nix = {
    settings.auto-optimise-store = true;
    gc = {
      automatic = true;
      dates = "daily";
      options = "--delete-older-than 2d";
    };
    extraOptions = "experimental-features = nix-command flakes";
    channel.enable = false;
    nixPath = [ "nixpkgs=${inputs.nixpkgs}" ];
  };

  console = {
    keyMap = lib.mkDefault "us";
    useXkbConfig = true;
  };

  system.stateVersion = "24.05";
}
