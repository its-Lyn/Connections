#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/scenes/game_scene.h"
#include "game/entities/player.h"
#include "game/entities/princess.h"

#include "game/entities/enemies/enemy_spawner.h"
#include "game/entities/enemies/enemy_normal.h"

#include "game/components/timer.h"

#include "engine/utilities/rand.h"

void on_panic_time_out(game_data* data) {
	// 1/3 chance for the princess to get agitated.
	if (rand() % 4 == 0) data->princess_state = STATE_AGITATED;
}

void on_run_time_out(game_data* data) {
	// Calm the woman down
	if (data->princess_state == STATE_AGITATED) data->princess_state = STATE_CALM;
}

// Adds an enemy to the *MAIN SCENE* every timeout
void on_enemy_spawn_time_out(game_data* data) {
	// TODO: Enemy variety.

	int side = rand_int(0, 3);
	Vector2 enemy_pos;

	switch (side) {
		case 0: // Top
			enemy_pos.x = rand_int(0, data->game_size.x);
			enemy_pos.y = -8;

			break;
		case 1: // Right
			enemy_pos.x = data->game_size.x;
			enemy_pos.y = rand_int(0, data->game_size.y);

			break;
		case 2: // Bottom
			enemy_pos.x = rand_int(0, data->game_size.x);
			enemy_pos.y = data->game_size.y;

			break;
		case 3: // Left
			enemy_pos.x = -8;
			enemy_pos.y = rand_int(0, data->game_size.y);

			break;
	}

	scene_add_entity(data->main_scene, enemy_normal_create(enemy_pos, rand_float(20, 30), data->princess));
}

void game_process(scene *game_scene, game_data *data) {
}

void game_render(scene* game_scene, game_data* data) {
}

scene* game_scene_create(game_data* data) {
	scene* s = scene_create(game_process, game_render);

	// creating player and adding to scene
	entity* player = player_create((Vector2){0, 0});
	scene_add_entity(s, player);

	// Princess
	data->princess = princess_create((Vector2){20, 10}, player);

	// Add panic timer.
	data->princess_timer = timer_engine_create(2.0f, true, false, on_panic_time_out);
	data->princess_state = STATE_CALM;

	// Add run imer.
	data->princess_run_timer = timer_engine_create(1.5f, false, true, on_run_time_out);

	entity_add_component(data->princess, data->princess_run_timer);
	entity_add_component(data->princess, data->princess_timer);

	scene_add_entity(s, data->princess);

	// Add enemy handler and spawner.
	data->enemy_spawn_timer = timer_engine_create(5.0f, true, false, on_enemy_spawn_time_out);

	entity* enemy_spawner = enemy_spawner_create();
	entity_add_component(enemy_spawner, data->enemy_spawn_timer);
	scene_add_entity(s, enemy_spawner);

	return s;
}

