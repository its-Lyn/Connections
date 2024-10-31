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

				if (collides && collider->collider.on_collide != NULL && collider->collider.enabled && other_collider->collider.enabled)
					collider->collider.on_collide(game_scene, collider, other_collider, data);
			}
		}
	}
}

#define OFFSET 3
#define GAP 1
#define HEALTH_SIZE 5

#define OFFSET_X 3
#define OFFSET_Y (4 + OFFSET_X * 2)
#define WIDTH 17
#define HEIGHT 5

void game_pre_render(scene* game_scene, game_data* data) {
	// drawing background
	DrawTexture(data->bg_texture, 0, 0, WHITE);
}

void game_render(scene* game_scene, game_data* data) {
	// Health
	int base_x = OFFSET;
	for (int i = 0; i < data->princess_lives; i++) {
		DrawRectangle(base_x, OFFSET, HEALTH_SIZE, HEALTH_SIZE, PINK);
		DrawRectangleLines(base_x, OFFSET, HEALTH_SIZE, HEALTH_SIZE, DARKPURPLE);
		base_x += HEALTH_SIZE + GAP;
	}

	// Empty background
	DrawRectangle(OFFSET_X, OFFSET_Y, WIDTH, HEIGHT, DARKGRAY);

	float elapsed = data->tugger->tugger.cooldown->timer.timer;
	float filled_width = (elapsed / PLAYER_TUG_COOLDOWN) * WIDTH;

	// Filled background
	if (data->tugger->tugger.cooldown->timer.enabled) DrawRectangle(OFFSET_X, OFFSET_Y, filled_width, HEIGHT, RED);
	else DrawRectangle(OFFSET_X, OFFSET_Y, WIDTH, HEIGHT, GREEN);

	// Border
	DrawRectangleLines(OFFSET_X, OFFSET_Y, WIDTH, HEIGHT, BLACK);
}

scene* game_scene_create(game_data* data) {
	scene* s = scene_create(game_process, game_render, game_pre_render);

	// creating player and adding to scene
	data->player = player_create(s, data, (Vector2){0, 0});
	scene_add_entity(s, data->player);

	// Princess
	data->princess = princess_create(data, s, (Vector2){20, 10}, data->player);
	data->princess_lives = 3;
	scene_add_entity(s, data->princess);

	// Add enemy handler and spawner.
	data->enemy_spawn_timer = timer_engine_create(5.0f, true, false, on_enemy_spawn_time_out);

	entity* enemy_spawner = enemy_spawner_create();
	entity_add_component(enemy_spawner, data->enemy_spawn_timer);
	scene_add_entity(s, enemy_spawner);

	return s;
}

