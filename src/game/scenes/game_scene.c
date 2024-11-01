#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"
#include "engine/utilities/rand.h"

#include "game/scenes/game_scene.h"
#include "game/entities/player.h"
#include "game/entities/princess.h"

#include "game/entities/enemies/enemy_spawner.h"
#include "game/entities/enemies/enemy_normal.h"
#include "game/entities/enemies/enemy_shoot.h"

#include "game/scenes/main_menu.h"

#include "game/components/text_button.h"
#include "game/components/timer.h"

#include "game/layers.h"

#include "game/colors.h"

#define SPAWN_TIME_MIN 2.5f
#define SPAWN_TIME_MAX 3.0f

static void quit_pressed(component* c, game_data* data) {}

static void resume_pressed(component* c, game_data* data) {
	data->is_paused = !data->is_paused;
}

static void main_menu_pressed(component* c, game_data* data) {
	data->is_paused = false;
	data->can_pause = false;
	scene_change(data->main_scene, main_menu_create(data));
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

void spawn_random_enemy(Vector2 pos, game_data* data) {
	entity* enemy;

	// 1/4 chance to spawn a shooter
	if (rand_int(0, 4) == 1) enemy = enemy_shoot_create(data->main_scene, pos, data->princess);
	else enemy = enemy_normal_create(data->main_scene, pos, data->princess);

	scene_add_entity(data->main_scene, enemy);
}

// Adds an enemy to the *MAIN SCENE* every timeout
void on_enemy_spawn_time_out(component* _timer, game_data* data) {
	int side = rand_int(0, 3);

	// 1/5 chance to spawn enemy on opposite side of screen.
	if (rand_int(0, 5) == 1)
		spawn_random_enemy(get_opposite_position(side, data), data);

	spawn_random_enemy(get_position(side, data), data);

	// Pick new spawn time.
	data->enemy_spawn_time = rand_float(SPAWN_TIME_MIN, SPAWN_TIME_MAX);
	data->enemy_spawn_timer->timer.timeout = data->enemy_spawn_time;
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

void game_pre_render(scene* game_scene, game_data* data) {
	// drawing background
	DrawTexture(data->bg_texture, 0, 0, WHITE);
}

#define OFFSET 3
#define GAP 1
#define HEALTH_SIZE 5

#define OFFSET_X 3
#define OFFSET_Y (4 + OFFSET_X * 2)
#define WIDTH 17
#define HEIGHT 5

void game_render(scene* game_scene, game_data* data) {
	// Health
	int base_x = OFFSET;
	for (int i = 0; i < data->princess_lives; i++) {
		DrawRectangle(base_x, OFFSET, HEALTH_SIZE, HEALTH_SIZE, COLOR_PINK);
		DrawRectangleLines(base_x, OFFSET, HEALTH_SIZE, HEALTH_SIZE, COLOR_DARK_RED);
		base_x += HEALTH_SIZE + GAP;
	}

	// Empty background
	DrawRectangle(OFFSET_X, OFFSET_Y, WIDTH, HEIGHT, COLOR_DARK_RED);

	float elapsed = data->tugger->tugger.cooldown->timer.timer;
	float filled_width = (elapsed / PLAYER_TUG_COOLDOWN) * WIDTH;

	// Filled background
	if (data->tugger->tugger.cooldown->timer.enabled) DrawRectangle(OFFSET_X, OFFSET_Y, filled_width, HEIGHT, COLOR_RED);
	else DrawRectangle(OFFSET_X, OFFSET_Y, WIDTH, HEIGHT, COLOR_PINK);

	// Border
	DrawRectangleLines(OFFSET_X, OFFSET_Y, WIDTH, HEIGHT, COLOR_BROWN);

	if (data->is_paused) {
		DrawRectangleV(Vector2Zero(), data->game_size, COLOR_BROWN);

		Vector2 pause_measure = MeasureTextEx(GetFontDefault(), "Paused", 20, 1);
		DrawText("Paused", ((data->game_size.x - pause_measure.x) - 4) / 2, 10, 20, COLOR_BEIGE);
	}
}

scene* game_scene_create(game_data* data) {
	scene* s = scene_create(game_process, game_render, game_pre_render);

	// creating player and adding to scene
	data->player = player_create(s, data, (Vector2){(data->game_size.x - PLAYER_WIDTH)/2, (data->game_size.y - PLAYER_HEIGHT)/2});
	scene_add_entity(s, data->player);

	// Princess
	data->princess = princess_create(data, s, (Vector2){data->game_size.x/2 + 10, data->game_size.y/2 + 10}, data->player);
	data->princess_lives = 3;
	scene_add_entity(s, data->princess);

	// Add enemy handler and spawner.
	data->enemy_spawn_timer = timer_engine_create(5.0f, true, false, on_enemy_spawn_time_out);

	entity* enemy_spawner = enemy_spawner_create();
	entity_add_component(enemy_spawner, data->enemy_spawn_timer);
	scene_add_entity(s, enemy_spawner);

	entity* ui_layer = enemy_spawner_create();
	ui_layer->handle_while_paused = true;

	Font font = GetFontDefault();
	Vector2 desktop_measure = MeasureTextEx(font, "Quit To Desktop", 10, 1);
	Vector2 main_menu_measure = MeasureTextEx(font, "Main Menu", 10, 1);
	Vector2 resume_measure = MeasureTextEx(font, "Resume", 10, 1);

	entity_add_component(ui_layer, text_button_create("Resume", (Vector2){ (data->game_size.x - resume_measure.x) / 2, 60 }, resume_pressed));
	entity_add_component(ui_layer, text_button_create("Main Menu", (Vector2){ (data->game_size.x - main_menu_measure.x) / 2, 71 }, main_menu_pressed));
	entity_add_component(ui_layer, text_button_create("Quit To Desktop", (Vector2){ (data->game_size.x - desktop_measure.x) / 2, 81 }, quit_pressed));

	scene_add_entity(s, ui_layer);

	return s;
}

