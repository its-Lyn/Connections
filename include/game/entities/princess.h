#pragma once

#include <raylib.h>

#include "engine/entity.h"
#include "engine/scenes/scene.h"

#include "game/game_data.h"

#define PRINCESS_SPEED  80.0f
#define PRINCESS_ACCEL 400.0f

#define PRINCESS_CALM_TIME 4.0f
#define PRINCESS_AGITATED_TIME 4.0f
#define PRINCESS_STUN_TIME 1.5f

struct entity* princess_create(game_data* data, scene* s, Vector2 position, struct entity* player);
