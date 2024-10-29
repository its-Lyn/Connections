#pragma once

// ???
struct game_data;

#include <raylib.h>

#include "engine/scenes/scene.h"

typedef struct game_data {
	struct scene* main_scene;

	struct entity* hello_text;
} game_data;
