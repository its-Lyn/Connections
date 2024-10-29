#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"

#define PLAYER_SPEED 200

static void update(component* c, game_data* data) {
	float x = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
	float y = (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  - (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
	Vector2 dir = Vector2Normalize((Vector2){x, y});
	c->owner->vel = Vector2Scale(dir, PLAYER_SPEED);
}

component* player_move_create() {
	return component_create(TYPE_PLAYER_MOVE, update, NULL, NULL);
}

