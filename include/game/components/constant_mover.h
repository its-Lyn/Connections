#pragma once

#include "engine/component.h"

typedef struct {
	Vector2 dir;
	float speed;
} constant_mover_data;

struct component* constant_mover_create(Vector2 direction, float speed);

