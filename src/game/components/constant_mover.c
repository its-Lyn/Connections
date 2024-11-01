// this is no longer a constant mover its actually just a follower lol

#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"

#include "game/components/constant_mover.h"

static void update(component* c, game_data* data) {
	Vector2 dir = Vector2Normalize(Vector2Subtract(c->constant_mover.locked->pos, c->owner->pos));
	Vector2 goal_vel = Vector2Scale(dir, c->owner->speed);
	c->owner->vel = Vector2MoveTowards(c->owner->vel, goal_vel, c->constant_mover.accel * GetFrameTime());
}

component* constant_mover_create(float accel, entity* locked) {
	component* c = component_create(TYPE_CONSTANT_MOVER, update, NULL, NULL);
	c->constant_mover.accel = accel;
	c->constant_mover.locked = locked;

	return c;
}

