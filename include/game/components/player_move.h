#pragma once

#include "engine/component.h"

typedef struct {
	float speed;
} player_move_data;

struct component* player_move_create(float speed);

