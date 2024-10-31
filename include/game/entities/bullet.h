#pragma once

#include <raylib.h>
#include "engine/entity.h"

struct entity* bullet_create(struct entity* target, Vector2 start_pos, float speed);
