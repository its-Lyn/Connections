#include "engine/component.h"
#include "engine/entity.h"

#include "game/components/line.h"

void line_draw(component* c, game_data* data) {
	DrawLineV(c->line.start_pos, c->line.end_pos, c->line.colour);
}

component* line_create(Vector2 start_pos, Vector2 end_pos, Color colour) {
	component* line = component_create(TYPE_LINE, NULL, line_draw, NULL);
	line->line.colour = colour;

	line->line.start_pos = start_pos;
	line->line.end_pos = end_pos;

	return line;
}
