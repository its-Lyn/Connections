#include <raylib.h>

#include "engine/component.h"
#include "game/components/label.h"

static void draw(component* c, game_data* data) {
	DrawTextEx(c->label.font, c->label.text, c->owner->pos, c->label.font_size, 1, BLACK);
}

component* label_create(const char* text, Font font, int font_size) {
	component* c = component_create(TYPE_LABEL, NULL, draw, NULL);

	c->label.text = text;
	c->label.font = font;
	c->label.font_size = font_size;

	return c;
}

