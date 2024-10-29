#pragma once

#include <raylib.h>

struct entity;

#include "engine/utilities/linked_list.h"
#include "engine/scenes/scene.h"
#include "engine/component.h"
#include "game/game_data.h"

typedef struct entity {
	scene* owner;
	linked_list* scene_elem; // element in the owner scene's entity list

	Vector2 pos, vel;
	linked_list* components;
} entity;

entity* entity_create(Vector2 position);
void entity_destroy(entity* e, game_data* data);
void entity_add_component(entity* e, struct component* c);
struct component* entity_get_component(entity* e, component_type type);
void entity_remove_component(entity* e, struct component* c);
void entity_update(entity* e, game_data* data);
void entity_draw(entity* e, game_data* data);

