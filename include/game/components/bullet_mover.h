#pragma once

#include "engine/entity.h"
#include "engine/component.h"

#include <raylib.h>

typedef struct {
	Vector2 direction;
} bullet_mover_data;

struct component* bullet_mover_create(Vector2 direction);
