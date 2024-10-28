#include "game/game.h"

#include "game/scenes/game_scene.h"

#include "engine/scenes/scene.h"
#include "engine/scenes/scene_utilities.h"

#include <raylib.h>
#include <stdlib.h>

void init(game_data *data) {
	data->message = "Hello, World!";

	data->font_size = 20;
	data->font_default = GetFontDefault();

	data->main_scene = scene_create(game_process, game_render);
}

void process(game_data* data) {
	scene_update_entities(data->main_scene, data);
}

void render(game_data *data) {
	BeginDrawing();
		ClearBackground(RAYWHITE);
		scene_draw_entities(data->main_scene, data);
	EndDrawing();
}

void kill(game_data *data) {
	free(data->main_scene);
	free(data);
}
