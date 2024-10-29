#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/scenes/game_scene.h"
#include "game/entities/player.h"

void game_process(scene *game_scene, game_data *data) {
}

void game_render(scene* game_scene, game_data* data) {
}

scene* game_scene_create(game_data* data) {
	scene* s = scene_create(game_process, game_render);

	// creating player and adding to scene
	entity* player = player_create((Vector2){0, 0});
	scene_add_entity(s, player);

	return s;
}

