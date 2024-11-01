#pragma once

#include <raylib.h>

#include "engine/scenes/scene.h"
#include "engine/entity.h"

#define SKULLBAT_SPEED_MIN 10.0f
#define SKULLBAT_SPEED_MAX 15.0f
#define SKULLBAT_ACCEL 350.0f

#define SKULLBAT_HEALTH 2
#define SKULLBAT_KNOCKBACK 175.0f
#define SKULLBAT_PLAYER_KNOCKBACK 125.0f

#define SKULLBAT_IFRAMES 0.35f

#define BULLET_TIME 3.0f
#define BULLET_SPEED 65.0f
#define BULLET_WIDTH   4
#define BULLET_HEIGHT  4

struct entity* enemy_shoot_create(scene* s, Vector2 position, struct entity* princess);
