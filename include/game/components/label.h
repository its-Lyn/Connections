#pragma once

#include <stdlib.h>

#include <raylib.h>

#include "engine/component.h"

typedef struct {
	const char* text;
	Font font;
	int font_size;

	Vector2 pos;
	Color colour;
} label_data;

struct component* label_create(const char* text, Font font, Vector2 pos, int font_size, Color colour);

