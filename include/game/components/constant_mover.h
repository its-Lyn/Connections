#pragma once

#include "engine/entity.h"
#include "engine/component.h"

typedef struct {
	struct entity* locked;
	float speed;
} constant_mover_data;

struct component* constant_mover_create(float speed, struct entity* locked);

