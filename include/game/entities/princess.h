#pragma once

#include <raylib.h>

#include "engine/entity.h"

#include "engine/scenes/scene.h"

struct entity* princess_create(struct scene* s, Vector2 position, struct entity* player);
