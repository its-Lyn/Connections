#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/scenes/scene_utilities.h"

#include "game/game_data.h"

entity* entity_create(Vector2 position, float speed) {
	entity* new_entity = malloc(sizeof(entity));

	new_entity->owner = NULL;
	new_entity->scene_elem = NULL;

	new_entity->pos = position;
	new_entity->vel = (Vector2){0, 0};
	new_entity->speed = speed;
	new_entity->components = NULL;
	new_entity->queued_for_delete = false;
	new_entity->handle_while_paused = false;

	return new_entity;
}

void entity_destroy(entity* e, game_data* data) {
	// destroying components and freeing each list element
	linked_list* elem = e->components;
	while (elem != NULL) {
		linked_list* next = elem->next;

		component* c = elem->data;
		component_destroy(c, data);
		free(elem);

		elem = next;
	}

	// removing this entity from it's owner scene's entity list
	if (e->owner != NULL) {
		scene_remove_entity(e->owner, e);
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
	// moving entity
	e->pos = Vector2Add(e->pos, Vector2Scale(e->vel, GetFrameTime()));

	// updating components
	for (linked_list* elem = e->components; elem != NULL; elem = elem->next) {
		component* c = elem->data;
		if (c->update != NULL) c->update(c, data);
	}
}

void entity_draw(entity* e, game_data* data) {
	for (linked_list* elem = e->components; elem != NULL; elem = elem->next) {
		component* c = elem->data;
		if (c->draw != NULL) c->draw(c, data);
	}
}

