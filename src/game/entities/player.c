#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "game/entities/player.h"

entity* player_create(Vector2 position) {
	entity* player = entity_create(position, PLAYER_MAX_SPEED);
	entity_add_component(player, player_move_create());
	entity_add_component(player, rectangle_create((Vector2){PLAYER_WIDTH, PLAYER_HEIGHT}, PURPLE));
	return player;
}

