#include "engine/component.h"
#include "engine/entity.h"

#include "engine/scenes/scene_utilities.h"

#include "game/components/bullet_mover.h"

#include <raymath.h>

static void bullet_mover_update(component* c, game_data* data) {
	// FUck me
	// We do not have an init function
	if (c->bullet_mover.direction.x == -9999)
		c->bullet_mover.direction = Vector2Normalize(Vector2Subtract(c->bullet_mover.target_position, c->owner->pos));

	Vector2 target = (Vector2) {
		c->bullet_mover.direction.x * c->bullet_mover.speed * GetFrameTime(),
		c->bullet_mover.direction.y * c->bullet_mover.speed * GetFrameTime()
	};

	c->owner->vel = Vector2MoveTowards(c->owner->vel, target, c->bullet_mover.speed * GetFrameTime());
	c->owner->pos = Vector2Add(c->owner->pos, c->owner->vel);

	// We are off screen
	if (c->owner->pos.x > data->game_size.x || c->owner->pos.y > data->game_size.y) {
		// I can't figure this one out
		// Who knew joining a jam with a language I don't know is a bad idea?
		// scene_remove_entity(data->main_scene, c->owner);
	}
}

component* bullet_mover_create(Vector2 target_position, float speed) {
	component* bullet_mover = component_create(TYPE_BULLET_MOVER, bullet_mover_update, NULL, NULL);
	bullet_mover->bullet_mover.speed = speed;
	bullet_mover->bullet_mover.target_position = target_position;
	bullet_mover->bullet_mover.direction = (Vector2) { -9999, -9999 };

	return bullet_mover;
}
