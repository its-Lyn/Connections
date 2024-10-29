#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"

#define PLAYER_WIDTH  8
#define PLAYER_HEIGHT 8

entity* player_create(Vector2 position) {
	entity* player = entity_create(position, 100);
	entity_add_component(player, player_move_create());
	entity_add_component(player, rectangle_create((Vector2){PLAYER_WIDTH, PLAYER_HEIGHT}, PURPLE));
	return player;
}

