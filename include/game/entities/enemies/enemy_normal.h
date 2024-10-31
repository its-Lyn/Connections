#pragma once

#include <raylib.h>

#include "engine/entity.h"

struct entity* enemy_normal_create(scene* s, Vector2 position, float speed, entity* princess);
