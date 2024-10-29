#include "engine/entity.h"
#include "engine/scenes/scene.h"

#include <stdlib.h>

void scene_update_entities(scene* s, game_data* data)
{
	// updating scene entities
	for (linked_list* elem = s->entities; elem != NULL; elem = elem->next) {
		entity* e = elem->data;
		entity_update(e, data);
	}

	// doing the scene update itself
	if (s->process != NULL)
		s->process(s, data);
}

void scene_draw_entities(scene* s, game_data* data)
{
	// drawing scene entities
	for (linked_list* elem = s->entities; elem != NULL; elem = elem->next) {
		entity* e = elem->data;
		entity_draw(e, data);
	}

	// doing the scene drawing itself
	if (s->render != NULL)
		s->render(s, data);
}

