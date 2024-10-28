#include "engine/scenes/scene_utilities.h"

#include <stdlib.h>

void scene_change(scene* current_scene, scene* new_scene)
{
	// Free old data.
	free(current_scene);
	current_scene = new_scene;
}

scene* scene_create(void (*process)(scene* s, game_data* data), void (*render)(scene *s, game_data* data))
{
	scene* new_scene = (scene*)malloc(sizeof(scene));

	new_scene->process = process;
	new_scene->render  = render;

	return new_scene;
}
