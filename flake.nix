{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { self
    , nixpkgs
    , flake-utils
    }:
    flake-utils.lib.eachDefaultSystem
      (system:
      let
        pkgs = import nixpkgs {
          system = system;
          overlays = [ ];
        };
      in
      with pkgs;
      {
        devShells.default = mkShellNoCC {
          buildInputs = [
            gnat13 # gcc with ada
            #gnatboot # gnat1
            ncurses # make menuconfig
            m4
            flex
            bison # Generate flashmap descriptor parser
            #clang
            zlib
            #acpica-tools # iasl
            pkg-config
            # qemu # test the image
            openssl
            python3
            libuuid
            nasm
            imagemagick
          ];
          shellHook = ''
            # TODO remove?
            NIX_LDFLAGS="$NIX_LDFLAGS -lncurses"
          '';
        };
      }
      );
}
