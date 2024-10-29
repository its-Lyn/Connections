#pragma once

// ???
struct game_data;

#include <raylib.h>

#include "engine/scenes/scene.h"

typedef enum {
	STATE_CALM = 0,
	STATE_AGITATED
} princess_state;

typedef struct game_data {
	struct scene* main_scene;

	struct component* princess_timer;
	struct component* princess_run_timer;
	princess_state princess_state;

	RenderTexture2D renderer;

	Vector2 game_size;
	float game_scale;

	Vector2 virt_mouse;
} game_data;
