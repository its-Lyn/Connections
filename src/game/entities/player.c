#include <raylib.h>

#include "engine/entity.h"
#include "engine/component.h"

#include "game/entities/player.h"

#include "game/components/animated_spritesheet.h"

#include "game/layers.h"

entity* player_create(scene* s, game_data* data, Vector2 position) {
	entity* player = entity_create(position, PLAYER_MAX_SPEED);

	component* animated_spritesheet = create_animated_spritesheet(0.2f, (Vector2){2, 1}, (Vector2){0, -2}, false, LoadTexture("assets/knight.png"), 0.0f, (Vector2){0, 0});
	animated_spritesheet->animated_spritesheet.enabled = true;
	entity_add_component(player, animated_spritesheet);

	entity_add_component(player, collider_create(s, (Vector2){4, 4}, 6, LAYER_PLAYER, 0, NULL));

	entity_add_component(player, player_move_create(player));

	component* tugger = tugger_create(player);
	entity_add_component(player, tugger);
	data->tugger = tugger;

	entity_add_component(player, player_attack_create(player));

	return player;
}

