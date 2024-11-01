#pragma once

#include <raylib.h>

#include "engine/entity.h"

#include "game/game_data.h"

struct entity* slash_create(game_data* data, Vector2 position, Vector2 dir);

