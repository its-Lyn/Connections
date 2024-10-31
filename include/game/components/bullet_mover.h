#pragma once

#include "engine/entity.h"
#include "engine/component.h"

#include <raylib.h>

typedef struct {
	Vector2 target_position;
	Vector2 direction;
	float speed;
} bullet_mover_data;

struct component* bullet_mover_create(Vector2 target_position, float speed);
