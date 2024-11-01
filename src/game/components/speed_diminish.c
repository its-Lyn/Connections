#include <raylib.h>

#include "engine/component.h"

#include "game/game_data.h"

static void update(component* c, game_data* data) {
	c->owner->speed -= c->speed_diminish.deaccel * GetFrameTime();
	if (c->owner->speed < 0) c->owner->speed = 0;
}

component* speed_diminish_create(float deaccel) {
	component* c = component_create(TYPE_SPEED_DIMINISH, update, NULL, NULL);

	c->speed_diminish.deaccel = deaccel;

	return c;
}

