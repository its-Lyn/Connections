#pragma once

#include "engine/component.h"

#include <raylib.h>

typedef struct {
	Vector2 start_pos;
	Vector2 end_pos;

	Color colour;
} line_data;

struct component* line_create(Vector2 start_pos, Vector2 end_pos, Color colour);
