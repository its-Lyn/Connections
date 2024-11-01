#include <raylib.h>

#include "engine/component.h"
#include "game/components/label.h"

#include "game/colors.h"

static void draw(component* c, game_data* data) {
	DrawTextEx(c->label.font, c->label.text, c->label.pos, c->label.font_size, 1, c->label.colour);
}

component* label_create(const char* text, Font font, Vector2 pos, int font_size, Color colour) {
	component* c = component_create(TYPE_LABEL, NULL, draw, NULL);

	c->label.text = text;
	c->label.font = font;
	c->label.font_size = font_size;

	c->label.pos = pos;
	c->label.colour = colour;

	return c;
}

