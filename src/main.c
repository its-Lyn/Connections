#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <raylib.h>

#include "engine/scenes/scene_utilities.h"
#include "game/game.h"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

// 0 means uncapped
#define FPS 0

bool end = false;

// Other loop function so it can be compatible with web.
void loop(void *game) {
	// We do this because emscripten wants void*
	game_data *data = (game_data*)game;

	// Update func
	process(data);

	// check for end
	if (data->end) {
		kill(data);
		CloseWindow();
		end = true;

#ifdef PLATFORM_WEB
		emscripten_cancel_main_loop();
#endif

		return;
	}

	// Draw func
	render(data);
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(128 * 5, 128 * 5, "Connections");

	// Do not quit when EXIT is pressed.
	SetExitKey(KEY_NULL);

	// Create the base game data
	game_data *data = malloc(sizeof(game_data));

	init(data);

#ifdef PLATFORM_WEB
	emscripten_set_main_loop_arg(loop, data, FPS, 1);
#else
	SetTargetFPS(FPS);
	while (!end && !WindowShouldClose()) loop(data);
#endif

	return 0;
}
