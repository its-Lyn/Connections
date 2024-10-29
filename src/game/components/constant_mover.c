#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"

#include "game/components/constant_mover.h"

static void update(component* c, game_data* data) {
	//c->owner->vel = Vector2Scale(c->constant_mover.dir, c->constant_mover.speed);
	c->owner->pos = Vector2MoveTowards(c->owner->pos, c->constant_mover.locked->pos, c->constant_mover.speed * GetFrameTime());
}

component* constant_mover_create(float speed, entity* locked) {
	component* c = component_create(TYPE_CONSTANT_MOVER, update, NULL, NULL);
	c->constant_mover.speed = speed;
	c->constant_mover.locked = locked;

	return c;
}

