#pragma once

#include "engine/component.h"
#include "engine/entity.h"

typedef struct {
	struct component* sprite;
} player_move_data;

struct component* player_move_create(struct entity* player);

