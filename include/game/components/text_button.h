#pragma once

#include "engine/component.h"

typedef struct {
	const char* text;
	Vector2 position;

	Rectangle data;
	bool holding;
	bool hovering;

	void (*on_click)(struct component*, game_data*);

	Color active_colour;
} text_button_data;

struct component* text_button_create(const char* text, Vector2 position, void (*on_click)(struct component*, game_data*));
