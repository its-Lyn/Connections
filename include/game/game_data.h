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
	struct component* princess_iframe;
	struct component* princess_run_timer;
	struct component* princess_stun_timer;
	struct component* princess_flash_timer;

	struct component* princess_normal_sprite;
	struct component* princess_flash_sprite;

	princess_state princess_state;
	int princess_lives;

	struct component* tugger;

	struct entity* player;

	Texture2D bg_texture;

	struct component* waves;
	Texture2D waves_texture;
	int waves_frame_h;

	int score;
	int high_score;
	int drawn_score;
	int score_measure;
	char* score_text;

	RenderTexture2D renderer;

	Vector2 game_size;
	float game_scale;

	Vector2 virt_mouse;

	bool is_paused;
	bool can_pause;

	bool end;
} game_data;
