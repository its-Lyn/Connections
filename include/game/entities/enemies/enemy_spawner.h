#pragma once

#include "engine/entity.h"
#include "game/game_data.h"

#define ENEMY_SPAWN_TIME_INITIAL 5.0f
#define ENEMY_SPAWN_TIME_MIN 2.5f
#define ENEMY_SPAWN_TIME_MAX 3.0f

#define ENEMY_SPAWN_WAVE_COUNT 5

struct entity* enemy_spawner_create(game_data* data);

