#pragma once

#include <raylib.h>

#include "engine/entity.h"

#include "engine/scenes/scene.h"

#define PLAYER_MIN_SPEED  50.0f
#define PLAYER_MAX_SPEED 100.0f

#define PLAYER_ACCEL    600.0f
#define PLAYER_FRICTION 300.0f

#define PLAYER_WIDTH  8
#define PLAYER_HEIGHT 10

#define PLAYER_TUG_COOLDOWN 2.0f
#define PLAYER_TUG_FORCE  250.0f

#define SLASH_START_SPEED 300.0f
#define SLASH_DEACCEL 1000.0f
#define SLASH_LIFETIME 0.3f
#define SLASH_COOLDOWN 1.0f

struct entity* player_create(struct scene* s,  game_data* data, Vector2 position);

