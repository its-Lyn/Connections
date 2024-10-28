#include "game/game.h"

#include <raylib.h>
#include <stdlib.h>

void init(game_data *data) {
	data->message = "Hello, World!";

	data->font_size = 20;
	data->font_default = GetFontDefault();
}

void process(game_data* data) {
	Vector2 measurements = MeasureTextEx(data->font_default, data->message, data->font_size, 1);
	data->position = (Vector2){
		(GetScreenWidth() - measurements.x) / 2,
		(GetScreenHeight() - measurements.y) / 2
	};
}

void render(game_data *data) {
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTextEx(data->font_default, data->message, data->position, data->font_size, 1, BLACK);
	EndDrawing();
}

void kill(game_data *data) {
	free(data);
}
