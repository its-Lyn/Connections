#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/game_data.h"
#include "game/layers.h"

static void on_collide(scene* s, component* self, component* other, game_data* data) {
	if (data->princess_lives >= 3) return;
	data->princess_lives += 1;
	scene_queue_remove(s, self->owner);
}

entity* crown_pickup_create(scene* s, Vector2 position) {
	entity* e = entity_create(position, 0.0f);

	component* anim = create_animated_spritesheet(0.1f, (Vector2){4, 1}, (Vector2){0, 0}, false, LoadTexture("assets/crown.png"), 0.0f, (Vector2){0, 0});
	anim->animated_spritesheet.enabled = true;
	entity_add_component(e, anim);

	entity_add_component(e, collider_create(s, (Vector2){4.0f, 4.0f}, 7.0f, 0, LAYER_PLAYER | LAYER_PRINCESS, on_collide));

	return e;
}

