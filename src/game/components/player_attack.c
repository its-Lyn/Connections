#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"
#include "engine/scenes/scene_utilities.h"

#include "game/game_data.h"
#include "game/entities/slash.h"
#include "game/entities/player.h"

static void update(component* c, game_data* data) {
	if (c->player_attack.cooldown->timer.enabled) return;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 pos = Vector2Add(data->player->pos, (Vector2){PLAYER_WIDTH/2, PLAYER_HEIGHT/2});
		scene_add_entity(data->main_scene, slash_create(data, pos, Vector2Normalize(Vector2Subtract(data->virt_mouse, pos))));

		c->player_attack.cooldown->timer.enabled = true;
		c->player_attack.cooldown->timer.timer = 0;
	} else if (IsKeyPressed(KEY_X)) {
		Vector2 pos = Vector2Add(data->player->pos, (Vector2){PLAYER_WIDTH/2, PLAYER_HEIGHT/2});

		// get input dir
		float x = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
		float y = (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  - (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
		Vector2 dir = Vector2Normalize((Vector2){x, y});

		// only update direction if its not 0 (to attack in last pressed direction)
		if (!Vector2Equals(dir, (Vector2){0, 0})) c->player_attack.dir = dir;

		scene_add_entity(data->main_scene, slash_create(data, pos, c->player_attack.dir));

		c->player_attack.cooldown->timer.enabled = true;
		c->player_attack.cooldown->timer.timer = 0;
	}
}

component* player_attack_create(entity* owner) {
	component* c = component_create(TYPE_PLAYER_ATTACK, update, NULL, NULL);

	component* cooldown = timer_engine_create(SLASH_COOLDOWN, false, true, NULL);
	entity_add_component(owner, cooldown);

	c->player_attack.dir = (Vector2){0, -1};
	c->player_attack.cooldown = cooldown;

	return c;
}

