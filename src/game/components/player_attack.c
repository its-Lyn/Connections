#include <raylib.h>

#include "engine/component.h"
#include "engine/scenes/scene_utilities.h"

#include "game/game_data.h"
#include "game/entities/slash.h"

static void update(component* c, game_data* data) {
	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;
	scene_add_entity(data->main_scene, slash_create(data->main_scene, data->player->pos));
}

component* player_attack_create() {
	return component_create(TYPE_PLAYER_ATTACK, update, NULL, NULL);
}

