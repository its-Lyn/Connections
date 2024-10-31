#pragma once

#include "engine/component.h"

typedef struct {
	int hp;
} enemy_health_data;

struct component* enemy_health_create(int hp);
