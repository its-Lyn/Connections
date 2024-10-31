#include <stdbool.h>

#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene.h"
#include "engine/scenes/scene_utilities.h"

#include "game/layers.h"
#include "game/colors.h"

void on_lifetime_timeout(component* timer, game_data* data) {
	scene_queue_remove(data->main_scene, timer->owner);
}

entity* slash_create(scene* s, Vector2 position) {
	entity* e = entity_create(position, 0.0f);

	entity_add_component(e, rectangle_create((Vector2){16, 16}, COLOR_BEIGE));
	entity_add_component(e, collider_create(s, (Vector2){8, 8}, 8, LAYER_SLASH, 0, NULL));
	entity_add_component(e, timer_engine_create(0.8f, true, true, on_lifetime_timeout));

	return e;
}

