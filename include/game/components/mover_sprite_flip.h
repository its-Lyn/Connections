#pragma once

#include "engine/component.h"
#include "engine/entity.h"

#include "game/game_data.h"

typedef struct {
	struct component* mover;
	struct component* sprite;
} mover_sprite_flip_data;

struct component* mover_sprite_flip_create(struct entity* e);

