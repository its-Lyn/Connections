#pragma once

// ???
struct scene;

#include "engine/utilities/linked_list.h"
#include "game/game_data.h"

typedef struct scene {
	linked_list* entities;

	void (*process)(struct scene*, struct game_data*);
	void (*render)(struct scene*, struct game_data*);
} scene;

void scene_update_entities(scene* s, struct game_data* data);
void scene_draw_entities(scene* s, struct game_data* data);
