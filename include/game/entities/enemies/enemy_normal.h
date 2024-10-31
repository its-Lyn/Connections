#pragma once

#include <raylib.h>

#include "engine/entity.h"

#define BAT_SPEED_MIN 20.0f
#define BAT_SPEED_MAX 25.0f

#define BAT_HEALTH 3
#define BAT_KNOCKBACK 70.0f

struct entity* enemy_normal_create(scene* s, Vector2 position, entity* princess);
