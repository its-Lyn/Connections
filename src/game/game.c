#include <stdlib.h>

#include <raylib.h>

#include "engine/scenes/scene.h"
#include "engine/scenes/scene_utilities.h"
#include "engine/entity.h"
#include "engine/component.h"

#include "game/game.h"
#include "game/scenes/game_scene.h"
#include "game/components/label.h"

void init(game_data *data) {
	data->main_scene = game_scene_create(data);
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

void kill(game_data* data) {
	scene_destroy(data->main_scene, data);
	free(data);
}
