#include "engine/entity.h"
#include "engine/scenes/scene.h"
#include "engine/scenes/scene_utilities.h"

#include <stdlib.h>
void scene_update_entities(scene* s, game_data* data)
{
	// Idk where else to handle this lmao
	if (data->can_pause && (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P))) {
		data->is_paused = !data->is_paused;
	}

	if (data->is_paused) {
		for (linked_list* elem = s->entities; elem != NULL; elem = elem->next) {
			entity* e = elem->data;
			if (e->handle_while_paused) entity_update(e, data);
		}

		return;
	}

	// updating scene entities
	for (linked_list* elem = s->entities; elem != NULL; elem = elem->next) {
		entity* e = elem->data;
		if (!e->handle_while_paused) entity_update(e, data);
	}

	// doing the scene update itself
	if (s->process != NULL)
		s->process(s, data);

	// Remove all the entities in queue
	linked_list* elem = s->delete_queue;
	while (elem != NULL) {
		linked_list* next_elem = elem->next;

		entity* e = elem->data;
		entity_destroy(e, data);
		free(elem);

		elem = next_elem;
	}
	s->delete_queue = NULL;

	// if scene changed, update main scene and delete current scene
	if (s->goto_scene != NULL) {
		data->main_scene = s->goto_scene;
		scene_destroy(s, data);
		return;
	}
}

void scene_draw_entities(scene* s, game_data* data)
{
	// scene pre-draw for sprites meant to be below everything else
	if (s->pre_render != NULL) {
		s->pre_render(s, data);
	}

	// drawing scene entities
	for (linked_list* elem = s->entities; elem != NULL; elem = elem->next) {
		entity* e = elem->data;
		if (!e->handle_while_paused) entity_draw(e, data);
	}

	// doing the scene drawing itself
	if (s->render != NULL)
		s->render(s, data);

	if (data->is_paused) {
		for (linked_list* elem = s->entities; elem != NULL; elem = elem->next) {
			entity* e = elem->data;
			if (e->handle_while_paused) entity_draw(e, data);
		}
	}
}

