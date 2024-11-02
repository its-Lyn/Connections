#include <raylib.h>

#include "engine/entity.h"
#include "engine/scenes/scene_utilities.h"
#include "engine/utilities/rand.h"

#include "game/entities/enemies/enemy_spawner.h"
#include "game/entities/enemies/enemy_normal.h"
#include "game/entities/enemies/enemy_shoot.h"
#include "game/components/wave_manager.h"

Vector2 get_position(int side, game_data* data) {
	Vector2 pos;
	switch (side) {
		case 0: // Top
			pos.x = rand_int(0, data->game_size.x);
			pos.y = -8;

			break;
		case 1: // Right
			pos.x = data->game_size.x;
			pos.y = rand_int(0, data->game_size.y);

			break;
		case 2: // Bottom
			pos.x = rand_int(0, data->game_size.x);
			pos.y = data->game_size.y;

			break;
		case 3: // Left
			pos.x = -8;
			pos.y = rand_int(0, data->game_size.y);

			break;
	}

	return pos;
}

Vector2 get_opposite_position(int side, game_data* data) {
	Vector2 pos;
	switch (side) {
		case 0: // Top -> Bottom
			pos.x = rand_int(0, data->game_size.x);
			pos.y = data->game_size.y;

			break;
		case 1: // Right -> Left
			pos.x = -8;
			pos.y = rand_int(0, data->game_size.y);

			break;
		case 2: // Bottom -> Top
			pos.x = rand_int(0, data->game_size.x);
			pos.y = -8;

			break;
		case 3: // Left -> Right
			pos.x = data->game_size.x;
			pos.y = rand_int(0, data->game_size.y);

			break;
	}

	return pos;
}

void spawn_random_enemy(wave_data wave, Vector2 pos, game_data* data) {
	entity* enemy;

	// Chance to spawn a shooter
	if (rand_float(0, 1) <= wave.shooter_chance) enemy = enemy_shoot_create(data->main_scene, pos, data->princess);
	else enemy = enemy_normal_create(data->main_scene, pos, data->princess);

	scene_add_entity(data->main_scene, enemy);
}

void on_enemy_spawn_time_out(component* c, game_data* data) {
	wave_manager_data wm = entity_get_component(c->owner, TYPE_WAVE_MANAGER)->wave_manager;
	wave_data wave = wm.waves[wm.curr_wave];

	int side = rand_int(0, 3);

	// Chance to spawn a second enemy on the opposite side of screen.
	if (rand_float(0, 1) <= wave.double_chance)
		spawn_random_enemy(wave, get_opposite_position(side, data), data);

	spawn_random_enemy(wave, get_position(side, data), data);

	// Pick new spawn time.
	c->timer.timeout = wave.spawn_time;
}

entity* enemy_spawner_create() {
	entity* e = entity_create((Vector2){0, 0}, 0);

	entity_add_component(e, wave_manager_create(e));
	entity_add_component(e, timer_engine_create(ENEMY_SPAWN_TIME_INITIAL, true, false, on_enemy_spawn_time_out));

	return e;
}
