#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/scenes/game_scene.h"
#include "game/components/label.h"

void game_process(scene *game_scene, game_data *data) {
	entity* hello_text = data->hello_text;

	component* c = entity_get_component(hello_text, TYPE_LABEL);
	if (c == NULL) return;

	Vector2 measurements = MeasureTextEx(c->label.font, c->label.text, c->label.font_size, 1);
	hello_text->pos = (Vector2) {
		(GetScreenWidth() - measurements.x) / 2,
		(GetScreenHeight() - measurements.y) / 2
	};
}

void game_render(scene* game_scene, game_data* data) {
}

scene* game_scene_create(game_data* data) {
	scene* s = scene_create(game_process, game_render);

	// creating hello world text
	entity* hello_text = entity_create((Vector2){0, 0});
	entity_add_component(hello_text, label_create("Hello, World!", GetFontDefault(), 20));
	entity_update(hello_text, data);
	scene_add_entity(s, hello_text);

	data->hello_text = hello_text;

	return s;
}

