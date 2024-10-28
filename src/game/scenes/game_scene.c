#include "game/scenes/game_scene.h"

void game_process(scene *game_scene, game_data *data)
{
	Vector2 measurements = MeasureTextEx(data->font_default, data->message, data->font_size, 1);
	data->position = (Vector2) {
		(GetScreenWidth() - measurements.x) / 2,
		(GetScreenHeight() - measurements.y) / 2
	};
}

void game_render(scene* game_scene, game_data* data)
{
	DrawTextEx(data->font_default, data->message, data->position, data->font_size, 1, BLACK);
}
