#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"

#include "game/components/constant_mover.h"

static void update(component* c, game_data* data) {
	c->owner->vel = Vector2Scale(c->constant_mover.dir, c->constant_mover.speed);
}

component* constant_mover_create(Vector2 direction, float speed) {
	component* c = component_create(TYPE_CONSTANT_MOVER, update, NULL, NULL);

	c->constant_mover.dir = Vector2Normalize(direction);
	c->constant_mover.speed = speed;

	return c;
}

