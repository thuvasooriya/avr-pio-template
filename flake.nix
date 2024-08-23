{
  description = "avr development environment with platformio";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
          config.allowUnfree = true;
        };
      in {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            # platformio core
            platformio-core
            # avr toolchain
            pkgsCross.avr.buildPackages.gcc
            pkgsCross.avr.buildPackages.binutils
          ];

          shellHook = ''
            echo "macos compatible avr development environment activated!"
            echo "platformio and avr toolchain are available."

            export PLATFORMIO_CORE_DIR="$HOME/.platformio"

            # pio pkg update

            # set up the avr toolchain path
            # export PATH=$PATH:${pkgs.pkgsCross.avr.buildPackages.gcc}/bin
            # export PATH=$PATH:${pkgs.pkgsCross.avr.buildPackages.binutils}/bin
          '';
        };
      }
    );
}
