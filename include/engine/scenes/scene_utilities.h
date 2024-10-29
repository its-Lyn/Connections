#pragma once

#include "engine/entity.h"
#include "engine/scenes/scene.h"
#include "game/game_data.h"
#include "engine/component.h"

void scene_change(scene* current_scene, scene* new_scene, game_data* data);
scene* scene_create(void (*process)(scene* s, game_data* data), void (*render)(scene *s, game_data* data));
void scene_destroy(scene* s, game_data* data);
void scene_add_entity(scene* s, struct entity* e);
void scene_remove_entity(scene* s, struct entity* e);

void scene_add_collider(scene* s, component* collider);
void scene_remove_collider(scene* s, component* collider);
