#pragma once

// ???
struct game_data;

#include <raylib.h>

#include "engine/scenes/scene.h"

typedef struct game_data {
	struct scene* main_scene;

	RenderTexture2D renderer;

	Vector2 game_size;
	float game_scale;

	Vector2 virt_mouse;
} game_data;
