#pragma once

#include <raylib.h>

#include "engine/entity.h"

#define BAT_SPEED_MIN 20.0f
#define BAT_SPEED_MAX 25.0f
#define BAT_ACCEL 350.0f

#define BAT_HEALTH 1
#define BAT_KNOCKBACK 175.0f
#define BAT_PLAYER_KNOCKBACK 125.0f

#define BAT_IFRAMES 0.35f

struct entity* enemy_normal_create(scene* s, Vector2 position, entity* princess);
