#pragma once

// ???
struct game_data;

#include <raylib.h>

#include "engine/scenes/scene.h"

typedef struct game_data {
	struct scene* main_scene;

	const char* message;

	Vector2 position;
	Font font_default;
	int font_size;
} game_data;
