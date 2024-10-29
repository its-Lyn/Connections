#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/scenes/game_scene.h"

void game_process(scene *game_scene, game_data *data) {
}

void game_render(scene* game_scene, game_data* data) {
}

scene* game_scene_create(game_data* data) {
	scene* s = scene_create(game_process, game_render);

	// creating player and adding to scene
	entity* player = entity_create((Vector2){0, 0});
	entity_add_component(player, player_move_create());
	entity_add_component(player, rectangle_create((Vector2){8, 8}, BLUE));
	scene_add_entity(s, player);

	return s;
}

