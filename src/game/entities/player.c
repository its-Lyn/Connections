#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "game/entities/player.h"

#include "game/components/animated_spritesheet.h"

#include "game/layers.h"

entity* player_create(scene* s, game_data* data, Vector2 position) {
	entity* player = entity_create(position, PLAYER_MAX_SPEED);

	component* animated_spritesheet = create_animated_spritesheet(0.2f, (Vector2){2, 1}, (Vector2){-1, 0}, false, LoadTexture("assets/knight.png"));
	animated_spritesheet->animated_spritesheet.enabled = true;
	entity_add_component(player,animated_spritesheet);

	entity_add_component(player, player_move_create(player));

	component* tugger = tugger_create(player);
	entity_add_component(player, tugger);
	data->tugger = tugger;

	return player;
}

