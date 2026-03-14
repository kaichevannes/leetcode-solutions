{
  description = "C++ project";

  inputs.nixpkgs.url = "nixpkgs";

  outputs =
    { nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system}.default = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } {
        packages = with pkgs; [
          cmake
          ninja
        ];

        shellHook = ''
          export CTEST_OUTPUT_ON_FAILURE=1
          if [ ! -d build ]; then
            cmake -S . -B build -G Ninja
          fi
          cd build
        '';
      };
    };
}
