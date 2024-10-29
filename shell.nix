{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
	buildInputs = with pkgs; [
		emscripten
		raylib
		pkg-config
	];
}

