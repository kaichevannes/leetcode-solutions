{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    cmake
    ninja
  ];

  shellHook = ''
    export CTEST_OUTPUT_ON_FAILURE=1
  '';
}
