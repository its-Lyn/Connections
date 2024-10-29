#pragma once

#include <raylib.h>

#include "engine/component.h"

#include "game/game_data.h"

typedef struct {
	int layer, mask;

	Vector2 offset;
	float radius;

	void (*on_collide)(game_data* data);

	scene* owner_scene;
	linked_list* list_elem;
} collider_data;

struct component* collider_create(scene* s, Vector2 offset, float radius, int layer, int mask, void (*on_collide)(game_data* data));
