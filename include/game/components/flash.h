#pragma once

#include <raylib.h>

#include "engine/component.h"

typedef enum {
	FLASH_FADE_IN = 0,
	FLASH_FADE_OUT
} flash_state;

typedef struct {
	flash_state state;
	bool flashing;

	float alpha;
	float speed;
	Rectangle size;
	Color colour;
} flash_data;

struct component* flash_create(Color colour, Rectangle size, float speed);
