#include <stdlib.h>

#include "engine/component.h"

component* component_create(component_type type, void (*update)(component*, game_data*), void (*draw)(component*, game_data*), void (*destroy)(component*, game_data*)) {
	component* c = calloc(1, sizeof(component));

	c->type = type;
	c->update = update;
	c->draw = draw;
	c->destroy = destroy;

	return c;
}

void component_destroy(component* c, game_data* data) {
	if (c->destroy != NULL) c->destroy(c, data);
	free(c);
}

