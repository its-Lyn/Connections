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

#include <raylib.h>
#include <raymath.h>

static void quit_pressed(component* c, game_data* data) {
	data->end = true;
}

static void retry_pressed(component* c, game_data* data) {
	data->is_paused = false;
	data->can_pause = true;
	scene_change(data->main_scene, game_scene_create(data));
}

static void main_menu_pressed(component* c, game_data* data) {
	data->is_paused = false;
	data->can_pause = false;
	scene_change(data->main_scene, main_menu_create(data));
}

void end_screen_preprocess(scene* s, game_data* data) {
	DrawTextureV(data->bg_texture, Vector2Zero(), WHITE);
}

void end_screen_process(scene* s, game_data* data) {}
void end_screen_draw(scene* s, game_data* data) {}

scene* end_screen_create(game_data* data) {
	scene* s = scene_create(end_screen_process, end_screen_draw, end_screen_preprocess);

	entity* ui_layer = entity_create((Vector2){0, 0}, 0.0f);

	Font font = GetFontDefault();
	entity_add_component(ui_layer, label_create("Better luck next time..", font, (Vector2){1, 1}, 10, COLOR_RED));
	entity_add_component(ui_layer, label_create("Ms. Knight!", font, (Vector2){1, 11}, 10, COLOR_RED));

	Vector2 desktop_measure = MeasureTextEx(font, "Quit To Desktop", 10, 1);
	Vector2 main_menu_measure = MeasureTextEx(font, "Main Menu", 10, 1);
	Vector2 retry_measure = MeasureTextEx(font, "Retry", 10, 1);

	entity_add_component(ui_layer, text_button_create("Retry", (Vector2){ (data->game_size.x - retry_measure.x) / 2, 60 }, retry_pressed));
	entity_add_component(ui_layer, text_button_create("Main Menu", (Vector2){ (data->game_size.x - main_menu_measure.x) / 2, 71 }, main_menu_pressed));
	entity_add_component(ui_layer, text_button_create("Quit To Desktop", (Vector2){ (data->game_size.x - desktop_measure.x) / 2, 81 }, quit_pressed));

	scene_add_entity(s, ui_layer);

	return s;
}
