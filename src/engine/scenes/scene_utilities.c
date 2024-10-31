#include "engine/entity.h"
#include "engine/scenes/scene_utilities.h"

#include "game/game_data.h"

#include <stdlib.h>

void scene_change(scene* current_scene, scene* new_scene) {
	current_scene->goto_scene = new_scene;
}

scene* scene_create(void (*process)(scene* s, game_data* data), void (*render)(scene* s, game_data* data), void (*pre_render)(scene* s, game_data* data)) {
	scene* new_scene = (scene*)malloc(sizeof(scene));

	new_scene->entities = NULL;
	new_scene->colliders = NULL;
	new_scene->process = process;
	new_scene->render  = render;
	new_scene->pre_render = pre_render;
	new_scene->goto_scene = NULL;

	return new_scene;
}

void scene_destroy(scene* s, game_data* data) {
	// destroying entities
	linked_list* elem = s->entities;
	while (elem != NULL) {
		linked_list* next = elem->next; // we need to keep track because entity_destroy frees the element

		entity* e = elem->data;
		entity_destroy(e, data);

		elem = next;
	}

	// freeing the scene itself
	free(s);
}


void scene_add_entity(scene* s, entity* e) {
	e->owner = s;
	s->entities = e->scene_elem = linked_list_insert(s->entities, e);
}

void scene_remove_entity(scene* s, entity* e) {
	if (e->owner != s || e->scene_elem == NULL) return;
	s->entities = linked_list_delete_element(s->entities, e->scene_elem);
}

void scene_add_collider(scene* s, component* collider) {
	s->colliders = collider->collider.list_elem = linked_list_insert(s->colliders, collider);
}

void scene_remove_collider(scene* s, component* collider) {
	if (collider->collider.list_elem == NULL) return;
	s->colliders = linked_list_delete_element(s->colliders, collider->collider.list_elem);
}
