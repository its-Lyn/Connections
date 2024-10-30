#pragma once

#include <raylib.h>

#include "engine/entity.h"
#include "engine/scenes/scene.h"

#include "game/game_data.h"

struct entity* princess_create(game_data* data, scene* s, Vector2 position, struct entity* player);
