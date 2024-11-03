#pragma once

#include "engine/entity.h"
#include "game/game_data.h"

#define ENEMY_SPAWN_TIME_INITIAL 10.0f
#define ENEMY_SPAWN_TIME_MAX_ADD 0.5f

#define ENEMY_SPAWN_WAVE_COUNT 5

struct entity* enemy_spawner_create(game_data* data);

