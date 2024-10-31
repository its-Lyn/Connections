#pragma once

// ???
struct scene;

#include "engine/utilities/linked_list.h"
#include "game/game_data.h"

typedef struct scene {
	linked_list* entities;
	linked_list* colliders;

	void (*process)(struct scene*, struct game_data*);
	void (*render)(struct scene*, struct game_data*);
	void (*pre_render)(struct scene*, struct game_data*);

	struct scene* goto_scene;
} scene;

void scene_update_entities(scene* s, struct game_data* data);
void scene_draw_entities(scene* s, struct game_data* data);
