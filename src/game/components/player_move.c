#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#include "engine/component.h"
#include "engine/entity.h"

#include "game/game_data.h"
#include "game/entities/player.h"

static void update(component* c, game_data* data) {
	c->owner->pos.x = Clamp(c->owner->pos.x, 0, data->game_size.x - 8);
	c->owner->pos.y = Clamp(c->owner->pos.y, 0, data->game_size.y - 8);

	float x = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
	float y = (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  - (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));
	Vector2 dir = Vector2Normalize((Vector2){x, y});

	animated_spritesheet_set_enabled(c->player_move.sprite, !Vector2Equals(dir, Vector2Zero()));

	// update sprite direction
	c->player_move.sprite->animated_spritesheet.fliph = (dir.x > 0.0f) || (dir.x == 0.0f && c->player_move.sprite->sprite.fliph);

	Vector2 goal_vel = Vector2Scale(dir, c->owner->speed);

	float accel = 0;
	if (Vector2Equals(dir, (Vector2){0, 0})) {
		// use friction if not pressing anything
		accel = PLAYER_FRICTION;
	} else {
		// accelerate faster if moving against current direction (braking)
		accel = Vector2DotProduct(dir, c->owner->vel) > 0.0f? PLAYER_ACCEL : PLAYER_ACCEL * 2.0f;
	}

	c->owner->vel = Vector2MoveTowards(c->owner->vel, goal_vel, accel * GetFrameTime());
}

component* player_move_create(entity* player) {
	component* c = component_create(TYPE_PLAYER_MOVE, update, NULL, NULL);

	c->player_move.sprite = entity_get_component(player, TYPE_ANIMATED_SPRITESHEET);

	return c;
}

