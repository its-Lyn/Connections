#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"

#include "game/game_data.h"

static void update(component* c, game_data* data) {
	Vector2 diff = Vector2Subtract(c->mover_sprite_flip.mover->constant_mover.locked->pos, c->owner->pos);
	Vector2 dir = Vector2Normalize(diff);
	component* sprite = c->mover_sprite_flip.sprite;
	sprite->sprite.fliph = (dir.x > 0) || (dir.x == 0 && sprite->sprite.fliph);
}

component* mover_sprite_flip_create(entity* e) {
	component* c = component_create(TYPE_MOVER_SPRITE_FLIP, update, NULL, NULL);

	c->mover_sprite_flip.mover  = entity_get_component(e, TYPE_CONSTANT_MOVER);
	c->mover_sprite_flip.sprite = entity_get_component(e, TYPE_SPRITE);

	return c;
}

