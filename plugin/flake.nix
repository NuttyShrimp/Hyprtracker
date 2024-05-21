{
  description = "Time tracking plugin for Hyprland";
  inputs = {
    hyprland.url = "git+https://github.com/hyprwm/Hyprland?submodules=1";
    nix-filter.url = "github:numtide/nix-filter";
    nixpkgs-unstable = {
      url = "github:nixos/nixpkgs/nixos-unstable";
    };
  };
  outputs = { self, hyprland, nix-filter, nixpkgs-unstable, ... }:
    let
      # inherit (hyprland.inputs) nixpkgs;
      inherit (nixpkgs-unstable) lib;

      forHyprlandSystems = fn: lib.genAttrs (builtins.attrNames hyprland.packages) (
      system:
        let
          pkgs = nixpkgs-unstable.legacyPackages.${system};
          unstable = import nixpkgs-unstable {
            system = system;
            config = {
              allowUnfree = true;
            };
          };
          hyprlandPkg = unstable.hyprland.dev; # hyprland.packages.${system}.hyprland;
          hyprtrackerPkg = self.packages.${system}.hyprtracker;
        in
        fn { inherit pkgs hyprlandPkg hyprtrackerPkg unstable; }
      );
    in {
      packages = forHyprlandSystems({ pkgs, hyprlandPkg, hyprtrackerPkg, ... }:
        {
          hyprtracker = pkgs.stdenv.mkDerivation {
            pname = "hyprtracker";
            version = "0.1";
            src = nix-filter.lib {
              root = ./.;
              include = [
                "src"
                ./Makefile
                ./CMakeLists.txt
                ./conanfile.py
                ./conandata.yml
                ./conan_provider.cmake
                ./hyprpm.toml
              ];
            };

            nativeBuildInputs = with pkgs; [
              cmake
              pkg-config
              conan
              hyprlandPkg
            ];

            buildInputs = with pkgs; [ hyprlandPkg conan ] ++ hyprlandPkg.buildInputs;

            dontUseCmakeConfigure = true;
            dontUseMesonConfigure = true;

            buildPhase = ''
              ls -al
              make
            '';

            installPhase = ''
              mkdir -p $out/lib
              cp ./hyprtracker.so $out/lib/libhyprtracker.so
            '';

            meta = with pkgs.lib; {
              homepage = "https://github.com/NuttyShrimp/hyprtracker";
              description = "a time tracking plugin for Hyprland";
              platforms = platforms.linux;
            };
          };
          default = hyprtrackerPkg;
        }
      );


      devShells = forHyprlandSystems ({ pkgs, hyprlandPkg, hyprtrackerPkg, unstable }: {
        default = pkgs.mkShell {
          name = "hyprtracker-dev";

          nativeBuildInputs = with pkgs; [
            clang-tools_16
            cmake
            bear
          ];

          buildInputs = [
            hyprlandPkg
          ];

          packages = with pkgs; [
            conan
            unstable.jetbrains.clion
            ccls
          ];

          inputsFrom = [
            hyprlandPkg
            hyprtrackerPkg
          ];
        };
      });
    };
}
