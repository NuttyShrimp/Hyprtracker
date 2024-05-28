{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {self, nixpkgs, flake-utils, ...} :
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
      in {
        devShells.default = pkgs.mkShell {
          name = "hyprtracker-viewer";

          nativeBuildInputs = with pkgs; [
            gtkmm4
            gtk4-layer-shell
            glibmm_2_68
            pkg-config
            cmake
          ];

          buildInputs = with pkgs; [
            gtkmm4
          ];

          packages = with pkgs; [
            # Development Tools
            conan
            cmake
            ccls
          ];
        };
      });
}
