#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "game/entities/player.h"

#include "game/layers.h"

entity* player_create(scene* s, Vector2 position) {
	entity* player = entity_create(position, PLAYER_MAX_SPEED);
	entity_add_component(player, player_move_create());
	entity_add_component(player, rectangle_create((Vector2){PLAYER_WIDTH, PLAYER_HEIGHT}, PURPLE));

	component* player_collider = collider_create(s, (Vector2) {4, 4}, 5, LAYER_PLAYER, LAYER_PRINCESS, NULL);
	entity_add_component(player, player_collider);

	return player;
}

