#include "engine/entity.h"
#include "engine/component.h"

#include "game/colors.h"
#include "game/components/text_button.h"

void text_button_update(component* c, game_data* data) {
	c->text_button.active_colour = c->text_button.hovering ? COLOR_YELLOW : COLOR_BEIGE;

	if (CheckCollisionPointRec(data->virt_mouse, c->text_button.data)) {
		if (!c->text_button.hovering && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) return;

		c->text_button.hovering = true;
	} else {
		if (c->text_button.hovering) {
			c->text_button.hovering = false;
		}
	}

	if (c->text_button.hovering && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		c->text_button.holding = true;
	}

	if (c->text_button.holding && c->text_button.hovering && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		c->text_button.holding = false;

		if (c->text_button.on_click != NULL) c->text_button.on_click(c, data);
	}
}

void text_button_draw(component* c, game_data* data) {
	DrawText(c->text_button.text, c->text_button.position.x, c->text_button.position.y, 10, c->text_button.active_colour);
	//DrawRectangleLinesEx(c->text_button.data, 1, COLOR_RED);
}

component* text_button_create(const char* text, Vector2 position, void (*on_click)(struct component*, game_data*)) {
	component* text_btn = component_create(TYPE_TEXT_BUTTON, text_button_update, text_button_draw, NULL);
	text_btn->text_button.holding = false;
	text_btn->text_button.hovering = false;

	text_btn->text_button.active_colour = WHITE;
	text_btn->text_button.text = text;
	text_btn->text_button.position = position;

	text_btn->text_button.on_click = on_click;

	Vector2 measurements = MeasureTextEx(GetFontDefault(), text, 10, 1);
	text_btn->text_button.data = (Rectangle) {
		position.x,
		position.y,
		measurements.x,
		measurements.y
	};

	return text_btn;
}
