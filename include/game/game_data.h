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

	struct entity* princess;
	struct component* princess_timer;
	struct component* princess_run_timer;
	struct component* princess_stun_timer;
	princess_state princess_state;

	struct component* enemy_spawn_timer;
	float enemy_spawn_time;

	struct entity* player;

	RenderTexture2D renderer;

	Vector2 game_size;
	float game_scale;

	Vector2 virt_mouse;
} game_data;
