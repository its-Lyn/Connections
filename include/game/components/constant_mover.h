#pragma once

#include "engine/entity.h"
#include "engine/component.h"

typedef struct {
	struct entity* locked;
	float accel;
} constant_mover_data;

struct component* constant_mover_create(float accel, struct entity* locked);

