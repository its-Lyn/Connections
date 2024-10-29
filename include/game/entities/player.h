#pragma once

#include <raylib.h>

#include "engine/entity.h"

#include "engine/scenes/scene.h"

#define PLAYER_MIN_SPEED  50.0f
#define PLAYER_MAX_SPEED 100.0f
#define PLAYER_WIDTH  8
#define PLAYER_HEIGHT 8

struct entity* player_create(struct scene* s, Vector2 position);

