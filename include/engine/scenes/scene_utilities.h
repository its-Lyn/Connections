#pragma once

#include "engine/scenes/scene.h"
#include "game/game_data.h"

void scene_change(scene* current_scene, scene* new_scene);
scene* scene_create(void (*process)(scene* s, game_data* data), void (*render)(scene *s, game_data* data));
