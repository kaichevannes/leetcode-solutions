{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    clang
    cmake
    ninja
  ];

  shellHook = ''
    export CTEST_OUTPUT_ON_FAILURE=1
    export CC=clang
    export CXX=clang++
  '';
}
