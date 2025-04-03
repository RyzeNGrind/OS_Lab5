{
  description = "Banker's Algorithm C Project";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        
        banker = pkgs.stdenv.mkDerivation {
          name = "banker";
          src = ./.; # Use the current directory as source
          buildInputs = [ pkgs.glibc ];
          buildPhase = ''
            ${pkgs.gcc}/bin/gcc -o banker banker.c -pthread
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp banker $out/bin/
          '';
        };
      in
      {
        packages.default = banker;
        
        apps.default = {
          type = "app";
          program = "${banker}/bin/banker";
        };
        
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            gcc
            gdb
            gnumake
            valgrind
          ];
          
          shellHook = ''
            echo "C development environment ready!"
            echo "You can now compile your programs with gcc:"
            echo "  gcc -o banker banker.c -pthread"
            echo "  ./banker 10 5 7"
            echo ""
            echo "Or run the banker app directly with:"
            echo "  nix run"
            echo "  nix run . -- 10 5 7"
          '';
        };
      }
    );
}
