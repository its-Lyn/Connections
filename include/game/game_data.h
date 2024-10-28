#pragma once

#include <raylib.h>

typedef struct {
	const char* message;

	Vector2 position;
	Font font_default;
	int font_size;
} game_data;
