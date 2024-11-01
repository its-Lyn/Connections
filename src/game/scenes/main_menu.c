#include "engine/entity.h"
#include "engine/component.h"

#include "game/scenes/game_scene.h"
#include "engine/scenes/scene_utilities.h"

#include "game/scenes/main_menu.h"
#include "game/components/label.h"
#include "game/components/text_button.h"
#include "game/colors.h"

#include "game/entities/enemies/enemy_spawner.h"

#include "stdio.h"
void on_play_clicked(component* c, game_data* data) {
	scene_change(data->main_scene, game_scene_create(data));
}

void main_menu_update(scene* s, game_data* data) {}

void main_menu_draw(scene* s, game_data* data) {
	ClearBackground(COLOR_BLUE);
}

scene* main_menu_create(game_data* data) {
	scene* s = scene_create(main_menu_update, main_menu_draw, NULL);

	// KEKW
	entity* ui_layer = enemy_spawner_create();
	scene_add_entity(s, ui_layer);

	// Ok fine I won't eyeball it
	Font font = GetFontDefault();
	Vector2 play_measure  = MeasureTextEx(font, "Play", 10, 1);
	Vector2 quit_measure  = MeasureTextEx(font, "Quit", 10, 1);
	Vector2 title_measure = MeasureTextEx(font, "Connections", 10, 1);

	entity_add_component(ui_layer, label_create("Connections", font, (Vector2){(data->game_size.x - title_measure.x) / 2, 10}, 10));

	entity_add_component(ui_layer, text_button_create("Play", (Vector2){(data->game_size.x - play_measure.x) / 2 , 90}, on_play_clicked));
	entity_add_component(ui_layer, text_button_create("Quit", (Vector2){(data->game_size.x - quit_measure.x) / 2, 101}, NULL));

	return s;
}
