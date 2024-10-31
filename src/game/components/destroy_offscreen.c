#include <raylib.h>

#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/game_data.h"

static void update(component* c, game_data* data) {
	if (c->owner->pos.x > data->game_size.x || c->owner->pos.x + c->destroy_offscreen.size.x < 0
	 || c->owner->pos.y > data->game_size.y || c->owner->pos.y + c->destroy_offscreen.size.y < 0) {
		// We are off screen, delete projectile
		scene_queue_remove(c->owner->owner, c->owner);
	}
}

component* destroy_offscreen_create(Vector2 size) {
	component* c = component_create(TYPE_DESTROY_OFFSCREEN, update, NULL, NULL);

	c->destroy_offscreen.size = size;

	return c;
}

