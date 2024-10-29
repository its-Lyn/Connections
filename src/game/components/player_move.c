#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"

static void update(component* c, game_data* data) {
	float x = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
	float y = (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  - (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
	Vector2 dir = Vector2Normalize((Vector2){x, y});
	c->owner->vel = Vector2Scale(dir, c->player_move.speed);
}

component* player_move_create(float speed) {
	component* c = component_create(TYPE_PLAYER_MOVE, update, NULL, NULL);
	c->player_move.speed = speed;
	return c;
}

