#pragma once

#include "engine/scenes/scene.h"
#include "engine/entity.h"
#include "engine/component.h"
#include "engine/utilities/linked_list.h"

typedef struct {
	float bullet_timer;
	float buller_timeout;

	struct entity* princess;
	struct scene* handler_scene;
} bullet_handler_data;

struct component* bullet_handler_create(float bullet_timeout, struct scene* handler_scene, struct entity* princess);
