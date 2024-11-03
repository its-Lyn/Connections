#pragma once

#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"

typedef struct {
	struct entity* player;
	Vector2 dir;
	struct component* sprite;
	struct component* flash_sprite;
} princess_move_data;

struct component* princess_move_create(struct entity* princess, struct entity* player, struct component* normal_sprite, struct component* flash_sprite);
