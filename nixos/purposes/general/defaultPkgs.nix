{ pkgs, ... }:

{
  environment.systemPackages = with pkgs; [
    man-pages
    haveged
    curl
    gnupg
    file
    nmap
    openssl
    wget
    unzip
  ];

  services.gpm.enable = true;
}
