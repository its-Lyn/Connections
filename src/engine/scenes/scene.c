#include "engine/entity.h"
#include "engine/scenes/scene.h"
#include "engine/scenes/scene_utilities.h"

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

	// if scene changed, update main scene and delete current scene
	if (s->goto_scene == NULL) return;
	data->main_scene = s->goto_scene;
	scene_destroy(s, data);
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

