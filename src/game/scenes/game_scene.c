#include "engine/entity.h"
#include "engine/component.h"

#include "game/scenes/game_scene.h"
#include "game/components/label.h"

void game_process(scene *game_scene, game_data *data)
{
	entity* hello_text = data->hello_text;

	component* c = entity_get_component(hello_text, TYPE_LABEL);
	if (c == NULL) return;

	Vector2 measurements = MeasureTextEx(c->label.font, c->label.text, c->label.font_size, 1);
	hello_text->pos = (Vector2) {
		(GetScreenWidth() - measurements.x) / 2,
		(GetScreenHeight() - measurements.y) / 2
	};
}

void game_render(scene* game_scene, game_data* data)
{
	entity_draw(data->hello_text, data);
}
