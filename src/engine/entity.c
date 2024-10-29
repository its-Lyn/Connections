#include <stdlib.h>

#include "engine/entity.h"
#include "game/game_data.h"

entity* entity_create(Vector2 position) {
	entity* new_entity = malloc(sizeof(entity));
	
	new_entity->pos = position;
	new_entity->vel = (Vector2){0, 0};
	new_entity->components = NULL;

	return new_entity;
}

void entity_destroy(entity* e, game_data* data) {
	linked_list* elem = e->components;
	while (elem != NULL) {
		linked_list* next = elem->next;

		component* c = elem->data;
		component_destroy(c, data);
		free(elem);

		elem = next;
	}

	free(e);
}

void entity_add_component(entity* e, component* c) {
	c->owner = e;
	e->components = linked_list_insert(e->components, c);
}

component* entity_get_component(entity* e, component_type type) {
	for (linked_list* elem = e->components; elem != NULL; elem = elem->next) {
		component* c = elem->data;
		if (c->type == type) return c;
	}

	return NULL;
}

void entity_update(entity* e, game_data* data) {
	for (linked_list* elem = e->components; elem != NULL; elem = elem->next) {
		component* c = elem->data;
		c->update(c, data);
	}
}

void entity_draw(entity* e, game_data* data) {
	for (linked_list* elem = e->components; elem != NULL; elem = elem->next) {
		component* c = elem->data;
		c->draw(c, data);
	}
}

