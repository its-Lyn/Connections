#pragma once

#include "engine/entity.h"

#define ENEMY_SPAWN_TIME_INITIAL 5.0f
#define ENEMY_SPAWN_TIME_MIN 2.5f
#define ENEMY_SPAWN_TIME_MAX 3.0f

struct entity* enemy_spawner_create();
