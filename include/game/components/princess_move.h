#pragma once

#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"

typedef struct {
	struct entity* player;
	Vector2 dir;
} princess_move_data;

struct component* princess_move_create(struct entity* player);