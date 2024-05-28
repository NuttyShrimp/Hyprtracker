{
  inputs = {
    hyprland.url = "git+https://github.com/hyprwm/Hyprland?submodules=1";
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    systems.url = "github:nix-systems/default-linux";
    hyprtracker = {
      url = "./plugin";
      inputs = {
        hyprland.follows = "hyprland";
        nixpkgs.follows = "nixpkgs";
      };
    };
  };

  outputs = {
    self,
    systems,
    hyprtracker,
    nixpkgs,
    ...
  }: let
    inherit (nixpkgs) lib;
    eachSystem = lib.genAttrs (import systems);

    pkgsFor = eachSystem (system:
      import nixpkgs {
        localSystem.system = system;
        overlays = [
          self.overlays.hyprland-plugins
        ];
      });
  in {
    packages = eachSystem (system: {
      inherit
        (pkgsFor.${system})
        hyprtracker
        ;
    });

    overlays = {
      default = self.overlays.hyprland-plugins;

      hyprland-plugins = final: prev: {
        hyprtracker = hyprtracker.packages.${prev.system}.default;
      };
    };

    checks = eachSystem (system: self.packages.${system});
  };
}
