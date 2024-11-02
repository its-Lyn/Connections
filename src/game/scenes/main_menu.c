#include <stdbool.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "game/scenes/game_scene.h"
#include "engine/scenes/scene_utilities.h"

#include "game/scenes/main_menu.h"
#include "game/components/label.h"
#include "game/components/text_button.h"
#include "game/components/line.h"
#include "game/colors.h"

#include "game/entities/enemies/enemy_spawner.h"

static void on_play_clicked(component* c, game_data* data) {
	data->can_pause = true;
	scene_change(data->main_scene, game_scene_create(data));
}

static void on_quit_clicked(component* c, game_data* data) {
	data->end = true;
}

static void main_menu_update(scene* s, game_data* data) {}

static void main_menu_draw(scene* s, game_data* data) {
	ClearBackground(COLOR_BLUE);
}

scene* main_menu_create(game_data* data) {
	scene* s = scene_create(main_menu_update, main_menu_draw, NULL);

	// KEKW
	entity* ui_layer = entity_create((Vector2){0, 0}, 0.0f);
	scene_add_entity(s, ui_layer);

	// Ok fine I won't eyeball it
	Font font = GetFontDefault();
	Vector2 play_measure  = MeasureTextEx(font, "Play", 10, 1);
	Vector2 quit_measure  = MeasureTextEx(font, "Quit", 10, 1);
	Vector2 title_measure = MeasureTextEx(font, "Connections", 20, 1);

	// Title
	entity_add_component(ui_layer, label_create("Connections", font, (Vector2){(data->game_size.x - title_measure.x) / 2, 15}, 20, COLOR_BEIGE));

	// Credits
	entity_add_component(ui_layer, label_create("Raylib NEXT Jam", font, (Vector2){1, 110}, 10, COLOR_GREEN));
	entity_add_component(ui_layer, label_create("Evelyn & Lilliana", font, (Vector2){10, 118}, 10, COLOR_GREEN));

	// UI Buttons
	entity_add_component(ui_layer, text_button_create("Play", (Vector2){(data->game_size.x - play_measure.x) / 2 , 60}, on_play_clicked));
	entity_add_component(ui_layer, text_button_create("Quit", (Vector2){(data->game_size.x - quit_measure.x) / 2, 71}, on_quit_clicked));

	// BG Details
	entity_add_component(ui_layer, line_create((Vector2){0, 5}, (Vector2){data->game_size.x, 10}, COLOR_BROWN));
	entity_add_component(ui_layer, line_create((Vector2){0, 45}, (Vector2){data->game_size.x, 45}, COLOR_BROWN));
	entity_add_component(ui_layer, line_create((Vector2){0, 70}, (Vector2){data->game_size.x, 80}, COLOR_BROWN));
	entity_add_component(ui_layer, line_create((Vector2){0, 110}, (Vector2){data->game_size.x, 100}, COLOR_BROWN));

	return s;
}
