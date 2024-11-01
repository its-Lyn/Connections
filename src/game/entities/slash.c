#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/game_data.h"
#include "game/layers.h"
#include "game/colors.h"

void on_lifetime_timeout(component* timer, game_data* data) {
	scene_queue_remove(data->main_scene, timer->owner);
}

entity* slash_create(game_data* data, Vector2 position) {
	entity* e = entity_create(position, 80.0f);

	entity_add_component(e, sprite_create("assets/slash.png", (Vector2){-7, -9}, WHITE, false));
	entity_add_component(e, collider_create(data->main_scene, (Vector2){0, 0}, 7, LAYER_SLASH, 0, NULL));
	entity_add_component(e, timer_engine_create(0.3f, true, true, on_lifetime_timeout));

	Vector2 dir = Vector2Normalize(Vector2Subtract(data->virt_mouse, position));
	entity_add_component(e, bullet_mover_create(dir));

	return e;
}

