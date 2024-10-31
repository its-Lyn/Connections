#pragma once

#include <raylib.h>
#include "engine/entity.h"

#include "game/game_data.h"

struct entity* bullet_create(struct entity* target, Vector2 start_pos, float speed, game_data* data);
