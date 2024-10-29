#include <stdlib.h>

#include <raylib.h>

#include "engine/component.h"

#include "game/game_data.h"

static void draw(component* c, game_data* data) {
	DrawRectangleV(c->owner->pos, c->rectangle.size, c->rectangle.color);
}

component* rectangle_create(Vector2 size, Color color) {
	component* c = component_create(TYPE_RECTANGLE, NULL, draw, NULL);

	c->rectangle.size = size;
	c->rectangle.color = color;

	return c;
}

