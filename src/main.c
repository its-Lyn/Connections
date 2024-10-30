#include <raylib.h>

#include <stdlib.h>
#include <stdio.h>

#include "game/game.h"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

// 0 means uncapped
#define FPS 0

// Other loop function so it can be compatible with web.
void loop(void *game) {
	// We do this because emscripten wants void*
	game_data *data = (game_data*)game;

	// Update func
	process(data);

	// Draw func
	render(data);
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(128 * 5, 128 * 5, "Connections");

	// Create the base game data
	game_data *data = malloc(sizeof(game_data));

	init(data);

#ifdef PLATFORM_WEB
	emscripten_set_main_loop_arg(loop, data, FPS, 1);
#else
	SetTargetFPS(FPS);
	while (!WindowShouldClose()) loop(data);
#endif

	kill(data);
	CloseWindow();

	return 0;
}
