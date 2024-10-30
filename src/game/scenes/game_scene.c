#include <raylib.h>
#include <raymath.h>

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

#include "game/layers.h"

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

	entity* enemy_normal = enemy_normal_create(enemy_pos, rand_float(20, 30), data->princess);
	entity_add_component(enemy_normal, collider_create(data->main_scene, (Vector2){4, 4}, 5, LAYER_ENEMIES, LAYER_PRINCESS, NULL));
	scene_add_entity(data->main_scene, enemy_normal);
}

void game_process(scene *game_scene, game_data *data) {
	// Most efficient evelyn code
	for (linked_list* elem = game_scene->colliders; elem != NULL; elem = elem->next) {
		component* collider = (component*)(elem->data);
		for (linked_list* other = data->main_scene->colliders; other != NULL; other = other->next) {
			component* other_collider = (component*)(other->data);
			if (collider->collider.mask & other_collider->collider.layer) {
				bool collides = CheckCollisionCircles(
					Vector2Add(collider->owner->pos, collider->collider.offset),
					collider->collider.radius,

					Vector2Add(other_collider->owner->pos, other_collider->collider.offset),
					other_collider->collider.radius
				);

				if (collides && collider->collider.on_collide != NULL) collider->collider.on_collide(data);
			}
		}
	}
}

void game_render(scene* game_scene, game_data* data) {
}

scene* game_scene_create(game_data* data) {
	scene* s = scene_create(game_process, game_render);

	// creating player and adding to scene
	entity* player = player_create(s, (Vector2){0, 0});

	scene_add_entity(s, player);

	// Princess
	data->princess = princess_create(data, s, (Vector2){20, 10}, player);
	scene_add_entity(s, data->princess);

	// Add enemy handler and spawner.
	data->enemy_spawn_timer = timer_engine_create(5.0f, true, false, on_enemy_spawn_time_out);

	entity* enemy_spawner = enemy_spawner_create();
	entity_add_component(enemy_spawner, data->enemy_spawn_timer);
	scene_add_entity(s, enemy_spawner);

	return s;
}

