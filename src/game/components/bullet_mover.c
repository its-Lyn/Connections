#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"
#include "engine/scenes/scene_utilities.h"

#include "game/components/bullet_mover.h"
#include "game/entities/enemies/enemy_shoot.h"

static void bullet_mover_update(component* c, game_data* data) {
	c->owner->vel = Vector2Scale(c->bullet_mover.direction, c->owner->speed);

	if (c->owner->pos.x > data->game_size.x || c->owner->pos.x + BULLET_WIDTH  < 0
	 || c->owner->pos.y > data->game_size.y || c->owner->pos.y + BULLET_HEIGHT < 0) {
		// We are off screen, delete projectile
		scene_queue_remove(c->owner->owner, c->owner);
	}
}

component* bullet_mover_create(Vector2 direction) {
	component* c = component_create(TYPE_BULLET_MOVER, bullet_mover_update, NULL, NULL);
	
	c->bullet_mover.direction = direction;

	return c;
}
