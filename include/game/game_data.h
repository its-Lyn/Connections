#pragma once

// ???
struct game_data;

#include <raylib.h>

#include "engine/scenes/scene.h"

typedef struct game_data {
	struct scene* main_scene;
} game_data;
