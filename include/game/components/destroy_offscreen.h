#pragma once

#include <raylib.h>

#include "engine/component.h"

typedef struct {
	Vector2 size;
} destroy_offscreen_data;

struct component* destroy_offscreen_create(Vector2 size);

