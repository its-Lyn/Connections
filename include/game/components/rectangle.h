#pragma once

#include <raylib.h>

#include "engine/component.h"

typedef struct {
	Vector2 size;
	Color color;
} rectangle_data;

struct component* rectangle_create(Vector2 size, Color color);

