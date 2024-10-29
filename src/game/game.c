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
	data->hello_text = entity_create((Vector2){0, 0});
	entity_add_component(data->hello_text, label_create("Hello, World!", GetFontDefault(), 20));

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

void kill(game_data* data) {
	entity_destroy(data->hello_text, data);
	free(data->main_scene);
	free(data);
}
