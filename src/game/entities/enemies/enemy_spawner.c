#include <raylib.h>

#include "engine/entity.h"
#include "engine/scenes/scene_utilities.h"
#include "engine/utilities/rand.h"

#include "game/entities/enemies/enemy_spawner.h"
#include "game/entities/enemies/enemy_normal.h"
#include "game/entities/enemies/enemy_shoot.h"

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

void spawn_random_enemy(Vector2 pos, game_data* data) {
	entity* enemy;

	// 1/4 chance to spawn a shooter
	if (rand_int(0, 4) == 1) enemy = enemy_shoot_create(data->main_scene, pos, data->princess);
	else enemy = enemy_normal_create(data->main_scene, pos, data->princess);

	scene_add_entity(data->main_scene, enemy);
}

void on_enemy_spawn_time_out(component* c, game_data* data) {
	int side = rand_int(0, 3);

	// 1/5 chance to spawn enemy on opposite side of screen.
	if (rand_int(0, 5) == 1)
		spawn_random_enemy(get_opposite_position(side, data), data);

	spawn_random_enemy(get_position(side, data), data);

	// Pick new spawn time.
	c->timer.timeout = rand_float(ENEMY_SPAWN_TIME_MIN, ENEMY_SPAWN_TIME_MAX);
}

entity* enemy_spawner_create() {
	entity* e = entity_create((Vector2){0, 0}, 0);

	entity_add_component(e, timer_engine_create(ENEMY_SPAWN_TIME_INITIAL, true, false, on_enemy_spawn_time_out));

	return e;
}
