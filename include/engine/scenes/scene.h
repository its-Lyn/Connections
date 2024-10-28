#pragma once

// ???
struct scene;

#include "game/game_data.h"

typedef struct scene {
	// entity[] entities;

	void (*process)(struct scene*, struct game_data*);
	void (*render)(struct scene*, struct game_data*);
} scene;

void scene_update_entities(scene* s, struct game_data* data);
void scene_draw_entities(scene* s, struct game_data* data);
