#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#include "game/game_data.h"

#include "engine/component.h"
#include "engine/entity.h"

static void update(component* c, game_data* data) {
	if (data->princess_state == STATE_AGITATED) {
		c->owner->vel = Vector2Zero();
		return;
	}

	float x = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
	float y = (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  - (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
	Vector2 dir = Vector2Normalize((Vector2){x, y});
	c->owner->vel = Vector2Scale(dir, c->owner->speed);
}

component* player_move_create() {
	component* c = component_create(TYPE_PLAYER_MOVE, update, NULL, NULL);
	return c;
}

