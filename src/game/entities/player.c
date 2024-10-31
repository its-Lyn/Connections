#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "game/entities/player.h"

#include "game/layers.h"

entity* player_create(scene* s, game_data* data, Vector2 position) {
	entity* player = entity_create(position, PLAYER_MAX_SPEED);
	entity_add_component(player, sprite_create("assets/knight1.png", (Vector2){0, -2}, WHITE, true));
	entity_add_component(player, player_move_create(player));

	component* tugger = tugger_create(player);
	entity_add_component(player, tugger);
	data->tugger = tugger;

	return player;
}

