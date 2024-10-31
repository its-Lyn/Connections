#pragma once

#include "engine/component.h"
#include "engine/entity.h"

typedef struct {
	struct component* cooldown;
} tugger_data;

struct component* tugger_create(struct entity* player);

