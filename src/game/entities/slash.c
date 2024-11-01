#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/entity.h"
#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/game_data.h"
#include "game/layers.h"
#include "game/colors.h"
#include "game/entities/player.h"

void on_lifetime_timeout(component* timer, game_data* data) {
	scene_queue_remove(data->main_scene, timer->owner);
}

entity* slash_create(game_data* data, Vector2 position, Vector2 dir) {
	entity* e = entity_create(position, SLASH_START_SPEED);

	float rot = -Vector2Angle(dir, (Vector2){0, -1}) * RAD2DEG; // WHY TF IS DRAWTEXTUREPRO ANGLE IN DEGREES AND BACKWARDS

	entity_add_component(e, sprite_create("assets/slash.png", (Vector2){0, 0}, WHITE, false, rot, (Vector2){12, 12}));
	entity_add_component(e, collider_create(data->main_scene, (Vector2){0, 0}, 12, LAYER_SLASH, 0, NULL));
	entity_add_component(e, timer_engine_create(SLASH_LIFETIME, true, true, on_lifetime_timeout));

	entity_add_component(e, bullet_mover_create(dir));

	entity_add_component(e, speed_diminish_create(SLASH_DEACCEL));

	return e;
}

