{
  description = "MedicalClinic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { nixpkgs, ... } @ inputs:
    let
        system = "x86_64-linux";
        pkgs = nixpkgs.legacyPackages.${system};
    in
  {
    # Dependencies: cmake, boost, ninja, gdb, clang-tools
    devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
            cmake
            ninja
            boost190
            gdb
            clang-tools
            pkg-config
        ];
        shellHook =
        ''
            echo "C++ dev shell activated: (cmake version: $(cmake --version | head -n1))"
        '';
    };
  };
}
