#include <stdio.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/scenes/game_scene.h"
#include "game/entities/player.h"
#include "game/entities/princess.h"

#include "game/entities/enemies/enemy_spawner.h"
#include "game/scenes/main_menu.h"

#include "game/components/text_button.h"
#include "game/components/timer.h"

#include "game/layers.h"

#include "game/colors.h"

#include "engine/utilities/rand.h"

static void quit_pressed(component* c, game_data* data) {
	data->end = true;
}

static void resume_pressed(component* c, game_data* data) {
	data->is_paused = !data->is_paused;
}

static void main_menu_pressed(component* c, game_data* data) {
	data->score = 0;

	data->is_paused = false;
	data->can_pause = false;
	scene_change(data->main_scene, main_menu_create(data));
}

static void on_score_timer_timeout(component* timer, game_data* data) {
	data->score += 10;
}

void shake(game_data* data) {
	if (!data->shaking) return;

	data->intensity -= GetFrameTime() / data->duration;
	if (data->intensity <= 0) {
		data->shaking = false;
		data->shake_offset = Vector2Zero();

		return;
	}

	float rot = rand_float(0, 2*PI);
	data->shake_offset = Vector2Scale((Vector2){ cosf(rot), sinf(rot) }, data->magnitude * data->intensity);
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

	data->game_camera.offset = data->shake_offset;
	if (data->shaking) shake(data);
}

void game_pre_render(scene* game_scene, game_data* data) {
	// drawing background
	if (data->waves->wave_manager.curr_wave == 0) {
		DrawTexture(data->tutorial0_texture, 0, 0, WHITE);
	} else if (data->waves->wave_manager.curr_wave == 1) {
		DrawTexture(data->tutorial1_texture, 0, 0, WHITE);
	} else {
		DrawTexture(data->bg_texture, 0, 0, WHITE);
	}
}

#define HEALTH_OFFSET 3
#define HEALTH_GAP 1
#define HEALTH_SIZE 5

#define TUGBAR_OFFSET_X 3
#define TUGBAR_OFFSET_Y (4 + TUGBAR_OFFSET_X * 2)
#define TUGBAR_WIDTH 17
#define TUGBAR_HEIGHT 5

#define WAVEBAR_OFFSET_X 1
#define WAVEBAR_OFFSET_Y 1

#define SCORE_OFFSET_X  -1
#define SCORE_OFFSET_Y   1
#define SCORE_FONT_SIZE 10

void game_render(scene* game_scene, game_data* data) {
	// Health
	int base_x = HEALTH_OFFSET;
	for (int i = 0; i < data->princess_lives; i++) {
		DrawRectangle(base_x, HEALTH_OFFSET, HEALTH_SIZE, HEALTH_SIZE, COLOR_PINK);
		DrawRectangleLines(base_x, HEALTH_OFFSET, HEALTH_SIZE, HEALTH_SIZE, COLOR_DARK_RED);
		base_x += HEALTH_SIZE + HEALTH_GAP;
	}

	// tug cooldown bar
	  // - Empty background
	DrawRectangle(TUGBAR_OFFSET_X, TUGBAR_OFFSET_Y, TUGBAR_WIDTH, TUGBAR_HEIGHT, COLOR_DARK_RED);

	float elapsed = data->tugger->tugger.cooldown->timer.timer;
	float filled_width = (elapsed / PLAYER_TUG_COOLDOWN) * TUGBAR_WIDTH;

	  // - Filled background
	if (data->tugger->tugger.cooldown->timer.enabled) DrawRectangle(TUGBAR_OFFSET_X, TUGBAR_OFFSET_Y, filled_width, TUGBAR_HEIGHT, COLOR_RED);
	else DrawRectangle(TUGBAR_OFFSET_X, TUGBAR_OFFSET_Y, TUGBAR_WIDTH, TUGBAR_HEIGHT, COLOR_PINK);

	  // - Border
	DrawRectangleLines(TUGBAR_OFFSET_X, TUGBAR_OFFSET_Y, TUGBAR_WIDTH, TUGBAR_HEIGHT, COLOR_BROWN);

	// wave bar
	Vector2 pos = (Vector2){(int)((data->game_size.x - data->waves_texture.width)/2 + WAVEBAR_OFFSET_X), WAVEBAR_OFFSET_Y};
	DrawTextureRec(data->waves_texture, (Rectangle){0, data->waves_frame_h * data->waves->wave_manager.curr_wave, data->waves_texture.width, data->waves_frame_h}, pos, WHITE);

	// score
	if (data->drawn_score != data->score) {
		// score changed
		// freeing old text
		free(data->score_text);

		// update score_text
		int text_len = snprintf(NULL, 0, "%d", data->score); // wont actually print anything since size is 0
		data->score_text = malloc(sizeof(text_len) + 1); // +1 for null terminator
		snprintf(data->score_text, text_len + 1, "%d", data->score);
		data->score_text[text_len] = '\0'; // setting null terminator (since i used malloc)

		// update measurement
		data->score_measure = MeasureText(data->score_text, SCORE_FONT_SIZE);

		// update drawn_score
		data->drawn_score = data->score;
	}
	DrawText(data->score_text, data->game_size.x - data->score_measure + SCORE_OFFSET_X, SCORE_OFFSET_Y, SCORE_FONT_SIZE, COLOR_BROWN);

	// pause screen
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

	// Add enemy spawner.
	scene_add_entity(s, enemy_spawner_create(data));

	// add UI layer
	entity* ui_layer = entity_create((Vector2){0, 0}, 0.0f);
	ui_layer->handle_while_paused = true;

	Font font = GetFontDefault();
	Vector2 desktop_measure = MeasureTextEx(font, "Quit To Desktop", 10, 1);
	Vector2 main_menu_measure = MeasureTextEx(font, "Main Menu", 10, 1);
	Vector2 resume_measure = MeasureTextEx(font, "Resume", 10, 1);

	entity_add_component(ui_layer, text_button_create("Resume", (Vector2){ (data->game_size.x - resume_measure.x) / 2, 60 }, resume_pressed));
	entity_add_component(ui_layer, text_button_create("Main Menu", (Vector2){ (data->game_size.x - main_menu_measure.x) / 2, 71 }, main_menu_pressed));
	entity_add_component(ui_layer, text_button_create("Quit To Desktop", (Vector2){ (data->game_size.x - desktop_measure.x) / 2, 81 }, quit_pressed));

	scene_add_entity(s, ui_layer);

	// score timer
	entity* score_timer = entity_create((Vector2){0, 0}, 0.0f);
	entity_add_component(score_timer, timer_engine_create(1.0f, true, false, on_score_timer_timeout));
	scene_add_entity(s, score_timer);

	return s;
}

