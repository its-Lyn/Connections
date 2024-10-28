#include "engine/scenes/scene.h"

#include <stdlib.h>

void scene_update_entities(scene* s, game_data* data)
{
	// TODO: Update each entity.

	if (s->process != NULL)
		s->process(s, data);
}

void scene_draw_entities(scene* s, game_data* data)
{
	// TODO: Render each entity.

	if (s->render != NULL)
		s->render(s, data);
}

