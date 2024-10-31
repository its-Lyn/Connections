#include "engine/component.h"
#include "game/components/timer.h"

#include <raylib.h>

void timer_update(component* c, game_data* data) {
	if (c->timer.enabled) {
		c->timer.timer += GetFrameTime();
		if (c->timer.timer >= c->timer.timeout) {
			c->timer.timer = 0;
			if (c->timer.one_shot)
				c->timer.enabled = false;

			if (c->timer.on_timeout != NULL) c->timer.on_timeout(c, data);
		}
	}
}

// We call it timer engine create because it conflicts with stdlib.
component* timer_engine_create(float timeout, bool enabled, bool one_shot, void (*on_timeout)(component*, game_data*)) {
	component* c = component_create(TYPE_TIMER, timer_update, NULL, NULL);
	c->timer.enabled = enabled;
	c->timer.timeout = timeout;
	c->timer.on_timeout = on_timeout;
	c->timer.one_shot = one_shot;
	c->timer.timer = 0;

	return c;
}
