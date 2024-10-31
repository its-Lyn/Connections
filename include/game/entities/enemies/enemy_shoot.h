#pragma once

#include <raylib.h>

#include "engine/scenes/scene.h"
#include "engine/entity.h"

#define SKULLBAT_SPEED_MIN 10.0f
#define SKULLBAT_SPEED_MAX 15.0f

#define BULLET_SPEED 100.0f
#define BULLET_WIDTH   4
#define BULLET_HEIGHT  4

struct entity* enemy_shoot_create(scene* s, Vector2 position, struct entity* princess);
