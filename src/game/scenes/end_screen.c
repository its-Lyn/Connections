#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "engine/scenes/scene_utilities.h"
#include "game/scenes/end_screen.h"

#include "game/components/label.h"
#include "game/components/text_button.h"
#include "game/entities/enemies/enemy_spawner.h"

#include "game/colors.h"

#include "game/scenes/main_menu.h"
#include "game/scenes/game_scene.h"

static void quit_pressed(component* c, game_data* data) {
	data->end = true;
}

static void retry_pressed(component* c, game_data* data) {
	data->score = 0;

	data->is_paused = false;
	data->can_pause = true;
	scene_change(data->main_scene, game_scene_create(data));
}

static void main_menu_pressed(component* c, game_data* data) {
	data->score = 0;

	data->is_paused = false;
	data->can_pause = false;
	scene_change(data->main_scene, main_menu_create(data));
}

void end_screen_preprocess(scene* s, game_data* data) {
	DrawTextureV(data->bg_texture, Vector2Zero(), WHITE);
	DrawRectangle(0, 0, data->game_size.x, 24, COLOR_BROWN);
}

void end_screen_process(scene* s, game_data* data) {}
void end_screen_draw(scene* s, game_data* data) {}

#define GAP 1
scene* end_screen_create(game_data* data) {
	scene* s = scene_create(end_screen_process, end_screen_draw, end_screen_preprocess);

	entity* ui_layer = entity_create((Vector2){0, 0}, 0.0f);

	Font font = GetFontDefault();

	// loss/win message
	if (data->waves->wave_manager.curr_wave >= 4) {
		// reached last wave, win message
		entity_add_component(ui_layer, label_create("Other knights arrived!", font, (Vector2){2,  2}, 10, COLOR_BEIGE));
		entity_add_component(ui_layer, label_create("Final wave reached! WON!", font, (Vector2){2, 12}, 10, COLOR_GREEN));
	} else {
		// did not reach last wave, loss
		entity_add_component(ui_layer, label_create("Princess captured...",  font, (Vector2){2,  2}, 10, COLOR_BEIGE));
		entity_add_component(ui_layer, label_create("Final wave NOT reached.", font, (Vector2){2, 12}, 10, COLOR_RED));
	}

	Vector2 desktop_measure = MeasureTextEx(font, "Quit To Desktop", 10, 1);
	Vector2 main_menu_measure = MeasureTextEx(font, "Main Menu", 10, 1);
	Vector2 retry_measure = MeasureTextEx(font, "Retry", 10, 1);

	entity_add_component(ui_layer, text_button_create("Retry", (Vector2){ (data->game_size.x - retry_measure.x) / 2, data->game_size.y - desktop_measure.y - main_menu_measure.y - desktop_measure.y - GAP * 3 }, retry_pressed));
	entity_add_component(ui_layer, text_button_create("Main Menu", (Vector2){ (data->game_size.x - main_menu_measure.x) / 2, data->game_size.y - desktop_measure.y - main_menu_measure.y - GAP * 2 }, main_menu_pressed));
	entity_add_component(ui_layer, text_button_create("Quit To Desktop", (Vector2){ (data->game_size.x - desktop_measure.x) / 2, data->game_size.y - desktop_measure.y - GAP }, quit_pressed));

	// Calculate high score
	if (data->score > data->high_score)
		data->high_score = data->score;

	size_t text_len = snprintf(NULL, 0, "Score: %d", data->score); // size is 0 so we dont actually print anything
	char* score_text = malloc(text_len + 1); // + 1 for null terminator
	snprintf(score_text, text_len + 1, "Score: %d", data->score);
	score_text[text_len] = '\0'; // null terminator

	Vector2 score_measure = MeasureTextEx(font, score_text, 10, 1);
	entity_add_component(ui_layer, label_create(score_text, font, (Vector2){(data->game_size.x - score_measure.x)/2, ((data->game_size.y - score_measure.y)/2) - 5}, 10, COLOR_BEIGE));

	free(score_text);

	size_t s_text_len = snprintf(NULL, 0, "High Score: %d", data->high_score); // size is 0 so we dont actually print anything
	char* s_score_text = malloc(s_text_len + 1); // + 1 for null terminator
	snprintf(s_score_text, s_text_len + 1, "High Score: %d", data->high_score);
	s_score_text[s_text_len] = '\0'; // null terminator

	Vector2 s_score_measure = MeasureTextEx(font, s_score_text, 10, 1);
	entity_add_component(ui_layer, label_create(s_score_text, font, (Vector2){(data->game_size.x - s_score_measure.x)/2, ((data->game_size.y - s_score_measure.y)/2) + 5}, 10, COLOR_BEIGE));

	free(s_score_text);

	scene_add_entity(s, ui_layer);

	return s;
}
