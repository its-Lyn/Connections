#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"

#include "engine/scenes/scene_utilities.h"

#include "game/components/collider.h"

void collider_update(component* c, game_data* data) {

}

void collider_draw(component* c, game_data* data) {
	DrawCircleLines(c->owner->pos.x + c->collider.offset.x, c->owner->pos.y + c->collider.offset.y, c->collider.radius, RED);
}

void collider_destroy(component* c, game_data* data) {
	scene_remove_collider(c->collider.owner_scene, c);
}

component* collider_create(scene* s, Vector2 offset, float radius, int layer, int mask, void (*on_collide)(game_data* data)) {
	component* c = component_create(TYPE_COLLIDER, collider_update, collider_draw, collider_destroy);
	c->collider.offset = offset;
	c->collider.radius = radius;
	c->collider.on_collide = on_collide;
	c->collider.list_elem = NULL;

	c->collider.layer = layer;
	c->collider.mask = mask;

	c->collider.owner_scene = s;

	scene_add_collider(s, c);

	return c;
}