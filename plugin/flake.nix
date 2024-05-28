{
  description = "Time tracking plugin for Hyprland";
  inputs = {
    hyprland.url = "git+https://github.com/hyprwm/Hyprland?submodules=1";
    nix-filter.url = "github:numtide/nix-filter";
    nixpkgs = {
      url = "github:nixos/nixpkgs/nixos-unstable";
    };
  };
  outputs = { self, hyprland, nix-filter, nixpkgs, ... }:
    let
      # inherit (hyprland.inputs) nixpkgs;
      inherit (nixpkgs) lib;

      forHyprlandSystems = fn: lib.genAttrs (builtins.attrNames hyprland.packages) (
      system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
          unstable = import nixpkgs {
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
                ./hyprpm.toml
              ];
            };

            nativeBuildInputs = with pkgs; [
              ninja
              cmake
              pkg-config
              hyprlandPkg
              sqlite
              sqlitecpp
            ];

            buildInputs = [ hyprlandPkg ] ++ hyprlandPkg.buildInputs;

            cmakeFlags = [ "-G Ninja -DCONAN:bool=Off" ];

            installPhase = ''
              mkdir -p $out/lib
              cp ./libhyprtracker.so $out/lib/libhyprtracker.so
            '';

            meta = with pkgs.lib; {
              homepage = "https://github.com/NuttyShrimp/hyprtracker";
              description = "a time tracking plugin for Hyprland";
              platforms = platforms.linux;
              license = licenses.mit;
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
